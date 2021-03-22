#include <algorithm>
#ifndef __SYNTHESIS__
#include <cassert>
#endif
#include <hls_stream.h>
#include "fifo_array.cpp"
#include "lz77.h"
using std::min;
using std::max;
int LZ77_BUFFER_SIZE = 128;
int LZ77_WINDOW_SIZE = 4096;
const char LZ77_ESCAPE_CHAR = '\\';
const char LZ77_SPLIT_CHAR = '\0';

static inline int putEscapedChar(FIFO_Array_UC_BUF& arr, unsigned char c, bool ctrl = false) {
#pragma HLS INLINE
	if (ctrl) {
		arr.push_back(LZ77_ESCAPE_CHAR);
		return 1;
	}
	else if (c == LZ77_ESCAPE_CHAR) {
		arr.push_back(LZ77_ESCAPE_CHAR);
		arr.push_back(LZ77_ESCAPE_CHAR);
		return 2;
	}
	else {
		arr.push_back(c);
		return 1;
	}
}
static inline unsigned char readEscapedChar(FIFO_Array_UC_BUF& arr, int& i,
	bool& ctrl, bool modifyIndex = true) {
#pragma HLS INLINE
	if (arr[i] == LZ77_ESCAPE_CHAR && (i + 1 >= arr.size() || arr[i + 1] != LZ77_ESCAPE_CHAR)) {
		if (modifyIndex){
			i++;
			arr.load(1);
		}
		ctrl = true;
		return LZ77_ESCAPE_CHAR;
	}
	else if (arr[i] == LZ77_ESCAPE_CHAR && (i + 1 < arr.size() && arr[i + 1] == LZ77_ESCAPE_CHAR)) {
		if (modifyIndex){
			i += 2;
			arr.load(2);
		}
		ctrl = false;
		return LZ77_ESCAPE_CHAR;
	}
	else {
		char c = arr[i];
		if (modifyIndex){
			i++;
			arr.load(1);
		}
		ctrl = false;
		return c;
	}
}
static inline void getLongestMatchingPhrase(const FIFO_Array_UC_BUF& data,
	const int windowStart, const int bufferStart, int& phraseStart, int& phraseLength,
	bool& firstCExists, unsigned char& firstC) {
	// Can be optimized using KMP, current is brute-force
	phraseStart = bufferStart;
	phraseLength = 0;
	firstCExists = false;
	for (int winIter = max(windowStart, 0);
		winIter < min(windowStart + LZ77_WINDOW_SIZE, data.size());
		winIter++) {
		for (int bufIter = bufferStart; bufIter < min(bufferStart + LZ77_BUFFER_SIZE, data.size()); bufIter++) {
#pragma HLS LOOP_FLATTEN
#pragma HLS UNROLL factor=48
			int tmpPhrasePos = bufIter - bufferStart;
			if (winIter + tmpPhrasePos >= min(windowStart + LZ77_WINDOW_SIZE, data.size()))break;
			if (data[winIter + tmpPhrasePos] != data[bufIter])break;
			int tmpPhraseLen = tmpPhrasePos + 1;
			if (tmpPhraseLen > phraseLength) {
				phraseStart = winIter - windowStart;
				phraseLength = tmpPhraseLen;
				firstCExists = bufIter + 1 < data.size();
				if (firstCExists) firstC = data[bufIter + 1];
			}
		}
	}
}
static inline void sizet2bytes(int num, unsigned char bytes[4]) {  //Little Endian
#pragma HLS INLINE
	unsigned char* ptr = reinterpret_cast<unsigned char*>(&num);
#ifndef __SYNTHESIS__
	assert(sizeof(int) == 4);
#endif
	for (int i = 0; i < sizeof(int); i++) {
#pragma HLS UNROLL
		bytes[i] = *ptr;
		ptr++;
	}
}
static inline int bytes2sizet(const FIFO_Array_UC_BUF& data, int startIndex) {
#pragma HLS INLINE
	int result;
	unsigned char* ptr = reinterpret_cast<unsigned char*>(&result);
	for (int i = 0; i < sizeof(int); i++) {
#pragma HLS UNROLL
		*ptr = data[startIndex + i];
		ptr++;
	}
	return result;
}
static void writeCtrlData(FIFO_Array_UC_BUF& data,
	int phraseStart, int phraseLength, unsigned char firstC, bool firstCExists = true) {
	unsigned char phraseStartBytes[4], phraseLengthBytes[4];
	sizet2bytes(phraseStart, phraseStartBytes);
	sizet2bytes(phraseLength, phraseLengthBytes);
	putEscapedChar(data, LZ77_ESCAPE_CHAR, true);
	putEscapedChar(data, LZ77_SPLIT_CHAR);
	for(int i=0;i<4;i++) data.push_back(phraseStartBytes[i]);
	for(int i=0;i<4;i++) data.push_back(phraseLengthBytes[i]);
	if (firstCExists)putEscapedChar(data, firstC);
	else {
		putEscapedChar(data, LZ77_ESCAPE_CHAR + 1);
		putEscapedChar(data, LZ77_ESCAPE_CHAR + 1);
	}
	putEscapedChar(data, LZ77_SPLIT_CHAR);
	putEscapedChar(data, LZ77_ESCAPE_CHAR, true);
}
static bool readCtrlData(FIFO_Array_UC_BUF& data, int& i,
	int& phraseStart, int& phraseLength, unsigned char& firstC, bool& firstCExists) {
	bool ctrl;
	readEscapedChar(data, i, ctrl, false);
	if (!ctrl) return false;
	readEscapedChar(data, i, ctrl);
	readEscapedChar(data, i, ctrl);
	phraseStart = bytes2sizet(data, i);
	i += sizeof(int);
	data.load(sizeof(int));
	phraseLength = bytes2sizet(data, i);
	i += sizeof(int);
	data.load(sizeof(int));
	firstCExists = !(i + 1 < data.size() && data[i] == LZ77_ESCAPE_CHAR + 1 && data[i + 1] == LZ77_ESCAPE_CHAR + 1);
	if (firstCExists) {
		firstC = readEscapedChar(data, i, ctrl);
	}
	else{
		i += 2;
		data.load(2);
	}
	i += 2;
	data.load(2);
	return true;
}
unsigned int lz77_compress(FIFO_Array_UC_BUF& origin, FIFO_Array_UC_BUF& compression) {
	int windowStart = -LZ77_WINDOW_SIZE, bufferStart = 0;
	int phraseStart, phraseLength;
	origin.init_load();
	while (windowStart < origin.size() && bufferStart < origin.size()) {
		bool firstCExists;
		unsigned char firstC;
		getLongestMatchingPhrase(origin, windowStart, bufferStart,
			phraseStart, phraseLength, firstCExists, firstC);
		if (!firstCExists)firstC = 0;
		if (phraseLength == 0) putEscapedChar(compression, origin[phraseStart]);
		else writeCtrlData(compression, phraseStart, phraseLength, firstC, firstCExists);
		windowStart += phraseLength + 1;
		bufferStart += phraseLength + 1;
	}
	compression.write_eof();
	return compression.write_size();
}
unsigned int lz77_decompress(FIFO_Array_UC_BUF& compression, FIFO_Array_UC_BUF& origin) {
	int windowStart = -LZ77_WINDOW_SIZE;
	int compressIndex = 0;
	int phraseStart, phraseLength;
	unsigned char c;
	bool ctrl, firstCExists;
	compression.init_load();
	while (compressIndex < compression.size()) {
		readEscapedChar(compression, compressIndex, ctrl, false);
		if (ctrl) {
			readCtrlData(compression, compressIndex, phraseStart, phraseLength, c, firstCExists);
			origin.insert_back_self(
				windowStart + phraseStart,
				windowStart + phraseStart + phraseLength);
			windowStart += phraseLength + firstCExists;
		}
		else {
			firstCExists = true;
			c = readEscapedChar(compression, compressIndex, ctrl);
			windowStart++;
		}
		if (firstCExists)origin.push_back(c);
	}
	origin.write_eof();
	return origin.write_size();
}
unsigned int lz77(
		bool optype, // optype==false: compress; optype==true: decompress
		hls::stream<stream_t>& streamIn,
		hls::stream<stream_t>& streamOut,
		int streamInSize
		){
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE s_axilite port=streamInSize
#pragma HLS INTERFACE s_axilite port=optype
#pragma HLS INTERFACE axis register both port=streamOut
#pragma HLS INTERFACE axis register both port=streamIn
	FIFO_Array_UC_BUF fifoInArr(streamIn, streamInSize);
	FIFO_Array_UC_BUF fifoOutArr(streamOut);
	if(!optype)
		return lz77_compress(fifoInArr, fifoOutArr) - 1;
	else
		return lz77_decompress(fifoInArr, fifoOutArr) - 1;
}
