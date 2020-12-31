// ==============================================================
// RTL generated by Vitis HLS - High-Level Synthesis from C, C++ and OpenCL
// Version: 2020.1
// Copyright (C) 1986-2020 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="EthInTop_EthInTop,hls_ip_2020_1,{HLS_INPUT_TYPE=cxx,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xcvu9p-flgb2104-2L-e,HLS_INPUT_CLOCK=3.333000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=2.433000,HLS_SYN_LAT=-1,HLS_SYN_TPT=none,HLS_SYN_MEM=8,HLS_SYN_DSP=0,HLS_SYN_FF=970,HLS_SYN_LUT=1549,HLS_VERSION=2020_1}" *)

module EthInTop (
        ap_clk,
        ap_rst_n,
        event_done,
        m_axi_gmem_AWVALID,
        m_axi_gmem_AWREADY,
        m_axi_gmem_AWADDR,
        m_axi_gmem_AWID,
        m_axi_gmem_AWLEN,
        m_axi_gmem_AWSIZE,
        m_axi_gmem_AWBURST,
        m_axi_gmem_AWLOCK,
        m_axi_gmem_AWCACHE,
        m_axi_gmem_AWPROT,
        m_axi_gmem_AWQOS,
        m_axi_gmem_AWREGION,
        m_axi_gmem_AWUSER,
        m_axi_gmem_WVALID,
        m_axi_gmem_WREADY,
        m_axi_gmem_WDATA,
        m_axi_gmem_WSTRB,
        m_axi_gmem_WLAST,
        m_axi_gmem_WID,
        m_axi_gmem_WUSER,
        m_axi_gmem_ARVALID,
        m_axi_gmem_ARREADY,
        m_axi_gmem_ARADDR,
        m_axi_gmem_ARID,
        m_axi_gmem_ARLEN,
        m_axi_gmem_ARSIZE,
        m_axi_gmem_ARBURST,
        m_axi_gmem_ARLOCK,
        m_axi_gmem_ARCACHE,
        m_axi_gmem_ARPROT,
        m_axi_gmem_ARQOS,
        m_axi_gmem_ARREGION,
        m_axi_gmem_ARUSER,
        m_axi_gmem_RVALID,
        m_axi_gmem_RREADY,
        m_axi_gmem_RDATA,
        m_axi_gmem_RLAST,
        m_axi_gmem_RID,
        m_axi_gmem_RUSER,
        m_axi_gmem_RRESP,
        m_axi_gmem_BVALID,
        m_axi_gmem_BREADY,
        m_axi_gmem_BRESP,
        m_axi_gmem_BID,
        m_axi_gmem_BUSER,
        ethernet_stream_out_TDATA,
        ethernet_stream_out_TVALID,
        ethernet_stream_out_TREADY,
        ethernet_stream_out_TKEEP,
        ethernet_stream_out_TSTRB,
        ethernet_stream_out_TLAST,
        s_axi_control_AWVALID,
        s_axi_control_AWREADY,
        s_axi_control_AWADDR,
        s_axi_control_WVALID,
        s_axi_control_WREADY,
        s_axi_control_WDATA,
        s_axi_control_WSTRB,
        s_axi_control_ARVALID,
        s_axi_control_ARREADY,
        s_axi_control_ARADDR,
        s_axi_control_RVALID,
        s_axi_control_RREADY,
        s_axi_control_RDATA,
        s_axi_control_RRESP,
        s_axi_control_BVALID,
        s_axi_control_BREADY,
        s_axi_control_BRESP,
        interrupt,
        event_start,
        stall_start_ext,
        stall_done_ext,
        stall_start_str,
        stall_done_str,
        stall_start_int,
        stall_done_int
);

