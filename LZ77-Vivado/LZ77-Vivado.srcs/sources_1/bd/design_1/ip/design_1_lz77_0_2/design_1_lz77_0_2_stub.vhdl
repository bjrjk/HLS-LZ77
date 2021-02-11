-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
-- Date        : Thu Feb 11 19:05:01 2021
-- Host        : DESKTOP-7EJIO30 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               D:/Programming/Github/HLS-LZ77/LZ77-Vivado/LZ77-Vivado.srcs/sources_1/bd/design_1/ip/design_1_lz77_0_2/design_1_lz77_0_2_stub.vhdl
-- Design      : design_1_lz77_0_2
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-2
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_lz77_0_2 is
  Port ( 
    s_axi_AXILiteS_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_AXILiteS_AWVALID : in STD_LOGIC;
    s_axi_AXILiteS_AWREADY : out STD_LOGIC;
    s_axi_AXILiteS_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_AXILiteS_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_AXILiteS_WVALID : in STD_LOGIC;
    s_axi_AXILiteS_WREADY : out STD_LOGIC;
    s_axi_AXILiteS_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_AXILiteS_BVALID : out STD_LOGIC;
    s_axi_AXILiteS_BREADY : in STD_LOGIC;
    s_axi_AXILiteS_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_AXILiteS_ARVALID : in STD_LOGIC;
    s_axi_AXILiteS_ARREADY : out STD_LOGIC;
    s_axi_AXILiteS_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_AXILiteS_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_AXILiteS_RVALID : out STD_LOGIC;
    s_axi_AXILiteS_RREADY : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    interrupt : out STD_LOGIC;
    streamIn_TVALID : in STD_LOGIC;
    streamIn_TREADY : out STD_LOGIC;
    streamIn_TDATA : in STD_LOGIC_VECTOR ( 7 downto 0 );
    streamIn_TLAST : in STD_LOGIC_VECTOR ( 0 to 0 );
    streamIn_TKEEP : in STD_LOGIC_VECTOR ( 0 to 0 );
    streamIn_TSTRB : in STD_LOGIC_VECTOR ( 0 to 0 );
    streamOut_TVALID : out STD_LOGIC;
    streamOut_TREADY : in STD_LOGIC;
    streamOut_TDATA : out STD_LOGIC_VECTOR ( 7 downto 0 );
    streamOut_TLAST : out STD_LOGIC_VECTOR ( 0 to 0 );
    streamOut_TKEEP : out STD_LOGIC_VECTOR ( 0 to 0 );
    streamOut_TSTRB : out STD_LOGIC_VECTOR ( 0 to 0 )
  );

end design_1_lz77_0_2;

architecture stub of design_1_lz77_0_2 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "s_axi_AXILiteS_AWADDR[5:0],s_axi_AXILiteS_AWVALID,s_axi_AXILiteS_AWREADY,s_axi_AXILiteS_WDATA[31:0],s_axi_AXILiteS_WSTRB[3:0],s_axi_AXILiteS_WVALID,s_axi_AXILiteS_WREADY,s_axi_AXILiteS_BRESP[1:0],s_axi_AXILiteS_BVALID,s_axi_AXILiteS_BREADY,s_axi_AXILiteS_ARADDR[5:0],s_axi_AXILiteS_ARVALID,s_axi_AXILiteS_ARREADY,s_axi_AXILiteS_RDATA[31:0],s_axi_AXILiteS_RRESP[1:0],s_axi_AXILiteS_RVALID,s_axi_AXILiteS_RREADY,ap_clk,ap_rst_n,interrupt,streamIn_TVALID,streamIn_TREADY,streamIn_TDATA[7:0],streamIn_TLAST[0:0],streamIn_TKEEP[0:0],streamIn_TSTRB[0:0],streamOut_TVALID,streamOut_TREADY,streamOut_TDATA[7:0],streamOut_TLAST[0:0],streamOut_TKEEP[0:0],streamOut_TSTRB[0:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "lz77,Vivado 2018.3";
begin
end;
