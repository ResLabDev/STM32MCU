/** @file gpio.c
*
* @brief A description of the module's purpose.
*
*/

#include "gpio.h"


// === Protected Functions ===
//
/*!
 * @fn			- PortCode
 *
 * @brief 		- Selects the GPIO port code according to the GPIOx base address
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[out]	- none
 *
 * @return 		- Port code
 *
 * @note		- none
*/
static inline uint8_t PortCode (GPIO_RegDef_t *p_GPIO)
{
	return (GPIOA == p_GPIO) ? 0 :
		   (GPIOB == p_GPIO) ? 1 :
		   (GPIOC == p_GPIO) ? 2 :
		   (GPIOD == p_GPIO) ? 3 :
		   (GPIOE == p_GPIO) ? 4 :
		   (GPIOE == p_GPIO) ? 5 :
		   (GPIOG == p_GPIO) ? 6 : 7;
}


// === Public APIs ===
//
/*!
 * @fn			- GPIO_PeriClockControl
 *
 * @brief 		- Enables or disables the peripheral clock for the given GPIO port
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[in]	- enable: ENABLE or DISABLE macros
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_PeriClockControl (GPIO_RegDef_t *p_GPIO, uint8_t enable)
{
	if (enable)
	{

		if (GPIOA == p_GPIO)
		{
			GPIOA_PCLK_EN();
		}
		else if (GPIOB == p_GPIO)
		{
			GPIOB_PCLK_EN();
		}
		else if (GPIOC == p_GPIO)
		{
			GPIOC_PCLK_EN();
		}
		else if (GPIOD == p_GPIO)
		{
			GPIOD_PCLK_EN();
		}
		else if (GPIOE == p_GPIO)
		{
			GPIOE_PCLK_EN();
		}
		else if (GPIOF == p_GPIO)
		{
			GPIOF_PCLK_EN();
		}
		else if (GPIOG == p_GPIO)
		{
			GPIOG_PCLK_EN();
		}
		else if (GPIOH == p_GPIO)
		{
			GPIOH_PCLK_EN();
		}
		else
		{
			// NOP
		}
	}
	else
	{
		if (GPIOA == p_GPIO)
		{
			GPIOA_PCLK_DI();
		}
		else if (GPIOB == p_GPIO)
		{
			GPIOB_PCLK_DI();
		}
		else if (GPIOC == p_GPIO)
		{
			GPIOC_PCLK_DI();
		}
		else if (GPIOD == p_GPIO)
		{
			GPIOD_PCLK_DI();
		}
		else if (GPIOE == p_GPIO)
		{
			GPIOE_PCLK_DI();
		}
		else if (GPIOF == p_GPIO)
		{
			GPIOF_PCLK_DI();
		}
		else if (GPIOG == p_GPIO)
		{
			GPIOG_PCLK_DI();
		}
		else if (GPIOH == p_GPIO)
		{
			GPIOH_PCLK_DI();
		}
		else
		{
			// NOP
		}
	}
}

/*!
 * @fn			- GPIO_Init
 *
 * @brief 		- Initialization of the GPIO Pins
 *
 * @param[in]	- *p_GPIOhandle: GPIO base address + pin configuration settings
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_Init (GPIO_Handle_t *p_GPIOhandle)
{
	uint32_t temp = 0;

	// 0. Enable GPIO Periphery Clock
	GPIO_PeriClockControl(p_GPIOhandle->p_GPIOx, ENABLE);

	// 1. Mode
	if (p_GPIOhandle->pinConfig.pinMode < GPIO_MODE_IT_FT)
	{
		// Non-Interrupt mode
		temp = ~(0x3 <<  (p_GPIOhandle->pinConfig.pinNumber << 1));									// Clearing the bits to be set
		p_GPIOhandle->p_GPIOx->MODER &= temp;
		temp = 0;
		temp = p_GPIOhandle->pinConfig.pinMode << (p_GPIOhandle->pinConfig.pinNumber << 1);			// Setting the bits
		p_GPIOhandle->p_GPIOx->MODER |= temp;

	}
	else
	{
		// Interrupt mode
		switch (p_GPIOhandle->pinConfig.pinMode)
		{
			case GPIO_MODE_IT_RT:
			{
				// 1. Configure the rising edge trigger selection register RTSR
				EXTI->RTSR |= (1 << p_GPIOhandle->pinConfig.pinNumber);				// Set RTSR
				EXTI->FTSR &= ~(1 << p_GPIOhandle->pinConfig.pinNumber);			// Clear FTSR
				break;
			}
			case GPIO_MODE_IT_FT:
			{
				// 1. Configure the falling edge trigger selection register FTSR
				EXTI->FTSR |= (1 << p_GPIOhandle->pinConfig.pinNumber);				// Set FTSR
				EXTI->RTSR &= ~(1 << p_GPIOhandle->pinConfig.pinNumber);			// Clear RTSR
				break;
			}
			case GPIO_MODE_IT_FRT:
			{
				// 1. Configure both rising and falling edge trigger selection registers
				EXTI->RTSR |= (1 << p_GPIOhandle->pinConfig.pinNumber);				// Set RTSR
				EXTI->FTSR |= (1 << p_GPIOhandle->pinConfig.pinNumber);				// Set FTSR
				break;
			}
			default:
			{
				// NOP
				break;
			}
		}

		// 2. Configure the GPIO port selection in SYSCFG_EXTICR (Enable IT at EXTI peripheral site)
		uint8_t extiRegSelect = p_GPIOhandle->pinConfig.pinNumber / 4;
		uint8_t extiRegSection = (p_GPIOhandle->pinConfig.pinNumber % 4) * 4;
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[extiRegSelect] = PortCode(p_GPIOhandle->p_GPIOx) << extiRegSection;

		// 3. Enable the EXTI interrupt delivery using IMR (Interrupt Mask Register)
		EXTI->IMR |= (1 << p_GPIOhandle->pinConfig.pinNumber);

	}

	// 2. Speed
	temp = ~(0x3 <<  (p_GPIOhandle->pinConfig.pinNumber << 1));												// Clearing the bits to be set
	p_GPIOhandle->p_GPIOx->OSPEEDR &= temp;
	temp = 0;
	temp = p_GPIOhandle->pinConfig.pinSpeed << (p_GPIOhandle->pinConfig.pinNumber << 1);					// Setting the bits
	p_GPIOhandle->p_GPIOx->OSPEEDR |= temp;

	// 3. Pull-up - Pull-down settings
	temp = ~(0x3 <<  (p_GPIOhandle->pinConfig.pinNumber << 1));												// Clearing the bits to be set
	p_GPIOhandle->p_GPIOx->PUPDR &= temp;
	temp = 0;
	temp = p_GPIOhandle->pinConfig.pinPuPdControl << (p_GPIOhandle->pinConfig.pinNumber << 1);
	p_GPIOhandle->p_GPIOx->PUPDR |= temp;

	// 4. Output type => Set just in case of OutPut Mode
	if (GPIO_MODE_OUT == p_GPIOhandle->pinConfig.pinMode)
	{
		temp = ~(0x3 <<  (p_GPIOhandle->pinConfig.pinNumber << 1));											// Clearing the bits to be set
		p_GPIOhandle->p_GPIOx->OTYPER &= temp;
		temp = 0;
		temp = p_GPIOhandle->pinConfig.pinOPType << p_GPIOhandle->pinConfig.pinNumber;						// Setting the bits
		p_GPIOhandle->p_GPIOx->OTYPER |= temp;
	}

	// 5. Alternate mode function
	if (GPIO_MODE_ALTFN == p_GPIOhandle->pinConfig.pinMode)
	{
		uint8_t afrRegSelect = p_GPIOhandle->pinConfig.pinNumber / 8;
		temp = ~(0xf <<  (p_GPIOhandle->pinConfig.pinNumber << 2));											// Clearing the bits to be set
		p_GPIOhandle->p_GPIOx->AFR[afrRegSelect] &= temp;
		temp = 0;
		temp = p_GPIOhandle->pinConfig.pinAltFunMode << ((p_GPIOhandle->pinConfig.pinNumber % 8) << 2); 	// Clearing the bits to be set
		p_GPIOhandle->p_GPIOx->AFR[afrRegSelect] |= temp;
	}
}

/*!
 * @fn			- GPIO_DeInit
 *
 * @brief 		- Resetting all the GPIO Registers
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_DeInit (GPIO_RegDef_t *p_GPIO)
{
	// Reset the RCC register regarding the designated GPIO periphery
	if (GPIOA == p_GPIO)
	{
		GPIOA_REG_RESET();
	}
	else if (GPIOB == p_GPIO)
	{
		GPIOB_REG_RESET();
	}
	else if (GPIOC == p_GPIO)
	{
		GPIOC_REG_RESET();
	}
	else if (GPIOD == p_GPIO)
	{
		GPIOD_REG_RESET();
	}
	else if (GPIOE == p_GPIO)
	{
		GPIOE_REG_RESET();
	}
	else if (GPIOF == p_GPIO)
	{
		GPIOF_REG_RESET();
	}
	else if (GPIOG == p_GPIO)
	{
		GPIOG_REG_RESET();
	}
	else if (GPIOH == p_GPIO)
	{
		GPIOH_REG_RESET();
	}
	else
	{
		// NOP
	}

	// Disable GPIO Periphery Clock
	GPIO_PeriClockControl(p_GPIO, DISABLE);
}

/*!
 * @fn			- GPIO_ReadPin
 *
 * @brief 		- Reading a single value from the selected pin
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[in]	- pinNumber: the pin selector
 * @param[out]	- none
 *
 * @return 		- The read value: should be 0 or 1
 *
 * @note		- none
*/
uint8_t GPIO_ReadPin (GPIO_RegDef_t *p_GPIO, uint8_t pinNumber)
{
	uint8_t value = 0;

	value = (uint8_t)(p_GPIO->IDR >> pinNumber) & 0x00000001;

	return value;
}

