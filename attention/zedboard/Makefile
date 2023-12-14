#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the attention program
#
# @desc: 1. "make" or "make sw" runs software execution by default
#        2. "make fpga" invokes the HW accelerator
#        3. "make clean" cleans up the directory


INC_PATH=/usr/include/vivado_hls
CFLAGS = -I${INC_PATH} -DHLS_NO_XIL_FPO_LIB

.PHONY: all sw fpga

all: sw

attention-arm: attention.cpp attention_test.cpp
	@echo "Compiling & executing attention software program on ARM ..."
	g++ ${CFLAGS} $^ -o $@

result/attention_arm_sim.txt: attention-arm
	mkdir -p result
	./$< | tee $@

sw: result/attention_arm_sim.txt
	@echo "Result saved to $@"

attention-fpga: host.cpp
	@echo "Compiling host program"
	g++ ${CFLAGS} $^ -o $@
	@echo "Make sure bitstream is loaded!"

fpga: attention-fpga
	@echo "Running attention accelerator ..."
	./$<

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf attention-arm vivado_hls.log *.prj result out.dat *~
	rm -rf attention-fpga