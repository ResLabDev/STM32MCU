/** @file gpio.h
*
* @brief GPIO Driver header file.
*
*/

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "mcu_STM32F446xx.h"


// === Type Definitions ===
//
typedef struct GPIO_PinConfig
{
	uint8_t pinNumber;				// According to @GPIO_PIN_NUM
	uint8_t pinMode;				// According to @GPIO_PIN_MODES
	uint8_t pinSpeed;				// According to @GPIO_PIN_SPEED
	uint8_t pinPuPdControl;			// According to @GPIO_PIN_PUPD
	uint8_t pinOPType;				// According to @GPIO_PIN_OP_TYPE
	uint8_t pinAltFunMode;			// According to @GPIO_ALTFN_MODE
} GPIO_PinConfig_t;

typedef struct GPIO_Handle
{
	GPIO_RegDef_t *p_GPIOx;
	GPIO_PinConfig_t pinConfig;

} GPIO_Handle_t;

// === Constant Definitions ===
//
/*
 * @GPIO_PIN_MODES
 * GPIO Mode Settings
 */
#define GPIO_MODE_IN			0
#define GPIO_MODE_OUT			1
#define GPIO_MODE_ALTFN			2
#define GPIO_MODE_ANALOG		3
#define GPIO_MODE_IT_RT			4		// Interrupt rising edge triggered
#define GPIO_MODE_IT_FT			5		// Interrupt falling edge triggered
#define GPIO_MODE_IT_FRT		6		// Interrupt falling-rising edge triggered

/*
 * @GPIO_PIN_OP_TYPE
 * GPIO Output Type Settings
 */
#define GPIO_OP_TYPE_PP			0		// Push-pull output
#define GPIO_OP_TYPE_OD			1		// Open-drain output

/*
 * @GPIO_PIN_SPEED
 * GPIO Output Speed Settings
 */
#define GPIO_OP_SPEED_LOW		0
#define GPIO_OP_SPEED_MEDIUM	1
#define GPIO_OP_SPEED_FAST		2
#define GPIO_OP_SPEED_HIGH		3

/*
 * @GPIO_PIN_PUPD
 * GPIO Pull-up AND Pull-down Configuration
 */
#define GPIO_NO_PUPD			0 		// No pull-up, pull-down
#define GPIO_PIN_PU				1 		// Pull-up
#define GPIO_PIN_PD				2 		// Pull-down

/*
 * @GPIO_PIN_NUM
 * GPIO Pin Numbers
 */
#define GPIO_PIN_NO_0			0
#define GPIO_PIN_NO_1			1
#define GPIO_PIN_NO_2			2
#define GPIO_PIN_NO_3			3
#define GPIO_PIN_NO_4			4
#define GPIO_PIN_NO_5			5
#define GPIO_PIN_NO_6			6
#define GPIO_PIN_NO_7			7
#define GPIO_PIN_NO_8			8
#define GPIO_PIN_NO_9			9
#define GPIO_PIN_NO_10			10
#define GPIO_PIN_NO_11			11
#define GPIO_PIN_NO_12			12
#define GPIO_PIN_NO_13			13
#define GPIO_PIN_NO_14			14
#define GPIO_PIN_NO_15			15

/*
 *  @GPIO_ALTFN_MODE
 * GPIO Alternate Function Modes
 */
#define GPIO_AF0			0
#define GPIO_AF1			1
#define GPIO_AF2			2
#define GPIO_AF3			3
#define GPIO_AF4			4
#define GPIO_AF5			5
#define GPIO_AF6			6
#define GPIO_AF7			7
#define GPIO_AF8			8
#define GPIO_AF9			9
#define GPIO_AF10			10
#define GPIO_AF11			11
#define GPIO_AF12			12
#define GPIO_AF13			13
#define GPIO_AF14			14
#define GPIO_AF15			15

// === Macros ===
//


// === API Functions ===
//
// GPIO Init and Deinit
//
void GPIO_PeriClockControl (GPIO_RegDef_t *p_GPIO, uint8_t enable);
void GPIO_Init (GPIO_Handle_t *p_GPIOhandle);
void GPIO_DeInit (GPIO_RegDef_t *p_GPIO);

// GPIO Read and Write
//
uint8_t GPIO_ReadPin (GPIO_RegDef_t *p_GPIO, uint8_t pinNumber);
uint16_t GPIO_ReadPort (GPIO_RegDef_t *p_GPIO);
void GPIO_WritePin (GPIO_RegDef_t *p_GPIO, uint8_t pinNumber, uint8_t value);
void GPIO_WritePort (GPIO_RegDef_t *p_GPIO, uint16_t value);
void GPIO_TogglePin (GPIO_RegDef_t *p_GPIO, uint8_t pinNumber);

// GPIO IRQ Handling
//
void GPIO_IRQHandling (uint8_t pinNumber);

#endif /* GPIO_H_ */

/*** EOF ***/
