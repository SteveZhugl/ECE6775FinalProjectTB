echo "Building and Running CSIM" 
make gemm-hw
echo "Genrate Verilog Code" 
vivado_hls -f run.tcl
echo "Generate FPGA Bitstream"
source run_bitstream.sh
echo "Send Bitstream to Zedd Board"
scp xillydemo.bit mts247@zhang-zedboard-11.ece.cornell.edu:~
echo "Sending project to zeddboard"
zip -r zedboard_proj.zip zedboard_project
scp zedboard_proj.zip mts247@zhang-zedboard-11.ece.cornell.edu:~
rm zedboard_proj.zip