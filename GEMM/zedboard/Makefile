#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the gemm program
#
# @desc: 1. "make" or "make sw" runs software execution by default
#        2. "make fpga" invokes the HW accelerator
#        3. "make clean" cleans up the directory


INC_PATH=/usr/include/vivado_hls
CFLAGS = -I${INC_PATH} -DHLS_NO_XIL_FPO_LIB

.PHONY: all sw fpga

all: sw

gemm-arm: gemm.cpp gemm_test.cpp
	@echo "Compiling & executing gemm software program on ARM ..."
	g++ ${CFLAGS} $^ -o $@

result/gemm_arm_sim.txt: gemm-arm
	mkdir -p result
	./$< | tee $@

sw: result/gemm_arm_sim.txt
	@echo "Result saved to $@"

gemm-fpga: host.cpp
	@echo "Compiling host program"
	g++ ${CFLAGS} $^ -o $@
	@echo "Make sure bitstream is loaded!"

fpga: gemm-fpga
	@echo "Running gemm accelerator ..."
	./$<

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf gemm-arm vivado_hls.log *.prj result out.dat *~
	rm -rf gemm-fpga
