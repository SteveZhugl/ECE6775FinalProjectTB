set moduleName softmax_128_s
set isTopModule 0
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isFreeRunPipelineModule 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {softmax<128>}
set C_modelType { void 0 }
set C_modelArgList {
	{ output_layer float 32 regular {array 128 { 1 3 } 1 1 }  }
	{ probability_distribu float 32 regular {array 128 { 0 3 } 0 1 }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "output_layer", "interface" : "memory", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "probability_distribu", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 13
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ output_layer_address0 sc_out sc_lv 7 signal 0 } 
	{ output_layer_ce0 sc_out sc_logic 1 signal 0 } 
	{ output_layer_q0 sc_in sc_lv 32 signal 0 } 
	{ probability_distribu_address0 sc_out sc_lv 7 signal 1 } 
	{ probability_distribu_ce0 sc_out sc_logic 1 signal 1 } 
	{ probability_distribu_we0 sc_out sc_logic 1 signal 1 } 
	{ probability_distribu_d0 sc_out sc_lv 32 signal 1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "output_layer_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "output_layer", "role": "address0" }} , 
 	{ "name": "output_layer_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_layer", "role": "ce0" }} , 
 	{ "name": "output_layer_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_layer", "role": "q0" }} , 
 	{ "name": "probability_distribu_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "probability_distribu", "role": "address0" }} , 
 	{ "name": "probability_distribu_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "probability_distribu", "role": "ce0" }} , 
 	{ "name": "probability_distribu_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "probability_distribu", "role": "we0" }} , 
 	{ "name": "probability_distribu_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "probability_distribu", "role": "d0" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9"],
		"CDFG" : "softmax_128_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "515842", "EstimateLatencyMax" : "38531842",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "output_layer", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "probability_distribu", "Type" : "Memory", "Direction" : "O"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.euler_sums_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_fadd_32ns_32ncud_U1", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_fmul_32ns_32ndEe_U2", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_fdiv_32ns_32neOg_U3", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_sitofp_32ns_3fYi_U4", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_fptrunc_64ns_g8j_U5", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_fpext_32ns_64hbi_U6", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_dadd_64ns_64nibs_U7", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dut_dmul_64ns_64njbC_U8", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	softmax_128_s {
		output_layer {Type I LastRead 1 FirstWrite -1}
		probability_distribu {Type O LastRead -1 FirstWrite 20}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "515842", "Max" : "38531842"}
	, {"Name" : "Interval", "Min" : "515842", "Max" : "38531842"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	output_layer { ap_memory {  { output_layer_address0 mem_address 1 7 }  { output_layer_ce0 mem_ce 1 1 }  { output_layer_q0 mem_dout 0 32 } } }
	probability_distribu { ap_memory {  { probability_distribu_address0 mem_address 1 7 }  { probability_distribu_ce0 mem_ce 1 1 }  { probability_distribu_we0 mem_we 1 1 }  { probability_distribu_d0 mem_din 1 32 } } }
}
