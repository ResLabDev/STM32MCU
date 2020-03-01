/** @file gpio_test.h
*
* @brief A description of the module's purpose.
*
*/

#ifndef SPI_TEST_H_
#define SPI_TEST_H_

#include <stdio.h>
#include <string.h>

#include "mcu_STM32F446xx.h"
#include "gpio.h"
#include "spi.h"

// === Type Definitions ===
//
#define NUM_OF(x)					(sizeof(x) / sizeof(*x))


// === Constant Definitions ===
//


// === Macros ===
//


// === Public API Functions ===
//
void SPI_Test_SendData (uint16_t cycle);
void SPI_Test_ReceiveData (uint16_t cycle);

#endif /* SPI_TEST_H_ */

/*** EOF ***/
