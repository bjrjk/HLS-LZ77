#include <stdlib.h>
#include "xparameters.h"
#include "xuartps.h"
#include "xil_printf.h"
#include "sleep.h"

char getchar_d(){
	char c = '\0';
	while(!XUartPs_IsReceiveData(STDIN_BASEADDRESS))
		usleep(10);
	c = XUartPs_ReadReg(STDIN_BASEADDRESS, XUARTPS_FIFO_OFFSET);
	if(c != '\r')
		xil_printf("%c",c);
	else
		xil_printf("\n\r");
	return c;
}

void gets_d(char* buf, int size){
	int i = 0;
	char c;
	while((c = getchar_d()) != '\r' && i < size - 1){
		buf[i++] = c;
	}
	buf[i] = '\0';
}

unsigned long getulong(){
	char buf[50];
	char* ptr;
	gets_d(buf, 50);
	return strtoul(buf, &ptr, 0);
}
