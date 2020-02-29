/** @file gpio_test.c
*
* @brief A description of the module's purpose.
*
*/

#include "gpio_test.h"


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
 * @fn			- ConfigUserLED
 *
 * @brief 		- Configures GPIO as the single green user LED on the Nucleo F446RE board
 *
 * @param[in]	- *p_GPIOHandle: GPIO Handle input
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void ConfigUserLED (GPIO_Handle_t *p_GPIOHandle)
{
	p_GPIOHandle->p_GPIOx = GPIOA;
	p_GPIOHandle->pinConfig.pinNumber = GPIO_PIN_NO_5;
	p_GPIOHandle->pinConfig.pinMode = GPIO_MODE_OUT;
	p_GPIOHandle->pinConfig.pinOPType = GPIO_OP_TYPE_PP;
	p_GPIOHandle->pinConfig.pinPuPdControl = GPIO_NO_PUPD;
	p_GPIOHandle->pinConfig.pinSpeed = GPIO_OP_SPEED_LOW;
}

/*!
 * @fn			- ConfigUserButton
 *
 * @brief 		- Configures GPIO as the single green user button input on the Nucleo F446RE board
 *
 * @param[in]	- *p_GPIOHandle: GPIO Handle input
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void ConfigUserButton (GPIO_Handle_t *p_GPIOHandle)
{
	p_GPIOHandle->p_GPIOx = GPIOC;
	p_GPIOHandle->pinConfig.pinNumber = GPIO_PIN_NO_13;
	p_GPIOHandle->pinConfig.pinMode = GPIO_MODE_IN;
	p_GPIOHandle->pinConfig.pinPuPdControl = GPIO_NO_PUPD;
	p_GPIOHandle->pinConfig.pinSpeed = GPIO_OP_SPEED_LOW;
}

/*!
 * @fn			- ConfigUserButtonIT
 *
 * @brief 		- Configures GPIO interrupt mode as the single green user button input on the Nucleo F446RE board
 *
 * @param[in]	- *p_GPIOHandle: GPIO Handle input
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
static void ConfigUserButtonIT (GPIO_Handle_t *p_GPIOHandle)
{
	p_GPIOHandle->p_GPIOx = GPIOC;
	p_GPIOHandle->pinConfig.pinNumber = GPIO_PIN_NO_13;
	p_GPIOHandle->pinConfig.pinMode = GPIO_MODE_IT_FT;
	p_GPIOHandle->pinConfig.pinPuPdControl = GPIO_PIN_PU;
	p_GPIOHandle->pinConfig.pinSpeed = GPIO_OP_SPEED_LOW;
}


// === Public API Functions ===
//
/*!
 * @fn			- GPIO_Test_LedToggleNoIT
 *
 * @brief 		- Toggles LED without using interrupt
 *
 * @param[in]	- cycle: calls "cycle" times the toggle function
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_Test_LedToggleNoIT (uint8_t cycle)
{
	printf(" >> LED toggling without interrupt.\n");

	GPIO_Handle_t GPIOhandle;

	// GPIO Configuration
	ConfigUserLED(&GPIOhandle);

	// Initialize GPIO
	GPIO_Init(&GPIOhandle);

	for (uint8_t i = 0; i < cycle; ++i)
	{
		GPIO_TogglePin(GPIOhandle.p_GPIOx, GPIOhandle.pinConfig.pinNumber);
		Delay(500000);
	}

	printf(" >> LED toggle test is finished.\n");
}

/*!
 * @fn			- GPIO_Test_LedToggleByButton
 *
 * @brief 		- Toggles LED without using interrupt
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_Test_LedToggleByButton (void)
{
	printf(" >> Push the blue user button to get the LED toogle!\n");

	GPIO_Handle_t LedHandle, ButtonHandle;

	// GPIO Configuration
	ConfigUserLED(&LedHandle);
	ConfigUserButton(&ButtonHandle);

	// Initialize GPIO
	GPIO_Init(&LedHandle);
	GPIO_Init(&ButtonHandle);

	GPIO_WritePin(LedHandle.p_GPIOx, LedHandle.pinConfig.pinNumber, 0);		// Initialize LED to be switched off

	uint8_t toggleFlag = 1;
	while (1)
	{
		// Polling input
		if (BUTTON_PRESSED == GPIO_ReadPin(ButtonHandle.p_GPIOx, ButtonHandle.pinConfig.pinNumber) )
		{
			Delay(100000);
			if (toggleFlag)
			{
				toggleFlag = 0;
				GPIO_TogglePin(LedHandle.p_GPIOx, LedHandle.pinConfig.pinNumber);
			}
		}
		else if (~toggleFlag)
		{
			toggleFlag = 1;
		}
		else
		{
			// NOP
		}

		Delay(100000);
	}
}

/*!
 * @fn			- GPIO_Test_LedToggleByButtonIT
 *
 * @brief 		- Toggles LED with using interrupt
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_Test_LedToggleByButtonIT (void)
{
	printf(" >> Push the blue user button to get the LED toogle! (IT Solution)\n");

	GPIO_Handle_t LedHandle, ButtonHandle;

	// GPIO Configuration
	ConfigUserLED(&LedHandle);
	ConfigUserButtonIT(&ButtonHandle);

	// Initialize GPIO
	GPIO_Init(&LedHandle);
	GPIO_Init(&ButtonHandle);

	// IRQ Configuration
	IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI15);
	IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);

	GPIO_WritePin(LedHandle.p_GPIOx, LedHandle.pinConfig.pinNumber, 0);		// Initialize LED to be switched off

	while (1);
}

/*!
 * @fn			- GPIO_Test_ClockOut
 *
 * @brief 		- Puts the HSI clock to the output PIN PA8
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_Test_ClockOut (void)
{
	// 1. Configure the RCC_CFGR register to HSI @ MCO1
	RCC->CFGR &= ~(0x3u << 21);		// Clearing MCO1 -> 21-22 bit positions

	// 2. Configure GPIO PA8 as Alternate Function to MSO1
	GPIO_Handle_t GpioMSO;
	GpioMSO.p_GPIOx = GPIOA;
	GpioMSO.pinConfig.pinNumber = GPIO_PIN_NO_8;
	GpioMSO.pinConfig.pinMode = GPIO_MODE_ALTFN;
	GpioMSO.pinConfig.pinAltFunMode = GPIO_AF0;

	GPIO_Init(&GpioMSO);
}

/*!
 * @fn			- EXTI15_10_IRQHandler
 *
 * @brief 		- ISR Handler for GPIO user button input (PC13)
 *
 * @param[in]	- none
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void EXTI15_10_IRQHandler (void)
{
	GPIO_IRQHandling(GPIO_PIN_NO_13);			// Clearing the pending register from the EXTI
	GPIO_TogglePin(GPIOA, GPIO_PIN_NO_5);		// Toogle the user LED
}

/*** EOF ***/
