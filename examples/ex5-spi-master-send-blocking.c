#include "nucleo-f401.h"
#include "string.h"

#define NUCLEO_Wait_For_Button_Press() while (!NUCLEO_Button_Read())
#define MASTER_ADDRESS 0x61
#define SLAVE_ADDRESS 0x68
#define DELAY() for (int i = 0; i < 1000000; ++i)

int main(void)
{

    NUCLEO_Button_Setup();
    NUCLEO_I2C_Init(MASTER_ADDRESS, 100000, ENABLE);

    uint8_t message[] = "test data";

    NUCLEO_I2C_Set_Status(ENABLE);

    while (1)
    {
        NUCLEO_Wait_For_Button_Press();
        DELAY();

        NUCLEO_I2C_Master_Send(message, strlen((char *)message), SLAVE_ADDRESS);
    }

    return 0;
}