parameter    ap_ST_fsm_state1 = 73'd1;
parameter    ap_ST_fsm_state2 = 73'd2;
parameter    ap_ST_fsm_state3 = 73'd4;
parameter    ap_ST_fsm_state4 = 73'd8;
parameter    ap_ST_fsm_state5 = 73'd16;
parameter    ap_ST_fsm_state6 = 73'd32;
parameter    ap_ST_fsm_state7 = 73'd64;
parameter    ap_ST_fsm_state8 = 73'd128;
parameter    ap_ST_fsm_state9 = 73'd256;
parameter    ap_ST_fsm_state10 = 73'd512;
parameter    ap_ST_fsm_state11 = 73'd1024;
parameter    ap_ST_fsm_state12 = 73'd2048;
parameter    ap_ST_fsm_state13 = 73'd4096;
parameter    ap_ST_fsm_state14 = 73'd8192;
parameter    ap_ST_fsm_state15 = 73'd16384;
parameter    ap_ST_fsm_state16 = 73'd32768;
parameter    ap_ST_fsm_state17 = 73'd65536;
parameter    ap_ST_fsm_state18 = 73'd131072;
parameter    ap_ST_fsm_state19 = 73'd262144;
parameter    ap_ST_fsm_state20 = 73'd524288;
parameter    ap_ST_fsm_state21 = 73'd1048576;
parameter    ap_ST_fsm_state22 = 73'd2097152;
parameter    ap_ST_fsm_state23 = 73'd4194304;
parameter    ap_ST_fsm_state24 = 73'd8388608;
parameter    ap_ST_fsm_state25 = 73'd16777216;
parameter    ap_ST_fsm_state26 = 73'd33554432;
parameter    ap_ST_fsm_state27 = 73'd67108864;
parameter    ap_ST_fsm_state28 = 73'd134217728;
parameter    ap_ST_fsm_state29 = 73'd268435456;
parameter    ap_ST_fsm_state30 = 73'd536870912;
parameter    ap_ST_fsm_state31 = 73'd1073741824;
parameter    ap_ST_fsm_state32 = 73'd2147483648;
parameter    ap_ST_fsm_state33 = 73'd4294967296;
parameter    ap_ST_fsm_state34 = 73'd8589934592;
parameter    ap_ST_fsm_state35 = 73'd17179869184;
parameter    ap_ST_fsm_state36 = 73'd34359738368;
parameter    ap_ST_fsm_state37 = 73'd68719476736;
parameter    ap_ST_fsm_state38 = 73'd137438953472;
parameter    ap_ST_fsm_state39 = 73'd274877906944;
parameter    ap_ST_fsm_state40 = 73'd549755813888;
parameter    ap_ST_fsm_state41 = 73'd1099511627776;
parameter    ap_ST_fsm_state42 = 73'd2199023255552;
parameter    ap_ST_fsm_state43 = 73'd4398046511104;
parameter    ap_ST_fsm_state44 = 73'd8796093022208;
parameter    ap_ST_fsm_state45 = 73'd17592186044416;
parameter    ap_ST_fsm_state46 = 73'd35184372088832;
parameter    ap_ST_fsm_state47 = 73'd70368744177664;
parameter    ap_ST_fsm_state48 = 73'd140737488355328;
parameter    ap_ST_fsm_state49 = 73'd281474976710656;
parameter    ap_ST_fsm_state50 = 73'd562949953421312;
parameter    ap_ST_fsm_state51 = 73'd1125899906842624;
parameter    ap_ST_fsm_state52 = 73'd2251799813685248;
parameter    ap_ST_fsm_state53 = 73'd4503599627370496;
parameter    ap_ST_fsm_state54 = 73'd9007199254740992;
parameter    ap_ST_fsm_state55 = 73'd18014398509481984;
parameter    ap_ST_fsm_state56 = 73'd36028797018963968;
parameter    ap_ST_fsm_state57 = 73'd72057594037927936;
parameter    ap_ST_fsm_state58 = 73'd144115188075855872;
parameter    ap_ST_fsm_state59 = 73'd288230376151711744;
parameter    ap_ST_fsm_state60 = 73'd576460752303423488;
parameter    ap_ST_fsm_state61 = 73'd1152921504606846976;
parameter    ap_ST_fsm_state62 = 73'd2305843009213693952;
parameter    ap_ST_fsm_state63 = 73'd4611686018427387904;
parameter    ap_ST_fsm_state64 = 73'd9223372036854775808;
parameter    ap_ST_fsm_state65 = 73'd18446744073709551616;
parameter    ap_ST_fsm_state66 = 73'd36893488147419103232;
parameter    ap_ST_fsm_state67 = 73'd73786976294838206464;
parameter    ap_ST_fsm_state68 = 73'd147573952589676412928;
parameter    ap_ST_fsm_state69 = 73'd295147905179352825856;
parameter    ap_ST_fsm_state70 = 73'd590295810358705651712;
parameter    ap_ST_fsm_state71 = 73'd1180591620717411303424;
parameter    ap_ST_fsm_pp0_stage0 = 73'd2361183241434822606848;
parameter    ap_ST_fsm_state75 = 73'd4722366482869645213696;
parameter    C_S_AXI_CONTROL_DATA_WIDTH = 32;
parameter    C_S_AXI_CONTROL_ADDR_WIDTH = 6;
parameter    C_S_AXI_DATA_WIDTH = 32;
parameter    C_M_AXI_GMEM_ID_WIDTH = 1;
parameter    C_M_AXI_GMEM_ADDR_WIDTH = 64;
parameter    C_M_AXI_GMEM_DATA_WIDTH = 128;
parameter    C_M_AXI_GMEM_AWUSER_WIDTH = 1;
parameter    C_M_AXI_GMEM_ARUSER_WIDTH = 1;
parameter    C_M_AXI_GMEM_WUSER_WIDTH = 1;
parameter    C_M_AXI_GMEM_RUSER_WIDTH = 1;
parameter    C_M_AXI_GMEM_BUSER_WIDTH = 1;
parameter    C_M_AXI_GMEM_USER_VALUE = 0;
parameter    C_M_AXI_GMEM_PROT_VALUE = 0;
parameter    C_M_AXI_GMEM_CACHE_VALUE = 3;
parameter    C_M_AXI_DATA_WIDTH = 32;

parameter C_S_AXI_CONTROL_WSTRB_WIDTH = (32 / 8);
parameter C_S_AXI_WSTRB_WIDTH = (32 / 8);
parameter C_M_AXI_GMEM_WSTRB_WIDTH = (128 / 8);
parameter C_M_AXI_WSTRB_WIDTH = (32 / 8);

