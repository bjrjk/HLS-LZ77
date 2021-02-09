#include <iostream>
#include <cstring>
#include "axis_stream_hardware.h"
static int axis_stream_hardware_test(){
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
int main(){
	return axis_stream_hardware_test();
}
