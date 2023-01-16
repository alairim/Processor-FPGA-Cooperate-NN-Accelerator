// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#include "vector_multiply_hw.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

const sc_logic vector_multiply_hw::ap_const_logic_1 = sc_dt::Log_1;
const sc_logic vector_multiply_hw::ap_const_logic_0 = sc_dt::Log_0;
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state1 = "1";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state2 = "10";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state3 = "100";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state4 = "1000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state5 = "10000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state6 = "100000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state7 = "1000000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state8 = "10000000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state9 = "100000000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state10 = "1000000000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state11 = "10000000000";
const sc_lv<12> vector_multiply_hw::ap_ST_fsm_state12 = "100000000000";
const sc_lv<32> vector_multiply_hw::ap_const_lv32_0 = "00000000000000000000000000000000";
const sc_lv<32> vector_multiply_hw::ap_const_lv32_1 = "1";
const sc_lv<32> vector_multiply_hw::ap_const_lv32_2 = "10";
const sc_lv<32> vector_multiply_hw::ap_const_lv32_6 = "110";
const sc_lv<32> vector_multiply_hw::ap_const_lv32_B = "1011";
const sc_lv<10> vector_multiply_hw::ap_const_lv10_0 = "0000000000";
const sc_lv<32> vector_multiply_hw::ap_const_lv32_7 = "111";
const sc_lv<32> vector_multiply_hw::ap_const_lv32_3 = "11";
const sc_lv<10> vector_multiply_hw::ap_const_lv10_310 = "1100010000";
const sc_lv<10> vector_multiply_hw::ap_const_lv10_1 = "1";
const sc_lv<1> vector_multiply_hw::ap_const_lv1_1 = "1";
const bool vector_multiply_hw::ap_const_boolean_1 = true;

