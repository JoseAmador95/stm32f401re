#include "stm32f401-i2c-driver.h"
#include "assert.h"

#define MILLISECONDS 1000
#define MICROSECONDS (1000 * MILLISECONDS)
#define NANOSECONDS (1000 * MICROSECONDS)

/**
 * @brief Blocks the thread until the I2C SR flag is set
 * @param[in] pI2Cx Pointer to I2C peripheral
 * @para[in] flag I2C Status Register flags from I2C_STATUS_FLAGS
 */
#define I2C_Wait_For_Flag(pI2Cx, flag) while (!I2C_Get_Flag_Status(pI2Cx, flag))

/**
 * @brief Max SCL rise time
 * @note Units are nanoseconds
 */
enum I2C_MAX_TRISE
{
    I2C_MAX_TRISE_SM = 1000,
    I2C_MAX_TRISE_FM = 300
};

/**
 * @brief I2C status flags from SR1 and SR2
 */
typedef enum I2C_STATUS_FLAGS
{
    I2C_FLAG_SB,
    I2C_FLAG_ADDR,
    I2C_FLAG_BTF,
    I2C_FLAG_ADD10,
    I2C_FLAG_STOPF,
    I2C_FLAG_RXNE,
    I2C_FLAG_TXE,
    I2C_FLAG_MSL,
    I2C_FLAG_BUSY,
    I2C_FLAG_TRA,
    I2C_FLAG_GEN_CALL,
    I2C_FLAG_SMBDE_FAULT,
    I2C_FLAG_SMB_HOST,
    I2C_FLAG_DUALF,
    I2C_FLAG_PEC
} I2C_STATUS_FLAGS;

/**
 * @brief I2C error flags from SR1
 */
typedef enum I2C_ERROR_FLAGS
{
    I2C_ERROR_BERR = 8,
    I2C_ERROR_ARLO = 9,
    I2C_ERROR_AF = 10,
    I2C_ERROR_OVR = 11,
    I2C_ERROR_PECERR = 12,
    I2C_ERROR_TIMEOUT = 14,
    I2C_ERROR_SMBALERT = 15
} I2C_ERROR_FLAGS;

/**
 * @brief Generate the I2C start condition
 * @param[in] pI2Cx I2C peripheral base address
 */
static void I2C_Generate_Start_Condition(typedef_I2C_t *pI2Cx);

/**
 * @brief Generate the I2C stop condition
 * @param[in] pI2Cx I2C peripheral base address
 */
static void I2C_Generate_Stop_Condition(typedef_I2C_t *pI2Cx);

/**
 * @brief Get I2C flag status from the Status Registers
 * @param[in] pI2Cx I2C peripheral base address
 * @param[in] flag I2C flag from SR1 & SR2
 */
static uint8_t I2C_Get_Flag_Status(typedef_I2C_t *pI2Cx, I2C_STATUS_FLAGS flag);

/**
 * @brief Get the value for the TRISE register
 * @param[in] scl_freq I2C SCL frequency
 */
static uint8_t I2C_TRISE_Max(uint32_t scl_freq);

/**
 * @brief Set the clock control register bits
 * @param[in] apb_freq APB1 Clock frequency
 * @param[in] scl_freq Target SCL frequency
 * @param[in] dc Duty-cycle for Fast mode
 */
static uint16_t I2C_CCR(uint8_t apb_freq, uint32_t scl_freq, I2C_FM_DC dc);

/**
 * @brief Get the role of the device (Master/Slave)
 * @param[in] pI2Cx Pointer to I2C peripheral
 * @return Returns an I2C_ROLE macro
 */
static I2C_ROLE I2C_Get_Device_Role(typedef_I2C_t *pI2Cx);

/**
 * @brief Triggers the I2C address phase
 * @param[in] pI2Cx Pointer to I2C peripheral
 * @param[in] slave_address Address of the slave device
 * @param[in] rw Operation to perform (Read from slave or Write to slave)
 * @details The address phase is when the I2C master sends the address and 
 *          operation to perform in the I2C bus. 
 */
static void I2C_Address_Phase(typedef_I2C_t *pI2Cx, uint16_t slave_address,
                              RW rw);

/**
 * @brief Clears the ADDR bit in the ADDR bit in Status Register 1
 * @param[in] pI2CHandle Pointer to a I2C handle
 */
