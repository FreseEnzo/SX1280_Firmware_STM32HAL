#include "Start.hpp"
#include "SerialDebug.hpp"
#include "usbd_cdc_if.h"
#include "string.h"
#include "RoboIME_SX1280.hpp"

extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;

//SerialDebug debug(&huart2, 32);
RoboIME_SX1280 radio;

uint8_t BufferReceived[128];
uint8_t count = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim==&htim6){

	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &huart2){
		//debug.serialTxCpltCallback();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin){
	case GPIO_PIN_8:
		radio.GPIOCallback();
		break;
	default:
		break;
	}
}

void start(){

	radio.setup();
   /*Radio Type*/
    bool isMaster = false;


	uint8_t Buffer[radio.bufferSize];
	memset( BufferReceived, 0x00, radio.bufferSize );
	HAL_Delay(5);

//	char *data = "hello adfa \n";
int count = 0;
while(1)
{

	if(isMaster == true)
	{

		// Send the next PING frame
		Buffer[0] = count;
		Buffer[1] = 2;
		Buffer[2] = 3;
		Buffer[3] = 4;
		Buffer[4] = 5;
		Buffer[5] = 6;
		Buffer[6] = 7;
		Buffer[7] = 8;
		for(int i = 8; i < 16; i++ )
		{
			Buffer[i] = i;
		}

		if(radio.sendPayload(Buffer, radio.bufferSize))
		{
			HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin); // verde
			count ++;
			HAL_Delay(10);
		}


	}
	else
	{
		radio.setRobotId(2);
		HAL_Delay(10);
			if(radio.receivePayload(BufferReceived))
			{
				 CDC_Transmit_FS(BufferReceived, radio.bufferSize);
			}


	}
	}
}
