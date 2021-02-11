#include "sys_intr.h"
void Setup_Intr_Exception(XScuGic * IntcInstancePtr)
{
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
            (Xil_ExceptionHandler)XScuGic_InterruptHandler,
            (void *)IntcInstancePtr);

    Xil_ExceptionEnable();
}

int Init_Intr_System(XScuGic * IntcInstancePtr)
{
    int Status;
    XScuGic_Config *IntcConfig;
    IntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
    if (NULL == IntcConfig) {
        return XST_FAILURE;
    }
    Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,IntcConfig->CpuBaseAddress);
    if (Status != XST_SUCCESS) {return XST_FAILURE;}
    return XST_SUCCESS;
}
