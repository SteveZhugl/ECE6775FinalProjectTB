# ECE6775FinalProjectTB
This repo is for Cornell ECE6775 Final Project
Team Member:Guanlin Zhu; Jerry Jin; Michael Shen; Xingze Li

## To Run the code

Running attention/ecelinux/shellscripts/hardware_e2e.sh from within the attention/ecelinux folder should compile and run the attention mechanism on CSIM and generate the bitstream that can be used to program the FPGA.

When the bitstream has been programmed onto the zedboard, running make fpga within the attention/zedboard folder should compile and run the attention mechanism on the board. 
