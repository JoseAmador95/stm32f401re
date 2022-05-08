#include "nucleo-f401.h"
#include <stdbool.h>
#include <stddef.h>

GPIO_Handle_t NUCLEO_BUTTON, NUCLEO_LED;
SPI_Handle_t NUCLEO_SPI;
I2C_Handle_t NUCLEO_I2C;

void NUCLEO_Button_Setup(void)
{
    NUCLEO_BUTTON.pGPIOx = NUCLEO_BUTTON_PORT;
    NUCLEO_BUTTON.GPIO_PinConfig.GPIO_pinPuPdControl = GPIO_PUPD_NO;
    NUCLEO_BUTTON.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_BUTTON_GPIO;
    NUCLEO_BUTTON.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    NUCLEO_BUTTON.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    GPIO_Init(&NUCLEO_BUTTON);
}

uint8_t NUCLEO_Button_Read(void)
{
    return !GPIO_ReadFromInputPin(NUCLEO_BUTTON_PORT, NUCLEO_BUTTON_GPIO);
}

void NUCLEO_LED_Setup(void)
{
    NUCLEO_LED.pGPIOx = NUCLEO_LED_PORT;
    NUCLEO_LED.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_LED_GPIO;
    NUCLEO_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    NUCLEO_LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    NUCLEO_LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    GPIO_Init(&NUCLEO_LED);
}

void NUCLEO_LED_Write(uint8_t EnOrDi)
{
    GPIO_WriteToOutputPin(NUCLEO_LED_PORT, NUCLEO_LED_GPIO, EnOrDi);
}

void NUCLEO_LED_Toggle(void)
{
    GPIO_ToggleOutputPin(NUCLEO_LED_PORT, NUCLEO_LED_GPIO);
}

void NUCLEO_button_int_ft(void)
{
    NUCLEO_BUTTON.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    GPIO_IRQ_PriorityConfig(IRQ_NO_EXTI15_10, 5);
    GPIO_IRQ_InterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
    GPIO_Init(&NUCLEO_BUTTON);
}

void NUCLEO_button_int_rt(void)
{
    NUCLEO_BUTTON.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
    GPIO_IRQ_PriorityConfig(IRQ_NO_EXTI15_10, 5);
    GPIO_IRQ_InterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
    GPIO_Init(&NUCLEO_BUTTON);
}

void NUCLEO_button_int_rft(void)
{
    NUCLEO_BUTTON.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RFT;
    GPIO_IRQ_PriorityConfig(IRQ_NO_EXTI15_10, 5);
    GPIO_IRQ_InterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
    GPIO_Init(&NUCLEO_BUTTON);
}

void NUCLEO_IRQHandling(void)
{
    GPIO_IRQ_Handling(NUCLEO_BUTTON_GPIO);
}

void NUCLEO_SPI_Init(void)
{
    GPIO_Handle_t SPIPins;
    SPIPins.pGPIOx = NUCLEO_SPI_GPIO_PORT;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_pinPuPdControl = GPIO_PUPD_NO;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;

    // MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_SPI_MISO_GPIO;
    GPIO_Init(&SPIPins);

    // MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_SPI_MOSI_GPIO;
    GPIO_Init(&SPIPins);

    // SCLK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_SPI_SCLK_GPIO;
    GPIO_Init(&SPIPins);

    // CS
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_SPI_CS_GPIO;
    GPIO_Init(&SPIPins);

    // SPI Peripheral config
    NUCLEO_SPI.pSPIx = NUCLEO_SPI_PERIPH;
    NUCLEO_SPI.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    NUCLEO_SPI.SPIConfig.SPI_CPHA = SPI_MODE_CPHA_LOW;
    NUCLEO_SPI.SPIConfig.SPI_CPOL = SPI_MODE_CPOL_LOW;
    NUCLEO_SPI.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    NUCLEO_SPI.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    NUCLEO_SPI.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV64;
    NUCLEO_SPI.SPIConfig.SPI_SSM = SPI_SSM_DISABLE;
    SPI_Init(&NUCLEO_SPI);

    SPI_SSIConfig(NUCLEO_SPI_PERIPH, DISABLE);
    SPI_SSOEConfig(NUCLEO_SPI_PERIPH, ENABLE);
}