static void I2C_Clear_ADDR_Flag(I2C_Handle_t *pI2CHandle);

static uint8_t I2C_Get_Error_Status(typedef_I2C_t *pI2Cx, I2C_ERROR_FLAGS flag);
void I2C_Application_EV_Callback(I2C_Handle_t *pI2CHandle, I2C_APP flag);

void I2C_PeriClockControl(typedef_I2C_t *pI2Cx, uint8_t status)
{
    if (status == ENABLE)
    {
        if (pI2Cx == I2C1)
        {
            I2C1_PCLK_EN();
        }
        else if (pI2Cx == I2C2)
        {
            I2C2_PCLK_EN();
        }
        else if (pI2Cx == I2C3)
        {
            I2C3_PCLK_EN();
        }
    }
    else if (status == DISABLE)
    {
        if (pI2Cx == I2C1)
        {
            I2C1_PCLK_DI();
        }
        else if (pI2Cx == I2C2)
        {
            I2C2_PCLK_DI();
        }
        else if (pI2Cx == I2C3)
        {
            I2C3_PCLK_DI();
        }
    }
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    // Enable the peripheral clock
    I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

    // Get the APB1 clock frequency
    uint8_t freq = RCC_get_apb1_freq() / 1000000;

    // Assert invalid values
    assert(freq >= 2 /* MHz */);  // APB1 freq must be >=2 MHz
    assert(freq <= 50 /* MHz */); // APB1 freq must be <=50 MHz

    // Speed > 100 kbps require duty-cycle = 16/9
    if (pI2CHandle->config.scl_freq > I2C_FREQ_SM)
    {
        assert(pI2CHandle->config.FM_DutyCycle == I2C_DC_16_9);
    }

    // 10-bit addressing and dual addressing must not be enabled simultaneously
    assert(!(pI2CHandle->config.enable_10_bit_address &&
             pI2CHandle->config.enable_dual_address));

    // Write the APB1 clock frequency
    pI2CHandle->pI2Cx->CR2 &= ~(0b111111 << I2C_CR2_FREQ);
    pI2CHandle->pI2Cx->CR2 |= freq << I2C_CR2_FREQ;

    // Enable the ACK control
    pI2CHandle->pI2Cx->CR1 |= pI2CHandle->config.ack_enable << I2C_CR1_ACK;

    // Enable the 16/9 duty-cycle for speeds greater than 100 kbps
    if (pI2CHandle->config.scl_freq <= I2C_FREQ_SM)
    {
        // 1/2 duty cycle
        pI2CHandle->pI2Cx->CCR &= ~(1 << I2C_CCR_DUTY);
    }
    else
    {
        // 9/16 duty cycle
        pI2CHandle->pI2Cx->CCR |= 1 << I2C_CCR_DUTY;
    }

    // Write the clock control register
    pI2CHandle->pI2Cx->CCR |= I2C_CCR(freq, pI2CHandle->config.scl_freq,
                                      pI2CHandle->config.FM_DutyCycle);

    // Set the device address
    if (pI2CHandle->config.enable_10_bit_address)
    {
        // 10-bit address
        pI2CHandle->pI2Cx->OAR1 |= 1 << I2C_OAR1_ADDMODE;
        pI2CHandle->pI2Cx->OAR1 |= (pI2CHandle->config.address & 0x3FF)
                                   << I2C_OAR1_ADD0;
    }
    else
    {
        // 7-bit address
        pI2CHandle->pI2Cx->OAR1 &= ~(1 << I2C_OAR1_ADDMODE);
        pI2CHandle->pI2Cx->OAR1 |= (pI2CHandle->config.address & 0x7F)
                                   << I2C_OAR1_ADD71;
    }

    // This bit must be set ALWAYS, no apparent reason
    pI2CHandle->pI2Cx->OAR1 |= 1 << I2C_OAR1_KEEP1;

    // Enable dual address
    if (pI2CHandle->config.enable_dual_address)
    {
        // Dual address
        pI2CHandle->pI2Cx->OAR2 |= 1 << I2C_OAR2_ENDUAL;
        pI2CHandle->pI2Cx->OAR2 |= (pI2CHandle->config.address2 & 0x7F)
                                   << I2C_OAR2_ENDUAL;
    }
    else
    {
        // Regular address
        pI2CHandle->pI2Cx->OAR2 &= ~(1 << I2C_OAR2_ENDUAL);
        pI2CHandle->pI2Cx->OAR2 &= ~(0x7F << I2C_OAR2_ENDUAL);
    }

    pI2CHandle->pI2Cx->TRISE &= ~(0b111111);
    pI2CHandle->pI2Cx->TRISE |= I2C_TRISE_Max(pI2CHandle->config.scl_freq);
}

