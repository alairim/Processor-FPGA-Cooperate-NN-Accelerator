// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#include "mult_accel_core_call.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

const sc_logic mult_accel_core_call::ap_const_logic_1 = sc_dt::Log_1;
const sc_logic mult_accel_core_call::ap_const_logic_0 = sc_dt::Log_0;
const sc_lv<2> mult_accel_core_call::ap_ST_fsm_state1 = "1";
const sc_lv<2> mult_accel_core_call::ap_ST_fsm_state2 = "10";
const sc_lv<32> mult_accel_core_call::ap_const_lv32_0 = "00000000000000000000000000000000";
const sc_lv<32> mult_accel_core_call::ap_const_lv32_1 = "1";
const bool mult_accel_core_call::ap_const_boolean_1 = true;

mult_accel_core_call::mult_accel_core_call(sc_module_name name) : sc_module(name), mVcdFile(0) {
    grp_mult_accel_core_fu_58 = new mult_accel_core("grp_mult_accel_core_fu_58");
    grp_mult_accel_core_fu_58->ap_clk(ap_clk);
    grp_mult_accel_core_fu_58->ap_rst(ap_rst);
    grp_mult_accel_core_fu_58->ap_start(grp_mult_accel_core_fu_58_ap_start);
    grp_mult_accel_core_fu_58->ap_done(grp_mult_accel_core_fu_58_ap_done);
    grp_mult_accel_core_fu_58->ap_idle(grp_mult_accel_core_fu_58_ap_idle);
    grp_mult_accel_core_fu_58->ap_ready(grp_mult_accel_core_fu_58_ap_ready);
    grp_mult_accel_core_fu_58->in_stream_data_V_dout(in_stream_data_V_dout);
    grp_mult_accel_core_fu_58->in_stream_data_V_empty_n(in_stream_data_V_empty_n);
    grp_mult_accel_core_fu_58->in_stream_data_V_read(grp_mult_accel_core_fu_58_in_stream_data_V_read);
    grp_mult_accel_core_fu_58->in_stream_keep_V_dout(in_stream_keep_V_dout);
    grp_mult_accel_core_fu_58->in_stream_keep_V_empty_n(in_stream_keep_V_empty_n);
    grp_mult_accel_core_fu_58->in_stream_keep_V_read(grp_mult_accel_core_fu_58_in_stream_keep_V_read);
    grp_mult_accel_core_fu_58->in_stream_strb_V_dout(in_stream_strb_V_dout);
    grp_mult_accel_core_fu_58->in_stream_strb_V_empty_n(in_stream_strb_V_empty_n);
    grp_mult_accel_core_fu_58->in_stream_strb_V_read(grp_mult_accel_core_fu_58_in_stream_strb_V_read);
    grp_mult_accel_core_fu_58->in_stream_user_V_dout(in_stream_user_V_dout);
    grp_mult_accel_core_fu_58->in_stream_user_V_empty_n(in_stream_user_V_empty_n);
    grp_mult_accel_core_fu_58->in_stream_user_V_read(grp_mult_accel_core_fu_58_in_stream_user_V_read);
    grp_mult_accel_core_fu_58->in_stream_last_V_dout(in_stream_last_V_dout);
    grp_mult_accel_core_fu_58->in_stream_last_V_empty_n(in_stream_last_V_empty_n);
    grp_mult_accel_core_fu_58->in_stream_last_V_read(grp_mult_accel_core_fu_58_in_stream_last_V_read);
    grp_mult_accel_core_fu_58->in_stream_id_V_dout(in_stream_id_V_dout);
    grp_mult_accel_core_fu_58->in_stream_id_V_empty_n(in_stream_id_V_empty_n);
    grp_mult_accel_core_fu_58->in_stream_id_V_read(grp_mult_accel_core_fu_58_in_stream_id_V_read);
    grp_mult_accel_core_fu_58->in_stream_dest_V_dout(in_stream_dest_V_dout);
    grp_mult_accel_core_fu_58->in_stream_dest_V_empty_n(in_stream_dest_V_empty_n);
    grp_mult_accel_core_fu_58->in_stream_dest_V_read(grp_mult_accel_core_fu_58_in_stream_dest_V_read);
    grp_mult_accel_core_fu_58->out_stream_data_V_din(grp_mult_accel_core_fu_58_out_stream_data_V_din);
    grp_mult_accel_core_fu_58->out_stream_data_V_full_n(out_stream_data_V_full_n);
    grp_mult_accel_core_fu_58->out_stream_data_V_write(grp_mult_accel_core_fu_58_out_stream_data_V_write);
    grp_mult_accel_core_fu_58->out_stream_keep_V_din(grp_mult_accel_core_fu_58_out_stream_keep_V_din);
    grp_mult_accel_core_fu_58->out_stream_keep_V_full_n(out_stream_keep_V_full_n);
    grp_mult_accel_core_fu_58->out_stream_keep_V_write(grp_mult_accel_core_fu_58_out_stream_keep_V_write);
    grp_mult_accel_core_fu_58->out_stream_strb_V_din(grp_mult_accel_core_fu_58_out_stream_strb_V_din);
    grp_mult_accel_core_fu_58->out_stream_strb_V_full_n(out_stream_strb_V_full_n);
    grp_mult_accel_core_fu_58->out_stream_strb_V_write(grp_mult_accel_core_fu_58_out_stream_strb_V_write);
    grp_mult_accel_core_fu_58->out_stream_user_V_din(grp_mult_accel_core_fu_58_out_stream_user_V_din);
    grp_mult_accel_core_fu_58->out_stream_user_V_full_n(out_stream_user_V_full_n);
    grp_mult_accel_core_fu_58->out_stream_user_V_write(grp_mult_accel_core_fu_58_out_stream_user_V_write);
    grp_mult_accel_core_fu_58->out_stream_last_V_din(grp_mult_accel_core_fu_58_out_stream_last_V_din);
    grp_mult_accel_core_fu_58->out_stream_last_V_full_n(out_stream_last_V_full_n);
    grp_mult_accel_core_fu_58->out_stream_last_V_write(grp_mult_accel_core_fu_58_out_stream_last_V_write);
    grp_mult_accel_core_fu_58->out_stream_id_V_din(grp_mult_accel_core_fu_58_out_stream_id_V_din);
    grp_mult_accel_core_fu_58->out_stream_id_V_full_n(out_stream_id_V_full_n);
    grp_mult_accel_core_fu_58->out_stream_id_V_write(grp_mult_accel_core_fu_58_out_stream_id_V_write);
    grp_mult_accel_core_fu_58->out_stream_dest_V_din(grp_mult_accel_core_fu_58_out_stream_dest_V_din);
    grp_mult_accel_core_fu_58->out_stream_dest_V_full_n(out_stream_dest_V_full_n);
    grp_mult_accel_core_fu_58->out_stream_dest_V_write(grp_mult_accel_core_fu_58_out_stream_dest_V_write);

    SC_METHOD(thread_ap_clk_no_reset_);
    dont_initialize();
    sensitive << ( ap_clk.pos() );

    SC_METHOD(thread_ap_CS_fsm_state1);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state2);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_done);
    sensitive << ( grp_mult_accel_core_fu_58_ap_done );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_ap_idle);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );

    SC_METHOD(thread_ap_ready);
    sensitive << ( grp_mult_accel_core_fu_58_ap_done );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_grp_mult_accel_core_fu_58_ap_start);
    sensitive << ( grp_mult_accel_core_fu_58_ap_start_reg );

    SC_METHOD(thread_in_stream_data_V_read);
    sensitive << ( grp_mult_accel_core_fu_58_in_stream_data_V_read );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_in_stream_dest_V_read);
    sensitive << ( grp_mult_accel_core_fu_58_in_stream_dest_V_read );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_in_stream_id_V_read);
    sensitive << ( grp_mult_accel_core_fu_58_in_stream_id_V_read );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_in_stream_keep_V_read);
    sensitive << ( grp_mult_accel_core_fu_58_in_stream_keep_V_read );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_in_stream_last_V_read);
    sensitive << ( grp_mult_accel_core_fu_58_in_stream_last_V_read );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_in_stream_strb_V_read);
    sensitive << ( grp_mult_accel_core_fu_58_in_stream_strb_V_read );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_in_stream_user_V_read);
    sensitive << ( grp_mult_accel_core_fu_58_in_stream_user_V_read );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_data_V_din);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_data_V_din );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_data_V_write);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_data_V_write );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_dest_V_din);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_dest_V_din );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_dest_V_write);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_dest_V_write );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_id_V_din);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_id_V_din );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_id_V_write);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_id_V_write );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_keep_V_din);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_keep_V_din );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_keep_V_write);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_keep_V_write );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_last_V_din);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_last_V_din );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_last_V_write);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_last_V_write );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_strb_V_din);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_strb_V_din );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_strb_V_write);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_strb_V_write );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_user_V_din);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_user_V_din );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_out_stream_user_V_write);
    sensitive << ( grp_mult_accel_core_fu_58_out_stream_user_V_write );
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_ap_NS_fsm);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( grp_mult_accel_core_fu_58_ap_done );
    sensitive << ( ap_CS_fsm_state2 );

    SC_THREAD(thread_hdltv_gen);
    sensitive << ( ap_clk.pos() );

    ap_CS_fsm = "01";
    grp_mult_accel_core_fu_58_ap_start_reg = SC_LOGIC_0;
    static int apTFileNum = 0;
    stringstream apTFilenSS;
    apTFilenSS << "mult_accel_core_call_sc_trace_" << apTFileNum ++;
    string apTFn = apTFilenSS.str();
    mVcdFile = sc_create_vcd_trace_file(apTFn.c_str());
    mVcdFile->set_time_unit(1, SC_PS);
    if (1) {
#ifdef __HLS_TRACE_LEVEL_PORT__
    sc_trace(mVcdFile, ap_clk, "(port)ap_clk");
    sc_trace(mVcdFile, ap_rst, "(port)ap_rst");
    sc_trace(mVcdFile, ap_start, "(port)ap_start");
    sc_trace(mVcdFile, ap_done, "(port)ap_done");
    sc_trace(mVcdFile, ap_idle, "(port)ap_idle");
    sc_trace(mVcdFile, ap_ready, "(port)ap_ready");
    sc_trace(mVcdFile, in_stream_data_V_dout, "(port)in_stream_data_V_dout");
    sc_trace(mVcdFile, in_stream_data_V_empty_n, "(port)in_stream_data_V_empty_n");
    sc_trace(mVcdFile, in_stream_data_V_read, "(port)in_stream_data_V_read");
    sc_trace(mVcdFile, in_stream_keep_V_dout, "(port)in_stream_keep_V_dout");
    sc_trace(mVcdFile, in_stream_keep_V_empty_n, "(port)in_stream_keep_V_empty_n");
    sc_trace(mVcdFile, in_stream_keep_V_read, "(port)in_stream_keep_V_read");
    sc_trace(mVcdFile, in_stream_strb_V_dout, "(port)in_stream_strb_V_dout");
    sc_trace(mVcdFile, in_stream_strb_V_empty_n, "(port)in_stream_strb_V_empty_n");
    sc_trace(mVcdFile, in_stream_strb_V_read, "(port)in_stream_strb_V_read");
    sc_trace(mVcdFile, in_stream_user_V_dout, "(port)in_stream_user_V_dout");
    sc_trace(mVcdFile, in_stream_user_V_empty_n, "(port)in_stream_user_V_empty_n");
    sc_trace(mVcdFile, in_stream_user_V_read, "(port)in_stream_user_V_read");
    sc_trace(mVcdFile, in_stream_last_V_dout, "(port)in_stream_last_V_dout");
    sc_trace(mVcdFile, in_stream_last_V_empty_n, "(port)in_stream_last_V_empty_n");
    sc_trace(mVcdFile, in_stream_last_V_read, "(port)in_stream_last_V_read");
    sc_trace(mVcdFile, in_stream_id_V_dout, "(port)in_stream_id_V_dout");
    sc_trace(mVcdFile, in_stream_id_V_empty_n, "(port)in_stream_id_V_empty_n");
    sc_trace(mVcdFile, in_stream_id_V_read, "(port)in_stream_id_V_read");
    sc_trace(mVcdFile, in_stream_dest_V_dout, "(port)in_stream_dest_V_dout");
    sc_trace(mVcdFile, in_stream_dest_V_empty_n, "(port)in_stream_dest_V_empty_n");
    sc_trace(mVcdFile, in_stream_dest_V_read, "(port)in_stream_dest_V_read");
    sc_trace(mVcdFile, out_stream_data_V_din, "(port)out_stream_data_V_din");
    sc_trace(mVcdFile, out_stream_data_V_full_n, "(port)out_stream_data_V_full_n");
    sc_trace(mVcdFile, out_stream_data_V_write, "(port)out_stream_data_V_write");
    sc_trace(mVcdFile, out_stream_keep_V_din, "(port)out_stream_keep_V_din");
    sc_trace(mVcdFile, out_stream_keep_V_full_n, "(port)out_stream_keep_V_full_n");
    sc_trace(mVcdFile, out_stream_keep_V_write, "(port)out_stream_keep_V_write");
    sc_trace(mVcdFile, out_stream_strb_V_din, "(port)out_stream_strb_V_din");
    sc_trace(mVcdFile, out_stream_strb_V_full_n, "(port)out_stream_strb_V_full_n");
    sc_trace(mVcdFile, out_stream_strb_V_write, "(port)out_stream_strb_V_write");
    sc_trace(mVcdFile, out_stream_user_V_din, "(port)out_stream_user_V_din");
    sc_trace(mVcdFile, out_stream_user_V_full_n, "(port)out_stream_user_V_full_n");
    sc_trace(mVcdFile, out_stream_user_V_write, "(port)out_stream_user_V_write");
    sc_trace(mVcdFile, out_stream_last_V_din, "(port)out_stream_last_V_din");
    sc_trace(mVcdFile, out_stream_last_V_full_n, "(port)out_stream_last_V_full_n");
    sc_trace(mVcdFile, out_stream_last_V_write, "(port)out_stream_last_V_write");
    sc_trace(mVcdFile, out_stream_id_V_din, "(port)out_stream_id_V_din");
    sc_trace(mVcdFile, out_stream_id_V_full_n, "(port)out_stream_id_V_full_n");
    sc_trace(mVcdFile, out_stream_id_V_write, "(port)out_stream_id_V_write");
    sc_trace(mVcdFile, out_stream_dest_V_din, "(port)out_stream_dest_V_din");
    sc_trace(mVcdFile, out_stream_dest_V_full_n, "(port)out_stream_dest_V_full_n");
    sc_trace(mVcdFile, out_stream_dest_V_write, "(port)out_stream_dest_V_write");
#endif
#ifdef __HLS_TRACE_LEVEL_INT__
    sc_trace(mVcdFile, ap_CS_fsm, "ap_CS_fsm");
    sc_trace(mVcdFile, ap_CS_fsm_state1, "ap_CS_fsm_state1");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_ap_start, "grp_mult_accel_core_fu_58_ap_start");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_ap_done, "grp_mult_accel_core_fu_58_ap_done");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_ap_idle, "grp_mult_accel_core_fu_58_ap_idle");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_ap_ready, "grp_mult_accel_core_fu_58_ap_ready");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_in_stream_data_V_read, "grp_mult_accel_core_fu_58_in_stream_data_V_read");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_in_stream_keep_V_read, "grp_mult_accel_core_fu_58_in_stream_keep_V_read");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_in_stream_strb_V_read, "grp_mult_accel_core_fu_58_in_stream_strb_V_read");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_in_stream_user_V_read, "grp_mult_accel_core_fu_58_in_stream_user_V_read");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_in_stream_last_V_read, "grp_mult_accel_core_fu_58_in_stream_last_V_read");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_in_stream_id_V_read, "grp_mult_accel_core_fu_58_in_stream_id_V_read");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_in_stream_dest_V_read, "grp_mult_accel_core_fu_58_in_stream_dest_V_read");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_data_V_din, "grp_mult_accel_core_fu_58_out_stream_data_V_din");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_data_V_write, "grp_mult_accel_core_fu_58_out_stream_data_V_write");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_keep_V_din, "grp_mult_accel_core_fu_58_out_stream_keep_V_din");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_keep_V_write, "grp_mult_accel_core_fu_58_out_stream_keep_V_write");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_strb_V_din, "grp_mult_accel_core_fu_58_out_stream_strb_V_din");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_strb_V_write, "grp_mult_accel_core_fu_58_out_stream_strb_V_write");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_user_V_din, "grp_mult_accel_core_fu_58_out_stream_user_V_din");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_user_V_write, "grp_mult_accel_core_fu_58_out_stream_user_V_write");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_last_V_din, "grp_mult_accel_core_fu_58_out_stream_last_V_din");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_last_V_write, "grp_mult_accel_core_fu_58_out_stream_last_V_write");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_id_V_din, "grp_mult_accel_core_fu_58_out_stream_id_V_din");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_id_V_write, "grp_mult_accel_core_fu_58_out_stream_id_V_write");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_dest_V_din, "grp_mult_accel_core_fu_58_out_stream_dest_V_din");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_out_stream_dest_V_write, "grp_mult_accel_core_fu_58_out_stream_dest_V_write");
    sc_trace(mVcdFile, grp_mult_accel_core_fu_58_ap_start_reg, "grp_mult_accel_core_fu_58_ap_start_reg");
    sc_trace(mVcdFile, ap_CS_fsm_state2, "ap_CS_fsm_state2");
    sc_trace(mVcdFile, ap_NS_fsm, "ap_NS_fsm");
