#!/bin/sh

# 
# Vivado(TM)
# runme.sh: a Vivado-generated Runs Script for UNIX
# Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
# 

if [ -z "$PATH" ]; then
  PATH=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vitis/2019.2/bin:/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2/ids_lite/ISE/bin/lin64:/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2/bin
else
  PATH=/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vitis/2019.2/bin:/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2/ids_lite/ISE/bin/lin64:/opt/xilinx/Xilinx_Vivado_vitis_2019.2/Vivado/2019.2/bin:$PATH
fi
export PATH

if [ -z "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=
else
  LD_LIBRARY_PATH=:$LD_LIBRARY_PATH
fi
export LD_LIBRARY_PATH

HD_PWD='/home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/synth_1'
cd "$HD_PWD"

HD_LOG=runme.log
/bin/touch $HD_LOG

ISEStep="./ISEWrap.sh"
EAStep()
{
     $ISEStep $HD_LOG "$@" >> $HD_LOG 2>&1
     if [ $? -ne 0 ]
     then
         exit
     fi
}

EAStep vivado -log xillydemo.vds -m64 -product Vivado -mode batch -messageDb vivado.pb -notrace -source xillydemo.tcl