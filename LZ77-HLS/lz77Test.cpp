#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include "axis_stream_hardware.h"
#include "fifo_array.cpp"
#include "fifo_array_hardware.h"
#include "mod_hardware.h"
#include "lz77.h"
using namespace std;
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
void readBin(string fileName, vector<unsigned char>& data) {
	ifstream f(fileName, ios::binary);
	char c;
	if (!f)return;
	do {
		f.read(&c, 1);
		if(!f.eof())data.push_back(c);
	} while (!f.eof());
	f.close();
}
bool cmpBin(const vector<unsigned char>& data1, const vector<unsigned char>& data2) {
	if (data1.size() != data2.size())return false;
	for (int i = 0; i < data1.size(); i++) {
		if (data1[i] != data2[i])return false;
	}
	return true;
}
int lz77_cosimu_test_zip(){
	unsigned char data_origin[] = "12341234";
	unsigned char data_std[]="\x31\x32\x33\x34\x5C\x00\xFC\x0F\x00\x00\x04\x00\x00\x00\x5D\x5D\x00\x5C";
	unsigned char data_read[100];
	hls::stream<stream_t> streamComIn("streamComIn"), streamComOut("streamComOut");
	for(int i=0;i<8;i++){
		stream_t tmp;
		tmp.data = data_origin[i];
		streamComIn << tmp;
	}
	unsigned int sizeCom = lz77(
			false, // optype==false: compress; optype==true: decompress
			streamComIn,
			streamComOut,
			8
	);
	for(int i=0;i<=sizeCom;i++){
		stream_t tmp;
		streamComOut >> tmp;
		data_read[i] = tmp.data;
	}
	if(sizeof(data_std)-1 != sizeCom)return 2;
	for(int i=0;i<sizeCom;i++)
		if(data_read[i] != data_std[i])
			return 1;
	return 0;
}
int lz77_cosimu_test_unzip(){
	unsigned char data_origin[] = "12341234";
	unsigned char data_std[]="\x31\x32\x33\x34\x5C\x00\xFC\x0F\x00\x00\x04\x00\x00\x00\x5D\x5D\x00\x5C";
	unsigned char data_read[100];
	hls::stream<stream_t> streamComIn("streamComIn"), streamComOut("streamComOut");
	for(int i=0;i<sizeof(data_std)-1;i++){
		stream_t tmp;
		tmp.data = data_std[i];
		streamComIn << tmp;
	}
	unsigned int sizeDeCom = lz77(
			true, // optype==false: compress; optype==true: decompress
			streamComIn,
			streamComOut,
			sizeof(data_std)-1
	);
	for(int i=0;i<=sizeDeCom;i++){
		stream_t tmp;
		streamComOut >> tmp;
		data_read[i] = tmp.data;
	}
	if(sizeof(data_origin)-1 != sizeDeCom)return 2;
	for(int i=0;i<sizeDeCom;i++)
		if(data_read[i] != data_origin[i])
			return 1;
	return 0;
}
int main(){
	return lz77_cosimu_test_unzip();
}
