// ==============================================================
// File generated on Sun Dec 11 17:08:42 +0100 2022
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
`timescale 1 ns / 1 ps
module mult_accel_core_call_top (
s_axi_CONTROL_BUS_AWADDR,
s_axi_CONTROL_BUS_AWVALID,
s_axi_CONTROL_BUS_AWREADY,
s_axi_CONTROL_BUS_WDATA,
s_axi_CONTROL_BUS_WSTRB,
s_axi_CONTROL_BUS_WVALID,
s_axi_CONTROL_BUS_WREADY,
s_axi_CONTROL_BUS_BRESP,
s_axi_CONTROL_BUS_BVALID,
s_axi_CONTROL_BUS_BREADY,
s_axi_CONTROL_BUS_ARADDR,
s_axi_CONTROL_BUS_ARVALID,
s_axi_CONTROL_BUS_ARREADY,
s_axi_CONTROL_BUS_RDATA,
s_axi_CONTROL_BUS_RRESP,
s_axi_CONTROL_BUS_RVALID,
s_axi_CONTROL_BUS_RREADY,
interrupt,
INPUT_STREAM_TVALID,
INPUT_STREAM_TREADY,
INPUT_STREAM_TDATA,
INPUT_STREAM_TKEEP,
INPUT_STREAM_TSTRB,
INPUT_STREAM_TUSER,
INPUT_STREAM_TLAST,
INPUT_STREAM_TID,
INPUT_STREAM_TDEST,
OUTPUT_STREAM_TVALID,
OUTPUT_STREAM_TREADY,
OUTPUT_STREAM_TDATA,
OUTPUT_STREAM_TKEEP,
OUTPUT_STREAM_TSTRB,
OUTPUT_STREAM_TUSER,
OUTPUT_STREAM_TLAST,
OUTPUT_STREAM_TID,
OUTPUT_STREAM_TDEST,
aresetn,
aclk
);

parameter C_S_AXI_CONTROL_BUS_ADDR_WIDTH = 4;
parameter C_S_AXI_CONTROL_BUS_DATA_WIDTH = 32;
parameter RESET_ACTIVE_LOW = 1;

input [C_S_AXI_CONTROL_BUS_ADDR_WIDTH - 1:0] s_axi_CONTROL_BUS_AWADDR ;
input s_axi_CONTROL_BUS_AWVALID ;
output s_axi_CONTROL_BUS_AWREADY ;
input [C_S_AXI_CONTROL_BUS_DATA_WIDTH - 1:0] s_axi_CONTROL_BUS_WDATA ;
input [C_S_AXI_CONTROL_BUS_DATA_WIDTH/8 - 1:0] s_axi_CONTROL_BUS_WSTRB ;
input s_axi_CONTROL_BUS_WVALID ;
output s_axi_CONTROL_BUS_WREADY ;
output [2 - 1:0] s_axi_CONTROL_BUS_BRESP ;
output s_axi_CONTROL_BUS_BVALID ;
input s_axi_CONTROL_BUS_BREADY ;
input [C_S_AXI_CONTROL_BUS_ADDR_WIDTH - 1:0] s_axi_CONTROL_BUS_ARADDR ;
input s_axi_CONTROL_BUS_ARVALID ;
output s_axi_CONTROL_BUS_ARREADY ;
output [C_S_AXI_CONTROL_BUS_DATA_WIDTH - 1:0] s_axi_CONTROL_BUS_RDATA ;
output [2 - 1:0] s_axi_CONTROL_BUS_RRESP ;
output s_axi_CONTROL_BUS_RVALID ;
input s_axi_CONTROL_BUS_RREADY ;
output interrupt ;


input INPUT_STREAM_TVALID ;
output INPUT_STREAM_TREADY ;
input [32 - 1:0] INPUT_STREAM_TDATA ;
input [4 - 1:0] INPUT_STREAM_TKEEP ;
input [4 - 1:0] INPUT_STREAM_TSTRB ;
input [4 - 1:0] INPUT_STREAM_TUSER ;
input [1 - 1:0] INPUT_STREAM_TLAST ;
input [5 - 1:0] INPUT_STREAM_TID ;
input [5 - 1:0] INPUT_STREAM_TDEST ;


output OUTPUT_STREAM_TVALID ;
input OUTPUT_STREAM_TREADY ;
output [32 - 1:0] OUTPUT_STREAM_TDATA ;
output [4 - 1:0] OUTPUT_STREAM_TKEEP ;
output [4 - 1:0] OUTPUT_STREAM_TSTRB ;
output [4 - 1:0] OUTPUT_STREAM_TUSER ;
output [1 - 1:0] OUTPUT_STREAM_TLAST ;
output [5 - 1:0] OUTPUT_STREAM_TID ;
output [5 - 1:0] OUTPUT_STREAM_TDEST ;

input aresetn ;

input aclk ;


wire [C_S_AXI_CONTROL_BUS_ADDR_WIDTH - 1:0] s_axi_CONTROL_BUS_AWADDR;
wire s_axi_CONTROL_BUS_AWVALID;
wire s_axi_CONTROL_BUS_AWREADY;
wire [C_S_AXI_CONTROL_BUS_DATA_WIDTH - 1:0] s_axi_CONTROL_BUS_WDATA;
wire [C_S_AXI_CONTROL_BUS_DATA_WIDTH/8 - 1:0] s_axi_CONTROL_BUS_WSTRB;
wire s_axi_CONTROL_BUS_WVALID;
wire s_axi_CONTROL_BUS_WREADY;
wire [2 - 1:0] s_axi_CONTROL_BUS_BRESP;
wire s_axi_CONTROL_BUS_BVALID;
wire s_axi_CONTROL_BUS_BREADY;
wire [C_S_AXI_CONTROL_BUS_ADDR_WIDTH - 1:0] s_axi_CONTROL_BUS_ARADDR;
wire s_axi_CONTROL_BUS_ARVALID;
wire s_axi_CONTROL_BUS_ARREADY;
wire [C_S_AXI_CONTROL_BUS_DATA_WIDTH - 1:0] s_axi_CONTROL_BUS_RDATA;
wire [2 - 1:0] s_axi_CONTROL_BUS_RRESP;
wire s_axi_CONTROL_BUS_RVALID;
wire s_axi_CONTROL_BUS_RREADY;
wire interrupt;


wire INPUT_STREAM_TVALID;
wire INPUT_STREAM_TREADY;
wire [32 - 1:0] INPUT_STREAM_TDATA;
wire [4 - 1:0] INPUT_STREAM_TKEEP;
wire [4 - 1:0] INPUT_STREAM_TSTRB;
wire [4 - 1:0] INPUT_STREAM_TUSER;
wire [1 - 1:0] INPUT_STREAM_TLAST;
wire [5 - 1:0] INPUT_STREAM_TID;
wire [5 - 1:0] INPUT_STREAM_TDEST;


wire OUTPUT_STREAM_TVALID;
wire OUTPUT_STREAM_TREADY;
wire [32 - 1:0] OUTPUT_STREAM_TDATA;
wire [4 - 1:0] OUTPUT_STREAM_TKEEP;
wire [4 - 1:0] OUTPUT_STREAM_TSTRB;
wire [4 - 1:0] OUTPUT_STREAM_TUSER;
wire [1 - 1:0] OUTPUT_STREAM_TLAST;
wire [5 - 1:0] OUTPUT_STREAM_TID;
wire [5 - 1:0] OUTPUT_STREAM_TDEST;

wire aresetn;


wire sig_mult_accel_core_call_ap_start;
wire sig_mult_accel_core_call_ap_ready;
wire sig_mult_accel_core_call_ap_done;
wire sig_mult_accel_core_call_ap_idle;

wire [32 - 1:0] sig_mult_accel_core_call_in_stream_data_V_dout;
wire sig_mult_accel_core_call_in_stream_data_V_empty_n;
wire sig_mult_accel_core_call_in_stream_data_V_read;
wire [4 - 1:0] sig_mult_accel_core_call_in_stream_keep_V_dout;
wire sig_mult_accel_core_call_in_stream_keep_V_empty_n;
wire sig_mult_accel_core_call_in_stream_keep_V_read;
wire [4 - 1:0] sig_mult_accel_core_call_in_stream_strb_V_dout;
wire sig_mult_accel_core_call_in_stream_strb_V_empty_n;
wire sig_mult_accel_core_call_in_stream_strb_V_read;
wire [4 - 1:0] sig_mult_accel_core_call_in_stream_user_V_dout;
wire sig_mult_accel_core_call_in_stream_user_V_empty_n;
wire sig_mult_accel_core_call_in_stream_user_V_read;
wire [1 - 1:0] sig_mult_accel_core_call_in_stream_last_V_dout;
wire sig_mult_accel_core_call_in_stream_last_V_empty_n;
wire sig_mult_accel_core_call_in_stream_last_V_read;
wire [5 - 1:0] sig_mult_accel_core_call_in_stream_id_V_dout;
wire sig_mult_accel_core_call_in_stream_id_V_empty_n;
wire sig_mult_accel_core_call_in_stream_id_V_read;
wire [5 - 1:0] sig_mult_accel_core_call_in_stream_dest_V_dout;
wire sig_mult_accel_core_call_in_stream_dest_V_empty_n;
wire sig_mult_accel_core_call_in_stream_dest_V_read;

wire [32 - 1:0] sig_mult_accel_core_call_out_stream_data_V_din;
wire sig_mult_accel_core_call_out_stream_data_V_full_n;
wire sig_mult_accel_core_call_out_stream_data_V_write;
wire [4 - 1:0] sig_mult_accel_core_call_out_stream_keep_V_din;
wire sig_mult_accel_core_call_out_stream_keep_V_full_n;
wire sig_mult_accel_core_call_out_stream_keep_V_write;
wire [4 - 1:0] sig_mult_accel_core_call_out_stream_strb_V_din;
wire sig_mult_accel_core_call_out_stream_strb_V_full_n;
wire sig_mult_accel_core_call_out_stream_strb_V_write;
wire [4 - 1:0] sig_mult_accel_core_call_out_stream_user_V_din;
wire sig_mult_accel_core_call_out_stream_user_V_full_n;
wire sig_mult_accel_core_call_out_stream_user_V_write;
wire [1 - 1:0] sig_mult_accel_core_call_out_stream_last_V_din;
wire sig_mult_accel_core_call_out_stream_last_V_full_n;
wire sig_mult_accel_core_call_out_stream_last_V_write;
wire [5 - 1:0] sig_mult_accel_core_call_out_stream_id_V_din;
wire sig_mult_accel_core_call_out_stream_id_V_full_n;
wire sig_mult_accel_core_call_out_stream_id_V_write;
wire [5 - 1:0] sig_mult_accel_core_call_out_stream_dest_V_din;
wire sig_mult_accel_core_call_out_stream_dest_V_full_n;
wire sig_mult_accel_core_call_out_stream_dest_V_write;

wire sig_mult_accel_core_call_ap_rst;



mult_accel_core_call mult_accel_core_call_U(
    .ap_start(sig_mult_accel_core_call_ap_start),
    .ap_ready(sig_mult_accel_core_call_ap_ready),
    .ap_done(sig_mult_accel_core_call_ap_done),
    .ap_idle(sig_mult_accel_core_call_ap_idle),
    .in_stream_data_V_dout(sig_mult_accel_core_call_in_stream_data_V_dout),
    .in_stream_data_V_empty_n(sig_mult_accel_core_call_in_stream_data_V_empty_n),
    .in_stream_data_V_read(sig_mult_accel_core_call_in_stream_data_V_read),
    .in_stream_keep_V_dout(sig_mult_accel_core_call_in_stream_keep_V_dout),
    .in_stream_keep_V_empty_n(sig_mult_accel_core_call_in_stream_keep_V_empty_n),
    .in_stream_keep_V_read(sig_mult_accel_core_call_in_stream_keep_V_read),
    .in_stream_strb_V_dout(sig_mult_accel_core_call_in_stream_strb_V_dout),
    .in_stream_strb_V_empty_n(sig_mult_accel_core_call_in_stream_strb_V_empty_n),
    .in_stream_strb_V_read(sig_mult_accel_core_call_in_stream_strb_V_read),
    .in_stream_user_V_dout(sig_mult_accel_core_call_in_stream_user_V_dout),
    .in_stream_user_V_empty_n(sig_mult_accel_core_call_in_stream_user_V_empty_n),
    .in_stream_user_V_read(sig_mult_accel_core_call_in_stream_user_V_read),
    .in_stream_last_V_dout(sig_mult_accel_core_call_in_stream_last_V_dout),
    .in_stream_last_V_empty_n(sig_mult_accel_core_call_in_stream_last_V_empty_n),
    .in_stream_last_V_read(sig_mult_accel_core_call_in_stream_last_V_read),
    .in_stream_id_V_dout(sig_mult_accel_core_call_in_stream_id_V_dout),
    .in_stream_id_V_empty_n(sig_mult_accel_core_call_in_stream_id_V_empty_n),
    .in_stream_id_V_read(sig_mult_accel_core_call_in_stream_id_V_read),
    .in_stream_dest_V_dout(sig_mult_accel_core_call_in_stream_dest_V_dout),
    .in_stream_dest_V_empty_n(sig_mult_accel_core_call_in_stream_dest_V_empty_n),
    .in_stream_dest_V_read(sig_mult_accel_core_call_in_stream_dest_V_read),
    .out_stream_data_V_din(sig_mult_accel_core_call_out_stream_data_V_din),
    .out_stream_data_V_full_n(sig_mult_accel_core_call_out_stream_data_V_full_n),
    .out_stream_data_V_write(sig_mult_accel_core_call_out_stream_data_V_write),
    .out_stream_keep_V_din(sig_mult_accel_core_call_out_stream_keep_V_din),
    .out_stream_keep_V_full_n(sig_mult_accel_core_call_out_stream_keep_V_full_n),
    .out_stream_keep_V_write(sig_mult_accel_core_call_out_stream_keep_V_write),
    .out_stream_strb_V_din(sig_mult_accel_core_call_out_stream_strb_V_din),
    .out_stream_strb_V_full_n(sig_mult_accel_core_call_out_stream_strb_V_full_n),
    .out_stream_strb_V_write(sig_mult_accel_core_call_out_stream_strb_V_write),
    .out_stream_user_V_din(sig_mult_accel_core_call_out_stream_user_V_din),
    .out_stream_user_V_full_n(sig_mult_accel_core_call_out_stream_user_V_full_n),
    .out_stream_user_V_write(sig_mult_accel_core_call_out_stream_user_V_write),
    .out_stream_last_V_din(sig_mult_accel_core_call_out_stream_last_V_din),
    .out_stream_last_V_full_n(sig_mult_accel_core_call_out_stream_last_V_full_n),
    .out_stream_last_V_write(sig_mult_accel_core_call_out_stream_last_V_write),
    .out_stream_id_V_din(sig_mult_accel_core_call_out_stream_id_V_din),
    .out_stream_id_V_full_n(sig_mult_accel_core_call_out_stream_id_V_full_n),
    .out_stream_id_V_write(sig_mult_accel_core_call_out_stream_id_V_write),
    .out_stream_dest_V_din(sig_mult_accel_core_call_out_stream_dest_V_din),
    .out_stream_dest_V_full_n(sig_mult_accel_core_call_out_stream_dest_V_full_n),
    .out_stream_dest_V_write(sig_mult_accel_core_call_out_stream_dest_V_write),
    .ap_rst(sig_mult_accel_core_call_ap_rst),
    .ap_clk(aclk)
);

mult_accel_core_call_CONTROL_BUS_if #(
    .C_ADDR_WIDTH(C_S_AXI_CONTROL_BUS_ADDR_WIDTH),
    .C_DATA_WIDTH(C_S_AXI_CONTROL_BUS_DATA_WIDTH))
mult_accel_core_call_CONTROL_BUS_if_U(
    .ACLK(aclk),
    .ARESETN(aresetn),
    .I_ap_start(sig_mult_accel_core_call_ap_start),
    .O_ap_ready(sig_mult_accel_core_call_ap_ready),
    .O_ap_done(sig_mult_accel_core_call_ap_done),
    .O_ap_idle(sig_mult_accel_core_call_ap_idle),
    .AWADDR(s_axi_CONTROL_BUS_AWADDR),
    .AWVALID(s_axi_CONTROL_BUS_AWVALID),
    .AWREADY(s_axi_CONTROL_BUS_AWREADY),
    .WDATA(s_axi_CONTROL_BUS_WDATA),
    .WSTRB(s_axi_CONTROL_BUS_WSTRB),
    .WVALID(s_axi_CONTROL_BUS_WVALID),
    .WREADY(s_axi_CONTROL_BUS_WREADY),
    .BRESP(s_axi_CONTROL_BUS_BRESP),
    .BVALID(s_axi_CONTROL_BUS_BVALID),
    .BREADY(s_axi_CONTROL_BUS_BREADY),
    .ARADDR(s_axi_CONTROL_BUS_ARADDR),
    .ARVALID(s_axi_CONTROL_BUS_ARVALID),
    .ARREADY(s_axi_CONTROL_BUS_ARREADY),
    .RDATA(s_axi_CONTROL_BUS_RDATA),
    .RRESP(s_axi_CONTROL_BUS_RRESP),
    .RVALID(s_axi_CONTROL_BUS_RVALID),
    .RREADY(s_axi_CONTROL_BUS_RREADY),
    .interrupt(interrupt));

mult_accel_core_call_INPUT_STREAM_if mult_accel_core_call_INPUT_STREAM_if_U(
    .ACLK(aclk),
    .ARESETN(aresetn),
    .in_stream_data_V_dout(sig_mult_accel_core_call_in_stream_data_V_dout),
    .in_stream_data_V_empty_n(sig_mult_accel_core_call_in_stream_data_V_empty_n),
    .in_stream_data_V_read(sig_mult_accel_core_call_in_stream_data_V_read),
    .in_stream_keep_V_dout(sig_mult_accel_core_call_in_stream_keep_V_dout),
    .in_stream_keep_V_empty_n(sig_mult_accel_core_call_in_stream_keep_V_empty_n),
    .in_stream_keep_V_read(sig_mult_accel_core_call_in_stream_keep_V_read),
    .in_stream_strb_V_dout(sig_mult_accel_core_call_in_stream_strb_V_dout),
    .in_stream_strb_V_empty_n(sig_mult_accel_core_call_in_stream_strb_V_empty_n),
    .in_stream_strb_V_read(sig_mult_accel_core_call_in_stream_strb_V_read),
    .in_stream_user_V_dout(sig_mult_accel_core_call_in_stream_user_V_dout),
    .in_stream_user_V_empty_n(sig_mult_accel_core_call_in_stream_user_V_empty_n),
    .in_stream_user_V_read(sig_mult_accel_core_call_in_stream_user_V_read),
    .in_stream_last_V_dout(sig_mult_accel_core_call_in_stream_last_V_dout),
    .in_stream_last_V_empty_n(sig_mult_accel_core_call_in_stream_last_V_empty_n),
    .in_stream_last_V_read(sig_mult_accel_core_call_in_stream_last_V_read),
    .in_stream_id_V_dout(sig_mult_accel_core_call_in_stream_id_V_dout),
    .in_stream_id_V_empty_n(sig_mult_accel_core_call_in_stream_id_V_empty_n),
    .in_stream_id_V_read(sig_mult_accel_core_call_in_stream_id_V_read),
    .in_stream_dest_V_dout(sig_mult_accel_core_call_in_stream_dest_V_dout),
    .in_stream_dest_V_empty_n(sig_mult_accel_core_call_in_stream_dest_V_empty_n),
    .in_stream_dest_V_read(sig_mult_accel_core_call_in_stream_dest_V_read),
    .TVALID(INPUT_STREAM_TVALID),
    .TREADY(INPUT_STREAM_TREADY),
    .TDATA(INPUT_STREAM_TDATA),
    .TKEEP(INPUT_STREAM_TKEEP),
    .TSTRB(INPUT_STREAM_TSTRB),
    .TUSER(INPUT_STREAM_TUSER),
    .TLAST(INPUT_STREAM_TLAST),
    .TID(INPUT_STREAM_TID),
    .TDEST(INPUT_STREAM_TDEST));

mult_accel_core_call_OUTPUT_STREAM_if mult_accel_core_call_OUTPUT_STREAM_if_U(
    .ACLK(aclk),
    .ARESETN(aresetn),
    .out_stream_data_V_din(sig_mult_accel_core_call_out_stream_data_V_din),
    .out_stream_data_V_full_n(sig_mult_accel_core_call_out_stream_data_V_full_n),
    .out_stream_data_V_write(sig_mult_accel_core_call_out_stream_data_V_write),
    .out_stream_keep_V_din(sig_mult_accel_core_call_out_stream_keep_V_din),
    .out_stream_keep_V_full_n(sig_mult_accel_core_call_out_stream_keep_V_full_n),
    .out_stream_keep_V_write(sig_mult_accel_core_call_out_stream_keep_V_write),
    .out_stream_strb_V_din(sig_mult_accel_core_call_out_stream_strb_V_din),
    .out_stream_strb_V_full_n(sig_mult_accel_core_call_out_stream_strb_V_full_n),
    .out_stream_strb_V_write(sig_mult_accel_core_call_out_stream_strb_V_write),
    .out_stream_user_V_din(sig_mult_accel_core_call_out_stream_user_V_din),
    .out_stream_user_V_full_n(sig_mult_accel_core_call_out_stream_user_V_full_n),
    .out_stream_user_V_write(sig_mult_accel_core_call_out_stream_user_V_write),
    .out_stream_last_V_din(sig_mult_accel_core_call_out_stream_last_V_din),
    .out_stream_last_V_full_n(sig_mult_accel_core_call_out_stream_last_V_full_n),
    .out_stream_last_V_write(sig_mult_accel_core_call_out_stream_last_V_write),
    .out_stream_id_V_din(sig_mult_accel_core_call_out_stream_id_V_din),
    .out_stream_id_V_full_n(sig_mult_accel_core_call_out_stream_id_V_full_n),
    .out_stream_id_V_write(sig_mult_accel_core_call_out_stream_id_V_write),
    .out_stream_dest_V_din(sig_mult_accel_core_call_out_stream_dest_V_din),
    .out_stream_dest_V_full_n(sig_mult_accel_core_call_out_stream_dest_V_full_n),
    .out_stream_dest_V_write(sig_mult_accel_core_call_out_stream_dest_V_write),
    .TVALID(OUTPUT_STREAM_TVALID),
    .TREADY(OUTPUT_STREAM_TREADY),
    .TDATA(OUTPUT_STREAM_TDATA),
    .TKEEP(OUTPUT_STREAM_TKEEP),
    .TSTRB(OUTPUT_STREAM_TSTRB),
    .TUSER(OUTPUT_STREAM_TUSER),
    .TLAST(OUTPUT_STREAM_TLAST),
    .TID(OUTPUT_STREAM_TID),
    .TDEST(OUTPUT_STREAM_TDEST));

mult_accel_core_call_ap_rst_if #(
    .RESET_ACTIVE_LOW(RESET_ACTIVE_LOW))
ap_rst_if_U(
    .dout(sig_mult_accel_core_call_ap_rst),
    .din(aresetn));

endmodule
