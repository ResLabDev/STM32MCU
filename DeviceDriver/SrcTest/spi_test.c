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
static void SPI1_PinInit (uint8_t slaveEnable)
{
	GPIO_Handle_t SPIpin;

	SPIpin.p_GPIOx 						= GPIOA;
	SPIpin.pinConfig.pinMode 			= GPIO_MODE_ALTFN;
	SPIpin.pinConfig.pinAltFunMode 		= GPIO_AF5;
	SPIpin.pinConfig.pinOPType 			= GPIO_OP_TYPE_PP;
	SPIpin.pinConfig.pinPuPdControl 	= GPIO_NO_PUPD;
	SPIpin.pinConfig.pinSpeed			= GPIO_OP_SPEED_HIGH;

	// SCK
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&SPIpin);

	// MOSI
	SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&SPIpin);

	// Set slave interfaces if enabled
	if (ENABLE == slaveEnable)
	{
		// MISO
		SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_6;
		GPIO_Init(&SPIpin);

		// NSS
		SPIpin.pinConfig.pinNumber = GPIO_PIN_NO_4;
		GPIO_Init(&SPIpin);
	}
}

/*!
 * @fn			- SPI1_Init
 *
 * @brief 		- Configures SPI1 interface
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void SPI1_Init (void)
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
	SPIHandle.SpiConfig.ssm 		= SPI_SSMMODE_EN;
	SPIHandle.SpiConfig.ssi 		= SPI_SSIMODE_EN;

	SPI_Init(&SPIHandle);
}


// === Public API Functions ===
//
/*!
 * @fn			- SPI_Test_SendData8
 *
 * @brief 		- Sending 1 Byte data on the SPI1 interface
 *
 * @param[in]	-
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
	printf(" $ Executing SPI Sending Bytes Test\n");

	// Initialize GPIOA to SPI1 alternate function mode
	SPI1_PinInit(DISABLE);

	// Initialize SPI
	SPI1_Init();

	// Enable SPI1
	SPI_PeripheralControl(SPI1, ENABLE);

	char buffer[] = "HELLO FROM SPI1";
	while (cycle --> 0)
	{
		SPI_SendData(SPI1, (uint8_t *)buffer, strlen(buffer));
		Delay(500000);
	}

	 printf(" $ SPI sending Bytes test is finished.\n");
}

/*** EOF ***/
