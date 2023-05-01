/*
 * UARTDebug.hpp
 *
 *  Created on: Feb 28, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_SERIALDEBUG_HPP_
#define SRC_COMPONENTS_SERIALDEBUG_HPP_

#include "main.h"
#include "StaticFIFO.hpp"
#include <stdio.h>
class SerialDebug{
public:
	enum DebugLevel{
		DEBUG_LEVEL_DEBUG,
		DEBUG_LEVEL_INFO,
		DEBUG_LEVEL_WARN,
		DEBUG_LEVEL_ERROR
	};

	SerialDebug(UART_HandleTypeDef* huartptr, uint32_t fifoSize);
	void serialTxCpltCallback();
	void setLevel(DebugLevel level);
	void debug(const char* data);
	void info(const char* data);
	void warn(const char* data);
	void error(const char* data);

	StaticFIFO* fifo;
private:
	//Must match the bufSize from StaticFIFO
	static const uint32_t bufSize = 128;
	bool transmitting = false;
	UART_HandleTypeDef* huartptr;
	char charBuf[bufSize];
	uint8_t uartBuf[bufSize];
	DebugLevel debugLevel = DEBUG_LEVEL_ERROR;
};






#endif /* SRC_COMPONENTS_SERIALDEBUG_HPP_ */