static uint16_t I2C_CCR(uint8_t apb_freq, uint32_t scl_freq, I2C_FM_DC dc)
{
    uint32_t scl_period; // Desired SCL period
    uint32_t CCR;        // APB-to-SCL ratio
    // MHz (1e6) (Frequency) to nanoseconds (1e-9) (Period)
    uint32_t apb_period = 1000U / apb_freq;
    if (scl_freq <= I2C_FREQ_SM)
    {
        // Standard mode
        // Hz (frequency) to nanoseconds (1e-9) (period)
        scl_period = 1000000000U / scl_freq;
        CCR = (scl_period / 2) / apb_period;
    }
    else
    {
        // Fast mode
        uint8_t duty_h, duty_l;
        scl_period = 1000000000U / scl_freq;

        if (dc == I2C_DC_2)
        {
            // 50% Duty cycle
            duty_l = 2;
            duty_h = 1;
        }
        else
        {
            // 9/16 Duty cycle
            duty_l = 16;
            duty_h = 9;
        }

        CCR = scl_freq / (duty_l + duty_h) / apb_period;
    }

    return CCR & 0x7FF;
}

void I2C_Deinit(I2C_Handle_t *pI2CHandle)
{
    if (pI2CHandle->pI2Cx == I2C1)
    {
        I2C1_REG_RESET();
    }
    else if (pI2CHandle->pI2Cx == I2C2)
    {
        I2C2_REG_RESET();
    }
    else if (pI2CHandle->pI2Cx == I2C3)
    {
        I2C3_REG_RESET();
    }
}

void I2C_IRQ_Interrupt_Config(I2C_IRQ irq_number, uint8_t status)
{
    NVIC_IRQ_Interrupt_Config(irq_number, status);
}

void I2C_IRQ_Priority_Config(I2C_IRQ irq_number, uint32_t priority)
{
    NVIC_IRQ_Priority_Config(irq_number, priority);
}

void I2C_Peripheral_Control(I2C_Handle_t *pI2CHandle, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        pI2CHandle->pI2Cx->CR1 |= 1 << I2C_CR1_PE;
    }
    else
    {
        pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
    }
}

void I2C_Address_Phase(typedef_I2C_t *pI2Cx, uint16_t slave_address, RW rw)
{
    uint32_t temp = slave_address << 1;
    if (rw == WRITE)
    {
        temp &= ~(1);
    }
    else
    {
        temp |= 1;
    }
    pI2Cx->DR = temp;
}

void I2C_ACK_Status(typedef_I2C_t *pI2Cx, uint8_t status)
{
    if (status == ENABLE)
    {
        pI2Cx->CR1 |= 1 << I2C_CR1_ACK;
    }
    else
    {
        pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
    }
}

/**
 * @brief Clears the ADDR bit in the ADDR bit in Status Register 1
 * @param[in] pI2Cx Pointer to a I2C perihperal
 */
void I2C_Clear_ADDR_Flag(I2C_Handle_t *pI2CHandle)
{
    uint32_t dummy;
    // Check for device role
    if (I2C_Get_Device_Role(pI2CHandle->pI2Cx) == I2C_ROLE_MASTER)
    {
        if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_RX)
        {
            if (pI2CHandle->length_rx == 1)
            {
                I2C_ACK_Status(pI2CHandle->pI2Cx, DISABLE);
                dummy = pI2CHandle->pI2Cx->SR1;
                dummy = pI2CHandle->pI2Cx->SR2;
                (void)dummy;
            }
        }
        else
        {
            dummy = pI2CHandle->pI2Cx->SR1;
            dummy = pI2CHandle->pI2Cx->SR2;
            (void)dummy;
        }
    }
    else
    {
        dummy = pI2CHandle->pI2Cx->SR1;
        dummy = pI2CHandle->pI2Cx->SR2;
        (void)dummy;
    }
}

