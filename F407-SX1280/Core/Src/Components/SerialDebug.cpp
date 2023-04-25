/*
 * UARTDebug.cpp
 *
 *  Created on: Feb 28, 2022
 *      Author: Gabriel
 */

#include "SerialDebug.hpp"
#include <string.h>

SerialDebug::SerialDebug(UART_HandleTypeDef* huartptr, uint32_t fifoSize)
: huartptr(huartptr)
{
	fifo = new StaticFIFO(fifoSize);
}

void SerialDebug::setLevel(DebugLevel level)
{
	debugLevel = level;
}

void SerialDebug::serialTxCpltCallback(){
	uint32_t numChars;
	uint8_t* pointer;
	if (fifo->pop(&pointer, &numChars, bufSize) >= 0){
		memcpy(uartBuf, pointer, numChars);
		HAL_UART_Transmit_DMA(huartptr, pointer, (uint16_t)numChars);
	}else{
		transmitting = false;
	}
}

void SerialDebug::debug(const char* data){
	if (debugLevel <= DEBUG_LEVEL_DEBUG){
		int numChars = sprintf(charBuf, "[%13lu] DBG: %.105s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			if(transmitting){
				fifo->push(charBuf, numChars);
			}else{
				transmitting = true;
				memcpy(uartBuf, (uint8_t*)charBuf, numChars);
				HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			}
		}
	}
}

void SerialDebug::info(const char* data){
	if (debugLevel <= DEBUG_LEVEL_INFO){
		int numChars = sprintf(charBuf, "[%13lu] INF: %.105s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			if(transmitting){
				fifo->push(charBuf, numChars);
			}else{
				transmitting = true;
				memcpy(uartBuf, (uint8_t*)charBuf, numChars);
				HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			}
		}
	}
}

void SerialDebug::warn(const char* data){
	if (debugLevel <= DEBUG_LEVEL_WARN){
		int numChars = sprintf(charBuf, "[%13lu] WRN: %.105s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			if(transmitting){
				fifo->push(charBuf, numChars);
			}else{
				transmitting = true;
				memcpy(uartBuf, (uint8_t*)charBuf, numChars);
				HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			}
		}
	}
}

void SerialDebug::error(const char* data){
	if (debugLevel <= DEBUG_LEVEL_ERROR){
		int numChars = sprintf(charBuf, "[%13lu] ERR: %.105s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			if(transmitting){
				fifo->push(charBuf, numChars);
			}else{
				transmitting = true;
				memcpy(uartBuf, (uint8_t*)charBuf, numChars);
				HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
			}
		}
	}
}
