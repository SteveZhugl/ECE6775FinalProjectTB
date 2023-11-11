#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the gemm program
#
# @desc: 1. Enter "make all" to make gemm-sw and gemm-hw
#        2. Enter "make gemm-sw" to compile & execute the gemm program
#        3. Enter "make gemm-hw" to synthesize gemm using run.tcl
#        4. Enter "make clean" to clean up the directory (before submission)

# Extract Vivado HLS include path
XILINX_VIVADO?=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2
XIL_HLS=source $(XILINX_VIVADO)/settings64.sh; vivado_hls
VHLS_INC=$(XILINX_VIVADO)/include
# Specify compilation flags
CFLAGS=-g -I${VHLS_INC}

K_VALUES=3
# TIP: You can add multiple values of K: just add a space between values like so:
# K_VALUES=1 2 3 4 5

SW_RESULTS=$(patsubst %,result/gemm_%-nn_sw_result.txt,$(K_VALUES))

.PHONY: all clean gemm-sw gemm-hw

# Compile & run gemm implementation
all: gemm-sw gemm-hw

gemm_%-nn_tb: gemm.cpp gemm_test.cpp
	g++ ${CFLAGS} -DK_CONST=$* $^ -o $@

result/gemm_%-nn_sw_result.txt: gemm_%-nn_tb
	mkdir -p result
	./$< | tee $@

gemm-sw: $(SW_RESULTS)

result/knn_result.csv: run.tcl gemm.cpp gemm_test.cpp
	$(XIL_HLS) -f $<

gemm-hw: result/knn_result.csv

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf gemm_*-nn_tb vivado_hls.log *nn.prj result out.dat *~