void I2C_Master_Receive_BLOCK(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                              uint8_t *buffer, uint16_t length,
                              uint8_t release_bus)
{
    // Generate the start condition
    I2C_Generate_Start_Condition(pI2CHandle->pI2Cx);

    // Wait until the start condition bit is set
    I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_SB);

    // Write the source address + r/nw bit
    I2C_Address_Phase(pI2CHandle->pI2Cx, slave_address, READ);

    // Wait for the address to be acknowledged
    I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_ADDR);

    // Receive the data
    if (length == 1)
    {
        I2C_ACK_Status(pI2CHandle->pI2Cx, DISABLE);
        I2C_Clear_ADDR_Flag(pI2CHandle);

        I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_RXNE);

        if (release_bus)
        {
            I2C_Generate_Stop_Condition(pI2CHandle->pI2Cx);
        }

        *buffer = pI2CHandle->pI2Cx->DR;
    }
    else if (length > 1)
    {
        I2C_Clear_ADDR_Flag(pI2CHandle);

        for (uint32_t i = length; i > 0; --i)
        {
            I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_RXNE);

            if (i == 2)
            {
                I2C_ACK_Status(pI2CHandle->pI2Cx, DISABLE);

                if (release_bus)
                {
                    I2C_Generate_Stop_Condition(pI2CHandle->pI2Cx);
                }
            }

            *(buffer++) = pI2CHandle->pI2Cx->DR;
        }
    }

    I2C_ACK_Status(pI2CHandle->pI2Cx,
                   pI2CHandle->config.ack_enable == I2C_ACK_ENABLE);
}

void I2C_Master_Send_BLOCK(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                           uint8_t *buffer, uint16_t length,
                           uint8_t release_bus)
{
    // Generate Start Conditon
    I2C_Generate_Start_Condition(pI2CHandle->pI2Cx);

    // Wait until the Start condition bit is set
    I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_SB);

    // Write the destination address + r/nw bit
    I2C_Address_Phase(pI2CHandle->pI2Cx, slave_address, WRITE);

    // Wait until the address is acknowledged
    I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_ADDR);

    uint32_t dummy = pI2CHandle->pI2Cx->SR2; // Read SR2 to clear ADDR
    (void)dummy;

    while (length > 0)
    {
        // Wait for the Tx buffer to empty
        I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_TXE);

        // Send data
        pI2CHandle->pI2Cx->DR = *(buffer++);
        length--;
    }

    I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_TXE);
    I2C_Wait_For_Flag(pI2CHandle->pI2Cx, I2C_FLAG_BTF);

    if (release_bus)
    {
        I2C_Generate_Stop_Condition(pI2CHandle->pI2Cx);
    }
}

uint8_t I2C_Master_Receive_IT(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                              uint8_t *buffer, uint16_t length,
                              uint8_t release_bus)
{
    I2C_STATUS i2c_status = pI2CHandle->i2c_status;

    if (i2c_status == I2C_STATUS_READY)
    {
        pI2CHandle->buffer_rx = buffer;
        pI2CHandle->length_rx = length;
        pI2CHandle->i2c_status = I2C_STATUS_BUSY_RX;
        pI2CHandle->device_address = slave_address;
        pI2CHandle->release_bus = release_bus;

        // Generate start condition
        I2C_Generate_Start_Condition(pI2CHandle->pI2Cx);

        // Enable the I2C interrupts for handling data flow
        pI2CHandle->pI2Cx->CR2 |= 1 << I2C_CR2_ITBUFEN;

        // Enable the I2C interrupts for handling the I2C events
        pI2CHandle->pI2Cx->CR2 |= 1 << I2C_CR2_ITEVTEN;

        // Enable the I2C interrupts for handling I2C errors
        pI2CHandle->pI2Cx->CR2 |= 1 << I2C_CR2_ITERREN;
    }

    return i2c_status == I2C_STATUS_READY;
}

