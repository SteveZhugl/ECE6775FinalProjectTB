#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the softmax program
#
# @desc: 1. Enter "make all" to make softmax-sw and softmax-hw
#        2. Enter "make softmax-sw" to compile & execute the softmax program
#        3. Enter "make softmax-hw" to synthesize softmax using run.tcl
#        4. Enter "make clean" to clean up the directory (before submission)

# Extract Vivado HLS include path
XILINX_VIVADO?=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2
XIL_HLS=source $(XILINX_VIVADO)/settings64.sh; vivado_hls
VHLS_INC=$(XILINX_VIVADO)/include
# Specify compilation flags
CFLAGS=-g -I${VHLS_INC} -DHLS_NO_XIL_FPO_LIB -std=c++11 

# SW_RESULTS=$(result/softmax_sw_result.txt)

.PHONY: all clean softmax-sw softmax-hw

# Compile & run softmax implementation
all: softmax-sw softmax-hw

softmax_tb: softmax.cpp softmax_test.cpp
	g++ ${CFLAGS} -DK_CONST=$* $^ -o $@

result/softmax_sw_result.txt: softmax_tb
	mkdir -p result
	./$< | tee $@

# softmax-sw: $(SW_RESULTS)
softmax-sw: csim


result/softmax_csim.txt: softmax_tb
	@echo "Running softmax sim..."
	mkdir -p result
	./$< | tee $@

csim: result/softmax_csim.txt
	@echo "Result recorded to $<"

result/softmax_result.csv: run.tcl softmax.cpp softmax_test.cpp
	$(XIL_HLS) -f $<

softmax-hw: result/softmax_result.csv

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf softmax_*_tb vivado_hls.log softmax_proj.prj result out.dat *~
