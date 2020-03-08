/*
 * @file spi.h
 *
 * @brief SPI driver header file
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include "mcu_STM32F446xx.h"

// === Type Definitions ===
//
typedef struct SPI_Config
{
	uint8_t deviceMode;				// @SPI_DEVMODE
	uint8_t busConfig;				// @SPI_BUSCONFIG
	uint8_t sclkSpeed;				// @SPI_SPEED
	uint8_t dff;					// @SPI_DFFMODE
	uint8_t cpol;					// @SPI_CPOLMODE
	uint8_t cpha;					// @SPI_CPHAMODE
	uint8_t ssm;					// @SPI_SSMMODE
	uint8_t ssi;					// @SPI_SSIMODE
	uint8_t ssoe;					// @SPI_SSOEMODE
} SPI_Config_t;

typedef struct SPI_Handle
{
	SPI_RegDef_t *p_SPIx;
	SPI_Config_t SpiConfig;
	uint8_t *p_TxBuffer;
	uint8_t *p_RxBuffer;
	uint8_t TxLen;
	uint8_t RxLen;
	uint8_t TxState;				// @SPI_API_STATE
	uint8_t RxState;				// @SPI_API_STATE
} SPI_Handle_t;


// === Constant Definitions ===
//
/*
 * @SPI_DEVMODE
 * The possible device modes of SPI interface
 */
#define SPI_DEVMODE_SLAVE		0
#define SPI_DEVMODE_MASTER		1

/*
 * @SPI_BUSCONFIG
 * The possible device modes of SPI interface
 */
#define SPI_BUSCONFIG_FD		0		// Full-duplex
#define SPI_BUSCONFIG_HD		1		// Half-duplex
#define SPI_BUSCONFIG_SRX		2		// Simplex, Rx only

/*
 * @SPI_SPEED
 * The possible device modes of SPI interface
 */
#define SPI_SPEED_DIV2			0
#define SPI_SPEED_DIV4			1
#define SPI_SPEED_DIV8			2
#define SPI_SPEED_DIV16			3
#define SPI_SPEED_DIV32			4
#define SPI_SPEED_DIV64			5
#define SPI_SPEED_DIV128		6
#define SPI_SPEED_DIV256		7

/*
 * @SPI_DFFMODE
 * The possible device modes of SPI interface
 */
#define SPI_DFFMODE_8BIT		0
#define SPI_DFFMODE_16BIT		1

/*
 * @SPI_CPOLMODE
 * The possible device modes of SPI interface
 */
#define SPI_CPOLMODE_LOW		0
#define SPI_CPOLMODE_HIGH		1

/*
 * @SPI_CPHAMODE
 * The possible device modes of SPI interface
 */
#define SPI_CPHAMODE_LEAD		0
#define  SPI_CPHAMODE_TRAIL		1

/*
 * @SPI_SSMMODE
 * The possible device modes of SPI interface
 */
#define SPI_SSMMODE_DI			0
#define SPI_SSMMODE_EN			1

/*
 * @SPI_SSIMODE
 * Internal slave select
 */
#define SPI_SSIMODE_DI			0
#define SPI_SSIMODE_EN			1

/*
 * @SPI_SSOEMODE
 * 0: SS output is disabled in master mode and the cell can work in multimaster configuration
 * 1: SS output is enabled in master mode and when the cell is enabled. The cell cannot work
in a multimaster environment.
 */
#define SPI_SSOEMODE_DI			0
#define SPI_SSOEMODE_EN			1

/*
 * @SPI_API_STATE
 * The possible SPI application states
 */
#define SPI_ST_READY			0
#define SPI_ST_BUSY_TX			1
#define SPI_ST_BUSY_RX			2

/*
 * @SPI_API_EVENTS
 * The possible SPI application events
 */
#define SPI_EVENT_TX_CMPLT		0		// SPI Tx transmission complete
#define SPI_EVENT_RX_CMPLT		1		// SPI Rx reception complete
#define SPI_EVENT_OVR_CMPLT		2		// SPI OVR overrun error occurred complete


// === API Functions ===
//
// SPI Init and Deinit
//
void SPI_PeriClockControl (SPI_RegDef_t *p_SPI, uint8_t enable);
void SPI_Init (SPI_Handle_t *p_SPIhandle);
void SPI_DeInit (SPI_RegDef_t *p_SPI);

// SPI Data Send and Receive
//
void SPI_SendData (SPI_RegDef_t *p_SPI, uint8_t *p_TxBuffer, uint32_t len);
void SPI_ReceiveData (SPI_RegDef_t *p_SPI, uint8_t *p_RxBuffer, uint32_t len);
uint8_t SPI_SendDataIT (SPI_Handle_t *p_SpiHandle, uint8_t *p_TxBuffer, uint32_t len);
uint8_t SPI_ReceiveDataIT (SPI_Handle_t *p_SpiHandle, uint8_t *p_RxBuffer, uint32_t len);

// SPI IRQ Handling
//
void SPI_IRQHandling (SPI_Handle_t *p_SpiHandle);

// SPI Control
//
void SPI_PeripheralControl (SPI_RegDef_t *p_SPIx, uint8_t enable);
void SPI_CloseTransmission (SPI_Handle_t *p_SpiHandle);
void SPI_CloseReception (SPI_Handle_t *p_SpiHandle);
void SPI_ClearOvrFlag (SPI_RegDef_t *p_Spi);

// SPI Application Callback
//
void SPI_API_EventCallback(SPI_Handle_t *p_SpiHandle, uint8_t appEvent);

#endif /* SPI_H_ */

/*** EOF ***/
