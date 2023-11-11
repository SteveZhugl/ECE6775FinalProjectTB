#=============================================================================
# run.tcl 
#=============================================================================
# @brief: A Tcl script for synthesizing the digit recongnition design.
#
# @desc: This script launches a batch of simulation & synthesis runs
# to quickly explore different K parameters.
#
# 1. The user specifies the list of K values.
# 2. Useful simulation & synthesis stats are consolidated into ./result/result.csv

#------------------------------------------------------
# Remove old result file
#------------------------------------------------------
set filename "knn_result.csv"
file delete -force "./result/${filename}"

# Define the bitwidth macros from CFLAGs
set CFLAGS "-DK_CONST=${K}"

# Project name
set hls_prj ${K}-nn.prj

# Open/reset the project
open_project ${hls_prj} -reset
# Top function of the design is "digitrec"
set_top digitrec

# Add design and testbench files
add_files digitrec.cpp -cflags $CFLAGS
add_files -tb digitrec_test.cpp -cflags $CFLAGS
add_files -tb data

open_solution "solution1"
# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10

# Do not inline update_knn and knn_vote functions 
set_directive_inline -off update_knn
set_directive_inline -off knn_vote
### You can add your own directives here ###

# # Loop Unrolling optimizations
set_directive_unroll digitrec/KNN_INIT_LOOP
set_directive_unroll digitrec/TRAIN_LOOP_INNER
set_directive_unroll knn_vote/MIN_DIST_LOOP
set_directive_unroll knn_vote/NEAR_NEIGHBOR_INIT_LOOP
set_directive_unroll knn_vote/KNN_VOTE_VAL_LOOP
# set_directive_unroll knn_vote/KNN_VOTE_ROW_LOOP
# set_directive_unroll knn_vote/KNN_VOTE_NEAR_NEIGHBOR_LOOP
# set_directive_unroll knn_vote/OUT_COUNTER_LOOP
# set_directive_unroll knn_vote/IN_COUNTER_LOOP

# Array Partitioning Optimizations
set_directive_array_partition -type complete digitrec knn_set
# set_directive_array_partition -type complete update_knn min_distances
set_directive_array_partition -type complete knn_vote nearest_neighbors

# Simulate the C++ design
csim_design
# Synthesize the design
csynth_design
# Co-simulate the design
#cosim_design

#---------------------------------------------
# Collect & dump out results from HLS reports
#---------------------------------------------
set argv [list $filename $hls_prj]
set argc 2
source "./script/collect_result.tcl"
}
exit