/*!
 * @fn			- GPIO_ReadPort
 *
 * @brief 		- Reading 16 port input
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[out]	- none
 *
 * @return 		- The GPIO input
 *
 * @note		- none
*/
uint16_t GPIO_ReadPort (GPIO_RegDef_t *p_GPIO)
{
	uint16_t value = (uint16_t)p_GPIO->IDR;

	return value;
}

/*!
 * @fn			- GPIO_WritePin
 *
 * @brief 		- Writing a single value to the selected pin
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[in]	- pinNumber: the pin selector
 * @param[in]	- value: 0 or 1 (Set / Clear)
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_WritePin (GPIO_RegDef_t *p_GPIO, uint8_t pinNumber, uint8_t value)
{
	if (SET == (value & 0x01))
	{
		p_GPIO->ODR |= (1 << pinNumber);		// Set pin
	}
	else
	{
		p_GPIO->ODR &= ~(1 << pinNumber);		// Clear pin
	}
}

/*!
 * @fn			- GPIO_WritePort
 *
 * @brief 		- Writing the whole value to the port
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[in]	- value: the whole data
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_WritePort (GPIO_RegDef_t *p_GPIO, uint16_t value)
{
	p_GPIO->ODR = value;
}

/*!
 * @fn			- GPIO_TogglePin
 *
 * @brief 		- Toggling the selected pin
 *
 * @param[in]	- *p_GPIO: base address of the GPIO peripheral
 * @param[in]	- pinNumber: the pin selector
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_TogglePin (GPIO_RegDef_t *p_GPIO, uint8_t pinNumber)
{
	p_GPIO->ODR ^= (1 << pinNumber);
}



/*!
 * @fn			- GPIO_IRQHandling
 *
 * @brief 		- GPIO Interrupt Request Handler
 *
 * @param[in]	- pinNumber: the number of the pin where the interrupt occured
 * @param[out]	- none
 *
 * @return 		- none
 *
 * @note		- none
*/
void GPIO_IRQHandling (uint8_t pinNumber)
{
	// 1. Clear the EXTI PR pending register corresponding to the pin number
	if (EXTI->PR & (1 << pinNumber) )
	{
		EXTI->PR |= (1 << pinNumber);	// Clearing the pending register
	}
}

/*** EOF ***/
