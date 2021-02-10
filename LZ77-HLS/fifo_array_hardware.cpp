#include "fifo_array_hardware.h"
#include "fifo_array.cpp"
#include <algorithm>
#define ARRAY_LEN 64

void fifo_array_hardware(
		hls::stream<unsigned char>& streamIn,
		hls::stream<unsigned char>& streamOut,
		int streamSize
		){
#pragma HLS INTERFACE axis register port=streamOut
#pragma HLS INTERFACE axis register port=streamIn
	FIFO_Array<unsigned char, ARRAY_LEN> fifoInArr(streamIn, streamSize);
	FIFO_Array<unsigned char, ARRAY_LEN> fifoOutArr(streamOut);
	fifoInArr.init_load();
	int ptr=0;
	do{
		int size = (streamSize - ptr >=  ARRAY_LEN) ? ARRAY_LEN : (streamSize - ptr);
		for(int i=0;i<size;i++,ptr++){
			fifoOutArr[ptr] = fifoInArr[ptr];
		}
		fifoOutArr.write(size);
	}while(!fifoInArr.load(ARRAY_LEN));
}
