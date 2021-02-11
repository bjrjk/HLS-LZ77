// ==============================================================
// File generated on Thu Feb 11 18:56:11 +0800 2021
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xlz77.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XLz77_CfgInitialize(XLz77 *InstancePtr, XLz77_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XLz77_Start(XLz77 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_CTRL) & 0x80;
    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XLz77_IsDone(XLz77 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XLz77_IsIdle(XLz77 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XLz77_IsReady(XLz77 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XLz77_EnableAutoRestart(XLz77 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XLz77_DisableAutoRestart(XLz77 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_CTRL, 0);
}

u32 XLz77_Get_return(XLz77 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_AP_RETURN);
    return Data;
}
void XLz77_Set_optype(XLz77 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_OPTYPE_DATA, Data);
}

u32 XLz77_Get_optype(XLz77 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_OPTYPE_DATA);
    return Data;
}

void XLz77_Set_streamInSize(XLz77 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_STREAMINSIZE_DATA, Data);
}

u32 XLz77_Get_streamInSize(XLz77 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_STREAMINSIZE_DATA);
    return Data;
}

void XLz77_InterruptGlobalEnable(XLz77 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_GIE, 1);
}

void XLz77_InterruptGlobalDisable(XLz77 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_GIE, 0);
}

void XLz77_InterruptEnable(XLz77 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_IER);
    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_IER, Register | Mask);
}

void XLz77_InterruptDisable(XLz77 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_IER);
    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_IER, Register & (~Mask));
}

void XLz77_InterruptClear(XLz77 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLz77_WriteReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_ISR, Mask);
}

u32 XLz77_InterruptGetEnabled(XLz77 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_IER);
}

u32 XLz77_InterruptGetStatus(XLz77 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XLz77_ReadReg(InstancePtr->Axilites_BaseAddress, XLZ77_AXILITES_ADDR_ISR);
}