void NUCLEO_SPI_Set_Status(uint8_t status)
{
    if (status == DISABLE)
    {
        while (SPI_GetFlagStatus(NUCLEO_SPI_PERIPH, SPI_FLAG_BUSY))
            ;
    }

    SPI_PeripheralControl(&NUCLEO_SPI, status);
}

void NUCLEO_SPI_Transfer(uint8_t *in, uint8_t *out, uint8_t length)
{
    SPI_Send(&NUCLEO_SPI, out, length);
    SPI_Receive(&NUCLEO_SPI, in, length);
}

void NUCLEO_SPI_Send(uint8_t *data, uint8_t length)
{
    NUCLEO_SPI_Transfer(NULL, data, length);
}

void NUCLEO_SPI_Receive(uint8_t *data, uint8_t length)
{
    NUCLEO_SPI_Transfer(NULL, NULL, length);
    NUCLEO_SPI_Transfer(data, NULL, length);
}

void NUCLEO_I2C_Init(uint16_t address, uint32_t scl_freq, uint8_t enable_pullup)
{

    GPIO_Handle_t I2CPins;
    I2CPins.pGPIOx = NUCLEO_I2C_GPIO_PORT;
    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
    if (enable_pullup == ENABLE)
    {
        I2CPins.GPIO_PinConfig.GPIO_pinPuPdControl = GPIO_PUPD_PU;
    }
    else
    {
        I2CPins.GPIO_PinConfig.GPIO_pinPuPdControl = GPIO_PUPD_NO;
    }

    // SDA
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_I2C_SDA_GPIO;
    GPIO_Init(&I2CPins);

    // SCL
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = NUCLEO_I2C_SCL_GPIO;
    GPIO_Init(&I2CPins);

    NUCLEO_I2C.pI2Cx = NUCLEO_I2C_PERIPH;
    NUCLEO_I2C.config.ack_enable = I2C_ACK_ENABLE;
    NUCLEO_I2C.config.address = address;
    NUCLEO_I2C.config.scl_freq = scl_freq;
    if (scl_freq > I2C_FREQ_SM)
    {
        NUCLEO_I2C.config.FM_DutyCycle = I2C_DC_16_9;
    }
    else
    {
        NUCLEO_I2C.config.FM_DutyCycle = I2C_DC_2;
    }

    I2C_Init(&NUCLEO_I2C);
}

void NUCLEO_I2C_Set_Status(uint8_t status)
{
    I2C_Peripheral_Control(&NUCLEO_I2C, status);
}

void NUCLEO_I2C_ACK_Status(uint8_t status)
{
    I2C_ACK_Status(NUCLEO_I2C.pI2Cx, status);
}

uint8_t NUCLEO_I2C_Master_Send(uint8_t *buffer, uint16_t length,
                               uint16_t slave_address, uint8_t release_bus)
{
    return I2C_Master_Send(&NUCLEO_I2C, slave_address, buffer, length,
                           release_bus);
}

uint8_t NUCLEO_I2C_Master_Receive(uint8_t *buffer, uint16_t length,
                                  uint16_t slave_address, uint8_t release_bus)
{
    return I2C_Master_Receive(&NUCLEO_I2C, slave_address, buffer, length,
                              release_bus);
}

void NUCLEO_I2C_EV_Handler(void)
{
    I2C_EV_Handler(&NUCLEO_I2C);
}

void NUCLEO_I2C_ERR_Handler(void)
{
    I2C_ERR_Handler(&NUCLEO_I2C);
}

void NUCLEO_I2C_Close(uint8_t stop_transfer)
{
    I2C_Close(&NUCLEO_I2C, stop_transfer);
}