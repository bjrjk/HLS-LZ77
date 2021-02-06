# HLS-LZ77
**This is a repo of HLS Implementation of LZ77 Data Compression Algorithm, which is a project for *The 2nd winter camp of domain-oriented customized computing* (*2021 Xilinx Winter Camp*).**

**The project is under development.**

## Proposal of Project
HLS-LZ77 is going to implement LZ77 data compression algorithm on Zynq-7000 FPGA using Vivado HLS. 

The implementation of this project will be split into two parts, PS (Processing System) and PL (Programmable Logic). 

In order to speed up the compression progress, LZ77 algorithm will be done on the PL side. For the sake of rapid iteration, the usage of HLS (High-Level Synthesis) is required for hardware development. 

PS will be responsible for human-computer interaction. The software part will be implemented in SDK at least, whose OS platform is standalone. If possible, software will also be realized on a PetaLinux release.

PS and PL will communicate via AXI (Advanced eXtensible Interface) Bus.

## Platform
- ALinx AX7020 FPGA Development Board (with Zynq-7000 series XC7X020-2CLG400I)
- Vivado 2018.3
- Vivado HLS 2018.3
- Vivado SDK 2018.3
