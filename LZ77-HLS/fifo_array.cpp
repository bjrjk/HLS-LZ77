#ifndef FIFO_ARRAY_H
#define FIFO_ARRAY_H

#ifndef __SYNTHESIS__
#include <cassert>
#endif
#include <algorithm>
#include <hls_stream.h>

// arrayLen must be a power of 2
template <typename T, unsigned int arrayLen>
class FIFO_Array{
private:
	T arr[arrayLen];
	unsigned int headIndex, streamSize;
	hls::stream<T>& stream_fifo;
public:
	FIFO_Array(hls::stream<T>& stream_fifo, unsigned int streamSize):
		headIndex(0), stream_fifo(stream_fifo), streamSize(streamSize) {
#ifndef __SYNTHESIS__
		assert((arrayLen & (arrayLen - 1)) == 0);
#endif
	}
	const T& operator [] (unsigned int i) const{
#ifndef __SYNTHESIS__
		assert(headIndex <= i && i < headIndex + arrayLen);
#endif
		return arr[i - headIndex];
	}
	T& operator [] (unsigned int i){
#ifndef __SYNTHESIS__
		assert(headIndex <= i && i < headIndex + arrayLen);
#endif
		return arr[i - headIndex];
	}
	void init_load(){
init_load_loop:
		for(int i=0;i<arrayLen;i++){
#pragma HLS UNROLL factor=4
			stream_fifo >> arr[i];
		}
	}
	void load(unsigned int size){
		if(size > arrayLen)return;
		if(headIndex + arrayLen + size >= streamSize)
			size = streamSize - headIndex - arrayLen;
load_loop:
		for(int i=0;i<size;i++){
#pragma HLS UNROLL factor=4
			stream_fifo >> arr[(headIndex + i) % arrayLen];
		}
		headIndex += size;
	}
};

#endif
