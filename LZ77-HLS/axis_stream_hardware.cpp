#include "axis_stream_hardware.h"

void stream_test(
		hls::stream<unsigned char>& streamIn,
		hls::stream<unsigned char>& streamOut,
		int streamSize
		){
#pragma HLS INTERFACE axis register port=streamOut
#pragma HLS INTERFACE axis register port=streamIn
	unsigned char c;
	for(int i=0;i<streamSize;i++){
		streamIn >> c;
		streamOut << c;
	}
}
