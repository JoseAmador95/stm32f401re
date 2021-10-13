#include "stm32f401xx_i2c_driver.h"
#include "assert.h"

#define MILLISECONDS 1000
#define MICROSECONDS (1000*MILLISECONDS)
#define NANOSECONDS (1000*MICROSECONDS)

/**
 * @brief Max SCL rise time
 * @note Units are nanoseconds
 */
enum I2C_MAX_TRISE {
    I2C_MAX_TRISE_SM = 1000,
    I2C_MAX_TRISE_FM = 300
};

/**
 * @brief I2C status flags from SR1 and SR2
 */
typedef enum
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
 * @brief APB clock prescaler values
 */
const uint8_t RCC_APB_PRESCALER_DIV[] = {2, 4, 8 ,16};

/**
 * @brief AHB clock prescaler values
 */
const uint16_t RCC_AHB_PRESCALER_DIV[] = {2, 4, 8, 16, 64, 128, 256, 512};

/**
 * @brief Generate the I2C start condition
 * @param[in] pI2Cx I2C peripheral base address
 */
static void I2C_Generate_Start_Condition(typedef_I2C_t* pI2Cx);

/**
 * @brief Generate the I2C stop condition
 * @param[in] pI2Cx I2C peripheral base address
 */
static void I2C_Generate_Stop_Condition(typedef_I2C_t* pI2Cx);

/**
 * @brief Get I2C flag status from the Status Registers
 * @param[in] pI2Cx I2C peripheral base address
 * @param[in] flag I2C flag from SR1 & SR2
 */
static uint8_t I2C_Get_Flag_Status(typedef_I2C_t* pI2Cx, I2C_STATUS_FLAGS flag);

/**
 * @brief Get the value for the TRISE register
 * @param[in] speed I2C SCL frequency
 */
static uint8_t I2C_TRISE_Max(uint32_t speed);

/**
 * @brief Set the clock control register bits
 * @param[in] apb_freq APB1 Clock frequency
 * @param[in] speed Target SCL frequency
 * @param[in] dc Duty-cycle for Fast mode
 */
static uint16_t I2C_CCR(uint8_t apb_freq, uint32_t speed, I2C_FM_DC dc);

void I2C_PeriClockControl(typedef_I2C_t* pI2Cx, uint8_t status)
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

SYSTEM_CLOCK_SWITCH RCC_get_systemclock_switch()
{
    return (RCC->CFGR >> RCC_CFGR_SWS) & 0b11;
}

uint32_t RCC_get_systemclock_freq()
{
    uint32_t freq;
    SYSTEM_CLOCK_SWITCH clock_source = RCC_get_systemclock_switch();

    switch (clock_source)
    {
        case SYSTEM_CLOCK_SWITCH_HSE:
            freq = HSE_FREQ;
            break;
        case SYSTEM_CLOCK_SWITCH_HSI:
            freq = HSI_FREQ;
            break;
        case SYSTEM_CLOCK_SWITCH_PLL:
            // TODO: IMPLEMENT get_pll_freq
            freq = -1;
            break;
    }

    return freq;
}

uint32_t RCC_get_ahb_freq()
{
    uint32_t freq;
    uint32_t systemclock_freq = RCC_get_systemclock_freq();

    uint8_t ahb1_prescaler_bits = (RCC->CFGR >> RCC_CFGR_HPRE) & 0b111;
    uint8_t ahb1_prescaler_enable = RCC->CFGR >> (RCC_CFGR_HPRE+3) & 0b1;

    if (ahb1_prescaler_enable)
    {
        uint16_t prescaler = RCC_AHB_PRESCALER_DIV[ahb1_prescaler_bits];
        freq = systemclock_freq / prescaler;
    }
    else
    {
        freq = systemclock_freq;
    }

    return freq;
}

uint32_t RCC_get_apb1_freq()
{
    uint32_t freq;
    uint32_t ahb_freq = RCC_get_ahb_freq();

    uint8_t apb1_prescaler_bits = (RCC->CFGR >> RCC_CFGR_PPRE1) & 0b011;
    uint8_t apb1_prescaler_enable = RCC->CFGR >> (RCC_CFGR_PPRE1+2) & 0b1;

    if (apb1_prescaler_enable)
    {
        uint8_t prescaler = RCC_APB_PRESCALER_DIV[apb1_prescaler_bits];
        freq = ahb_freq / prescaler;
    }
    else
    {
        freq = ahb_freq;
    }

    return freq;
}


