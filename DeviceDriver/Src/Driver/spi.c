/** @file spi.c
*
* @brief A description of the module's purpose.
*
*/

#include "spi.h"

// === Protected Functions ===
//
/*!
 * @fn			- SPI_GetFlagStatus
 *
 * @brief 		- Checks the status of the flag from the SPI SR register
 *
 * @param[in]	- *p_SPI: base address of the SPI peripheral
 * @param[in]	- flagType: SPI_FLAG_RXNE, SPI_FLAG_TXE
 * @param[out]	- none
 *
 * @return 		- FLAG_SET, FLAG_RESET: according to the choosen SPI's RXNE or TXE buffer value
 *
 * @note		- none
*/
uint8_t static inline SPI_GetFlagStatus (SPI_RegDef_t *p_SPIx, uint32_t flagType)
{
	if (p_SPIx->SR & flagType)
	{
		return FLAG_SET;
	}

	return FLAG_RESET;
}


//=== Public APIs ===
//
/*!
 * @fn			- SPI_PeriClockControl
 *
 * @brief 		- Enables or disables the peripheral clock for the given SPI interface
 *
 * @param[in]	- *p_SPI: base address of the SPI peripheral
 * @param[in]	- enable: ENABLE or DISABLE macros
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void SPI_PeriClockControl (SPI_RegDef_t *p_SPI, uint8_t enable)
{
	if (enable)
	{
		if (SPI1 == p_SPI)
		{
			SPI1_PCLK_EN();
		}
		else if (SPI2 == p_SPI)
		{
			SPI2_PCLK_EN();
		}
		else if (SPI3 == p_SPI)
		{
			SPI3_PCLK_EN();
		}
		else if (SPI4 == p_SPI)
		{
			SPI4_PCLK_EN();
		}
		else
		{
			// NOP
		}
	}
	else
	{
		if (SPI1 == p_SPI)
		{
			SPI1_PCLK_DI();
		}
		else if (SPI2 == p_SPI)
		{
			SPI2_PCLK_DI();
		}
		else if (SPI3 == p_SPI)
		{
			SPI3_PCLK_DI();
		}
		else if (SPI4 == p_SPI)
		{
			SPI4_PCLK_DI();
		}
		else
		{
			// NOP
		}
	}
}

/*!
 * @fn			- SPI_Init
 *
 * @brief 		- Initialization of the SPI Interface
 *
 * @param[in]	- *p_SPIhandle: SPI base address + configuration settings
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void SPI_Init (SPI_Handle_t *p_SPIhandle)
{
	uint32_t configReg = 0;

	// 0. Enable SPI Periphery Clock
	SPI_PeriClockControl(p_SPIhandle->p_SPIx, ENABLE);

	// 1. Configure Device Mode (Master / Slave)
	configReg |= (p_SPIhandle->SpiConfig.deviceMode & 1) << SPI_CR1REG_MSTR;

	// 2. Configure the Bus
	switch (p_SPIhandle->SpiConfig.busConfig)
	{
		case SPI_BUSCONFIG_FD:														// Full-duplex
			configReg &= ~(1 << SPI_CR1REG_BIDIMODE);		// Clear BIDIMODE
			break;
		case SPI_BUSCONFIG_HD:														// Half-duplex
			configReg |= (1 << SPI_CR1REG_BIDIMODE);		// Set BIDIMODE
			break;
		case SPI_BUSCONFIG_SRX:														// Simplex, Rx only
			configReg &= ~(1 << SPI_CR1REG_BIDIMODE);		// Clear BIDIMODE
			configReg |= (1 << SPI_CR1REG_RXONLY);			// Set RXONLY
			break;
		default:
			break;
	}

	// 3. Configure SPI Serial Clock speed (Baud Rate)
	configReg |= (p_SPIhandle->SpiConfig.sclkSpeed & 0xf) << SPI_CR1REG_BR;

	// 4. Configure SPI Data Frame Format
	configReg |= (p_SPIhandle->SpiConfig.dff & 1) << SPI_CR1REG_DFF;

	// 5. Configure SPI Clock Polarity
	configReg |= (p_SPIhandle->SpiConfig.cpol & 1) << SPI_CR1REG_CPOL;

	// 6. Configure SPI  Clock Phase
	configReg |= (p_SPIhandle->SpiConfig.cpha & 1) << SPI_CR1REG_CPHA;

	// 7. Configure SPI Slave Software Management
	configReg |= (p_SPIhandle->SpiConfig.ssm & 1) << SPI_CR1REG_SSM;

	// 8. Configure SPI Internal Slave Select
	configReg |= (p_SPIhandle->SpiConfig.ssi & 1) << SPI_CR1REG_SSI;

	// === Save config in SPI CR1 register ===
	p_SPIhandle->p_SPIx->CR1 = configReg;

	configReg = 0;
	// 9. Configure SPI SS output enable
	configReg |= (p_SPIhandle->SpiConfig.ssoe & 1) << SPI_CR2REG_SSOE;

	// === Save config in SPI CR2 register ===
	p_SPIhandle->p_SPIx->CR2 = configReg;
}

/*!
 * @fn			- SPI_DeInit
 *
 * @brief 		- Resetting the SPI registers
 *
 * @param[in]	- *p_SPI: base address of the SPI peripheral
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void SPI_DeInit (SPI_RegDef_t *p_SPI)
{
	// Reset the RCC register regarding the designated SPI periphery
	if (SPI1 == p_SPI)
	{
		SPI1_REG_RESET();
	}
	else if (SPI2 == p_SPI)
	{
		SPI2_REG_RESET();
	}
	else if (SPI3 == p_SPI)
	{
		SPI3_REG_RESET();
	}
	else if (SPI4 == p_SPI)
	{
		SPI4_REG_RESET();
	}
	else
	{
		// NOP
	}

	// Disable the SPI periphery clock
	SPI_PeriClockControl(p_SPI, DISABLE);
}

/*!
 * @fn			- SPI_SendData
 *
 * @brief 		- Sending data on Tx
 *
 * @param[in]	- *p_SPI: base address of the SPI peripheral
 * @param[out]	- *p_TxBuffer: Pointer to the Tx buffer to be written
 * @param[in]	- len: Number of Bytes to be transmitted
 *
 * @return 		- none
 *
 * @note		- This function is blocking call, polling type at Tx flag waiting
*/
void SPI_SendData (SPI_RegDef_t *p_SPI, uint8_t *p_TxBuffer, uint32_t len)
{
	if (0 == len)	// If "len" is 0, exit from the function
	{
		return;
	}

	while (len --> 0)
	{
		// 1. Wait until Tx buffer is empty
		while (SPI_GetFlagStatus(p_SPI, SPI_FLAG_TXE) == FLAG_RESET);

		// 2. Check the DFF bit CR1
		if (p_SPI->CR1 & (1 << SPI_CR1REG_DFF))
		{
			// 2 Bytes Data Frame Format
			if (len > 1)										// Avoid infinite loop in case of odd len value
			{
				p_SPI->DR = *((uint16_t *)p_TxBuffer);
                (*(uint16_t **) &p_TxBuffer) ++;				// Increment 8 bit Tx buffer twice
                len--;
			}
			else	// Odd data length
            {
				p_SPI->DR = (*((uint16_t *)p_TxBuffer)) & 0xff;	// Mask final character in case of odd len value
            }
		}
		else
		{
			// 1 Byte Data Frame Format
			p_SPI->DR = *p_TxBuffer;
			p_TxBuffer++;
		}
	}
}

