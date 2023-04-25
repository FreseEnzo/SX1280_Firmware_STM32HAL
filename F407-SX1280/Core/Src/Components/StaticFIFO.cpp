/*
 * DebugFIFO.cpp
 *
 *  Created on: May 26, 2022
 *      Author: Gabriel
 */

#include "StaticFIFO.hpp"

#include <cstring>

StaticFIFO::StaticFIFO(uint32_t fifoSize) : fifoSize(fifoSize){
	fifo = new StringContainer[fifoSize];
}

StaticFIFO::~StaticFIFO() {
	delete fifo;
}

int32_t StaticFIFO::push(const char* string){
	if (((fifoSize + firstIdx) - lastIdx) % fifoSize == 1) {
		return 0; //overflow
	}else if(strlen(string) + 1 > bufSize){
		return -2; //length limit
	}
	StringContainer stringContainer;
	for(uint32_t i=0; i < (strlen(string) + 1); i++){
		stringContainer.buffer[i] = string[i];
	}
	stringContainer.length = strlen(string) + 1;
	fifo[lastIdx] = stringContainer;
	lastIdx = (lastIdx + 1) % fifoSize;
	return (((fifoSize + lastIdx) - firstIdx) % fifoSize);
}

int32_t StaticFIFO::push(uint8_t* pointer, uint32_t length){
	if (((fifoSize + firstIdx) - lastIdx) % fifoSize == 1) {
		return 0; //overflow
	}else if(length > bufSize){
		return -2; //length limit
	}
	StringContainer stringContainer;
	for(uint32_t i=0; i < length; i++){
		stringContainer.buffer[i] = pointer[i];
	}
	stringContainer.length = length;
	fifo[lastIdx] = stringContainer;
	lastIdx = (lastIdx + 1) % fifoSize;
	return (((fifoSize + lastIdx) - firstIdx) % fifoSize);
}

int32_t StaticFIFO::push(char* stringPointer, uint32_t stringLength){
	if (((fifoSize + firstIdx) - lastIdx) % fifoSize == 1) {
		return 0; //overflow
	}else if(stringLength > bufSize){
		return -2; //length limit
	}
	StringContainer stringContainer;
	for(uint32_t i=0; i < (stringLength); i++){
		stringContainer.buffer[i] = stringPointer[i];
	}
	stringContainer.length = stringLength;
	fifo[lastIdx] = stringContainer;
	lastIdx = (lastIdx + 1) % fifoSize;
	return (((fifoSize + lastIdx) - firstIdx) % fifoSize);
}

int32_t StaticFIFO::pop(uint8_t** pointer, uint32_t* length, uint32_t max_length){
    if (lastIdx == firstIdx){
    	return -1;	//underrun
    }else if(fifo[firstIdx].length > max_length){
    	return -2;	//length limit
    }
    *pointer = fifo[firstIdx].buffer;
    *length = fifo[firstIdx].length;
    firstIdx = (firstIdx + 1) % fifoSize;
    return (((fifoSize + lastIdx) - firstIdx) % fifoSize);
}
