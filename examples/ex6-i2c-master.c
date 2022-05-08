#include "nucleo-f401.h"

#define MASTER_ADDRESS 0x61
#define SLAVE_ADDRESS 0x68
#define I2C_FREQ 50000

#define NUCLEO_Wait_For_Button_Press() while (!NUCLEO_Button_Read())
#define CMD_READ_BYTE 0x51
#define CMD_READ_FULL 0x52
#define BUFF_SIZE 50

#define DELAY() for (int i = 0; i < 100000; ++i)
#define WAIT_UNTIL_TRUE(f)                                                     \
    while (f == 0)                                                             \
        ;

int main(void)
{
    NUCLEO_I2C_Init(MASTER_ADDRESS, I2C_FREQ, ENABLE);
    NUCLEO_Button_Setup();
    NUCLEO_I2C_Set_Status(ENABLE);
    NUCLEO_I2C_ACK_Status(ENABLE);

    I2C_IRQ_Interrupt_Config(I2C_IRQ_I2C1_EV, ENABLE);
    I2C_IRQ_Interrupt_Config(I2C_IRQ_I2C1_ER, ENABLE);

    uint8_t buff[BUFF_SIZE];
    uint8_t cmd;
    uint8_t length;
    while (1)
    {
        NUCLEO_Wait_For_Button_Press();
        DELAY();

        cmd = CMD_READ_BYTE;

        WAIT_UNTIL_TRUE(
            NUCLEO_I2C_Master_Send(&cmd, 1, SLAVE_ADDRESS, DISABLE));

        WAIT_UNTIL_TRUE(
            NUCLEO_I2C_Master_Receive(&length, 1, SLAVE_ADDRESS, DISABLE));

        cmd = CMD_READ_FULL;

        WAIT_UNTIL_TRUE(
            NUCLEO_I2C_Master_Send(&cmd, 1, SLAVE_ADDRESS, DISABLE));

        WAIT_UNTIL_TRUE(
            NUCLEO_I2C_Master_Receive(buff, length, SLAVE_ADDRESS, ENABLE));
    }

    return 0;
}

void I2C1_EV_IRQHandler(void)
{
    NUCLEO_I2C_EV_Handler();
}

void I2C1_ER_IRQHandler(void)
{
    NUCLEO_I2C_ERR_Handler();
}

void I2C_Application_EV_Callback(I2C_Handle_t pI2CHandle, I2C_APP flag)
{
    if (flag == I2C_APP_EV_TX_COMPLETE)
    {
        (void)0;
    }
    else if (flag == I2C_APP_EV_RX_COMPLETE)
    {
        (void)0;
    }
    else if (flag == I2C_APP_ERROR_AF)
    {
        NUCLEO_I2C_Close(ENABLE);
    }
}