uint8_t I2C_Master_Send_IT(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                           uint8_t *buffer, uint16_t length,
                           uint8_t release_bus)
{
    I2C_STATUS i2c_status = pI2CHandle->i2c_status;

    if (i2c_status == I2C_STATUS_READY)
    {
        pI2CHandle->buffer_tx = buffer;
        pI2CHandle->length_tx = length;
        pI2CHandle->i2c_status = I2C_STATUS_BUSY_TX;
        pI2CHandle->device_address = slave_address;
        pI2CHandle->release_bus = release_bus;

        // Generate start condition
        I2C_Generate_Start_Condition(pI2CHandle->pI2Cx);

        // Enable the I2C interrupts for handling data flow
        pI2CHandle->pI2Cx->CR2 |= 1 << I2C_CR2_ITBUFEN;

        // Enable the I2C interrupts for handling the I2C events
        pI2CHandle->pI2Cx->CR2 |= 1 << I2C_CR2_ITEVTEN;

        // Enable the I2C interrupts for handling I2C errors
        pI2CHandle->pI2Cx->CR2 |= 1 << I2C_CR2_ITERREN;
    }

    return i2c_status == I2C_STATUS_READY;
}

uint8_t I2C_Master_Receive(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                           uint8_t *buffer, uint16_t length,
                           uint8_t release_bus)
{
#ifdef I2C_API_BLOCKING
    I2C_Master_Receive_BLOCK(pI2CHandle, slave_address, buffer, length,
                             release_bus);
    return 0;
#else
    return I2C_Master_Receive_IT(pI2CHandle, slave_address, buffer, length,
                                 release_bus);
#endif
}

uint8_t I2C_Master_Send(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                        uint8_t *buffer, uint16_t length, uint8_t release_bus)
{
#ifdef I2C_API_BLOCKING
    I2C_Master_Send_BLOCK(pI2CHandle, slave_address, buffer, length,
                          release_bus);
    return 0;
#else
    return I2C_Master_Send_IT(pI2CHandle, slave_address, buffer, length,
                              release_bus);
#endif
}

void I2C_EV_Handler(I2C_Handle_t *pI2CHandle)
{
    // Check if the event interrupts are enabled
    uint8_t i2c_ev_int_enabled =
        (uint32_t)(pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITEVTEN)) != 0;

    // Check if the buffer interrupts are enabled
    uint8_t i2c_buff_int_enabled =
        (uint32_t)(pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITBUFEN)) != 0;

    // Check if this handler should have been triggered
    if (!i2c_ev_int_enabled)
    {
        // Exit as the interrupts are not enabled
        return;
    }

    if (I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_SB))
    {
        // I2C Start Condition detected
        // Next step: Execute address phase
        RW operation;
        if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_TX)
        {
            operation = WRITE;
        }
        else if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_RX)
        {
            operation = READ;
        }

        I2C_Address_Phase(pI2CHandle->pI2Cx, pI2CHandle->device_address,
                          operation);
    }

    if (I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_ADDR))
    {
        // I2C Address ack detected
        // Next Step: Clear the ADDR bit
        // The R/W operations are handled after the Byte Transfer is finished
        I2C_Clear_ADDR_Flag(pI2CHandle);
    }

    if (I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_BTF))
    {
        // An I2C transfer has been completed
        if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_TX)
        {
            // I2C device is in transmission mode
            if (I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_TXE))
            {
                // TX buffer is empy
                // I2C peripheral may have completed transmission
                if (pI2CHandle->length_tx == 0)
                {
                    // Transmission is completed
                    // The I2C peripheral will be reset for the next transfer

                    // Generate a stop condition
                    if (pI2CHandle->release_bus)
                    {
                        I2C_Generate_Stop_Condition(pI2CHandle->pI2Cx);
                    }

                    // Reset I2C Handler to default state
                    I2C_Close(pI2CHandle, DISABLE);

                    // Notify the application about tx complete
                    I2C_Application_EV_Callback(pI2CHandle,
                                                I2C_APP_EV_TX_COMPLETE);
                }
            }
        }
        else
        {
            // Nothing to do if RXNE is set
        }
    }

    if (I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_STOPF))
    {
        // The STOPF bit is only used in slave mode

        // Clear the STOPF flag
        pI2CHandle->pI2Cx->CR1 |= 0;

        I2C_Application_EV_Callback(pI2CHandle, I2C_APP_EV_STOP);
    }

    // if the buffer interrupts are enabled
    if (i2c_buff_int_enabled)
    {
        // If the TXE flag is enabled
        if (I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_TXE))
        {
            // If the device is master
            if (I2C_Get_Device_Role(pI2CHandle->pI2Cx) == I2C_ROLE_MASTER)
            {
                // If the master device is transmitting
                if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_TX)
                {
                    // If there are pending bytes to transfer
                    if (pI2CHandle->length_tx)
                    {
                        pI2CHandle->pI2Cx->DR = *(pI2CHandle->buffer_tx++);
                        pI2CHandle->length_tx--;
                    }
                }
            }
        }

        // If the RXNE flag is enabled
        if (I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_RXNE))
        {
            // If the device is I2C master
            if (I2C_Get_Device_Role(pI2CHandle->pI2Cx) == I2C_ROLE_MASTER)
            {
                // If the device is busy in RX
                if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_RX)
                {
                    if (pI2CHandle->length_rx == 1)
                    {
                        *(pI2CHandle->buffer_rx++) = pI2CHandle->pI2Cx->DR;
                        pI2CHandle->length_rx--;
                    }
                    else if (pI2CHandle->length_rx > 1)
                    {
                        if (pI2CHandle->length_rx == 2)
                        {
                            I2C_ACK_Status(pI2CHandle->pI2Cx, DISABLE);
                        }

                        *(pI2CHandle->buffer_rx++) = pI2CHandle->pI2Cx->DR;
                        pI2CHandle->length_rx--;
                    }
                    else if (pI2CHandle->length_rx == 0)
                    {
                        I2C_Generate_Stop_Condition(pI2CHandle->pI2Cx);

                        I2C_Close(pI2CHandle, DISABLE);

                        I2C_Application_EV_Callback(pI2CHandle,
                                                    I2C_APP_EV_RX_COMPLETE);
                    }
                }
            }
        }
    }
}

