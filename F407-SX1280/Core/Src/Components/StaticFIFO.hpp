/*
 * DebugFIFO.hpp
 *
 *  Created on: May 26, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_STATICFIFO_HPP_
#define SRC_COMPONENTS_STATICFIFO_HPP_

#include "main.h"

class StaticFIFO {
public:
	StaticFIFO(uint32_t fifoSize);
	virtual ~StaticFIFO();
	int32_t push(const char* string);
	int32_t push(uint8_t* pointer, uint32_t length);
	int32_t push(char* stringPointer, uint32_t stringLength);
	int32_t pop(uint8_t** pointer, uint32_t* length, uint32_t max_length);
private:
	//Must match bufSize from SerialDebug
	static const uint32_t bufSize = 128;
	uint32_t fifoSize;
	class StringContainer{
	public:
		uint8_t buffer[bufSize];
		uint32_t length;
	};
	StringContainer* fifo;
	uint32_t firstIdx = 0;
	uint32_t lastIdx = 0;
};

#endif /* SRC_COMPONENTS_STATICFIFO_HPP_ */
