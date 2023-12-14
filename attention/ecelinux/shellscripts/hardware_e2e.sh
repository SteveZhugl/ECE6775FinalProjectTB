echo "Building and Running CSIM" 
make attention-hw
echo "Genrate Verilog Code" 
vivado_hls -f run.tcl
echo "Generate FPGA Bitstream"
source run_bitstream.sh