vector_multiply_hw::vector_multiply_hw(sc_module_name name) : sc_module(name), mVcdFile(0) {
    mult_accel_core_cbkb_U8 = new mult_accel_core_cbkb<1,5,32,32,32>("mult_accel_core_cbkb_U8");
    mult_accel_core_cbkb_U8->clk(ap_clk);
    mult_accel_core_cbkb_U8->reset(ap_rst);
    mult_accel_core_cbkb_U8->din0(out_write_assign_reg_44);
    mult_accel_core_cbkb_U8->din1(tmp_1_reg_122);
    mult_accel_core_cbkb_U8->ce(ap_var_for_const0);
    mult_accel_core_cbkb_U8->dout(grp_fu_67_p2);
    mult_accel_core_ccud_U9 = new mult_accel_core_ccud<1,4,32,32,32>("mult_accel_core_ccud_U9");
    mult_accel_core_ccud_U9->clk(ap_clk);
    mult_accel_core_ccud_U9->reset(ap_rst);
    mult_accel_core_ccud_U9->din0(a_load_reg_112);
    mult_accel_core_ccud_U9->din1(b_load_reg_117);
    mult_accel_core_ccud_U9->ce(ap_var_for_const0);
    mult_accel_core_ccud_U9->dout(grp_fu_72_p2);

    SC_METHOD(thread_ap_clk_no_reset_);
    dont_initialize();
    sensitive << ( ap_clk.pos() );

    SC_METHOD(thread_a_address0);
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( tmp_fu_88_p1 );

    SC_METHOD(thread_a_ce0);
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_ap_CS_fsm_state1);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state12);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state2);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state3);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state4);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state7);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state8);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_done);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_76_p2 );

    SC_METHOD(thread_ap_idle);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );

    SC_METHOD(thread_ap_ready);
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_76_p2 );

    SC_METHOD(thread_ap_return);
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_76_p2 );
    sensitive << ( out_write_assign_reg_44 );
    sensitive << ( ap_return_preg );

    SC_METHOD(thread_b_address0);
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( tmp_fu_88_p1 );

    SC_METHOD(thread_b_ce0);
    sensitive << ( ap_CS_fsm_state2 );

    SC_METHOD(thread_exitcond_fu_76_p2);
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( i_reg_56 );

    SC_METHOD(thread_i_1_fu_82_p2);
    sensitive << ( i_reg_56 );

    SC_METHOD(thread_tmp_fu_88_p1);
    sensitive << ( i_reg_56 );

    SC_METHOD(thread_ap_NS_fsm);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_76_p2 );

    SC_THREAD(thread_ap_var_for_const0);

    ap_CS_fsm = "000000000001";
    ap_return_preg = "00000000000000000000000000000000";
    static int apTFileNum = 0;
    stringstream apTFilenSS;
    apTFilenSS << "vector_multiply_hw_sc_trace_" << apTFileNum ++;
    string apTFn = apTFilenSS.str();
    mVcdFile = sc_create_vcd_trace_file(apTFn.c_str());
    mVcdFile->set_time_unit(1, SC_PS);
    if (1) {
#ifdef __HLS_TRACE_LEVEL_PORT_HIER__
    sc_trace(mVcdFile, ap_clk, "(port)ap_clk");
    sc_trace(mVcdFile, ap_rst, "(port)ap_rst");
    sc_trace(mVcdFile, ap_start, "(port)ap_start");
    sc_trace(mVcdFile, ap_done, "(port)ap_done");
    sc_trace(mVcdFile, ap_idle, "(port)ap_idle");
    sc_trace(mVcdFile, ap_ready, "(port)ap_ready");
    sc_trace(mVcdFile, a_address0, "(port)a_address0");
    sc_trace(mVcdFile, a_ce0, "(port)a_ce0");
    sc_trace(mVcdFile, a_q0, "(port)a_q0");
    sc_trace(mVcdFile, b_address0, "(port)b_address0");
    sc_trace(mVcdFile, b_ce0, "(port)b_ce0");
    sc_trace(mVcdFile, b_q0, "(port)b_q0");
    sc_trace(mVcdFile, ap_return, "(port)ap_return");
#endif
#ifdef __HLS_TRACE_LEVEL_INT__
    sc_trace(mVcdFile, ap_CS_fsm, "ap_CS_fsm");
    sc_trace(mVcdFile, ap_CS_fsm_state1, "ap_CS_fsm_state1");
    sc_trace(mVcdFile, i_1_fu_82_p2, "i_1_fu_82_p2");
    sc_trace(mVcdFile, i_1_reg_97, "i_1_reg_97");
    sc_trace(mVcdFile, ap_CS_fsm_state2, "ap_CS_fsm_state2");
    sc_trace(mVcdFile, exitcond_fu_76_p2, "exitcond_fu_76_p2");
    sc_trace(mVcdFile, a_load_reg_112, "a_load_reg_112");
    sc_trace(mVcdFile, ap_CS_fsm_state3, "ap_CS_fsm_state3");
    sc_trace(mVcdFile, b_load_reg_117, "b_load_reg_117");
    sc_trace(mVcdFile, grp_fu_72_p2, "grp_fu_72_p2");
    sc_trace(mVcdFile, tmp_1_reg_122, "tmp_1_reg_122");
    sc_trace(mVcdFile, ap_CS_fsm_state7, "ap_CS_fsm_state7");
    sc_trace(mVcdFile, grp_fu_67_p2, "grp_fu_67_p2");
    sc_trace(mVcdFile, ap_CS_fsm_state12, "ap_CS_fsm_state12");
    sc_trace(mVcdFile, out_write_assign_reg_44, "out_write_assign_reg_44");
    sc_trace(mVcdFile, i_reg_56, "i_reg_56");
    sc_trace(mVcdFile, tmp_fu_88_p1, "tmp_fu_88_p1");
    sc_trace(mVcdFile, ap_CS_fsm_state8, "ap_CS_fsm_state8");
    sc_trace(mVcdFile, ap_CS_fsm_state4, "ap_CS_fsm_state4");
    sc_trace(mVcdFile, ap_return_preg, "ap_return_preg");
    sc_trace(mVcdFile, ap_NS_fsm, "ap_NS_fsm");
#endif

    }
}

vector_multiply_hw::~vector_multiply_hw() {
    if (mVcdFile) 
        sc_close_vcd_trace_file(mVcdFile);

    delete mult_accel_core_cbkb_U8;
    delete mult_accel_core_ccud_U9;
}

void vector_multiply_hw::thread_ap_var_for_const0() {
    ap_var_for_const0 = ap_const_logic_1;
}

void vector_multiply_hw::thread_ap_clk_no_reset_() {
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_CS_fsm = ap_ST_fsm_state1;
    } else {
        ap_CS_fsm = ap_NS_fsm.read();
    }
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_return_preg = ap_const_lv32_0;
    } else {
        if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
             esl_seteq<1,1,1>(exitcond_fu_76_p2.read(), ap_const_lv1_1))) {
            ap_return_preg = out_write_assign_reg_44.read();
        }
    }
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state12.read())) {
        i_reg_56 = i_1_reg_97.read();
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
                esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
        i_reg_56 = ap_const_lv10_0;
    }
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state12.read())) {
        out_write_assign_reg_44 = grp_fu_67_p2.read();
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
                esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
        out_write_assign_reg_44 = ap_const_lv32_0;
    }
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state3.read())) {
        a_load_reg_112 = a_q0.read();
        b_load_reg_117 = b_q0.read();
    }
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        i_1_reg_97 = i_1_fu_82_p2.read();
    }
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state7.read())) {
        tmp_1_reg_122 = grp_fu_72_p2.read();
    }
}

void vector_multiply_hw::thread_a_address0() {
    a_address0 =  (sc_lv<10>) (tmp_fu_88_p1.read());
}

void vector_multiply_hw::thread_a_ce0() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        a_ce0 = ap_const_logic_1;
    } else {
        a_ce0 = ap_const_logic_0;
    }
}

