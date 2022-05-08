#include "nucleo-f401.h"

#define MASTER_ADDRESS 0x61
#define SLAVE_ADDRESS 0b1000000
#define I2C_FREQ 100000
#define READ_MEMORY_1 0xFA
#define READ_MEMORY_2 0xFC
#define MEMORY_ADDRESS_1 0x0F
#define MEMORY_ADDRESS_2 0xC9

#define NUCLEO_Wait_For_Button_Press() while (!NUCLEO_Button_Read())

#define DELAY() for (int i = 0; i < 100000; ++i)
#define WAIT_UNTIL_TRUE(f) while ((f) == 0)

int main(void)
{
    NUCLEO_I2C_Init(MASTER_ADDRESS, I2C_FREQ, ENABLE);
    NUCLEO_Button_Setup();
    NUCLEO_I2C_Set_Status(ENABLE);
    NUCLEO_I2C_ACK_Status(ENABLE);
    uint8_t buff[8] = {0};

    while (true)
    {
        WAIT_UNTIL_TRUE(NUCLEO_Button_Read() == 1);

        I2C_IRQ_Interrupt_Config(I2C_IRQ_I2C1_EV, ENABLE);
        I2C_IRQ_Interrupt_Config(I2C_IRQ_I2C1_ER, ENABLE);

        buff[0] = READ_MEMORY_1;
        buff[1] = MEMORY_ADDRESS_2;

        NUCLEO_I2C_Master_Send(buff, 2, SLAVE_ADDRESS, false);
        NUCLEO_I2C_Master_Receive(buff, 4, SLAVE_ADDRESS, true);

        buff[4] = READ_MEMORY_2;
        buff[5] = MEMORY_ADDRESS_2;

        NUCLEO_I2C_Master_Send(buff + 4, 2, SLAVE_ADDRESS, false);
        NUCLEO_I2C_Master_Receive(buff + 4, 4, SLAVE_ADDRESS, true);
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