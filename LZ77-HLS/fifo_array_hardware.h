#ifndef FIFO_ARRAY_HARDWARE_H
#define FIFO_ARRAY_HARDWARE_H

#include <hls_stream.h>

void fifo_array_hardware(
		hls::stream<unsigned char>& streamIn,
		hls::stream<unsigned char>& streamOut,
		int streamSize
		);

#endif