input   ap_clk;
input   ap_rst_n;
output   event_done;
output   m_axi_gmem_AWVALID;
input   m_axi_gmem_AWREADY;
output  [C_M_AXI_GMEM_ADDR_WIDTH - 1:0] m_axi_gmem_AWADDR;
output  [C_M_AXI_GMEM_ID_WIDTH - 1:0] m_axi_gmem_AWID;
output  [7:0] m_axi_gmem_AWLEN;
output  [2:0] m_axi_gmem_AWSIZE;
output  [1:0] m_axi_gmem_AWBURST;
output  [1:0] m_axi_gmem_AWLOCK;
output  [3:0] m_axi_gmem_AWCACHE;
output  [2:0] m_axi_gmem_AWPROT;
output  [3:0] m_axi_gmem_AWQOS;
output  [3:0] m_axi_gmem_AWREGION;
output  [C_M_AXI_GMEM_AWUSER_WIDTH - 1:0] m_axi_gmem_AWUSER;
output   m_axi_gmem_WVALID;
input   m_axi_gmem_WREADY;
output  [C_M_AXI_GMEM_DATA_WIDTH - 1:0] m_axi_gmem_WDATA;
output  [C_M_AXI_GMEM_WSTRB_WIDTH - 1:0] m_axi_gmem_WSTRB;
output   m_axi_gmem_WLAST;
output  [C_M_AXI_GMEM_ID_WIDTH - 1:0] m_axi_gmem_WID;
output  [C_M_AXI_GMEM_WUSER_WIDTH - 1:0] m_axi_gmem_WUSER;
output   m_axi_gmem_ARVALID;
input   m_axi_gmem_ARREADY;
output  [C_M_AXI_GMEM_ADDR_WIDTH - 1:0] m_axi_gmem_ARADDR;
output  [C_M_AXI_GMEM_ID_WIDTH - 1:0] m_axi_gmem_ARID;
output  [7:0] m_axi_gmem_ARLEN;
output  [2:0] m_axi_gmem_ARSIZE;
output  [1:0] m_axi_gmem_ARBURST;
output  [1:0] m_axi_gmem_ARLOCK;
output  [3:0] m_axi_gmem_ARCACHE;
output  [2:0] m_axi_gmem_ARPROT;
output  [3:0] m_axi_gmem_ARQOS;
output  [3:0] m_axi_gmem_ARREGION;
output  [C_M_AXI_GMEM_ARUSER_WIDTH - 1:0] m_axi_gmem_ARUSER;
input   m_axi_gmem_RVALID;
output   m_axi_gmem_RREADY;
input  [C_M_AXI_GMEM_DATA_WIDTH - 1:0] m_axi_gmem_RDATA;
input   m_axi_gmem_RLAST;
input  [C_M_AXI_GMEM_ID_WIDTH - 1:0] m_axi_gmem_RID;
input  [C_M_AXI_GMEM_RUSER_WIDTH - 1:0] m_axi_gmem_RUSER;
input  [1:0] m_axi_gmem_RRESP;
input   m_axi_gmem_BVALID;
output   m_axi_gmem_BREADY;
input  [1:0] m_axi_gmem_BRESP;
input  [C_M_AXI_GMEM_ID_WIDTH - 1:0] m_axi_gmem_BID;
input  [C_M_AXI_GMEM_BUSER_WIDTH - 1:0] m_axi_gmem_BUSER;
output  [63:0] ethernet_stream_out_TDATA;
output   ethernet_stream_out_TVALID;
input   ethernet_stream_out_TREADY;
output  [7:0] ethernet_stream_out_TKEEP;
output  [7:0] ethernet_stream_out_TSTRB;
output  [0:0] ethernet_stream_out_TLAST;
input   s_axi_control_AWVALID;
output   s_axi_control_AWREADY;
input  [C_S_AXI_CONTROL_ADDR_WIDTH - 1:0] s_axi_control_AWADDR;
input   s_axi_control_WVALID;
output   s_axi_control_WREADY;
input  [C_S_AXI_CONTROL_DATA_WIDTH - 1:0] s_axi_control_WDATA;
input  [C_S_AXI_CONTROL_WSTRB_WIDTH - 1:0] s_axi_control_WSTRB;
input   s_axi_control_ARVALID;
output   s_axi_control_ARREADY;
input  [C_S_AXI_CONTROL_ADDR_WIDTH - 1:0] s_axi_control_ARADDR;
output   s_axi_control_RVALID;
input   s_axi_control_RREADY;
output  [C_S_AXI_CONTROL_DATA_WIDTH - 1:0] s_axi_control_RDATA;
output  [1:0] s_axi_control_RRESP;
output   s_axi_control_BVALID;
input   s_axi_control_BREADY;
output  [1:0] s_axi_control_BRESP;
output   interrupt;
output   event_start;
output   stall_start_ext;
output   stall_done_ext;
output   stall_start_str;
output   stall_done_str;
output   stall_start_int;
output   stall_done_int;

reg stall_start_ext;
reg stall_done_ext;
reg stall_start_str;
reg stall_done_str;
reg stall_start_int;
reg stall_done_int;

(* shreg_extract = "no" *) reg    ap_rst_reg_2;
(* shreg_extract = "no" *) reg    ap_rst_reg_1;
(* shreg_extract = "no" *) reg    ap_rst_n_inv;
wire    ap_start;
reg    ap_done;
reg    ap_idle;
(* fsm_encoding = "none" *) reg   [72:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    ap_ready;
wire   [63:0] in_r;
wire   [31:0] buffSize;
wire   [31:0] keep;
reg    gmem_blk_n_AR;
wire    ap_CS_fsm_state2;
reg    gmem_blk_n_R;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter1;
wire    ap_block_pp0_stage0;
reg   [0:0] icmp_ln882_reg_230;
reg    ethernet_stream_out_TDATA_blk_n;
reg    ap_enable_reg_pp0_iter2;
reg   [0:0] icmp_ln882_reg_230_pp0_iter1_reg;
wire    gmem_AWREADY;
wire    gmem_WREADY;
reg    gmem_ARVALID;
wire    gmem_ARREADY;
wire    gmem_RVALID;
reg    gmem_RREADY;
wire   [127:0] gmem_RDATA;
wire    gmem_RLAST;
wire   [0:0] gmem_RID;
wire   [0:0] gmem_RUSER;
wire   [1:0] gmem_RRESP;
wire    gmem_BVALID;
wire   [1:0] gmem_BRESP;
wire   [0:0] gmem_BID;
wire   [0:0] gmem_BUSER;
reg   [31:0] indvars_iv_reg_135;
reg   [59:0] trunc_ln_reg_219;
wire   [0:0] icmp_ln882_fu_166_p2;
wire    ap_block_state72_pp0_stage0_iter0;
reg    ap_block_state73_pp0_stage0_iter1;
reg    ap_block_state73_io;
wire    ap_block_state74_pp0_stage0_iter2;
reg    ap_block_state74_io;
reg    ap_block_pp0_stage0_11001;
wire   [31:0] add_ln695_fu_171_p2;
reg    ap_enable_reg_pp0_iter0;
wire    ap_CS_fsm_state71;
reg    ap_block_pp0_stage0_subdone;
reg    ap_condition_pp0_exit_iter0_state72;
wire   [63:0] sext_ln542_fu_156_p1;
reg    ap_block_pp0_stage0_01001;
wire    ap_CS_fsm_state75;
wire    regslice_both_ethernet_stream_out_V_data_V_U_apdone_blk;
reg   [72:0] ap_NS_fsm;
wire    ap_ext_blocking_cur_n;
wire    ap_str_blocking_cur_n;
wire    ap_ext_blocking_n;
wire    ap_str_blocking_n;
wire    ap_int_blocking_n;
reg    ap_ext_blocking_n_reg;
reg    ap_str_blocking_n_reg;
reg    ap_int_blocking_n_reg;
reg    ap_idle_pp0;
wire    ap_enable_pp0;
wire   [63:0] ethernet_stream_out_TDATA_int_regslice;
reg    ethernet_stream_out_TVALID_int_regslice;
wire    ethernet_stream_out_TREADY_int_regslice;
wire    regslice_both_ethernet_stream_out_V_data_V_U_vld_out;
wire    regslice_both_ethernet_stream_out_V_keep_V_U_apdone_blk;
wire   [7:0] ethernet_stream_out_TKEEP_int_regslice;
wire    regslice_both_ethernet_stream_out_V_keep_V_U_ack_in_dummy;
wire    regslice_both_ethernet_stream_out_V_keep_V_U_vld_out;
wire    regslice_both_ethernet_stream_out_V_strb_V_U_apdone_blk;
wire   [7:0] ethernet_stream_out_TSTRB_int_regslice;
wire    regslice_both_ethernet_stream_out_V_strb_V_U_ack_in_dummy;
wire    regslice_both_ethernet_stream_out_V_strb_V_U_vld_out;
wire    regslice_both_ethernet_stream_out_V_last_V_U_apdone_blk;
wire   [0:0] ethernet_stream_out_TLAST_int_regslice;
wire    regslice_both_ethernet_stream_out_V_last_V_U_ack_in_dummy;
wire    regslice_both_ethernet_stream_out_V_last_V_U_vld_out;

// power-on initialization
initial begin
#0 ap_rst_reg_2 = 1'b1;
#0 ap_rst_reg_1 = 1'b1;
#0 ap_rst_n_inv = 1'b1;
#0 ap_CS_fsm = 73'd1;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter2 = 1'b0;
#0 ap_enable_reg_pp0_iter0 = 1'b0;
end

EthInTop_control_s_axi #(
    .C_S_AXI_ADDR_WIDTH( C_S_AXI_CONTROL_ADDR_WIDTH ),
    .C_S_AXI_DATA_WIDTH( C_S_AXI_CONTROL_DATA_WIDTH ))
