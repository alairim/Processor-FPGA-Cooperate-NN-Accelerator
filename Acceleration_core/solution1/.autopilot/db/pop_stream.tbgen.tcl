set moduleName pop_stream
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 1
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {pop_stream}
set C_modelType { float 32 }
set C_modelArgList {
	{ e_data_V int 32 regular {fifo 0 volatile }  }
	{ e_keep_V int 4 regular {fifo 0 volatile }  }
	{ e_strb_V int 4 regular {fifo 0 volatile }  }
	{ e_user_V int 4 regular {fifo 0 volatile }  }
	{ e_last_V int 1 regular {fifo 0 volatile }  }
	{ e_id_V int 5 regular {fifo 0 volatile }  }
	{ e_dest_V int 5 regular {fifo 0 volatile }  }
}
set C_modelArgMapList {[ 
	{ "Name" : "e_data_V", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "e_keep_V", "interface" : "fifo", "bitwidth" : 4, "direction" : "READONLY"} , 
 	{ "Name" : "e_strb_V", "interface" : "fifo", "bitwidth" : 4, "direction" : "READONLY"} , 
 	{ "Name" : "e_user_V", "interface" : "fifo", "bitwidth" : 4, "direction" : "READONLY"} , 
 	{ "Name" : "e_last_V", "interface" : "fifo", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "e_id_V", "interface" : "fifo", "bitwidth" : 5, "direction" : "READONLY"} , 
 	{ "Name" : "e_dest_V", "interface" : "fifo", "bitwidth" : 5, "direction" : "READONLY"} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 32} ]}
# RTL Port declarations: 
set portNum 35
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ e_data_V_dout sc_in sc_lv 32 signal 0 } 
	{ e_data_V_empty_n sc_in sc_logic 1 signal 0 } 
	{ e_data_V_read sc_out sc_logic 1 signal 0 } 
	{ e_keep_V_dout sc_in sc_lv 4 signal 1 } 
	{ e_keep_V_empty_n sc_in sc_logic 1 signal 1 } 
	{ e_keep_V_read sc_out sc_logic 1 signal 1 } 
	{ e_strb_V_dout sc_in sc_lv 4 signal 2 } 
	{ e_strb_V_empty_n sc_in sc_logic 1 signal 2 } 
	{ e_strb_V_read sc_out sc_logic 1 signal 2 } 
	{ e_user_V_dout sc_in sc_lv 4 signal 3 } 
	{ e_user_V_empty_n sc_in sc_logic 1 signal 3 } 
	{ e_user_V_read sc_out sc_logic 1 signal 3 } 
	{ e_last_V_dout sc_in sc_lv 1 signal 4 } 
	{ e_last_V_empty_n sc_in sc_logic 1 signal 4 } 
	{ e_last_V_read sc_out sc_logic 1 signal 4 } 
	{ e_id_V_dout sc_in sc_lv 5 signal 5 } 
	{ e_id_V_empty_n sc_in sc_logic 1 signal 5 } 
	{ e_id_V_read sc_out sc_logic 1 signal 5 } 
	{ e_dest_V_dout sc_in sc_lv 5 signal 6 } 
	{ e_dest_V_empty_n sc_in sc_logic 1 signal 6 } 
	{ e_dest_V_read sc_out sc_logic 1 signal 6 } 
	{ ap_return sc_out sc_lv 32 signal -1 } 
	{ e_data_V_blk_n sc_out sc_logic 1 signal -1 } 
	{ e_keep_V_blk_n sc_out sc_logic 1 signal -1 } 
	{ e_strb_V_blk_n sc_out sc_logic 1 signal -1 } 
	{ e_user_V_blk_n sc_out sc_logic 1 signal -1 } 
	{ e_last_V_blk_n sc_out sc_logic 1 signal -1 } 
	{ e_id_V_blk_n sc_out sc_logic 1 signal -1 } 
	{ e_dest_V_blk_n sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "e_data_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "e_data_V", "role": "dout" }} , 
 	{ "name": "e_data_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_data_V", "role": "empty_n" }} , 
 	{ "name": "e_data_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_data_V", "role": "read" }} , 
 	{ "name": "e_keep_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "e_keep_V", "role": "dout" }} , 
 	{ "name": "e_keep_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_keep_V", "role": "empty_n" }} , 
 	{ "name": "e_keep_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_keep_V", "role": "read" }} , 
 	{ "name": "e_strb_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "e_strb_V", "role": "dout" }} , 
 	{ "name": "e_strb_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_strb_V", "role": "empty_n" }} , 
 	{ "name": "e_strb_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_strb_V", "role": "read" }} , 
 	{ "name": "e_user_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "e_user_V", "role": "dout" }} , 
 	{ "name": "e_user_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_user_V", "role": "empty_n" }} , 
 	{ "name": "e_user_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_user_V", "role": "read" }} , 
 	{ "name": "e_last_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "e_last_V", "role": "dout" }} , 
 	{ "name": "e_last_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_last_V", "role": "empty_n" }} , 
 	{ "name": "e_last_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_last_V", "role": "read" }} , 
 	{ "name": "e_id_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "e_id_V", "role": "dout" }} , 
 	{ "name": "e_id_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_id_V", "role": "empty_n" }} , 
 	{ "name": "e_id_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_id_V", "role": "read" }} , 
 	{ "name": "e_dest_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "e_dest_V", "role": "dout" }} , 
 	{ "name": "e_dest_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_dest_V", "role": "empty_n" }} , 
 	{ "name": "e_dest_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_dest_V", "role": "read" }} , 
 	{ "name": "ap_return", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return", "role": "default" }} , 
 	{ "name": "e_data_V_blk_n", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_data_V_blk_n", "role": "default" }} , 
 	{ "name": "e_keep_V_blk_n", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_keep_V_blk_n", "role": "default" }} , 
 	{ "name": "e_strb_V_blk_n", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_strb_V_blk_n", "role": "default" }} , 
 	{ "name": "e_user_V_blk_n", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_user_V_blk_n", "role": "default" }} , 
 	{ "name": "e_last_V_blk_n", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_last_V_blk_n", "role": "default" }} , 
 	{ "name": "e_id_V_blk_n", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_id_V_blk_n", "role": "default" }} , 
 	{ "name": "e_dest_V_blk_n", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "e_dest_V_blk_n", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
		"CDFG" : "pop_stream",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "e_data_V", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "e_data_V_blk_n", "Type" : "RtlPort"}]},
			{"Name" : "e_keep_V", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "e_keep_V_blk_n", "Type" : "RtlPort"}]},
			{"Name" : "e_strb_V", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "e_strb_V_blk_n", "Type" : "RtlPort"}]},
			{"Name" : "e_user_V", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "e_user_V_blk_n", "Type" : "RtlPort"}]},
			{"Name" : "e_last_V", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "e_last_V_blk_n", "Type" : "RtlPort"}]},
			{"Name" : "e_id_V", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "e_id_V_blk_n", "Type" : "RtlPort"}]},
			{"Name" : "e_dest_V", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "e_dest_V_blk_n", "Type" : "RtlPort"}]}]}]}


