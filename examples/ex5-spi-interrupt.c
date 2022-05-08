/**
 * @file EX5_SPI_TX_RX_INT.c
 * @author Jose Amador
 * @brief This program is a demo of SPI TX & RX with interrupts
 * 
 * Pinout:
 * | Nucleo | Arduino |
 * | Master |  Slave  |
 * | ------ | ------- |
 * |  D13   |   D13   |
 * |  D12   |   D12   |
 * |  D11   |   D11   |
 * |   A2   |   D10   |
 * |  D08   |   D08   |
 */

#include "nucleo-f401.h"
#include <stdio.h>

#define MAXLEN 500		 // Max bytes per message
char recvBuffer[MAXLEN]; // SPI message buffer

#define INTERRUPT_PIN NUCLEO_PIN_D08_GPIO
#define INTERRUPT_PORT NUCLEO_PIN_D08_PORT
#define INTERRUPT_IRQ IRQ_NO_EXTI9_5

volatile char readByte;
volatile uint8_t recvStop;
volatile uint8_t dataAvailable = 0;

// Delay function
void delay(void)
{
	for (int i = 0; i < 1000000; ++i);
}

int main(void)
{
	uint8_t dummy = 0xFB;

	NUCLEO_SPI_Init();
	GPIO_Handle_t gpioInt = GPIO_Setup(
		INTERRUPT_PIN,
		INTERRUPT_PORT,
		GPIO_MODE_IT_FT,
		GPIO_SPEED_LOW,
		GPIO_PUPD_PU,
		GPIO_OP_TYPE_PP);
	(void) gpioInt;

	GPIO_IRQ_PriorityConfig(INTERRUPT_IRQ, 15);
	GPIO_IRQ_InterruptConfig(INTERRUPT_IRQ, ENABLE);

	SPI_SSOEConfig(NUCLEO_SPI_PERIPH, ENABLE);
	SPI_IRQ_PriorityConfig(IRQ_NO_SPI1, 15);
	SPI_IRQ_InterruptConfig(IRQ_NO_SPI1, ENABLE);

	while (1)
	{
		recvStop = 0;

		while (!dataAvailable);

		GPIO_IRQ_InterruptConfig(INTERRUPT_IRQ, DISABLE);
		NUCLEO_SPI_Set_Status(ENABLE);

		while (!recvStop)
		{
			while (SPI_Send(&NUCLEO_SPI, &dummy, 1) == SPI_BUSY_IN_TX);
			while (SPI_Receive(&NUCLEO_SPI, (uint8_t*) &readByte, 1) == SPI_BUSY_IN_RX);
		}

		while (SPI_GetFlagStatus(NUCLEO_SPI.pSPIx, SPI_FLAG_BUSY));

		NUCLEO_SPI_Set_Status(DISABLE);

		printf("Received data: %s\n", recvBuffer);

		dataAvailable = 0;

		GPIO_IRQ_InterruptConfig(INTERRUPT_IRQ, ENABLE);
	}

	return 0;
}

void SPI1_IRQHandler(void)
{
	SPI_IRQ_Handling(&NUCLEO_SPI);
}

void SPI_ApplicationEventCallback(SPI_Handle_t* pSPIHandle, uint8_t AppEv)
{
	static uint32_t i = 0;
	if (AppEv == SPI_EVENT_RX_COMPLETE)
	{
		recvBuffer[i++] = readByte;
		if (readByte == '\0' || i == MAXLEN)
		{
			recvStop = 1;
			recvBuffer[i-1] = '\0';
			i = 0;
		}
	}
}

void EXTI9_5_IRQHandler(void)
{
	GPIO_IRQ_Handling(INTERRUPT_PIN);
	dataAvailable = 1;
}