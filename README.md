# ECE6775FinalProjectTB
This repo is for Cornell ECE6775 Final Project
Team Member:Guanlin Zhu; Jerry Jin; Michael Shen; Xingze Li

## To Run the code

Running attention/ecelinux/shellscripts/hardware_e2e.sh from within the attention/ecelinux folder should compile and run the attention mechanism on CSIM and generate the bitstream that can be used to program the FPGA.

When the bitstream has been programmed onto the zedboard, running make fpga within the attention/zedboard folder should compile and run the attention mechanism on the board. 


## About the customized data type
We create a customized E2M2 (sign bit not counted) data type using ap_fixed and ap_int.
The new class ap_float contains three member function, ap_fixed<> mantissa, ap_int<> exponent and bool sign.
The constructor is mainly for conversion from float to ap_float.
The main operators are overloaded for supporting our modules, GEMM and softmax except for division and no math operation supported.
There is also a member function for conversion from ap_float to float type.
The current class is not templated yet, which means it only support E2M2, however, it is easy to design a E2M1 type with this.