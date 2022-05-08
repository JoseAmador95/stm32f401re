#include "nucleo-f401.h"

void delay(void)
{
	for (int i = 0; i < 1000000; ++i);
}

int main(void)
{
	NUCLEO_button_setup();
	NUCLEO_LED_setup();
	NUCLEO_button_int_ft();
	while (1);

	return 0;
}

void EXTI15_10_IRQHandler(void)
{
	NUCLEO_IRQHandling();
	GPIO_ToggleOutputPin(NUCLEO_LED_PORT, NUCLEO_LED_GPIO);
	delay();
}
