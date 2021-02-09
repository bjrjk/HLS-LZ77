#ifndef AXIS_STREAM_HARDWARE_H
#define AXIS_STREAM_HARDWARE_H

#include <hls_stream.h>

void stream_test(
		hls::stream<unsigned char>& streamIn,
		hls::stream<unsigned char>& streamOut,
		int streamSize
		);

#endif