#endif

    }
    mHdltvinHandle.open("mult_accel_core_call.hdltvin.dat");
    mHdltvoutHandle.open("mult_accel_core_call.hdltvout.dat");
}

mult_accel_core_call::~mult_accel_core_call() {
    if (mVcdFile) 
        sc_close_vcd_trace_file(mVcdFile);

    mHdltvinHandle << "] " << endl;
    mHdltvoutHandle << "] " << endl;
    mHdltvinHandle.close();
    mHdltvoutHandle.close();
    delete grp_mult_accel_core_fu_58;
}

void mult_accel_core_call::thread_ap_clk_no_reset_() {
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_CS_fsm = ap_ST_fsm_state1;
    } else {
        ap_CS_fsm = ap_NS_fsm.read();
    }
    if ( ap_rst.read() == ap_const_logic_1) {
        grp_mult_accel_core_fu_58_ap_start_reg = ap_const_logic_0;
    } else {
        if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
             esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
            grp_mult_accel_core_fu_58_ap_start_reg = ap_const_logic_1;
        } else if (esl_seteq<1,1,1>(ap_const_logic_1, grp_mult_accel_core_fu_58_ap_ready.read())) {
            grp_mult_accel_core_fu_58_ap_start_reg = ap_const_logic_0;
        }
    }
}

