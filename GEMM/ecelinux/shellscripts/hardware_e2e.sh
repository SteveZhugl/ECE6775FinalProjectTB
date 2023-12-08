echo "Building and Running CSIM" 
make gemm-hw
echo "Genrate Verilog Code" 
vivado_hls -f run.tcl
echo "Generate FPGA Bitstream"
source run_bitstream.sh
echo "Send Bitstream to Zedd Board"
scp xillydemo.bit mts247@zhang-zedboard-11.ece.cornell.edu:~
