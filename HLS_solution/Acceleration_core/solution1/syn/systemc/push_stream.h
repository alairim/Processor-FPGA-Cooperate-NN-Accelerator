// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _push_stream_HH_
#define _push_stream_HH_

#include "systemc.h"
#include "AESL_pkg.h"


namespace ap_rtl {

struct push_stream : public sc_module {
    // Port declarations 3
    sc_out< sc_logic > ap_ready;
    sc_in< sc_lv<32> > v_read;
    sc_out< sc_lv<32> > ap_return;


    // Module declarations
    push_stream(sc_module_name name);
    SC_HAS_PROCESS(push_stream);

    ~push_stream();

    sc_trace_file* mVcdFile;

    static const sc_logic ap_const_logic_1;
    static const bool ap_const_boolean_1;
    static const sc_logic ap_const_logic_0;
    // Thread declarations
    void thread_ap_ready();
    void thread_ap_return();
};

}

using namespace ap_rtl;

#endif
