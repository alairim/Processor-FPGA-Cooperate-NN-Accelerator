
set PATH=
call D:/Xilinx/Vivado/2018.3/bin/xelab xil_defaultlib.apatb_mult_accel_core_call_top glbl -prj mult_accel_core_call.prj -L smartconnect_v1_0 -L axi_protocol_checker_v1_1_12 -L axi_protocol_checker_v1_1_13 -L axis_protocol_checker_v1_1_11 -L axis_protocol_checker_v1_1_12 -L xil_defaultlib -L unisims_ver -L xpm --initfile "D:/Xilinx/Vivado/2018.3/data/xsim/ip/xsim_ip.ini" --lib "ieee_proposed=./ieee_proposed" -s mult_accel_core_call 
call D:/Xilinx/Vivado/2018.3/bin/xsim --noieeewarnings mult_accel_core_call -tclbatch mult_accel_core_call.tcl

