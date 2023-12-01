// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2019.2.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _dut_HH_
#define _dut_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "softmax_128_s.h"
#include "softmax_128_s_eulbkb.h"

namespace ap_rtl {

struct dut : public sc_module {
    // Port declarations 12
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_in< sc_lv<32> > strm_in_a_V_dout;
    sc_in< sc_logic > strm_in_a_V_empty_n;
    sc_out< sc_logic > strm_in_a_V_read;
    sc_out< sc_lv<32> > strm_out_V_din;
    sc_in< sc_logic > strm_out_V_full_n;
    sc_out< sc_logic > strm_out_V_write;


    // Module declarations
    dut(sc_module_name name);
    SC_HAS_PROCESS(dut);

    ~dut();

    sc_trace_file* mVcdFile;

    ofstream mHdltvinHandle;
    ofstream mHdltvoutHandle;
    softmax_128_s_eulbkb* input1_U;
    softmax_128_s_eulbkb* output_U;
    softmax_128_s* grp_softmax_128_s_fu_111;
    sc_signal< sc_lv<5> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_logic > strm_in_a_V_blk_n;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<1> > icmp_ln14_fu_117_p2;
    sc_signal< sc_logic > strm_out_V_blk_n;
    sc_signal< sc_logic > ap_CS_fsm_state5;
    sc_signal< sc_lv<8> > i_fu_123_p2;
    sc_signal< bool > ap_block_state2;
    sc_signal< sc_lv<8> > i_1_fu_140_p2;
    sc_signal< sc_lv<8> > i_1_reg_162;
    sc_signal< sc_logic > ap_CS_fsm_state4;
    sc_signal< sc_lv<1> > icmp_ln23_fu_134_p2;
    sc_signal< sc_lv<7> > input1_address0;
    sc_signal< sc_logic > input1_ce0;
    sc_signal< sc_logic > input1_we0;
    sc_signal< sc_lv<32> > input1_q0;
    sc_signal< sc_lv<7> > output_address0;
    sc_signal< sc_logic > output_ce0;
    sc_signal< sc_logic > output_we0;
    sc_signal< sc_lv<32> > output_q0;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_ap_start;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_ap_done;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_ap_idle;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_ap_ready;
    sc_signal< sc_lv<7> > grp_softmax_128_s_fu_111_output_layer_address0;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_output_layer_ce0;
    sc_signal< sc_lv<7> > grp_softmax_128_s_fu_111_probability_distribu_address0;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_probability_distribu_ce0;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_probability_distribu_we0;
    sc_signal< sc_lv<32> > grp_softmax_128_s_fu_111_probability_distribu_d0;
    sc_signal< sc_lv<8> > i_0_reg_89;
    sc_signal< sc_lv<8> > i1_0_reg_100;
    sc_signal< sc_logic > ap_CS_fsm_state3;
    sc_signal< sc_logic > grp_softmax_128_s_fu_111_ap_start_reg;
    sc_signal< bool > ap_block_state2_ignore_call0;
    sc_signal< sc_lv<64> > zext_ln16_fu_129_p1;
    sc_signal< sc_lv<64> > zext_ln24_fu_146_p1;
    sc_signal< sc_lv<5> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<5> ap_ST_fsm_state1;
    static const sc_lv<5> ap_ST_fsm_state2;
    static const sc_lv<5> ap_ST_fsm_state3;
    static const sc_lv<5> ap_ST_fsm_state4;
    static const sc_lv<5> ap_ST_fsm_state5;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_4;
    static const sc_lv<32> ap_const_lv32_3;
    static const sc_lv<8> ap_const_lv8_0;
    static const sc_lv<32> ap_const_lv32_2;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<8> ap_const_lv8_80;
    static const sc_lv<8> ap_const_lv8_1;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_clk_no_reset_();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state3();
    void thread_ap_CS_fsm_state4();
    void thread_ap_CS_fsm_state5();
    void thread_ap_block_state2();
    void thread_ap_block_state2_ignore_call0();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_grp_softmax_128_s_fu_111_ap_start();
    void thread_i_1_fu_140_p2();
    void thread_i_fu_123_p2();
    void thread_icmp_ln14_fu_117_p2();
    void thread_icmp_ln23_fu_134_p2();
    void thread_input1_address0();
    void thread_input1_ce0();
    void thread_input1_we0();
    void thread_output_address0();
    void thread_output_ce0();
    void thread_output_we0();
    void thread_strm_in_a_V_blk_n();
    void thread_strm_in_a_V_read();
    void thread_strm_out_V_blk_n();
    void thread_strm_out_V_din();
    void thread_strm_out_V_write();
    void thread_zext_ln16_fu_129_p1();
    void thread_zext_ln24_fu_146_p1();
    void thread_ap_NS_fsm();
    void thread_hdltv_gen();
};

}

using namespace ap_rtl;

#endif