control_s_axi_U(
    .AWVALID(s_axi_control_AWVALID),
    .AWREADY(s_axi_control_AWREADY),
    .AWADDR(s_axi_control_AWADDR),
    .WVALID(s_axi_control_WVALID),
    .WREADY(s_axi_control_WREADY),
    .WDATA(s_axi_control_WDATA),
    .WSTRB(s_axi_control_WSTRB),
    .ARVALID(s_axi_control_ARVALID),
    .ARREADY(s_axi_control_ARREADY),
    .ARADDR(s_axi_control_ARADDR),
    .RVALID(s_axi_control_RVALID),
    .RREADY(s_axi_control_RREADY),
    .RDATA(s_axi_control_RDATA),
    .RRESP(s_axi_control_RRESP),
    .BVALID(s_axi_control_BVALID),
    .BREADY(s_axi_control_BREADY),
    .BRESP(s_axi_control_BRESP),
    .ACLK(ap_clk),
    .ARESET(ap_rst_n_inv),
    .ACLK_EN(1'b1),
    .in_r(in_r),
    .buffSize(buffSize),
    .keep(keep),
    .ap_start(ap_start),
    .interrupt(interrupt),
    .event_start(event_start),
    .ap_ready(ap_ready),
    .ap_done(ap_done),
    .ap_idle(ap_idle)
);

EthInTop_gmem_m_axi #(
    .CONSERVATIVE( 1 ),
    .USER_DW( 128 ),
    .USER_AW( 64 ),
    .USER_MAXREQS( 69 ),
    .NUM_READ_OUTSTANDING( 16 ),
    .NUM_WRITE_OUTSTANDING( 16 ),
    .MAX_READ_BURST_LENGTH( 16 ),
    .MAX_WRITE_BURST_LENGTH( 16 ),
    .C_M_AXI_ID_WIDTH( C_M_AXI_GMEM_ID_WIDTH ),
    .C_M_AXI_ADDR_WIDTH( C_M_AXI_GMEM_ADDR_WIDTH ),
    .C_M_AXI_DATA_WIDTH( C_M_AXI_GMEM_DATA_WIDTH ),
    .C_M_AXI_AWUSER_WIDTH( C_M_AXI_GMEM_AWUSER_WIDTH ),
    .C_M_AXI_ARUSER_WIDTH( C_M_AXI_GMEM_ARUSER_WIDTH ),
    .C_M_AXI_WUSER_WIDTH( C_M_AXI_GMEM_WUSER_WIDTH ),
    .C_M_AXI_RUSER_WIDTH( C_M_AXI_GMEM_RUSER_WIDTH ),
    .C_M_AXI_BUSER_WIDTH( C_M_AXI_GMEM_BUSER_WIDTH ),
    .C_USER_VALUE( C_M_AXI_GMEM_USER_VALUE ),
    .C_PROT_VALUE( C_M_AXI_GMEM_PROT_VALUE ),
    .C_CACHE_VALUE( C_M_AXI_GMEM_CACHE_VALUE ))
