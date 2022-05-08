#include "nucleo-f401.h"

void delay(void)
{
	for (int i = 0; i < 500000; ++i);
}

int main(void)
{
	NUCLEO_LED_Setup();
	NUCLEO_Button_Setup();

	while (1)
	{
		if (NUCLEO_Button_Read())
		{
            NUCLEO_LED_Toggle();
			delay();
		}
	}
}
