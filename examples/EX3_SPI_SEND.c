#include "NUCLEO_F401.h"

// Alt mode 6
// PB9 	NSS
// PB10	SCLK
// PB14 MISO
// PB15	MOSI

void delay(void)
{
	for (int i = 0; i < 1000000; ++i);
}

int main(void)
{
	NUCLEO_Button_Setup();
	//SPI_PeriClockControl(NUCLEO_SPI_PERIPH, ENABLE);
	NUCLEO_SPI_Init();

	char msg[] = "Hello World";
	uint8_t data_length = strlen(msg);

	while (1)
	{
		while (!NUCLEO_Button_Read());
		delay();

		SPI_PeripheralControl(NUCLEO_SPI_PERIPH, ENABLE);
		SPI_Send(NUCLEO_SPI_PERIPH, &data_length, 1);
		SPI_Send(NUCLEO_SPI_PERIPH, (uint8_t *)msg, data_length);

		while (SPI_GetFlagStatus(NUCLEO_SPI_PERIPH, SPI_FLAG_BUSY));

		SPI_PeripheralControl(NUCLEO_SPI_PERIPH, DISABLE);
	}
}