void I2C_Init(I2C_Handle_t* pI2CHandle)
{
    I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

    // Get the APB1 clock frequency
    uint8_t freq = RCC_get_apb1_freq() / 1000000;

    // Assert invalid values
    assert(freq >= 2 /* MHz */); // APB1 freq must be >=2 MHz
    assert(freq <= 50 /* MHz */); // APB1 freq must be <=50 MHz

    // Speed > 100 kbps require duty-cycle = 16/9
    if (pI2CHandle->config.speed > I2C_SPEED_SM)
    {
        assert(pI2CHandle->config.FM_DutyCycle == I2C_DC_16_9);
    }

    // 10-bit addressing and dual addressing must not be enabled simultaneously
    assert(!(pI2CHandle->config.enable_10_bit_address && pI2CHandle->config.enable_dual_address));

    // Write the APB1 clock frequency
    pI2CHandle->pI2Cx->CR2 &= ~(0b111111 << I2C_CR2_FREQ);
    pI2CHandle->pI2Cx->CR2 |= freq << I2C_CR2_FREQ;

    // Enable the ACK control
    pI2CHandle->pI2Cx->CR1 |= pI2CHandle->config.ACK_Control << I2C_CR1_ACK;

    // Enable the 16/9 duty-cycle for speeds greater than 100 kbps
    if (pI2CHandle->config.speed <= I2C_SPEED_SM)
    {
        pI2CHandle->pI2Cx->CCR &= ~(1 << I2C_CCR_DUTY);
    }
    else 
    {
        pI2CHandle->pI2Cx->CCR |= 1 << I2C_CCR_DUTY;
    }

    // Write the clock control register
    pI2CHandle->pI2Cx->CCR |= I2C_CCR(
        freq,
        pI2CHandle->config.speed,
        pI2CHandle->config.FM_DutyCycle
    );

    // Set the device address
    // 0 -> Master, else -> slave
    if (pI2CHandle->config.enable_10_bit_address)
    {
        pI2CHandle->pI2Cx->OAR1 |= 1 << I2C_OAR1_ADDMODE;
        pI2CHandle->pI2Cx->OAR1 |= (pI2CHandle->config.address & 0x3FF) << I2C_OAR1_ADD0;
    }
    else
    {
        pI2CHandle->pI2Cx->OAR1 &= ~(1 << I2C_OAR1_ADDMODE);
        pI2CHandle->pI2Cx->OAR1 |= (pI2CHandle->config.address & 0x7F) << I2C_OAR1_ADD71;
    }
    pI2CHandle->pI2Cx->OAR1 |= 1 << I2C_OAR1_KEEP1;

    // Enable dual address
    if (pI2CHandle->config.enable_dual_address)
    {
        pI2CHandle->pI2Cx->OAR2 |= 1 << I2C_OAR2_ENDUAL;
        pI2CHandle->pI2Cx->OAR2 |= (pI2CHandle->config.address2 & 0x7F) << I2C_OAR2_ENDUAL;
    }
    else
    {
        pI2CHandle->pI2Cx->OAR2 &= ~(1 << I2C_OAR2_ENDUAL);
        pI2CHandle->pI2Cx->OAR2 &= ~(0x7F << I2C_OAR2_ENDUAL);
    }

    pI2CHandle->pI2Cx->TRISE &= ~(0b111111);
    pI2CHandle->pI2Cx->TRISE |= I2C_TRISE_Max(pI2CHandle->config.speed);

}

static uint16_t I2C_CCR(uint8_t apb_freq, uint32_t scl_freq, I2C_FM_DC dc)
{
    uint32_t scl_period; // Desired SCL period
    uint32_t CCR; // APB-to-SCL ratio
    // MHz (1e6) (Frequency) to nanoseconds (1e-9) (Period) 
    uint32_t apb_period = 1000U/apb_freq;
     if (scl_freq <= I2C_SPEED_SM)
    {
        // Standard mode
        // Hz (frequency) to nanoseconds (1e-9) (period)
        scl_period  = 1000000000U/scl_freq;
        CCR = (scl_period/2)/apb_period;
    }
    else 
    {
        // Fast mode
        uint8_t duty_h, duty_l;
        scl_period = 1000000000U/scl_freq;

        if (dc == I2C_DC_2)
        {
            duty_l = 2;
            duty_h = 1;
        }
        else
        {
            duty_l = 16;
            duty_h = 9;
        }

        CCR = scl_freq / (duty_l + duty_h) / apb_period;
    }

    return CCR & 0x7FF;

}

