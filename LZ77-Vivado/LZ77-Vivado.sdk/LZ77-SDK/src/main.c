#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_mem.h"
#include "stdio_d.h"
#include "xtime_l.h"
#include "xparameters.h"
#include "xuartps.h"
#include "sleep.h"
#include "dma_intr.h"
#include "sys_intr.h"
#include "xlz77.h"

static XScuGic Intc;
static XAxiDma AxiDma;
static XLz77 LZ77;
static XLz77_Config* LZ77_configPtr;

u8 *TxBufferPtr = (u8 *) TX_BUFFER_BASE;
u8 *RxBufferPtr = (u8 *) RX_BUFFER_BASE;

int DMA_Recv(int bufSize) {
	int Status;
	RxDone = 0;
	Error = 0;

	Status = XAxiDma_SimpleTransfer(&AxiDma, (u32) RxBufferPtr, bufSize,
			XAXIDMA_DEVICE_TO_DMA);
	if (Status != XST_SUCCESS)
		return XST_FAILURE;
	while (!RxDone)
		;
	//while (XAxiDma_Busy(&AxiDma, XAXIDMA_DEVICE_TO_DMA));
	if (Error)
		return XST_FAILURE;
	Xil_DCacheInvalidateRange((u32) RxBufferPtr, bufSize);

	return XST_SUCCESS;
}

int DMA_Send(int bufSize) {
	int Status;
	TxDone = 0;
	Error = 0;

	Xil_DCacheFlushRange((u32) TxBufferPtr, bufSize);
	Status = XAxiDma_SimpleTransfer(&AxiDma, (u32) TxBufferPtr, bufSize,
			XAXIDMA_DMA_TO_DEVICE);
	if (Status != XST_SUCCESS)
		return XST_FAILURE;
	while (!TxDone)
		;
	//while (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE));

	if (Error)
		return XST_FAILURE;
	else
		return XST_SUCCESS;
}

int init_LZ77() {
	LZ77_configPtr = XLz77_LookupConfig(XPAR_LZ77_0_DEVICE_ID);
	if (!LZ77_configPtr) {
		xil_printf("ERROR: Lookup of accelerator configuration failed.\n\r");
		return XST_FAILURE;
	}
	xil_printf("Initialize the device\n\r");
	long status = XLz77_CfgInitialize(&LZ77, LZ77_configPtr);
	if (status != XST_SUCCESS) {
		xil_printf("ERROR: Could not initialize accelerator.\n\r");
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

void init() {
	init_platform();
	DMA_Intr_Init(&AxiDma, 0);
	Init_Intr_System(&Intc);
	Setup_Intr_Exception(&Intc);
	DMA_Setup_Intr_System(&Intc, &AxiDma, TX_INTR_ID, RX_INTR_ID);
	DMA_Intr_Enable(&Intc, &AxiDma);
	init_LZ77();
}

void uninit() {
	cleanup_platform();
}

void compress(unsigned char* src, unsigned char* dst, int src_len, int* dst_len) {
	Xil_MemCpy(TxBufferPtr, src, src_len);
	XLz77_Set_optype(&LZ77, 0);
	XLz77_Set_streamInSize(&LZ77, src_len);
	DMA_Send(src_len);
	XLz77_Start(&LZ77);
	while (XLz77_IsDone(&LZ77) == 0)
		;
	*dst_len = XLz77_Get_return(&LZ77);
	DMA_Recv((*dst_len) + 1);
	Xil_MemCpy(dst, RxBufferPtr, *dst_len);
}

void decompress(unsigned char* src, unsigned char* dst, int src_len,
		int* dst_len) {
	Xil_MemCpy(TxBufferPtr, src, src_len);
	XLz77_Set_optype(&LZ77, 1);
	XLz77_Set_streamInSize(&LZ77, src_len);
	DMA_Send(src_len);
	XLz77_Start(&LZ77);
	while (XLz77_IsDone(&LZ77) == 0)
		;
	*dst_len = XLz77_Get_return(&LZ77);
	DMA_Recv((*dst_len) + 1);
	Xil_MemCpy(dst, RxBufferPtr, *dst_len);
}

void LZ77_Test(unsigned char* src, unsigned char* dst, unsigned char* mid, int src_len) {
	XTime tEnd, tCur;
	u32 tUsed;
	int dst_len, mid_len;
	xil_printf("LZ77 Algorithm Test Start...\r\n");
	xil_printf("Original data size is %d\r\n", src_len);
	XTime_GetTime(&tCur);
	compress(src, dst, src_len, &dst_len);
	XTime_GetTime(&tEnd);
	tUsed = ((tEnd - tCur) * 1000000) / (COUNTS_PER_SECOND);
	xil_printf("Compressed data size is %d\r\n", dst_len);
	xil_printf("Compress time elapsed is %d us\r\n", tUsed);
	XTime_GetTime(&tCur);
	decompress(dst, mid, dst_len, &mid_len);
	XTime_GetTime(&tEnd);
	tUsed = ((tEnd - tCur) * 1000000) / (COUNTS_PER_SECOND);
	xil_printf("Decompressed data size is %d\r\n", mid_len);
	xil_printf("Decompress time elapsed is %d us\r\n", tUsed);
	if(memcmp(src, mid, src_len))
		xil_printf("LZ77 algorithm detected wrong result.\r\n");
	else
		xil_printf("LZ77 algorithm finished successfully.\r\n");
}

int main() {
	init();
	xil_printf(
			"LZ77 hardware standalone implementation, Console output via UART:\n\r");

	unsigned char src[] = "12341234";
	unsigned char dst[10000];
	unsigned char mid[10000];

	LZ77_Test(src, dst, mid, sizeof(src) - 1);

	xil_printf("LZ77 Hardware Implementation Finished!\n\r");
	uninit();
	return 0;
}
