#ifndef DMA_INTR_H
#define DMA_INTR_H
#include "xaxidma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xdebug.h"
#include "xscugic.h"
/************************** Constant Definitions *****************************/
/*
 * Device hardware build related constants.
 */
#define DMA_DEV_ID      XPAR_AXIDMA_0_DEVICE_ID
#define MEM_BASE_ADDR       0x01000000

#define RX_INTR_ID      XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR
#define TX_INTR_ID      XPAR_FABRIC_AXI_DMA_0_MM2S_INTROUT_INTR

#define TX_BUFFER_BASE      (MEM_BASE_ADDR + 0x00100000)
#define RX_BUFFER_BASE      (MEM_BASE_ADDR + 0x00300000)

#define RESET_TIMEOUT_COUNTER   10000

extern volatile int TxDone;
extern volatile int RxDone;
extern volatile int Error;

int  DMA_Setup_Intr_System(XScuGic * IntcInstancePtr,XAxiDma * AxiDmaPtr, u16 TxIntrId, u16 RxIntrId);
int  DMA_Intr_Enable(XScuGic * IntcInstancePtr,XAxiDma *DMAPtr);
int  DMA_Intr_Init(XAxiDma *DMAPtr,u32 DeviceId);
void DMA_DisableIntrSystem(XScuGic * IntcInstancePtr,u16 TxIntrId, u16 RxIntrId);
#endif