set ArgLastReadFirstWriteLatency {
	pop_stream {
		e_data_V {Type I LastRead 0 FirstWrite -1}
		e_keep_V {Type I LastRead 0 FirstWrite -1}
		e_strb_V {Type I LastRead 0 FirstWrite -1}
		e_user_V {Type I LastRead 0 FirstWrite -1}
		e_last_V {Type I LastRead 0 FirstWrite -1}
		e_id_V {Type I LastRead 0 FirstWrite -1}
		e_dest_V {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "0", "Max" : "0"}
	, {"Name" : "Interval", "Min" : "0", "Max" : "0"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	e_data_V { ap_fifo {  { e_data_V_dout fifo_data 0 32 }  { e_data_V_empty_n fifo_status 0 1 }  { e_data_V_read fifo_update 1 1 } } }
	e_keep_V { ap_fifo {  { e_keep_V_dout fifo_data 0 4 }  { e_keep_V_empty_n fifo_status 0 1 }  { e_keep_V_read fifo_update 1 1 } } }
	e_strb_V { ap_fifo {  { e_strb_V_dout fifo_data 0 4 }  { e_strb_V_empty_n fifo_status 0 1 }  { e_strb_V_read fifo_update 1 1 } } }
	e_user_V { ap_fifo {  { e_user_V_dout fifo_data 0 4 }  { e_user_V_empty_n fifo_status 0 1 }  { e_user_V_read fifo_update 1 1 } } }
	e_last_V { ap_fifo {  { e_last_V_dout fifo_data 0 1 }  { e_last_V_empty_n fifo_status 0 1 }  { e_last_V_read fifo_update 1 1 } } }
	e_id_V { ap_fifo {  { e_id_V_dout fifo_data 0 5 }  { e_id_V_empty_n fifo_status 0 1 }  { e_id_V_read fifo_update 1 1 } } }
	e_dest_V { ap_fifo {  { e_dest_V_dout fifo_data 0 5 }  { e_dest_V_empty_n fifo_status 0 1 }  { e_dest_V_read fifo_update 1 1 } } }
}