void I2C_ERR_Handler(I2C_Handle_t *pI2CHandle)
{
    if ((pI2CHandle->pI2Cx->CR2 & (1 << I2C_CR2_ITERREN)) == 0)
    {
        // Error interrupts are not enabled
        return;
    }

    // Bus error
    if (I2C_Get_Error_Status(pI2CHandle->pI2Cx, I2C_ERROR_BERR))
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_BERR);

        I2C_Application_EV_Callback(pI2CHandle, I2C_APP_ERROR_BERR);
    }

    // Arbitration Lost error
    if (I2C_Get_Error_Status(pI2CHandle->pI2Cx, I2C_ERROR_ARLO))
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_ARLO);

        I2C_Application_EV_Callback(pI2CHandle, I2C_APP_ERROR_ARLO);
    }

    // Acknowledgement Failed error
    if (I2C_Get_Error_Status(pI2CHandle->pI2Cx, I2C_ERROR_AF))
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_AF);

        I2C_Application_EV_Callback(pI2CHandle, I2C_APP_ERROR_AF);
    }

    // Overrun/Underrun error
    if (I2C_Get_Error_Status(pI2CHandle->pI2Cx, I2C_ERROR_OVR))
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_OVR);

        I2C_Application_EV_Callback(pI2CHandle, I2C_APP_ERROR_OVR);
    }

    // Timeout error
    if (I2C_Get_Error_Status(pI2CHandle->pI2Cx, I2C_ERROR_TIMEOUT))
    {
        pI2CHandle->pI2Cx->SR1 &= ~(1 << I2C_SR1_TIMEOUT);

        I2C_Application_EV_Callback(pI2CHandle, I2C_APP_ERROR_TIMEOUT);
    }
}

static void I2C_Generate_Start_Condition(typedef_I2C_t *pI2Cx)
{
    pI2Cx->CR1 |= 1 << I2C_CR1_START;
}

static void I2C_Generate_Stop_Condition(typedef_I2C_t *pI2Cx)
{
    pI2Cx->CR1 |= 1 << I2C_CR1_STOP;
}