void mult_accel_core_call::thread_ap_CS_fsm_state1() {
    ap_CS_fsm_state1 = ap_CS_fsm.read()[0];
}

void mult_accel_core_call::thread_ap_CS_fsm_state2() {
    ap_CS_fsm_state2 = ap_CS_fsm.read()[1];
}

void mult_accel_core_call::thread_ap_done() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(grp_mult_accel_core_fu_58_ap_done.read(), ap_const_logic_1))) {
        ap_done = ap_const_logic_1;
    } else {
        ap_done = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_ap_idle() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()))) {
        ap_idle = ap_const_logic_1;
    } else {
        ap_idle = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_ap_ready() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(grp_mult_accel_core_fu_58_ap_done.read(), ap_const_logic_1))) {
        ap_ready = ap_const_logic_1;
    } else {
        ap_ready = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_grp_mult_accel_core_fu_58_ap_start() {
    grp_mult_accel_core_fu_58_ap_start = grp_mult_accel_core_fu_58_ap_start_reg.read();
}

void mult_accel_core_call::thread_in_stream_data_V_read() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        in_stream_data_V_read = grp_mult_accel_core_fu_58_in_stream_data_V_read.read();
    } else {
        in_stream_data_V_read = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_in_stream_dest_V_read() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        in_stream_dest_V_read = grp_mult_accel_core_fu_58_in_stream_dest_V_read.read();
    } else {
        in_stream_dest_V_read = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_in_stream_id_V_read() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        in_stream_id_V_read = grp_mult_accel_core_fu_58_in_stream_id_V_read.read();
    } else {
        in_stream_id_V_read = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_in_stream_keep_V_read() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        in_stream_keep_V_read = grp_mult_accel_core_fu_58_in_stream_keep_V_read.read();
    } else {
        in_stream_keep_V_read = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_in_stream_last_V_read() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        in_stream_last_V_read = grp_mult_accel_core_fu_58_in_stream_last_V_read.read();
    } else {
        in_stream_last_V_read = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_in_stream_strb_V_read() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        in_stream_strb_V_read = grp_mult_accel_core_fu_58_in_stream_strb_V_read.read();
    } else {
        in_stream_strb_V_read = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_in_stream_user_V_read() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        in_stream_user_V_read = grp_mult_accel_core_fu_58_in_stream_user_V_read.read();
    } else {
        in_stream_user_V_read = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_out_stream_data_V_din() {
    out_stream_data_V_din = grp_mult_accel_core_fu_58_out_stream_data_V_din.read();
}

void mult_accel_core_call::thread_out_stream_data_V_write() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        out_stream_data_V_write = grp_mult_accel_core_fu_58_out_stream_data_V_write.read();
    } else {
        out_stream_data_V_write = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_out_stream_dest_V_din() {
    out_stream_dest_V_din = grp_mult_accel_core_fu_58_out_stream_dest_V_din.read();
}

void mult_accel_core_call::thread_out_stream_dest_V_write() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        out_stream_dest_V_write = grp_mult_accel_core_fu_58_out_stream_dest_V_write.read();
    } else {
        out_stream_dest_V_write = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_out_stream_id_V_din() {
    out_stream_id_V_din = grp_mult_accel_core_fu_58_out_stream_id_V_din.read();
}

void mult_accel_core_call::thread_out_stream_id_V_write() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        out_stream_id_V_write = grp_mult_accel_core_fu_58_out_stream_id_V_write.read();
    } else {
        out_stream_id_V_write = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_out_stream_keep_V_din() {
    out_stream_keep_V_din = grp_mult_accel_core_fu_58_out_stream_keep_V_din.read();
}

void mult_accel_core_call::thread_out_stream_keep_V_write() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        out_stream_keep_V_write = grp_mult_accel_core_fu_58_out_stream_keep_V_write.read();
    } else {
        out_stream_keep_V_write = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_out_stream_last_V_din() {
    out_stream_last_V_din = grp_mult_accel_core_fu_58_out_stream_last_V_din.read();
}

void mult_accel_core_call::thread_out_stream_last_V_write() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        out_stream_last_V_write = grp_mult_accel_core_fu_58_out_stream_last_V_write.read();
    } else {
        out_stream_last_V_write = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_out_stream_strb_V_din() {
    out_stream_strb_V_din = grp_mult_accel_core_fu_58_out_stream_strb_V_din.read();
}

void mult_accel_core_call::thread_out_stream_strb_V_write() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        out_stream_strb_V_write = grp_mult_accel_core_fu_58_out_stream_strb_V_write.read();
    } else {
        out_stream_strb_V_write = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_out_stream_user_V_din() {
    out_stream_user_V_din = grp_mult_accel_core_fu_58_out_stream_user_V_din.read();
}

void mult_accel_core_call::thread_out_stream_user_V_write() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        out_stream_user_V_write = grp_mult_accel_core_fu_58_out_stream_user_V_write.read();
    } else {
        out_stream_user_V_write = ap_const_logic_0;
    }
}

