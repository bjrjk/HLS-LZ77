#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_mem.h"
#include "stdio_d.h"
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

u8 *TxBufferPtr= (u8 *)TX_BUFFER_BASE;
u8 *RxBufferPtr= (u8 *)RX_BUFFER_BASE;

int DMA_Recv(int bufSize)
{
	int Status;
	RxDone = 0;
	Error = 0;

	Status = XAxiDma_SimpleTransfer(&AxiDma,(u32) RxBufferPtr,
			bufSize, XAXIDMA_DEVICE_TO_DMA);
	if (Status != XST_SUCCESS) return XST_FAILURE;
	while (!RxDone);
	//while (XAxiDma_Busy(&AxiDma, XAXIDMA_DEVICE_TO_DMA));
	if (Error) return XST_FAILURE;
	Xil_DCacheInvalidateRange((u32)RxBufferPtr, bufSize);

	return XST_SUCCESS;
}

int DMA_Send(int bufSize)
{
	int Status;
	TxDone = 0;
	Error = 0;

	Xil_DCacheFlushRange((u32)TxBufferPtr, bufSize);
	Status = XAxiDma_SimpleTransfer(&AxiDma,(u32) TxBufferPtr,
			bufSize, XAXIDMA_DMA_TO_DEVICE);
	if (Status != XST_SUCCESS) return XST_FAILURE;
	while (!TxDone);
	//while (XAxiDma_Busy(&AxiDma, XAXIDMA_DMA_TO_DEVICE));

	if (Error) return XST_FAILURE;
	else return XST_SUCCESS;
}

int init_LZ77(){
	print("LZ77 Hardware Implementation, Standalone UART:\n\r");
	LZ77_configPtr = XLz77_LookupConfig(XPAR_LZ77_0_DEVICE_ID);
	if (!LZ77_configPtr)
	{
		xil_printf("ERROR: Lookup of accelerator configuration failed.\n\r");
		return XST_FAILURE;
	}
	xil_printf("Initialize the device\n\r");
	long status = XLz77_CfgInitialize(&LZ77, LZ77_configPtr);
	if (status != XST_SUCCESS)
	{
		xil_printf("ERROR: Could not initialize accelerator.\n\r");
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

void init()
{
    init_platform();
    DMA_Intr_Init(&AxiDma,0);
    Init_Intr_System(&Intc);
    Setup_Intr_Exception(&Intc);
    DMA_Setup_Intr_System(&Intc,&AxiDma,TX_INTR_ID,RX_INTR_ID);
    DMA_Intr_Enable(&Intc,&AxiDma);
    init_LZ77();
}

void uninit()
{
	cleanup_platform();
}

void compress_test()
{
	//Compress Test
	xil_printf("Compress Test Start...\n\r");
	unsigned char data_to_compress[1000] = "12341234";
	unsigned char data_compressed[1000];
	unsigned char data_compressed_std[1000] = "\x31\x32\x33\x34\x5C\x00\xFC\x0F\x00\x00\x04\x00\x00\x00\x5D\x5D\x00\x5C";
	Xil_MemCpy(TxBufferPtr, data_to_compress, sizeof(data_to_compress));
	int data_to_compress_len = 8;
	XLz77_Set_optype(&LZ77, 0);
	XLz77_Set_streamInSize(&LZ77, data_to_compress_len);
	DMA_Send(data_to_compress_len);
	XLz77_Start(&LZ77);
	while(XLz77_IsDone(&LZ77) == 0);
	int data_compressed_len = XLz77_Get_return(&LZ77);
	DMA_Recv(data_compressed_len+1);
	Xil_MemCpy(data_compressed, RxBufferPtr, data_compressed_len);
	xil_printf("Compressed Data Size:%d\n\r", data_compressed_len);
	for(int i=0;i<data_compressed_len;i++){
		if(data_compressed_std[i] != data_compressed[i]){
			xil_printf("Failed!\n\r");
			return XST_FAILURE;
		}
	}
	xil_printf("Compress Success!\n\r");
}

void decompress_test()
{
	//Decompress Test
	xil_printf("Decompress Test Start...\n\r");
	unsigned char data_to_compress[1000] = "12341234";
	unsigned char data_decompressed[1000];
	unsigned char data_compressed_std[1000] = "\x31\x32\x33\x34\x5C\x00\xFC\x0F\x00\x00\x04\x00\x00\x00\x5D\x5D\x00\x5C";
	Xil_MemCpy(TxBufferPtr, data_compressed_std, sizeof(data_compressed_std));
	int data_to_decompress_len = 18;
	XLz77_Set_optype(&LZ77, 1);
	XLz77_Set_streamInSize(&LZ77, data_to_decompress_len);
	DMA_Send(data_to_decompress_len);
	XLz77_Start(&LZ77);
	while(XLz77_IsDone(&LZ77) == 0);
	int data_decompressed_len = XLz77_Get_return(&LZ77);
	DMA_Recv(data_decompressed_len+1);
	Xil_MemCpy(data_decompressed, RxBufferPtr, data_decompressed_len);
	xil_printf("Decompressed Data Size:%d\n\r", data_decompressed_len);
	for(int i=0;i<data_decompressed_len;i++){
		if(data_to_compress[i] != data_decompressed[i]){
			xil_printf("Failed!\n\r");
			return XST_FAILURE;
		}
	}
	xil_printf("Decompress Success!\n\r");
}

int main()
{
	init();

	compress_test();
	decompress_test();

	xil_printf("LZ77 Hardware Implementation Finished!\n\r");

    uninit();
    return 0;
}
