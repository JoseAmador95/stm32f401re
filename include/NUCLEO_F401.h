#ifndef __NUCLEO_F401_H_
#define __NUCLEO_F401_H_

#include "STM32F401RE.h"

#define NUCLEO_PIN_D00_GPIO 3
#define NUCLEO_PIN_D00_PORT GPIOA
#define NUCLEO_PIN_D01_GPIO 2
#define NUCLEO_PIN_D01_PORT GPIOA
#define NUCLEO_PIN_D02_GPIO 10
#define NUCLEO_PIN_D02_PORT GPIOA
#define NUCLEO_PIN_D03_GPIO 3
#define NUCLEO_PIN_D03_PORT GPIOB
#define NUCLEO_PIN_D04_GPIO 5
#define NUCLEO_PIN_D04_PORT GPIOB
#define NUCLEO_PIN_D05_GPIO 4
#define NUCLEO_PIN_D05_PORT GPIOB
#define NUCLEO_PIN_D06_GPIO 10
#define NUCLEO_PIN_D06_PORT GPIOB
#define NUCLEO_PIN_D07_GPIO 8
#define NUCLEO_PIN_D07_PORT GPIOA
#define NUCLEO_PIN_D08_GPIO 9
#define NUCLEO_PIN_D08_PORT GPIOA
#define NUCLEO_PIN_D09_GPIO 7
#define NUCLEO_PIN_D09_PORT GPIOC
#define NUCLEO_PIN_D10_GPIO 6
#define NUCLEO_PIN_D10_PORT GPIOB
#define NUCLEO_PIN_D11_GPIO 7
#define NUCLEO_PIN_D11_PORT GPIOA
#define NUCLEO_PIN_D12_GPIO 6
#define NUCLEO_PIN_D12_PORT GPIOA
#define NUCLEO_PIN_D13_GPIO 5
#define NUCLEO_PIN_D13_PORT GPIOA
#define NUCLEO_PIN_D14_GPIO 9
#define NUCLEO_PIN_D14_PORT GPIOB
#define NUCLEO_PIN_D15_GPIO 8
#define NUCLEO_PIN_D15_PORT GPIOB

#define NUCLEO_PIN_A0_GPIO 0
#define NUCLEO_PIN_A0_PORT GPIOA
#define NUCLEO_PIN_A1_GPIO 1
#define NUCLEO_PIN_A1_PORT GPIOA
#define NUCLEO_PIN_A2_GPIO 4
#define NUCLEO_PIN_A2_PORT GPIOA
#define NUCLEO_PIN_A3_GPIO 0
#define NUCLEO_PIN_A3_PORT GPIOB
#define NUCLEO_PIN_A4_GPIO 1
#define NUCLEO_PIN_A4_PORT GPIOC
#define NUCLEO_PIN_A5_GPIO 0
#define NUCLEO_PIN_A5_PORT GPIOC

#define NUCLEO_BUTTON_GPIO 13
#define NUCLEO_BUTTON_PORT GPIOC

#define NUCLEO_LED_GPIO NUCLEO_PIN_D13_GPIO
#define NUCLEO_LED_PORT NUCLEO_PIN_D13_PORT

#define NUCLEO_SPI_PERIPH SPI1
#define NUCLEO_SPI_GPIO_PORT GPIOA
#define NUCLEO_SPI_MISO_GPIO NUCLEO_PIN_D12_GPIO
#define NUCLEO_SPI_MOSI_GPIO NUCLEO_PIN_D11_GPIO
#define NUCLEO_SPI_SCLK_GPIO NUCLEO_PIN_D13_GPIO
#define NUCLEO_SPI_CS_GPIO NUCLEO_PIN_A2_GPIO

#define NUCLEO_I2C_PERIPH I2C1
#define NUCLEO_I2C_GPIO_PORT GPIOB
#define NUCLEO_I2C_SDA_GPIO NUCLEO_PIN_D14_GPIO
#define NUCLEO_I2C_SCL_GPIO NUCLEO_PIN_D15_GPIO

#define NUCLEO_UART_TX_GPIO NUCLEO_PIN_D01_GPIO
#define NUCLEO_UART_TX_PORT NUCLEO_PIN_D01_PORT
#define NUCLEO_UART_RX_GPIO NUCLEO_PIN_D00_GPIO
#define NUCLEO_UART_RX_PORT NUCLEO_PIN_D00_PORT

GPIO_Handle_t NUCLEO_BUTTON, NUCLEO_LED;
SPI_Handle_t NUCLEO_SPI;
I2C_Handle_t NUCLEO_I2C;

void NUCLEO_Button_Setup(void);
uint8_t NUCLEO_Button_Read(void);
void NUCLEO_LED_Setup(void);
void NUCLEO_LED_Write(uint8_t EnOrDi);
void NUCLEO_LED_Toggle(void);
void NUCLEO_button_int_ft(void);
void NUCLEO_button_int_rt(void);
void NUCLEO_button_int_rft(void);
void NUCLEO_IRQHandling(void);

void NUCLEO_SPI_Init(void);
void NUCLEO_SPI_Set_Status(uint8_t status);
void NUCLEO_SPI_Transfer(uint8_t* in, uint8_t* out, uint8_t length);
void NUCLEO_SPI_Send(uint8_t* data, uint8_t length);
void NUCLEO_SPI_Receive(uint8_t* data, uint8_t length);

void NUCLEO_I2C_Init(uint16_t address, uint32_t speed, uint8_t enable_pullup);
void NUCLEO_I2C_Set_Status(uint8_t status);
void NUCLEO_I2C_Master_Send(uint8_t* buffer, uint16_t length, uint16_t slave_address);


#endif
