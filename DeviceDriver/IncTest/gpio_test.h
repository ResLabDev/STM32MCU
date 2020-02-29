/** @file gpio_test.h
*
* @brief A description of the module's purpose.
*
*/

#ifndef GPIO_TEST_H_
#define GPIO_TEST_H_

#include <stdio.h>

#include "mcu_STM32F446xx.h"
#include "gpio.h"

// === Type Definitions ===
//


// === Constant Definitions ===
//
#define BUTTON_PRESSED		0
#define BUTTON_RELEASED		1


// === Macros ===
//


// === Public API Functions ===
//
void GPIO_Test_LedToggleNoIT (uint8_t cycle);
void GPIO_Test_LedToggleByButton (void);
void GPIO_Test_LedToggleByButtonIT (void);
void GPIO_Test_ClockOut (void);


#endif /* GPIO_TEST_H_ */

/*** EOF ***/
