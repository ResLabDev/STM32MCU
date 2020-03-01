/** @file spi_test.c
*
* @brief A description of the module's purpose.
*
*/

#include "spi_test.h"


// === Protected Functions ===
//
/*!
 * @fn			- Delay
 *
 * @brief 		- Dummy delay as empty for loop (NOP)
 *
 * @param[in]	- duration: for loop limit
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void Delay (uint32_t duration)
{
	for (uint32_t i = 0; i < duration; ++i);
}

/*!
 * @fn			- SPI1_PinInit
 *
 * @brief 		- Configures the pinouts of SPI1 interface
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void SPI1_PinInit ()
{
	GPIO_Handle_t SPIpin;

	SPIpin.p_GPIOx 						= GPIOA;
	SPIpin.pinConfig.pinMode 			= GPIO_MODE_ALTFN;
	SPIpin.pinConfig.pinAltFunMode 		= GPIO_AF5;
	SPIpin.pinConfig.pinOPType 			= GPIO_OP_TYPE_PP;
	SPIpin.pinConfig.pinPuPdControl 	= GPIO_PIN_PU;
	SPIpin.pinConfig.pinSpeed			= GPIO_OP_SPEED_HIGH;

	// SCK
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIpin);

	// MOSI
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIpin);

	// MISO
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&SPIpin);

	// NSS
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&SPIpin);
}

/*!
 * @fn			- SPI2_PinInit
 *
 * @brief 		- Configures the pinouts of SPI2 interface
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void SPI2_PinInit ()
{
	GPIO_Handle_t SPIpin;

	SPIpin.p_GPIOx 						= GPIOB;
	SPIpin.pinConfig.pinMode 			= GPIO_MODE_ALTFN;
	SPIpin.pinConfig.pinAltFunMode 		= GPIO_AF5;
	SPIpin.pinConfig.pinOPType 			= GPIO_OP_TYPE_PP;
	SPIpin.pinConfig.pinPuPdControl 	= GPIO_NO_PUPD;
	SPIpin.pinConfig.pinSpeed			= GPIO_OP_SPEED_HIGH;

	// SCK
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIpin);

	// MOSI
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIpin);

	// MISO
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIpin);

	// NSS
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIpin);
}


/*!
 * @fn			- SPI1_Init
 *
 * @brief 		- Configures SPI1 interface
 *
 * @param[in]	- ssmControl: Software Slave Management
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void SPI1_Init (uint8_t ssmControl)
{
	SPI_Handle_t SPIHandle;

	// Configure SPI1
	SPIHandle.p_SPIx 				= SPI1;
	SPIHandle.SpiConfig.busConfig  	= SPI_BUSCONFIG_FD;

	SPIHandle.SpiConfig.deviceMode	= SPI_DEVMODE_MASTER;
	SPIHandle.SpiConfig.sclkSpeed	= SPI_SPEED_DIV8;
	SPIHandle.SpiConfig.dff 		= SPI_DFFMODE_8BIT;
	SPIHandle.SpiConfig.cpol 	  	= SPI_CPOLMODE_LOW;
	SPIHandle.SpiConfig.cpha 	  	= SPI_CPHAMODE_LEAD;
	SPIHandle.SpiConfig.ssi 		= SPI_SSIMODE_EN;
	SPIHandle.SpiConfig.ssoe		= SPI_SSOEMODE_EN;

	if (ENABLE == ssmControl)
	{
		SPIHandle.SpiConfig.ssm 	= SPI_SSMMODE_EN;
	}
	else
	{
		SPIHandle.SpiConfig.ssm 	= SPI_SSMMODE_DI;
	}

	SPI_Init(&SPIHandle);
}

/*!
 * @fn			- SPI2_Init
 *
 * @brief 		- Configures SPI2 interface
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void SPI2_Init (void)
{
	SPI_Handle_t SPIHandle;

	// Configure SPI1
	SPIHandle.p_SPIx 				= SPI2;
	SPIHandle.SpiConfig.busConfig  	= SPI_BUSCONFIG_FD;

	SPIHandle.SpiConfig.deviceMode	= SPI_DEVMODE_SLAVE;
	SPIHandle.SpiConfig.sclkSpeed	= SPI_SPEED_DIV8;
	SPIHandle.SpiConfig.dff 		= SPI_DFFMODE_8BIT;
	SPIHandle.SpiConfig.cpol 	  	= SPI_CPOLMODE_LOW;
	SPIHandle.SpiConfig.cpha 	  	= SPI_CPHAMODE_LEAD;
	SPIHandle.SpiConfig.ssm 		= SPI_SSMMODE_DI;
	SPIHandle.SpiConfig.ssi 		= SPI_SSIMODE_EN;
	SPIHandle.SpiConfig.ssoe		= SPI_SSOEMODE_EN;

	SPI_Init(&SPIHandle);
}


// === Public API Functions ===
//
/*!
 * @fn			- SPI_Test_SendData8
 *
 * @brief 		- Sending 1 Byte data on the SPI1 interface
 *
 * @param[in]	- cycle: Repetition value
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- PIN Alternate Function Mode: AF5
 * 				  Nucleo F446RE Board
 * 				  	 PA4: SPI1_NSS		=> do not use
 * 				  11 PA5: SPI1_SCK
 * 				  13 PA6: SPI1_MISO	=> do not use
 * 				  15 PA7: SPI1_MOSI
 * 				   9 GND
 *
*/
void SPI_Test_SendData (uint16_t cycle)
{
	printf(" $ Executing SPI Sending Bytes Test...\n");

	// Initialize GPIOA to SPI1 alternate function mode
	SPI1_PinInit();

	// Initialize SPI
	SPI1_Init(DISABLE);

	// Enable SPI1
	SPI_PeripheralControl(SPI1, ENABLE);

	char buffer[] = "HELLO FROM SPI1";

	while (cycle)
	{
		SPI_SendData(SPI1, (uint8_t *)buffer, strlen(buffer));
		Delay(500000);
		printf(" $ Remaining cycle: %u.\n", cycle);
		cycle--;
	}

	// Closing the communication
	SPI_PeripheralControl(SPI1, DISABLE);

	printf(" $ ... Finished SPI Sending Bytes Test.\n");
}

