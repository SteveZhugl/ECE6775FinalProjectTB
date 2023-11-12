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
CFLAGS=-g -I${VHLS_INC} -DHLS_NO_XIL_FPO_LIB -std=c++11 

# SW_RESULTS=$(result/gemm_sw_result.txt)

.PHONY: all clean gemm-sw gemm-hw

# Compile & run gemm implementation
all: gemm-sw gemm-hw

gemm_tb: gemm.cpp gemm_test.cpp
	g++ ${CFLAGS} -DK_CONST=$* $^ -o $@

result/gemm_sw_result.txt: gemm_tb
	mkdir -p result
	./$< | tee $@

# gemm-sw: $(SW_RESULTS)
gemm-sw: csim


result/gemm_csim.txt: gemm_tb
	@echo "Running gemm sim..."
	mkdir -p result
	./$< | tee $@

csim: result/gemm_csim.txt
	@echo "Result recorded to $<"

result/gemm_result.csv: run.tcl gemm.cpp gemm_test.cpp
	$(XIL_HLS) -f $<

gemm-hw: result/gemm_result.csv

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf gemm_*_tb vivado_hls.log gemm_proj.prj result out.dat *~
