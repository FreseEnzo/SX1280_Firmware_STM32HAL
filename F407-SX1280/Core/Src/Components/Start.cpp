#include "Start.hpp"
#include "SerialDebug.hpp"
#include "sx1280/sx1280-hal.h"
#include "usbd_cdc_if.h"
#include "string.h"
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern SPI_HandleTypeDef hspi2;

SerialDebug debug(&huart2, 32);
SX1280Hal radio0(&hspi2, SX1280_NSS_GPIO_Port, SX1280_NSS_Pin, SX1280_BUSY_GPIO_Port, SX1280_BUSY_Pin, SX1280_RST_GPIO_Port, SX1280_RST_Pin, NULL);

PacketParams_t PacketParams;
PacketStatus_t PacketStatus;
ModulationParams_t ModulationParams;
uint8_t syncWord[5] = { 0xDD, 0xA0, 0x96, 0x69, 0xDD };




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim==&htim6){

	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if(huart == &huart2){
		debug.serialTxCpltCallback();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin){
	case 8:
		radio0.HalInterruptCallback();
		break;
	default:
		break;
	}
}

void start(){
	/* Modulation Params*/

   ModulationParams.Params.Flrc.BitrateBandwidth  = ( RadioFlrcBitrates_t )       FLRC_BR_0_260_BW_0_3;
   ModulationParams.Params.Flrc.CodingRate        = ( RadioFlrcCodingRates_t )    FLRC_CR_1_2;
   ModulationParams.Params.Flrc.ModulationShaping = ( RadioModShapings_t )        RADIO_MOD_SHAPING_BT_1_0;

   PacketParams.Params.Flrc.PreambleLength        = ( RadioPreambleLengths_t )     PREAMBLE_LENGTH_32_BITS;
   PacketParams.Params.Flrc.SyncWordLength        = ( RadioFlrcSyncWordLengths_t )FLRC_SYNCWORD_LENGTH_4_BYTE;
   PacketParams.Params.Flrc.SyncWordMatch         = ( RadioSyncWordRxMatchs_t )   RADIO_RX_MATCH_SYNCWORD_1;
   PacketParams.Params.Flrc.HeaderType            = ( RadioPacketLengthModes_t )  RADIO_PACKET_VARIABLE_LENGTH;
   PacketParams.Params.Flrc.PayloadLength         =                               15;
   PacketParams.Params.Flrc.CrcLength             = ( RadioCrcTypes_t )           RADIO_CRC_3_BYTES;
   PacketParams.Params.Flrc.Whitening             = ( RadioWhiteningModes_t )	  RADIO_WHITENING_OFF;

   ModulationParams.PacketType = PACKET_TYPE_FLRC;
   PacketParams.PacketType     = PACKET_TYPE_FLRC;

   /*Radio Type*/
    bool isMaster = false;




	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	debug.info("-----Init-----");
	debug.info("Init timers begin");
	HAL_TIM_Base_Start(&htim6);
	debug.info("Init timers end");
	debug.info("Init radio begin");
	HAL_Delay(500);

	radio0.Init();
	radio0.SetRegulatorMode(USE_LDO);
	radio0.SetStandby( STDBY_RC);
	//radio0.SetLNAGainSetting(LNA_HIGH_SENSITIVITY_MODE);
	radio0.SetPacketType( ModulationParams.PacketType );
	radio0.SetModulationParams( &ModulationParams );
	radio0.SetPacketParams( &PacketParams );

	radio0.SetRfFrequency( 2402000000UL );
	radio0.SetBufferBaseAddresses( 0x00, 0x00 );


	// only used in GFSK, FLRC (4 bytes max) and BLE mode
	//radio0.SetSyncWord( 1, syncWord ); // NAO USEI
	// only used in GFSK, FLRC
	//uint8_t crcSeedLocal[2] = {0x45, 0x67}; // NAO USEI
	//radio0.SetCrcSeed( crcSeedLocal ); // NAO USEI
	//radio0.SetCrcPolynomial( 0x0123 ); // NAOP USEI
	radio0.SetTxParams( 0, RADIO_RAMP_20_US );
	uint16_t RxIrqMask = IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT;
	radio0.SetDioIrqParams( RxIrqMask, RxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
	radio0.SetRx( ( TickTime_t ) { RADIO_TICK_SIZE_1000_US, 0xFFFF } );
	//Frese



	radio0.SetPollingMode( );
	radio0.ProcessIrqs( );


	uint8_t Buffer[16];
    uint8_t BufferReceived[16];
	uint8_t BufferSize = 16;
	memset( &BufferReceived, 0x00, BufferSize );

	char *data = "hello adfa \n";

while(1)
{
	if(isMaster == true)
	{

		// Send the next PING frame
		Buffer[0] = 1;
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

		uint16_t TxIrqMask = IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT;
		radio0.SetDioIrqParams( TxIrqMask, TxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
		radio0.SendPayload( Buffer, 16,( TickTime_t ){ RADIO_TICK_SIZE_1000_US, 100 } );
		HAL_Delay(10);
		radio0.GetIrqStatus();
		debug.info("Init radio end");
	}
	else
	{


			 radio0.GetPayload(BufferReceived, &BufferSize, 16);
			 CDC_Transmit_FS(BufferReceived, 16);
			 //CDC_Transmit_FS((uint8_t*)data, strlen(data));
			 HAL_Delay(1000);
			 memset( &BufferReceived, 0x00, BufferSize );

	}
	}
}
