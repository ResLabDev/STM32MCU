/** @file mcu_STM32F446xx.c
*
* @brief STM32F446xx MCU function collection
*
*/

#include "mcu_STM32F446xx.h"


// === Protected Functions ===
//


// === Public API Functions ===
//
/*!
 * @fn			- IRQInterruptConfig
 *
 * @brief 		- Enable or Disables the NVIC (via EXTI) Interrupt
 *
 * @param[in]	- IRQNumber: The number of the interrupt request
 * @param[in]	- enable: enables or disables the interrupt
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void IRQInterruptConfig (uint8_t IRQNumber,  uint8_t enable)
{
	if (ENABLE == enable)
	{
		// Configure ISER (Interrupt Set Enable Register) register
		NVIC_ISER->reg[IRQNumber / 32] |= (1 << (IRQNumber % 32));
	}
	else
	{
		// Configure ICER (Interrupt Clear Enable Register) register
		NVIC_ICER->reg[IRQNumber / 32] |= (1 << (IRQNumber % 32));
	}
}

/*!
 * @fn			- IRQPriorityConfig
 *
 * @brief 		- Sets the priority level of the interrupt
 *
 * @param[in]	- IRQNumber: The number of the interrupt request
 * @param[in]	- IRQPriority: The priority level of the interrupt request
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void IRQPriorityConfig (uint8_t IRQNumber, uint8_t IRQPriority)
{
	uint8_t shift = ((IRQNumber % 4) * 8) + (8 - NO_IPR_BITS);
	NVIC_IPR->reg[IRQNumber / 4] |= (IRQPriority << shift);
}

/*** EOF ***/


