/**
  ******************************************************************************
  * @file    main.c
  * @author  Auto-generated by STM32CubeIDE
  * @version V1.0
  * @brief   Default main function.
  ******************************************************************************
*/

#include "gpio_test.h"
#include "spi_test.h"


int main(void)
{
	printf(" >> STM32 system is started.\n");

	SPI_Test_ReceiveData (20);
#if 0
	SPI_Test_SendData(20);
	GPIO_Test_ClockOut();
	GPIO_Test_LedToggleNoIT(20);
	GPIO_Test_LedToggleByButton();
	GPIO_Test_LedToggleByButtonIT();
#endif

	while (1);

	return 0;
}