void I2C_Deinit(I2C_Handle_t* pI2CHandle)
{
    if (pI2CHandle == I2C1)
    {
        I2C1_REG_RESET();
    }
    else if (pI2CHandle == I2C2)
    {
        I2C2_REG_RESET();
    }
    else if (pI2CHandle == I2C3)
    {
        I2C3_REG_RESET();
    }
}


void I2C_IRQ_InterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (IRQNumber < 32)
			*NVIC_ISER0 |= (1 << IRQNumber);
		else if (IRQNumber >= 32 && IRQNumber < 64)
			*NVIC_ISER1 |= (1 << IRQNumber) % 32;
		else if (IRQNumber >= 64 && IRQNumber < 96)
			*NVIC_ISER2 |= (1 << IRQNumber) % 64;
	}
	else
	{
		if (IRQNumber < 32)
			*NVIC_ICER0 |= (1 << IRQNumber);
		else if (IRQNumber >= 32 && IRQNumber < 64)
			*NVIC_ICER1 |= (1 << IRQNumber) % 32;
		else if (IRQNumber >= 64 && IRQNumber < 96)
			*NVIC_ICER2 |= (1 << IRQNumber) % 64;
	}
}

void I2C_IRQ_PriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_Section = IRQNumber % 4;
	uint8_t ShiftAmmount = 8 * iprx_Section + 8 - CORTEX_NO_PR_BITS;
	*(NVIC_IPR + iprx) |= IRQPriority << ShiftAmmount;
}

void I2C_Peripheral_Control(I2C_Handle_t* pI2CHandle, uint8_t EnOrDi)
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

void I2C_Master_Send(I2C_Handle_t* pI2CHandle, uint16_t slave_address, uint8_t* buffer, uint16_t length)
{
    // Generate Start Conditon
    I2C_Generate_Start_Condition(pI2CHandle->pI2Cx);

    // Wait until the Start condition bit is set
    while (!I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_SB));

    // Write the destination address + r/nw bit
    pI2CHandle->pI2Cx->DR = (slave_address << 1) & ~(1) ;

    // Wait until the address is acknowledged
    while (!I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_ADDR));
    uint32_t dummy = pI2CHandle->pI2Cx->SR2; // Read SR2 to clear ADDR

    while (length > 0)
    {   
        // Wait for the Tx buffer to empty
        while (!I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_TXE));

        // Send data
        pI2CHandle->pI2Cx->DR = *(buffer++);
        length--;
    }
    
    while (!I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_TXE));
    while (!I2C_Get_Flag_Status(pI2CHandle->pI2Cx, I2C_FLAG_BTF));

    I2C_Generate_Stop_Condition(pI2CHandle->pI2Cx);
}

static void I2C_Generate_Start_Condition(typedef_I2C_t* pI2Cx)
{
    pI2Cx->CR1 |= 1 << I2C_CR1_START;
}

static void I2C_Generate_Stop_Condition(typedef_I2C_t* pI2Cx)
{
    pI2Cx->CR1 |= 1 << I2C_CR1_STOP;
}

static uint8_t I2C_Get_Flag_Status(typedef_I2C_t* pI2Cx, I2C_STATUS_FLAGS flag)
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
    }

    return status;
}

static uint8_t I2C_TRISE_Max(uint32_t speed)
{
    const uint32_t apb_freq = RCC_get_apb1_freq();
    const uint32_t apb_period = NANOSECONDS/apb_freq; // apb freq in nanoseconds

    // Max SCL rise time for SM or FM, respectively (in nanoseconds)
    const uint16_t max_Trise = (speed <= I2C_SPEED_SM) ? I2C_MAX_TRISE_SM : I2C_MAX_TRISE_FM; 

    // Compute the TRISE bits using the formula
    uint8_t TRISE = max_Trise / apb_period;

    // Return 5 bits of TRISE+1 (required by the reference manual)
    return (TRISE + 1) & 0x1F;
}