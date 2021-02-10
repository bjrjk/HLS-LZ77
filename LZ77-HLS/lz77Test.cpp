#include <iostream>
#include <cstring>
#include "axis_stream_hardware.h"
#include "fifo_array.cpp"
#include "fifo_array_hardware.h"
#include "mod_hardware.h"
int axis_stream_hardware_test(){
	unsigned char data_origin[] = "1234567891011121314151617181920";
	unsigned char data_read[sizeof(data_origin)];
	hls::stream<unsigned char> streamIn("streamIn"), streamOut("streamOut");
	for(int i=0;i<sizeof(data_origin);i++)
		streamIn << data_origin[i];
	stream_test(streamIn, streamOut, sizeof(data_origin));
	for(int i=0;i<sizeof(data_origin);i++)
		streamOut >> data_read[i];
	for(int i=0;i<sizeof(data_origin);i++)
		if(data_origin[i] != data_read[i])
			return 1;
	return 0;
}
int mod_hardware_test(){
	return MOD(10, 3) != 1;
}
int fifo_array_test_1(){
	unsigned char data_origin[] = "1234567891011121314151617181920";
	unsigned char data_read[sizeof(data_origin)];
	hls::stream<unsigned char> streamIn("streamIn"), streamOut("streamOut");
	for(int i=0;i<sizeof(data_origin);i++)
		streamIn << data_origin[i];
	fifo_array_hardware(streamIn, streamOut, sizeof(data_origin));
	for(int i=0;i<sizeof(data_origin);i++)
		streamOut >> data_read[i];
	for(int i=0;i<sizeof(data_origin);i++)
		if(data_origin[i] != data_read[i])
			return 1;
	return 0;
}
int fifo_array_test_2(){
	unsigned char data_origin[] = "1234567891011121314151617181920212223242526272829303132333435363738394041424344454647484950";
	unsigned char data_read[sizeof(data_origin)];
	hls::stream<unsigned char> streamIn("streamIn"), streamOut("streamOut");
	for(int i=0;i<sizeof(data_origin);i++)
		streamIn << data_origin[i];
	fifo_array_hardware(streamIn, streamOut, sizeof(data_origin));
	for(int i=0;i<sizeof(data_origin);i++)
		streamOut >> data_read[i];
	for(int i=0;i<sizeof(data_origin);i++)
		if(data_origin[i] != data_read[i])
			return 1;
	return 0;
}
int main(){
	return fifo_array_test_2();
}
