# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
set_msg_config  -id {BD 41-968}  -string {{xillybus_S_AXI}}  -new_severity {INFO} 
set_msg_config  -id {BD 41-967}  -string {{xillybus_ip_0/xillybus_M_AXI}}  -new_severity {INFO} 
set_msg_config  -id {BD 41-967}  -string {{xillybus_ip_0/xillybus_S_AXI}}  -new_severity {INFO} 
set_msg_config  -id {BD 41-678}  -string {{xillybus_S_AXI/Reg}}  -new_severity {INFO} 
set_msg_config  -id {BD 41-1356}  -string {{xillybus_S_AXI/Reg}}  -new_severity {INFO} 
set_msg_config  -id {BD 41-759}  -string {{xlconcat_0/In}}  -new_severity {INFO} 
set_msg_config  -id {Netlist 29-160}  -string {{vivado_system_processing_system7}}  -new_severity {INFO} 
set_param project.vivado.isBlockSynthRun true
set_msg_config -msgmgr_mode ooc_run
create_project -in_memory -part xc7z020clg484-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.cache/wt [current_project]
set_property parent.project_path /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.xpr [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY} [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property ip_repo_paths /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vivado-ip [current_project]
update_ip_catalog
set_property ip_output_repo /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_ip -quiet /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo.xci
set_property used_in_implementation false [get_files -all /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo.xdc]
set_property used_in_implementation false [get_files -all /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_clocks.xdc]
set_property used_in_implementation false [get_files -all /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_ooc.xdc]

# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param ips.enableIPCacheLiteLoad 1

set cached_ip [config_ip_cache -export -no_bom  -dir /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/vga_fifo_synth_1 -new_name vga_fifo -ip [get_ips vga_fifo]]

if { $cached_ip eq {} } {
close [open __synthesis_is_running__ w]

synth_design -top vga_fifo -part xc7z020clg484-1 -mode out_of_context

#---------------------------------------------------------
# Generate Checkpoint/Stub/Simulation Files For IP Cache
#---------------------------------------------------------
# disable binary constraint mode for IPCache checkpoints
set_param constraints.enableBinaryConstraints false

catch {
 write_checkpoint -force -noxdef -rename_prefix vga_fifo_ vga_fifo.dcp

 set ipCachedFiles {}
 write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ vga_fifo_stub.v
 lappend ipCachedFiles vga_fifo_stub.v

 write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ vga_fifo_stub.vhdl
 lappend ipCachedFiles vga_fifo_stub.vhdl

 write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ vga_fifo_sim_netlist.v
 lappend ipCachedFiles vga_fifo_sim_netlist.v

 write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ vga_fifo_sim_netlist.vhdl
 lappend ipCachedFiles vga_fifo_sim_netlist.vhdl
set TIME_taken [expr [clock seconds] - $TIME_start]

 config_ip_cache -add -dcp vga_fifo.dcp -move_files $ipCachedFiles -use_project_ipc  -synth_runtime $TIME_taken  -ip [get_ips vga_fifo]
}

rename_ref -prefix_all vga_fifo_

# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef vga_fifo.dcp
create_report "vga_fifo_synth_1_synth_report_utilization_0" "report_utilization -file vga_fifo_utilization_synth.rpt -pb vga_fifo_utilization_synth.pb"

if { [catch {
  file copy -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/vga_fifo_synth_1/vga_fifo.dcp /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo.dcp
} _RESULT ] } { 
  send_msg_id runtcl-3 error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
  error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
}

if { [catch {
  write_verilog -force -mode synth_stub /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_stub.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a Verilog synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  write_vhdl -force -mode synth_stub /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_stub.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a VHDL synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  write_verilog -force -mode funcsim /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_sim_netlist.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the Verilog functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

if { [catch {
  write_vhdl -force -mode funcsim /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_sim_netlist.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the VHDL functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}


} else {


if { [catch {
  file copy -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/vga_fifo_synth_1/vga_fifo.dcp /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo.dcp
} _RESULT ] } { 
  send_msg_id runtcl-3 error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
  error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
}

if { [catch {
  file rename -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/vga_fifo_synth_1/vga_fifo_stub.v /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_stub.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a Verilog synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  file rename -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/vga_fifo_synth_1/vga_fifo_stub.vhdl /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_stub.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a VHDL synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  file rename -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/vga_fifo_synth_1/vga_fifo_sim_netlist.v /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_sim_netlist.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the Verilog functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

if { [catch {
  file rename -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.runs/vga_fifo_synth_1/vga_fifo_sim_netlist.vhdl /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_sim_netlist.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the VHDL functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

}; # end if cached_ip 

if {[file isdir /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.ip_user_files/ip/vga_fifo]} {
  catch { 
    file copy -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_stub.v /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.ip_user_files/ip/vga_fifo
  }
}

if {[file isdir /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.ip_user_files/ip/vga_fifo]} {
  catch { 
    file copy -force /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/vivado-essentials/vga_fifo/vga_fifo_stub.vhdl /home/xl834/transformer/ECE6775FinalProjectTB/GEMM/zedboard_project/xillybus/vivado/xillydemo.ip_user_files/ip/vga_fifo
  }
}
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
