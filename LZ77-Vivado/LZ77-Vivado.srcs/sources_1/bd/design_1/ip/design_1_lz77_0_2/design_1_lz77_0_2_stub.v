// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Thu Feb 11 19:05:01 2021
// Host        : DESKTOP-7EJIO30 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               D:/Programming/Github/HLS-LZ77/LZ77-Vivado/LZ77-Vivado.srcs/sources_1/bd/design_1/ip/design_1_lz77_0_2/design_1_lz77_0_2_stub.v
// Design      : design_1_lz77_0_2
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z020clg400-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "lz77,Vivado 2018.3" *)
module design_1_lz77_0_2(s_axi_AXILiteS_AWADDR, 
  s_axi_AXILiteS_AWVALID, s_axi_AXILiteS_AWREADY, s_axi_AXILiteS_WDATA, 
  s_axi_AXILiteS_WSTRB, s_axi_AXILiteS_WVALID, s_axi_AXILiteS_WREADY, 
  s_axi_AXILiteS_BRESP, s_axi_AXILiteS_BVALID, s_axi_AXILiteS_BREADY, 
  s_axi_AXILiteS_ARADDR, s_axi_AXILiteS_ARVALID, s_axi_AXILiteS_ARREADY, 
  s_axi_AXILiteS_RDATA, s_axi_AXILiteS_RRESP, s_axi_AXILiteS_RVALID, 
  s_axi_AXILiteS_RREADY, ap_clk, ap_rst_n, interrupt, streamIn_TVALID, streamIn_TREADY, 
  streamIn_TDATA, streamIn_TLAST, streamIn_TKEEP, streamIn_TSTRB, streamOut_TVALID, 
  streamOut_TREADY, streamOut_TDATA, streamOut_TLAST, streamOut_TKEEP, streamOut_TSTRB)
/* synthesis syn_black_box black_box_pad_pin="s_axi_AXILiteS_AWADDR[5:0],s_axi_AXILiteS_AWVALID,s_axi_AXILiteS_AWREADY,s_axi_AXILiteS_WDATA[31:0],s_axi_AXILiteS_WSTRB[3:0],s_axi_AXILiteS_WVALID,s_axi_AXILiteS_WREADY,s_axi_AXILiteS_BRESP[1:0],s_axi_AXILiteS_BVALID,s_axi_AXILiteS_BREADY,s_axi_AXILiteS_ARADDR[5:0],s_axi_AXILiteS_ARVALID,s_axi_AXILiteS_ARREADY,s_axi_AXILiteS_RDATA[31:0],s_axi_AXILiteS_RRESP[1:0],s_axi_AXILiteS_RVALID,s_axi_AXILiteS_RREADY,ap_clk,ap_rst_n,interrupt,streamIn_TVALID,streamIn_TREADY,streamIn_TDATA[7:0],streamIn_TLAST[0:0],streamIn_TKEEP[0:0],streamIn_TSTRB[0:0],streamOut_TVALID,streamOut_TREADY,streamOut_TDATA[7:0],streamOut_TLAST[0:0],streamOut_TKEEP[0:0],streamOut_TSTRB[0:0]" */;
  input [5:0]s_axi_AXILiteS_AWADDR;
  input s_axi_AXILiteS_AWVALID;
  output s_axi_AXILiteS_AWREADY;
  input [31:0]s_axi_AXILiteS_WDATA;
  input [3:0]s_axi_AXILiteS_WSTRB;
  input s_axi_AXILiteS_WVALID;
  output s_axi_AXILiteS_WREADY;
  output [1:0]s_axi_AXILiteS_BRESP;
  output s_axi_AXILiteS_BVALID;
  input s_axi_AXILiteS_BREADY;
  input [5:0]s_axi_AXILiteS_ARADDR;
  input s_axi_AXILiteS_ARVALID;
  output s_axi_AXILiteS_ARREADY;
  output [31:0]s_axi_AXILiteS_RDATA;
  output [1:0]s_axi_AXILiteS_RRESP;
  output s_axi_AXILiteS_RVALID;
  input s_axi_AXILiteS_RREADY;
  input ap_clk;
  input ap_rst_n;
  output interrupt;
  input streamIn_TVALID;
  output streamIn_TREADY;
  input [7:0]streamIn_TDATA;
  input [0:0]streamIn_TLAST;
  input [0:0]streamIn_TKEEP;
  input [0:0]streamIn_TSTRB;
  output streamOut_TVALID;
  input streamOut_TREADY;
  output [7:0]streamOut_TDATA;
  output [0:0]streamOut_TLAST;
  output [0:0]streamOut_TKEEP;
  output [0:0]streamOut_TSTRB;
endmodule
