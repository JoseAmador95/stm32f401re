/**
 * 
 */

#include "NUCLEO_F401.h"
#include "string.h"

#define MASTER_ADDRESS 0x61
#define SLAVE_ADDRESS 0x68

// Delay function
void delay(void)
{
	for (int i = 0; i < 1000000; ++i);
}

int main(void)
{

	NUCLEO_Button_Setup();
	NUCLEO_I2C_Init(MASTER_ADDRESS, 100000, ENABLE);

	uint8_t message[] = "test data";

	NUCLEO_I2C_Set_Status(ENABLE);

	while(1)
	{
		while(!NUCLEO_Button_Read());

		delay();

		NUCLEO_I2C_Master_Send(message, strlen((char*) message), SLAVE_ADDRESS);
	}

	return 0;
}