static uint8_t I2C_Get_Flag_Status(typedef_I2C_t *pI2Cx, I2C_STATUS_FLAGS flag)
{
    uint8_t status;

    switch (flag)
    {
    case I2C_FLAG_SB: // Start Bit ocurred
        status = (pI2Cx->SR1 >> I2C_SR1_SB) & 0x01;
        break;
    case I2C_FLAG_ADDR: // Address matched
        status = (pI2Cx->SR1 >> I2C_SR1_ADDR) & 0x01;
        break;
    case I2C_FLAG_TXE: // TX buffer empty
        status = (pI2Cx->SR1 >> I2C_SR1_TXE) & 0x01;
        break;
    case I2C_FLAG_RXNE: // RX buffer not empty
        status = (pI2Cx->SR1 >> I2C_SR1_RXNE) & 0x01;
        break;
    case I2C_FLAG_BTF: // Byte transfer finished
        status = (pI2Cx->SR1 >> I2C_SR1_BTF) & 0x01;
        break;
    case I2C_FLAG_BUSY: // Bus busy
        status = (pI2Cx->SR2 >> I2C_SR2_BUSY) & 0x01;
        break;
    case I2C_FLAG_ADD10:
        status = (pI2Cx->SR1 >> I2C_SR1_ADD10) & 0x01;
        break;
    case I2C_FLAG_STOPF:
        status = (pI2Cx->SR1 >> I2C_SR1_STOPF) & 0x01;
        break;
    case I2C_FLAG_MSL:
        status = (pI2Cx->SR2 >> I2C_SR2_MSL) & 0x01;
        break;
    case I2C_FLAG_TRA:
        status = (pI2Cx->SR2 >> I2C_SR2_TRA) & 0x01;
        break;
    case I2C_FLAG_GEN_CALL:
        status = (pI2Cx->SR2 >> I2C_SR2_GENCALL) & 0x01;
        break;
    case I2C_FLAG_SMB_HOST:
    case I2C_FLAG_SMBDE_FAULT:
    case I2C_FLAG_DUALF:
    case I2C_FLAG_PEC:
    default:
        break;

    }

    return status;
}

static uint8_t I2C_Get_Error_Status(typedef_I2C_t *pI2Cx, I2C_ERROR_FLAGS flag)
{
    return pI2Cx->SR1 & (1 << (uint8_t)flag);
}

static uint8_t I2C_TRISE_Max(uint32_t scl_freq)
{
    const uint32_t apb_freq = RCC_get_apb1_freq();
    const uint32_t apb_period =
        NANOSECONDS / apb_freq; // apb freq in nanoseconds

    // Max SCL rise time for SM or FM, respectively (in nanoseconds)
    const uint16_t max_Trise =
        (scl_freq <= I2C_FREQ_SM) ? I2C_MAX_TRISE_SM : I2C_MAX_TRISE_FM;

    // Compute the TRISE bits using the formula
    uint8_t TRISE = max_Trise / apb_period;

    // Return 5 bits of TRISE+1 (required by the reference manual)
    return (TRISE + 1) & 0x1F;
}

static I2C_ROLE I2C_Get_Device_Role(typedef_I2C_t *pI2Cx)
{
    if (pI2Cx->SR2 & (1 << I2C_SR2_MSL))
    {
        return I2C_ROLE_MASTER;
    }
    else
    {
        return I2C_ROLE_SLAVE;
    }
}

void I2C_Close(I2C_Handle_t *pI2CHandle, uint8_t stop_transfer)
{
    // Disabel interrupts for events and buffer
    pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITEVTEN);
    pI2CHandle->pI2Cx->CR2 &= ~(1 << I2C_CR2_ITBUFEN);

    if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_TX)
    {
        pI2CHandle->buffer_tx = NULL;
        pI2CHandle->length_tx = 0;
    }
    else if (pI2CHandle->i2c_status == I2C_STATUS_BUSY_RX)
    {
        pI2CHandle->buffer_rx = NULL;
        pI2CHandle->length_rx = 0;
        if (pI2CHandle->config.ack_enable == I2C_ACK_ENABLE)
        {
            I2C_ACK_Status(pI2CHandle->pI2Cx, ENABLE);
        }
    }

    pI2CHandle->i2c_status = I2C_STATUS_READY;
    pI2CHandle->release_bus = ENABLE;

    if (stop_transfer)
    {
        I2C_Generate_Start_Condition(pI2CHandle->pI2Cx);
    }
}

__weak void I2C_Application_EV_Callback(I2C_Handle_t *pI2CHandle, I2C_APP flag)
{
    // Weak implementation
}