void mult_accel_core_call::thread_ap_NS_fsm() {
    switch (ap_CS_fsm.read().to_uint64()) {
        case 1 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
                ap_NS_fsm = ap_ST_fsm_state2;
            } else {
                ap_NS_fsm = ap_ST_fsm_state1;
            }
            break;
        case 2 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && esl_seteq<1,1,1>(grp_mult_accel_core_fu_58_ap_done.read(), ap_const_logic_1))) {
                ap_NS_fsm = ap_ST_fsm_state1;
            } else {
                ap_NS_fsm = ap_ST_fsm_state2;
            }
            break;
        default : 
            ap_NS_fsm = "XX";
            break;
    }
}

void mult_accel_core_call::thread_hdltv_gen() {
    const char* dump_tv = std::getenv("AP_WRITE_TV");
    if (!(dump_tv && string(dump_tv) == "on")) return;

    wait();

    mHdltvinHandle << "[ " << endl;
    mHdltvoutHandle << "[ " << endl;
    int ap_cycleNo = 0;
    while (1) {
        wait();
        const char* mComma = ap_cycleNo == 0 ? " " : ", " ;
        mHdltvinHandle << mComma << "{"  <<  " \"ap_rst\" :  \"" << ap_rst.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"ap_start\" :  \"" << ap_start.read() << "\" ";
        mHdltvoutHandle << mComma << "{"  <<  " \"ap_done\" :  \"" << ap_done.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"ap_idle\" :  \"" << ap_idle.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"ap_ready\" :  \"" << ap_ready.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_data_V_dout\" :  \"" << in_stream_data_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_data_V_empty_n\" :  \"" << in_stream_data_V_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"in_stream_data_V_read\" :  \"" << in_stream_data_V_read.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_keep_V_dout\" :  \"" << in_stream_keep_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_keep_V_empty_n\" :  \"" << in_stream_keep_V_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"in_stream_keep_V_read\" :  \"" << in_stream_keep_V_read.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_strb_V_dout\" :  \"" << in_stream_strb_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_strb_V_empty_n\" :  \"" << in_stream_strb_V_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"in_stream_strb_V_read\" :  \"" << in_stream_strb_V_read.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_user_V_dout\" :  \"" << in_stream_user_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_user_V_empty_n\" :  \"" << in_stream_user_V_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"in_stream_user_V_read\" :  \"" << in_stream_user_V_read.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_last_V_dout\" :  \"" << in_stream_last_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_last_V_empty_n\" :  \"" << in_stream_last_V_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"in_stream_last_V_read\" :  \"" << in_stream_last_V_read.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_id_V_dout\" :  \"" << in_stream_id_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_id_V_empty_n\" :  \"" << in_stream_id_V_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"in_stream_id_V_read\" :  \"" << in_stream_id_V_read.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_dest_V_dout\" :  \"" << in_stream_dest_V_dout.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"in_stream_dest_V_empty_n\" :  \"" << in_stream_dest_V_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"in_stream_dest_V_read\" :  \"" << in_stream_dest_V_read.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_data_V_din\" :  \"" << out_stream_data_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"out_stream_data_V_full_n\" :  \"" << out_stream_data_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_data_V_write\" :  \"" << out_stream_data_V_write.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_keep_V_din\" :  \"" << out_stream_keep_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"out_stream_keep_V_full_n\" :  \"" << out_stream_keep_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_keep_V_write\" :  \"" << out_stream_keep_V_write.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_strb_V_din\" :  \"" << out_stream_strb_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"out_stream_strb_V_full_n\" :  \"" << out_stream_strb_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_strb_V_write\" :  \"" << out_stream_strb_V_write.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_user_V_din\" :  \"" << out_stream_user_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"out_stream_user_V_full_n\" :  \"" << out_stream_user_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_user_V_write\" :  \"" << out_stream_user_V_write.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_last_V_din\" :  \"" << out_stream_last_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"out_stream_last_V_full_n\" :  \"" << out_stream_last_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_last_V_write\" :  \"" << out_stream_last_V_write.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_id_V_din\" :  \"" << out_stream_id_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"out_stream_id_V_full_n\" :  \"" << out_stream_id_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_id_V_write\" :  \"" << out_stream_id_V_write.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_dest_V_din\" :  \"" << out_stream_dest_V_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"out_stream_dest_V_full_n\" :  \"" << out_stream_dest_V_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"out_stream_dest_V_write\" :  \"" << out_stream_dest_V_write.read() << "\" ";
        mHdltvinHandle << "}" << std::endl;
        mHdltvoutHandle << "}" << std::endl;
        ap_cycleNo++;
    }
}

}

