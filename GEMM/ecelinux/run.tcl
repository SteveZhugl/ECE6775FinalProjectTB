#=============================================================================
# run.tcl 
#=============================================================================
# @brief: A Tcl script for synthesizing the GEMM design.
#
#
# Useful simulation & synthesis stats are consolidated into ./result/result.csv

#------------------------------------------------------
# Remove old result file
#------------------------------------------------------
set filename "gemm_result.csv"
file delete -force "./result/${filename}"

# Define the bitwidth macros from CFLAGs
# set CFLAGS "-DK_CONST=${K}"

# Project name
set hls_prj gemm_proj.prj

# Open/reset the project
open_project ${hls_prj} -reset
# Top function of the design 
set_top dut

# Add design and testbench files
add_files gemm.cpp -cflags "-std=c++11"
add_files -tb gemm_test.cpp -cflags "-std=c++11"
add_files -tb data

open_solution "solution1"
# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10


# Simulate the C++ design
csim_design -O
# Synthesize the design
csynth_design
# Co-simulate the design
#cosim_design

#---------------------------------------------
# Collect & dump out results from HLS reports
#---------------------------------------------
set argv [list $filename $hls_prj]
set argc 2
# source "./script/collect_result.tcl"
exit