/*!
 * @fn			- SPI_ReceiveData
 *
 * @brief 		- Receive data on the Rx
 *
 * @param[in]	- *p_SPI: base address of the SPI peripheral
 * @param[out]	- *p_RxBuffer Pointer to the Rx buffer to be read
 * @param[in]	- len: Number of Bytes to be received
 *
 * @return 		- none
 *
 * @note		- none
*/
void SPI_ReceiveData (SPI_RegDef_t *p_SPI, uint8_t *p_RxBuffer, uint32_t len)
{
	if (0 == len)	// If "len" is 0, exit from the function
	{
		return;
	}

	while (len --> 0)
	{
		// 1. Wait until Rx buffer is not empty
		while (SPI_GetFlagStatus(p_SPI, SPI_FLAG_RXNE) == FLAG_RESET);

		// 2. Check the DFF bit CR1
		if (p_SPI->CR1 & (1 << SPI_CR1REG_DFF))
		{
			// 2 Bytes Data Frame Format
			if (len > 1)										// Avoid infinite loop in case of odd len value
			{
				*((uint16_t *)p_RxBuffer) = p_SPI->DR;
                (*(uint16_t **) &p_RxBuffer) ++;				// Increment 8 bit Rx buffer twice
                len--;
			}
			else	// Odd data length
            {
				(*((uint16_t *)p_RxBuffer)) = p_SPI->DR & 0xff;	// Mask final character in case of odd len value
            }
		}
		else
		{
			// 1 Byte Data Frame Format
			*p_RxBuffer = p_SPI->DR & 0xff;
		}
	}

}

// SPI IRQ Handling
//
void SPI_IRQHandling (SPI_Handle_t *p_SPIhandler);

// Other APIs
//
/*!
 * @fn			- SPI_PeripheralControl
 *
 * @brief 		- Enables o disables the SPI periphery
 *
 * @param[in]	- *p_SPI: base address of the SPI peripheral
 * @param[out]	- none
  @param[in]	- control: ENABLE or DISABLE macros
 *
 * @return 		- none
 *
 * @note		- none
*/
void SPI_PeripheralControl (SPI_RegDef_t *p_SPIx, uint8_t control)
{
	if (ENABLE == control)
	{
		p_SPIx->CR1 |= (1 << SPI_CR1REG_SPE);
	}
	else
	{
		p_SPIx->CR1 &= ~(1 << SPI_CR1REG_SPE);
	}
}

/*** EOF ***/

