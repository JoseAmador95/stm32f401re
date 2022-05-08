/*
Example 04: SPI RX & TX test
This example tests the SPI TX and RX capabilities.
It requires an SPI slave (Arduino Uno board) with the
Slave program running. This program sends a command byte
to the slave and pulls a GPIO if the response is the 
expected.

Make sure to add the global #define SPI_API_BLOCKING
*/

#include "nucleo-f401.h"
#include "string.h"

void command_led_ctrl();
void command_led_read();
void command_sensor_read();
void command_print();
void command_read_id();

enum command
{
	COMMAND_LED_CTRL = 0x50,
	COMMAND_SENSOR_READ = 0x51,
	COMMAND_LED_READ = 0x52,
	COMMAND_PRINT = 0x53,
	COMMAND_ID_READ = 0x54
};

/**
 * Ackowlegement pin number and port
 */
#define PIN_ACK_GPIO NUCLEO_PIN_D08_GPIO
#define PIN_ACK_PORT NUCLEO_PIN_D08_PORT

// Command byte for toggling the LED
#define COMMAND_LED_CTRL 0x50

// Delay function
void delay(void)
{
	for (int i = 0; i < 1000000; ++i)
		;
}

// Check slave response function
uint8_t SPI_VerifyResponse(uint8_t *ackbyte)
{
	return *ackbyte == (uint8_t)0xF5;
}

int main(void)
{
	// Setup the ACK pin
	GPIO_Handle_t pin_ack = GPIO_Setup(
		PIN_ACK_GPIO,
		PIN_ACK_PORT,
		GPIO_MODE_OUT,
		GPIO_SPEED_MEDIUM,
		GPIO_PUPD_NO,
		GPIO_OP_TYPE_PP);
	(void) pin_ack;

	// Setup the on-board button
	NUCLEO_Button_Setup();
	// Setup the Arduino-like SPI bus
	NUCLEO_SPI_Init();

	uint8_t command = COMMAND_LED_CTRL; // Buffer to send commands to the slave

	while (1)
	{
		// Wait for the user to push the button
		while (!NUCLEO_Button_Read());

		// Wait for debouncing
		delay();

		// Enable SPI peripheral
		NUCLEO_SPI_Set_Status(ENABLE);

		switch(command)
		{
			case COMMAND_LED_CTRL:
				command_led_ctrl();
			break;
			case COMMAND_LED_READ:
				command_led_read();
			break;
			case COMMAND_SENSOR_READ:
				command_sensor_read();
			break;
			case COMMAND_PRINT:
				command_print();
			break;
			case COMMAND_ID_READ:
				command_read_id();
			break;
		}

		// Disable the SPI peripheral
		NUCLEO_SPI_Set_Status(DISABLE);

		command = (command < 0x54) ? command + 1 : COMMAND_LED_CTRL;
	}
}

void command_led_ctrl()
{
	static uint8_t status = 1;
	uint8_t ackbyte, dummy, args[2];
	uint8_t command = COMMAND_LED_CTRL;

	NUCLEO_SPI_Transfer(&dummy, &command, 1);
	dummy = 0;
	NUCLEO_SPI_Transfer(&ackbyte, &dummy, 1);

	if (SPI_VerifyResponse(&ackbyte))
	{
		args[0] = 8;
		args[1] = status;

		NUCLEO_SPI_Transfer(args, args, 2);
	}
}

void command_sensor_read()
{
	uint8_t command = COMMAND_SENSOR_READ;
	uint8_t ackbyte, dummy, arg, read;

	NUCLEO_SPI_Transfer(&dummy, &command, 1);
	NUCLEO_SPI_Transfer(&ackbyte, &dummy, 1);

	if (SPI_VerifyResponse(&ackbyte))
	{
		arg = 0;

		NUCLEO_SPI_Transfer(&dummy, &arg, 1);
		delay();
		NUCLEO_SPI_Transfer(&read, &dummy, 1);
	}
}

void command_led_read()
{
	uint8_t command = COMMAND_LED_READ;
	uint8_t dummy, arg, read, ackbyte;

	NUCLEO_SPI_Transfer(&dummy, &command, 1);
	NUCLEO_SPI_Transfer(&ackbyte, &dummy, 1);

	if (SPI_VerifyResponse(&ackbyte))
	{
		arg = 8;

		NUCLEO_SPI_Transfer(&dummy, &arg, 1);
		delay();
		NUCLEO_SPI_Transfer(&read, &dummy, 1);
	}
}

void command_print()
{
	uint8_t command = COMMAND_PRINT;
	uint8_t ackbyte, len, dummy;

	uint8_t msg[] = "MESSAGE";

	len = strlen((const char*) msg);

	NUCLEO_SPI_Transfer(&dummy, &command, 1);
	NUCLEO_SPI_Transfer(&ackbyte, &dummy, 1);

	if (SPI_VerifyResponse(&ackbyte))
	{
		NUCLEO_SPI_Transfer(&dummy, &len, 1);
		NUCLEO_SPI_Transfer(msg, msg, len);
	}
}

void command_read_id()
{
	uint8_t command = COMMAND_ID_READ;
	uint8_t ackbyte, dummy, id[11];

	NUCLEO_SPI_Transfer(&dummy, &command, 1);
	NUCLEO_SPI_Transfer(&ackbyte, &dummy, 1);

	if (SPI_VerifyResponse(&ackbyte))
	{
		NUCLEO_SPI_Transfer(id, id, 11);
	}
}