//
/*!
 * @fn			- SPI_Test_ReceiveData
 *
 * @brief 		- Sending data on the SPI1 (master) interface and getting it on SPI2 (slave)
 *
 * @param[in]	- cycle: Repetition value
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- PIN Alternate Function Mode: AF5
 * 				  Nucleo F446RE Board
 * 				  		SPI1	SPI2	SPI1 Nucleo		SPI2 Nucleo
 * 				  NSS	PA4		PB12	CN7/32			CN10/16
 * 				  SCK	PA5 	PB13	CN10/11			CN10/30
 * 				  MISO	PA6		PB14	CN10/13			CN10/28
 * 				  MOSI	PA7		PB15	CN10/15			CN10/26
 * 				  GND					CN10/9
 *
*/
void SPI_Test_ReceiveData (uint16_t cycle)
{
	printf(" $ Executing SPI Receive Byte Test...\n");

	// 1. Configure SPI1 as master
	SPI1_PinInit(ENABLE);			// Initialize GPIOA to SPI1 alternate function mode
	SPI1_Init(ENABLE);

	// 2. Configure SPI2 as slave
	SPI2_PinInit();					// Initialize GPIOB to SPI2 alternate function mode
	SPI2_Init();

	// Enable SPIs
	SPI_PeripheralControl(SPI1, ENABLE);
	SPI_PeripheralControl(SPI2, ENABLE);

	uint8_t cmd = 0;
	uint8_t ack;
	uint8_t i = 0;

	while (cycle --> 0)
	{
		// Master send cmd to slave
		SPI_SendData(SPI1, &cmd, 1);
		SPI_ReceiveData(SPI2, &ack, 1);
		printf(" $ %3u. CMD: %3u, ACK: %3u\n", i++, cmd++, ack);

		Delay(500000);
	}

	// Disable SPIs
	SPI_PeripheralControl(SPI1, DISABLE);
	SPI_PeripheralControl(SPI2, DISABLE);

	printf(" $ ... Finished SPI Receinving Byte Test.\n");
}


/*** EOF ***/
