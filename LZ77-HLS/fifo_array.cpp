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
	unsigned int readIndex, writeIndex, streamSize;
	hls::stream<T>& stream_fifo;
public:
	FIFO_Array(hls::stream<T>& stream_fifo):
		readIndex(0), writeIndex(0),
		stream_fifo(stream_fifo), streamSize(0) {
#ifndef __SYNTHESIS__
		assert((arrayLen & (arrayLen - 1)) == 0);
		printf("Write_FIFO_Array Constructor£º %x\n",&stream_fifo);
#endif
	}
	FIFO_Array(hls::stream<T>& stream_fifo, unsigned int streamSize):
		readIndex(0), writeIndex(0),
		stream_fifo(stream_fifo), streamSize(streamSize) {
#ifndef __SYNTHESIS__
		assert((arrayLen & (arrayLen - 1)) == 0);
		printf("Read_FIFO_Array Constructor£º %x\n",&stream_fifo);
#endif
	}
	const T& operator [] (unsigned int i) const{
#ifndef __SYNTHESIS__
		assert(readIndex <= i && i < readIndex + arrayLen);
#endif
		return arr[i % arrayLen];
	}
	T& operator [] (unsigned int i){
#ifndef __SYNTHESIS__
		assert(readIndex <= i && i < readIndex + arrayLen);
#endif
		return arr[i % arrayLen];
	}
	void init_load(){
init_load_loop:
		for(int i=0;i<std::min(arrayLen, streamSize);i++){
#pragma HLS UNROLL factor=4
			stream_fifo >> arr[i];
		}
	}
	bool load(unsigned int size){ //Indicate the stream is EOF
		if(size > arrayLen)return false;
		if(readIndex + arrayLen >= streamSize)return true;
		if(readIndex + arrayLen + size >= streamSize)
			size = streamSize - readIndex - arrayLen;
load_loop:
		for(int i=0;i<size;i++){
#pragma HLS UNROLL factor=4
			stream_fifo >> arr[(readIndex + i) % arrayLen];
		}
		readIndex += size;
		return false;
	}
	void write(unsigned int size){
		if(size > arrayLen)return;
write_loop:
		for(int i=0;i<size;i++){
#pragma HLS UNROLL factor=4
			stream_fifo << arr[(writeIndex + i) % arrayLen];
		}
		writeIndex += size;
		readIndex += size;
	}
};

#endif
