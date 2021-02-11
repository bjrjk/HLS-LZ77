// ==============================================================
// File generated on Thu Feb 11 11:55:32 +0800 2021
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xlz77.h"

extern XLz77_Config XLz77_ConfigTable[];

XLz77_Config *XLz77_LookupConfig(u16 DeviceId) {
	XLz77_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XLZ77_NUM_INSTANCES; Index++) {
		if (XLz77_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XLz77_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XLz77_Initialize(XLz77 *InstancePtr, u16 DeviceId) {
	XLz77_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XLz77_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XLz77_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