gmem_m_axi_U(
    .AWVALID(m_axi_gmem_AWVALID),
    .AWREADY(m_axi_gmem_AWREADY),
    .AWADDR(m_axi_gmem_AWADDR),
    .AWID(m_axi_gmem_AWID),
    .AWLEN(m_axi_gmem_AWLEN),
    .AWSIZE(m_axi_gmem_AWSIZE),
    .AWBURST(m_axi_gmem_AWBURST),
    .AWLOCK(m_axi_gmem_AWLOCK),
    .AWCACHE(m_axi_gmem_AWCACHE),
    .AWPROT(m_axi_gmem_AWPROT),
    .AWQOS(m_axi_gmem_AWQOS),
    .AWREGION(m_axi_gmem_AWREGION),
    .AWUSER(m_axi_gmem_AWUSER),
    .WVALID(m_axi_gmem_WVALID),
    .WREADY(m_axi_gmem_WREADY),
    .WDATA(m_axi_gmem_WDATA),
    .WSTRB(m_axi_gmem_WSTRB),
    .WLAST(m_axi_gmem_WLAST),
    .WID(m_axi_gmem_WID),
    .WUSER(m_axi_gmem_WUSER),
    .ARVALID(m_axi_gmem_ARVALID),
    .ARREADY(m_axi_gmem_ARREADY),
    .ARADDR(m_axi_gmem_ARADDR),
    .ARID(m_axi_gmem_ARID),
    .ARLEN(m_axi_gmem_ARLEN),
    .ARSIZE(m_axi_gmem_ARSIZE),
    .ARBURST(m_axi_gmem_ARBURST),
    .ARLOCK(m_axi_gmem_ARLOCK),
    .ARCACHE(m_axi_gmem_ARCACHE),
    .ARPROT(m_axi_gmem_ARPROT),
    .ARQOS(m_axi_gmem_ARQOS),
    .ARREGION(m_axi_gmem_ARREGION),
    .ARUSER(m_axi_gmem_ARUSER),
    .RVALID(m_axi_gmem_RVALID),
    .RREADY(m_axi_gmem_RREADY),
    .RDATA(m_axi_gmem_RDATA),
    .RLAST(m_axi_gmem_RLAST),
    .RID(m_axi_gmem_RID),
    .RUSER(m_axi_gmem_RUSER),
    .RRESP(m_axi_gmem_RRESP),
    .BVALID(m_axi_gmem_BVALID),
    .BREADY(m_axi_gmem_BREADY),
    .BRESP(m_axi_gmem_BRESP),
    .BID(m_axi_gmem_BID),
    .BUSER(m_axi_gmem_BUSER),
    .ACLK(ap_clk),
    .ARESET(ap_rst_n_inv),
    .ACLK_EN(1'b1),
    .I_ARVALID(gmem_ARVALID),
    .I_ARREADY(gmem_ARREADY),
    .I_ARADDR(sext_ln542_fu_156_p1),
    .I_ARID(1'd0),
    .I_ARLEN(buffSize),
    .I_ARSIZE(3'd0),
    .I_ARLOCK(2'd0),
    .I_ARCACHE(4'd0),
    .I_ARQOS(4'd0),
    .I_ARPROT(3'd0),
    .I_ARUSER(1'd0),
    .I_ARBURST(2'd0),
    .I_ARREGION(4'd0),
    .I_RVALID(gmem_RVALID),
    .I_RREADY(gmem_RREADY),
    .I_RDATA(gmem_RDATA),
    .I_RID(gmem_RID),
    .I_RUSER(gmem_RUSER),
    .I_RRESP(gmem_RRESP),
    .I_RLAST(gmem_RLAST),
    .I_AWVALID(1'b0),
    .I_AWREADY(gmem_AWREADY),
    .I_AWADDR(64'd0),
    .I_AWID(1'd0),
    .I_AWLEN(32'd0),
    .I_AWSIZE(3'd0),
    .I_AWLOCK(2'd0),
    .I_AWCACHE(4'd0),
    .I_AWQOS(4'd0),
    .I_AWPROT(3'd0),
    .I_AWUSER(1'd0),
    .I_AWBURST(2'd0),
    .I_AWREGION(4'd0),
    .I_WVALID(1'b0),
    .I_WREADY(gmem_WREADY),
    .I_WDATA(128'd0),
    .I_WID(1'd0),
    .I_WUSER(1'd0),
    .I_WLAST(1'b0),
    .I_WSTRB(16'd0),
    .I_BVALID(gmem_BVALID),
    .I_BREADY(1'b0),
    .I_BRESP(gmem_BRESP),
    .I_BID(gmem_BID),
    .I_BUSER(gmem_BUSER)
);

regslice_both #(
    .DataWidth( 64 ))
regslice_both_ethernet_stream_out_V_data_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(ethernet_stream_out_TDATA_int_regslice),
    .vld_in(ethernet_stream_out_TVALID_int_regslice),
    .ack_in(ethernet_stream_out_TREADY_int_regslice),
    .data_out(ethernet_stream_out_TDATA),
    .vld_out(regslice_both_ethernet_stream_out_V_data_V_U_vld_out),
    .ack_out(ethernet_stream_out_TREADY),
    .apdone_blk(regslice_both_ethernet_stream_out_V_data_V_U_apdone_blk)
);

regslice_both #(
    .DataWidth( 8 ))
regslice_both_ethernet_stream_out_V_keep_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(ethernet_stream_out_TKEEP_int_regslice),
    .vld_in(ethernet_stream_out_TVALID_int_regslice),
    .ack_in(regslice_both_ethernet_stream_out_V_keep_V_U_ack_in_dummy),
    .data_out(ethernet_stream_out_TKEEP),
    .vld_out(regslice_both_ethernet_stream_out_V_keep_V_U_vld_out),
    .ack_out(ethernet_stream_out_TREADY),
    .apdone_blk(regslice_both_ethernet_stream_out_V_keep_V_U_apdone_blk)
);

regslice_both #(
    .DataWidth( 8 ))
regslice_both_ethernet_stream_out_V_strb_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(ethernet_stream_out_TSTRB_int_regslice),
    .vld_in(ethernet_stream_out_TVALID_int_regslice),
    .ack_in(regslice_both_ethernet_stream_out_V_strb_V_U_ack_in_dummy),
    .data_out(ethernet_stream_out_TSTRB),
    .vld_out(regslice_both_ethernet_stream_out_V_strb_V_U_vld_out),
    .ack_out(ethernet_stream_out_TREADY),
    .apdone_blk(regslice_both_ethernet_stream_out_V_strb_V_U_apdone_blk)
);

regslice_both #(
    .DataWidth( 1 ))
regslice_both_ethernet_stream_out_V_last_V_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst_n_inv),
    .data_in(ethernet_stream_out_TLAST_int_regslice),
    .vld_in(ethernet_stream_out_TVALID_int_regslice),
    .ack_in(regslice_both_ethernet_stream_out_V_last_V_U_ack_in_dummy),
    .data_out(ethernet_stream_out_TLAST),
    .vld_out(regslice_both_ethernet_stream_out_V_last_V_U_vld_out),
    .ack_out(ethernet_stream_out_TREADY),
    .apdone_blk(regslice_both_ethernet_stream_out_V_last_V_U_apdone_blk)
);

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_enable_reg_pp0_iter0 <= 1'b0;
    end else begin
        if (((1'b1 == ap_condition_pp0_exit_iter0_state72) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
            ap_enable_reg_pp0_iter0 <= 1'b0;
        end else if ((1'b1 == ap_CS_fsm_state71)) begin
            ap_enable_reg_pp0_iter0 <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            if ((1'b1 == ap_condition_pp0_exit_iter0_state72)) begin
                ap_enable_reg_pp0_iter1 <= (1'b1 ^ ap_condition_pp0_exit_iter0_state72);
            end else if ((1'b1 == 1'b1)) begin
                ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
            end
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst_n_inv == 1'b1) begin
        ap_enable_reg_pp0_iter2 <= 1'b0;
    end else begin
        if ((1'b0 == ap_block_pp0_stage0_subdone)) begin
            ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
        end else if ((1'b1 == ap_CS_fsm_state71)) begin
            ap_enable_reg_pp0_iter2 <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    ap_ext_blocking_n_reg <= ap_ext_blocking_n;
end

always @ (posedge ap_clk) begin
    ap_rst_n_inv <= ap_rst_reg_1;
end

always @ (posedge ap_clk) begin
    ap_rst_reg_1 <= ap_rst_reg_2;
end

always @ (posedge ap_clk) begin
    ap_rst_reg_2 <= ~ap_rst_n;
end

always @ (posedge ap_clk) begin
    ap_str_blocking_n_reg <= ap_str_blocking_n;
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state71)) begin
        indvars_iv_reg_135 <= 32'd0;
    end else if (((ap_enable_reg_pp0_iter0 == 1'b1) & (icmp_ln882_fu_166_p2 == 1'd0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        indvars_iv_reg_135 <= add_ln695_fu_171_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_pp0_stage0) & (1'b0 == ap_block_pp0_stage0_11001))) begin
        icmp_ln882_reg_230 <= icmp_ln882_fu_166_p2;
        icmp_ln882_reg_230_pp0_iter1_reg <= icmp_ln882_reg_230;
    end
end

always @ (posedge ap_clk) begin
    if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
        trunc_ln_reg_219 <= {{in_r[63:4]}};
    end
end

always @ (*) begin
    if ((icmp_ln882_fu_166_p2 == 1'd1)) begin
        ap_condition_pp0_exit_iter0_state72 = 1'b1;
    end else begin
        ap_condition_pp0_exit_iter0_state72 = 1'b0;
    end
end

always @ (*) begin
    if (((regslice_both_ethernet_stream_out_V_data_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state75))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter0 == 1'b0) & (ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if (((regslice_both_ethernet_stream_out_V_data_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state75))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((((icmp_ln882_reg_230_pp0_iter1_reg == 1'd0) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0)) | ((1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln882_reg_230 == 1'd0) & (1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1)))) begin
        ethernet_stream_out_TDATA_blk_n = ethernet_stream_out_TREADY_int_regslice;
    end else begin
        ethernet_stream_out_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln882_reg_230 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter1 == 1'b1))) begin
        ethernet_stream_out_TVALID_int_regslice = 1'b1;
    end else begin
        ethernet_stream_out_TVALID_int_regslice = 1'b0;
    end
end

always @ (*) begin
    if (((gmem_ARREADY == 1'b1) & (1'b1 == ap_CS_fsm_state2))) begin
        gmem_ARVALID = 1'b1;
    end else begin
        gmem_ARVALID = 1'b0;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln882_reg_230 == 1'd0) & (1'b0 == ap_block_pp0_stage0_11001) & (ap_enable_reg_pp0_iter1 == 1'b1))) begin
        gmem_RREADY = 1'b1;
    end else begin
        gmem_RREADY = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        gmem_blk_n_AR = m_axi_gmem_ARREADY;
    end else begin
        gmem_blk_n_AR = 1'b1;
    end
end

always @ (*) begin
    if (((1'b1 == ap_CS_fsm_pp0_stage0) & (icmp_ln882_reg_230 == 1'd0) & (1'b0 == ap_block_pp0_stage0) & (ap_enable_reg_pp0_iter1 == 1'b1))) begin
        gmem_blk_n_R = m_axi_gmem_RVALID;
    end else begin
        gmem_blk_n_R = 1'b1;
    end
end

always @ (*) begin
    if (((ap_ext_blocking_n_reg == 1'b0) & (ap_ext_blocking_n == 1'b1))) begin
        stall_done_ext = 1'b1;
    end else begin
        stall_done_ext = 1'b0;
    end
end

always @ (*) begin
    if (((ap_int_blocking_n_reg == 1'b0) & (ap_int_blocking_n == 1'b1))) begin
        stall_done_int = 1'b1;
    end else begin
        stall_done_int = 1'b0;
    end
end

always @ (*) begin
    if (((ap_str_blocking_n_reg == 1'b0) & (ap_str_blocking_n == 1'b1))) begin
        stall_done_str = 1'b1;
    end else begin
        stall_done_str = 1'b0;
    end
end

always @ (*) begin
    if (((ap_ext_blocking_n_reg == 1'b1) & (ap_ext_blocking_n == 1'b0))) begin
        stall_start_ext = 1'b1;
    end else begin
        stall_start_ext = 1'b0;
    end
end

always @ (*) begin
    if (((ap_int_blocking_n_reg == 1'b1) & (ap_int_blocking_n == 1'b0))) begin
        stall_start_int = 1'b1;
    end else begin
        stall_start_int = 1'b0;
    end
end

always @ (*) begin
    if (((ap_str_blocking_n_reg == 1'b1) & (ap_str_blocking_n == 1'b0))) begin
        stall_start_str = 1'b1;
    end else begin
        stall_start_str = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((ap_start == 1'b1) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if (((gmem_ARREADY == 1'b1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        ap_ST_fsm_state3 : begin
            ap_NS_fsm = ap_ST_fsm_state4;
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            ap_NS_fsm = ap_ST_fsm_state6;
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state7;
        end
        ap_ST_fsm_state7 : begin
            ap_NS_fsm = ap_ST_fsm_state8;
        end
        ap_ST_fsm_state8 : begin
            ap_NS_fsm = ap_ST_fsm_state9;
        end
        ap_ST_fsm_state9 : begin
            ap_NS_fsm = ap_ST_fsm_state10;
        end
        ap_ST_fsm_state10 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        ap_ST_fsm_state11 : begin
            ap_NS_fsm = ap_ST_fsm_state12;
        end
        ap_ST_fsm_state12 : begin
            ap_NS_fsm = ap_ST_fsm_state13;
        end
        ap_ST_fsm_state13 : begin
            ap_NS_fsm = ap_ST_fsm_state14;
        end
        ap_ST_fsm_state14 : begin
            ap_NS_fsm = ap_ST_fsm_state15;
        end
        ap_ST_fsm_state15 : begin
            ap_NS_fsm = ap_ST_fsm_state16;
        end
        ap_ST_fsm_state16 : begin
            ap_NS_fsm = ap_ST_fsm_state17;
        end
        ap_ST_fsm_state17 : begin
            ap_NS_fsm = ap_ST_fsm_state18;
        end
        ap_ST_fsm_state18 : begin
            ap_NS_fsm = ap_ST_fsm_state19;
        end
        ap_ST_fsm_state19 : begin
            ap_NS_fsm = ap_ST_fsm_state20;
        end
        ap_ST_fsm_state20 : begin
            ap_NS_fsm = ap_ST_fsm_state21;
        end
        ap_ST_fsm_state21 : begin
            ap_NS_fsm = ap_ST_fsm_state22;
        end
        ap_ST_fsm_state22 : begin
            ap_NS_fsm = ap_ST_fsm_state23;
        end
        ap_ST_fsm_state23 : begin
            ap_NS_fsm = ap_ST_fsm_state24;
        end
        ap_ST_fsm_state24 : begin
            ap_NS_fsm = ap_ST_fsm_state25;
        end
        ap_ST_fsm_state25 : begin
            ap_NS_fsm = ap_ST_fsm_state26;
        end
        ap_ST_fsm_state26 : begin
            ap_NS_fsm = ap_ST_fsm_state27;
        end
        ap_ST_fsm_state27 : begin
            ap_NS_fsm = ap_ST_fsm_state28;
        end
        ap_ST_fsm_state28 : begin
            ap_NS_fsm = ap_ST_fsm_state29;
        end
        ap_ST_fsm_state29 : begin
            ap_NS_fsm = ap_ST_fsm_state30;
        end
        ap_ST_fsm_state30 : begin
            ap_NS_fsm = ap_ST_fsm_state31;
        end
        ap_ST_fsm_state31 : begin
            ap_NS_fsm = ap_ST_fsm_state32;
        end
        ap_ST_fsm_state32 : begin
            ap_NS_fsm = ap_ST_fsm_state33;
        end
        ap_ST_fsm_state33 : begin
            ap_NS_fsm = ap_ST_fsm_state34;
        end
        ap_ST_fsm_state34 : begin
            ap_NS_fsm = ap_ST_fsm_state35;
        end
        ap_ST_fsm_state35 : begin
            ap_NS_fsm = ap_ST_fsm_state36;
        end
        ap_ST_fsm_state36 : begin
            ap_NS_fsm = ap_ST_fsm_state37;
        end
        ap_ST_fsm_state37 : begin
            ap_NS_fsm = ap_ST_fsm_state38;
        end
        ap_ST_fsm_state38 : begin
            ap_NS_fsm = ap_ST_fsm_state39;
        end
        ap_ST_fsm_state39 : begin
            ap_NS_fsm = ap_ST_fsm_state40;
        end
        ap_ST_fsm_state40 : begin
            ap_NS_fsm = ap_ST_fsm_state41;
        end
        ap_ST_fsm_state41 : begin
            ap_NS_fsm = ap_ST_fsm_state42;
        end
        ap_ST_fsm_state42 : begin
            ap_NS_fsm = ap_ST_fsm_state43;
        end
        ap_ST_fsm_state43 : begin
            ap_NS_fsm = ap_ST_fsm_state44;
        end
        ap_ST_fsm_state44 : begin
            ap_NS_fsm = ap_ST_fsm_state45;
        end
        ap_ST_fsm_state45 : begin
            ap_NS_fsm = ap_ST_fsm_state46;
        end
        ap_ST_fsm_state46 : begin
            ap_NS_fsm = ap_ST_fsm_state47;
        end
        ap_ST_fsm_state47 : begin
            ap_NS_fsm = ap_ST_fsm_state48;
        end
        ap_ST_fsm_state48 : begin
            ap_NS_fsm = ap_ST_fsm_state49;
        end
        ap_ST_fsm_state49 : begin
            ap_NS_fsm = ap_ST_fsm_state50;
        end
        ap_ST_fsm_state50 : begin
            ap_NS_fsm = ap_ST_fsm_state51;
        end
        ap_ST_fsm_state51 : begin
            ap_NS_fsm = ap_ST_fsm_state52;
        end
        ap_ST_fsm_state52 : begin
            ap_NS_fsm = ap_ST_fsm_state53;
        end
        ap_ST_fsm_state53 : begin
            ap_NS_fsm = ap_ST_fsm_state54;
        end
        ap_ST_fsm_state54 : begin
            ap_NS_fsm = ap_ST_fsm_state55;
        end
        ap_ST_fsm_state55 : begin
            ap_NS_fsm = ap_ST_fsm_state56;
        end
        ap_ST_fsm_state56 : begin
            ap_NS_fsm = ap_ST_fsm_state57;
        end
        ap_ST_fsm_state57 : begin
            ap_NS_fsm = ap_ST_fsm_state58;
        end
        ap_ST_fsm_state58 : begin
            ap_NS_fsm = ap_ST_fsm_state59;
        end
        ap_ST_fsm_state59 : begin
            ap_NS_fsm = ap_ST_fsm_state60;
        end
        ap_ST_fsm_state60 : begin
            ap_NS_fsm = ap_ST_fsm_state61;
        end
        ap_ST_fsm_state61 : begin
            ap_NS_fsm = ap_ST_fsm_state62;
        end
        ap_ST_fsm_state62 : begin
            ap_NS_fsm = ap_ST_fsm_state63;
        end
        ap_ST_fsm_state63 : begin
            ap_NS_fsm = ap_ST_fsm_state64;
        end
        ap_ST_fsm_state64 : begin
            ap_NS_fsm = ap_ST_fsm_state65;
        end
        ap_ST_fsm_state65 : begin
            ap_NS_fsm = ap_ST_fsm_state66;
        end
        ap_ST_fsm_state66 : begin
            ap_NS_fsm = ap_ST_fsm_state67;
        end
        ap_ST_fsm_state67 : begin
            ap_NS_fsm = ap_ST_fsm_state68;
        end
        ap_ST_fsm_state68 : begin
            ap_NS_fsm = ap_ST_fsm_state69;
        end
        ap_ST_fsm_state69 : begin
            ap_NS_fsm = ap_ST_fsm_state70;
        end
        ap_ST_fsm_state70 : begin
            ap_NS_fsm = ap_ST_fsm_state71;
        end
        ap_ST_fsm_state71 : begin
            ap_NS_fsm = ap_ST_fsm_pp0_stage0;
        end
        ap_ST_fsm_pp0_stage0 : begin
            if ((~((ap_enable_reg_pp0_iter0 == 1'b1) & (icmp_ln882_fu_166_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter1 == 1'b0)) & ~((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter1 == 1'b0)))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((((ap_enable_reg_pp0_iter0 == 1'b1) & (icmp_ln882_fu_166_p2 == 1'd1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter1 == 1'b0)) | ((ap_enable_reg_pp0_iter2 == 1'b1) & (1'b0 == ap_block_pp0_stage0_subdone) & (ap_enable_reg_pp0_iter1 == 1'b0)))) begin
                ap_NS_fsm = ap_ST_fsm_state75;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end
        end
        ap_ST_fsm_state75 : begin
            if (((regslice_both_ethernet_stream_out_V_data_V_U_apdone_blk == 1'b0) & (1'b1 == ap_CS_fsm_state75))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state75;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln695_fu_171_p2 = (indvars_iv_reg_135 + 32'd1);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd71];

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state71 = ap_CS_fsm[32'd70];

assign ap_CS_fsm_state75 = ap_CS_fsm[32'd72];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage0_01001 = ((gmem_RVALID == 1'b0) & (icmp_ln882_reg_230 == 1'd0) & (ap_enable_reg_pp0_iter1 == 1'b1));
end

always @ (*) begin
    ap_block_pp0_stage0_11001 = (((1'b1 == ap_block_state74_io) & (ap_enable_reg_pp0_iter2 == 1'b1)) | ((ap_enable_reg_pp0_iter1 == 1'b1) & ((1'b1 == ap_block_state73_io) | ((gmem_RVALID == 1'b0) & (icmp_ln882_reg_230 == 1'd0)))));
end

always @ (*) begin
    ap_block_pp0_stage0_subdone = (((1'b1 == ap_block_state74_io) & (ap_enable_reg_pp0_iter2 == 1'b1)) | ((ap_enable_reg_pp0_iter1 == 1'b1) & ((1'b1 == ap_block_state73_io) | ((gmem_RVALID == 1'b0) & (icmp_ln882_reg_230 == 1'd0)))));
end

assign ap_block_state72_pp0_stage0_iter0 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state73_io = ((ethernet_stream_out_TREADY_int_regslice == 1'b0) & (icmp_ln882_reg_230 == 1'd0));
end

always @ (*) begin
    ap_block_state73_pp0_stage0_iter1 = ((gmem_RVALID == 1'b0) & (icmp_ln882_reg_230 == 1'd0));
end

always @ (*) begin
    ap_block_state74_io = ((ethernet_stream_out_TREADY_int_regslice == 1'b0) & (icmp_ln882_reg_230_pp0_iter1_reg == 1'd0));
end

assign ap_block_state74_pp0_stage0_iter2 = ~(1'b1 == 1'b1);

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_ext_blocking_cur_n = (gmem_blk_n_R & gmem_blk_n_AR);

assign ap_ext_blocking_n = (ap_ext_blocking_cur_n & 1'b1);

assign ap_int_blocking_n = (1'b1 & 1'b1);

assign ap_str_blocking_cur_n = ethernet_stream_out_TDATA_blk_n;

assign ap_str_blocking_n = (ap_str_blocking_cur_n & 1'b1);

assign ethernet_stream_out_TDATA_int_regslice = gmem_RDATA[63:0];

assign ethernet_stream_out_TKEEP_int_regslice = {{gmem_RDATA[71:64]}};

assign ethernet_stream_out_TLAST_int_regslice = gmem_RDATA[32'd80];

assign ethernet_stream_out_TSTRB_int_regslice = {{gmem_RDATA[79:72]}};

assign ethernet_stream_out_TVALID = regslice_both_ethernet_stream_out_V_data_V_U_vld_out;

assign event_done = ap_done;

assign icmp_ln882_fu_166_p2 = ((indvars_iv_reg_135 == buffSize) ? 1'b1 : 1'b0);

assign sext_ln542_fu_156_p1 = $signed(trunc_ln_reg_219);

always @ (posedge ap_clk) begin
    ap_int_blocking_n_reg <= 1'b1;
end

endmodule //EthInTop