void vector_multiply_hw::thread_ap_CS_fsm_state1() {
    ap_CS_fsm_state1 = ap_CS_fsm.read()[0];
}

void vector_multiply_hw::thread_ap_CS_fsm_state12() {
    ap_CS_fsm_state12 = ap_CS_fsm.read()[11];
}

void vector_multiply_hw::thread_ap_CS_fsm_state2() {
    ap_CS_fsm_state2 = ap_CS_fsm.read()[1];
}

void vector_multiply_hw::thread_ap_CS_fsm_state3() {
    ap_CS_fsm_state3 = ap_CS_fsm.read()[2];
}

void vector_multiply_hw::thread_ap_CS_fsm_state4() {
    ap_CS_fsm_state4 = ap_CS_fsm.read()[3];
}

void vector_multiply_hw::thread_ap_CS_fsm_state7() {
    ap_CS_fsm_state7 = ap_CS_fsm.read()[6];
}

void vector_multiply_hw::thread_ap_CS_fsm_state8() {
    ap_CS_fsm_state8 = ap_CS_fsm.read()[7];
}

void vector_multiply_hw::thread_ap_done() {
    if (((esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) && 
          esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read())) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
          esl_seteq<1,1,1>(exitcond_fu_76_p2.read(), ap_const_lv1_1)))) {
        ap_done = ap_const_logic_1;
    } else {
        ap_done = ap_const_logic_0;
    }
}

void vector_multiply_hw::thread_ap_idle() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()))) {
        ap_idle = ap_const_logic_1;
    } else {
        ap_idle = ap_const_logic_0;
    }
}

void vector_multiply_hw::thread_ap_ready() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(exitcond_fu_76_p2.read(), ap_const_lv1_1))) {
        ap_ready = ap_const_logic_1;
    } else {
        ap_ready = ap_const_logic_0;
    }
}

void vector_multiply_hw::thread_ap_return() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(exitcond_fu_76_p2.read(), ap_const_lv1_1))) {
        ap_return = out_write_assign_reg_44.read();
    } else {
        ap_return = ap_return_preg.read();
    }
}

void vector_multiply_hw::thread_b_address0() {
    b_address0 =  (sc_lv<10>) (tmp_fu_88_p1.read());
}

void vector_multiply_hw::thread_b_ce0() {
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read())) {
        b_ce0 = ap_const_logic_1;
    } else {
        b_ce0 = ap_const_logic_0;
    }
}

void vector_multiply_hw::thread_exitcond_fu_76_p2() {
    exitcond_fu_76_p2 = (!i_reg_56.read().is_01() || !ap_const_lv10_310.is_01())? sc_lv<1>(): sc_lv<1>(i_reg_56.read() == ap_const_lv10_310);
}

void vector_multiply_hw::thread_i_1_fu_82_p2() {
    i_1_fu_82_p2 = (!i_reg_56.read().is_01() || !ap_const_lv10_1.is_01())? sc_lv<10>(): (sc_biguint<10>(i_reg_56.read()) + sc_biguint<10>(ap_const_lv10_1));
}

void vector_multiply_hw::thread_tmp_fu_88_p1() {
    tmp_fu_88_p1 = esl_zext<64,10>(i_reg_56.read());
}

void vector_multiply_hw::thread_ap_NS_fsm() {
    switch (ap_CS_fsm.read().to_uint64()) {
        case 1 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
                ap_NS_fsm = ap_ST_fsm_state2;
            } else {
                ap_NS_fsm = ap_ST_fsm_state1;
            }
            break;
        case 2 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && esl_seteq<1,1,1>(exitcond_fu_76_p2.read(), ap_const_lv1_1))) {
                ap_NS_fsm = ap_ST_fsm_state1;
            } else {
                ap_NS_fsm = ap_ST_fsm_state3;
            }
            break;
        case 4 : 
            ap_NS_fsm = ap_ST_fsm_state4;
            break;
        case 8 : 
            ap_NS_fsm = ap_ST_fsm_state5;
            break;
        case 16 : 
            ap_NS_fsm = ap_ST_fsm_state6;
            break;
        case 32 : 
            ap_NS_fsm = ap_ST_fsm_state7;
            break;
        case 64 : 
            ap_NS_fsm = ap_ST_fsm_state8;
            break;
        case 128 : 
            ap_NS_fsm = ap_ST_fsm_state9;
            break;
        case 256 : 
            ap_NS_fsm = ap_ST_fsm_state10;
            break;
        case 512 : 
            ap_NS_fsm = ap_ST_fsm_state11;
            break;
        case 1024 : 
            ap_NS_fsm = ap_ST_fsm_state12;
            break;
        case 2048 : 
            ap_NS_fsm = ap_ST_fsm_state2;
            break;
        default : 
            ap_NS_fsm = "XXXXXXXXXXXX";
            break;
    }
}

}
