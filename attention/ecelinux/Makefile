#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the attention program
#
# @desc: 1. Enter "make all" to make attention-sw and attention-hw
#        2. Enter "make attention-sw" to compile & execute the attention program
#        3. Enter "make attention-hw" to synthesize attention using run.tcl
#        4. Enter "make clean" to clean up the directory (before submission)

# Extract Vivado HLS include path
XILINX_VIVADO?=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2
XIL_HLS=source $(XILINX_VIVADO)/settings64.sh; vivado_hls
VHLS_INC=$(XILINX_VIVADO)/include
# Specify compilation flags
CFLAGS=-g -I${VHLS_INC} -DHLS_NO_XIL_FPO_LIB -std=c++11 

# SW_RESULTS=$(result/attention_sw_result.txt)

.PHONY: all clean attention-sw attention-hw

# Compile & run attention implementation
all: attention-sw attention-hw

attention_tb: attention.cpp attention_test.cpp
#attention_tb: attention_test.cpp
	g++ ${CFLAGS} -DK_CONST=$* $^ -o $@

result/attention_sw_result.txt: attention_tb
	mkdir -p result
	./$< | tee $@

# attention-sw: $(SW_RESULTS)
attention-sw: csim


result/attention_csim.txt: attention_tb
	@echo "Running attention sim..."
	mkdir -p result
	./$< | tee $@

csim: result/attention_csim.txt
	@echo "Result recorded to $<"

result/attention_result.csv: run.tcl attention.cpp attention_test.cpp
	$(XIL_HLS) -f $<

attention-hw: result/attention_result.csv

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf attention_*_tb vivado_hls.log attention_proj.prj result out.dat *~ xillydemo.bit attention_tb
