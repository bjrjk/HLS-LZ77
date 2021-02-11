#ifndef LZ77_H
#define LZ77_H

#include <hls_stream.h>
#include <ap_axi_sdata.h>
#include "fifo_array.cpp"


extern int LZ77_BUFFER_SIZE;
extern int LZ77_WINDOW_SIZE;
extern const char LZ77_ESCAPE_CHAR;
/*	When the low byte of window offset is LZ77_BUFFER_SIZE in compressed data, decompress 
	algorithm will recognize compressed data as uncompressed data incorrectly. So insert 
	a split char after the escape. */
extern const char LZ77_SPLIT_CHAR;
#define FIFO_ARRAY_BUFFER_SIZE 8192
typedef ap_axis<8,0,0,0> stream_t;
typedef FIFO_Array_APInt<8, FIFO_ARRAY_BUFFER_SIZE> FIFO_Array_UC_BUF;

unsigned int lz77(
		bool optype, // optype==false: compress; optype==true: decompress
		hls::stream<stream_t>& streamIn,
		hls::stream<stream_t>& streamOut,
		int streamInSize
		);

unsigned int lz77_compress(
		FIFO_Array_UC_BUF& origin, 
		FIFO_Array_UC_BUF& compression
		);

unsigned int lz77_decompress(
		FIFO_Array_UC_BUF& compression, 
		FIFO_Array_UC_BUF& origin
		);

#endif
