// ==============================================================
// File generated on Thu Feb 11 18:56:11 +0800 2021
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XLZ77_H
#define XLZ77_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xlz77_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XLz77_Config;
#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XLz77;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XLz77_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XLz77_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XLz77_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XLz77_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XLz77_Initialize(XLz77 *InstancePtr, u16 DeviceId);
XLz77_Config* XLz77_LookupConfig(u16 DeviceId);
int XLz77_CfgInitialize(XLz77 *InstancePtr, XLz77_Config *ConfigPtr);
#else
int XLz77_Initialize(XLz77 *InstancePtr, const char* InstanceName);
int XLz77_Release(XLz77 *InstancePtr);
#endif

void XLz77_Start(XLz77 *InstancePtr);
u32 XLz77_IsDone(XLz77 *InstancePtr);
u32 XLz77_IsIdle(XLz77 *InstancePtr);
u32 XLz77_IsReady(XLz77 *InstancePtr);
void XLz77_EnableAutoRestart(XLz77 *InstancePtr);
void XLz77_DisableAutoRestart(XLz77 *InstancePtr);
u32 XLz77_Get_return(XLz77 *InstancePtr);

void XLz77_Set_optype(XLz77 *InstancePtr, u32 Data);
u32 XLz77_Get_optype(XLz77 *InstancePtr);
void XLz77_Set_streamInSize(XLz77 *InstancePtr, u32 Data);
u32 XLz77_Get_streamInSize(XLz77 *InstancePtr);

void XLz77_InterruptGlobalEnable(XLz77 *InstancePtr);
void XLz77_InterruptGlobalDisable(XLz77 *InstancePtr);
void XLz77_InterruptEnable(XLz77 *InstancePtr, u32 Mask);
void XLz77_InterruptDisable(XLz77 *InstancePtr, u32 Mask);
void XLz77_InterruptClear(XLz77 *InstancePtr, u32 Mask);
u32 XLz77_InterruptGetEnabled(XLz77 *InstancePtr);
u32 XLz77_InterruptGetStatus(XLz77 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
