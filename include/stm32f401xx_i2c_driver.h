

#ifndef __STM32F401XX_I2C__
#define __STM32F401XX_I2C__

#include "STM32F401RE.h"
#include "stdbool.h"

#define HSI_FREQ 8000000 //!< Internal clock frequency (Hz)
#define HSE_FREQ 16000000 //!< External clock frequency (Hz)

typedef enum
{
    SYSTEM_CLOCK_SWITCH_HSI = 0,
    SYSTEM_CLOCK_SWITCH_HSE,
    SYSTEM_CLOCK_SWITCH_PLL
} SYSTEM_CLOCK_SWITCH;

/**
 * @brief I2C Serial Clock Speed values
 */
typedef enum 
{
    I2C_SPEED_SM = 100000, //!< I2C Standard Mode
    I2C_SPEED_FM = 400000 //!< I2C Fast Mode
} I2C_SPEED;

/**
 * @brief Acknowledge control
 */
typedef enum 
{
    I2C_ACK_DEFAULT = false,
    I2C_ACK_ENABLE = false,
    I2C_ACK_DISABLE = true
} I2C_ACK_CTRL;

/**
 * @brief FM Duty Cycle
 */
typedef enum 
{
    I2C_DC_2 = 0,
    I2C_DC_16_9 = 1
} I2C_FM_DC;

/**
 * @brief Configuration structure for I2C peripheral
 */
typedef struct 
{

    I2C_SPEED speed;      //!< Serial Clock Speed
    uint16_t address;   //!< Device address (7-bit)
    I2C_ACK_CTRL ACK_Control; //!< Acknowledge control
    I2C_FM_DC FM_DutyCycle;   //!< FM Duty Cycle
    bool enable_10_bit_address; // enable 10-bit address
    bool enable_dual_address; // enable dual address
    uint8_t address2; // Dual address
} I2C_Config_t;

/**
 * @brief Structure for I2C peripheral
 */
typedef struct 
{
    typedef_I2C_t *pI2Cx; //!< I2C peripheral register structure
    I2C_Config_t config; //!< I2C peripheral configuration
} I2C_Handle_t;

/**
 * @brief Enable or Disable the I2C perihperal clock
 * @param[in] pI2Cx I2C peripheral base address
 * @param[in] EnorDi Enable or Disable
 * @note This function should be called before doing any 
 *       other operation in the I2C peripheral.
 */
void I2C_PeriClockControl(typedef_I2C_t* pI2Cx, uint8_t EnorDi);

/**
 * @brief Disable a I2C peripheral
 * @param[in] pI2CHandle Pointer to I2C handle pointer
 */
void I2C_Deinit(I2C_Handle_t* pI2CHandle);

/**
 * @brief Enable a I2C peripheral
 * @param[in] pI2CHandle Pointer to I2C handle pointer
 */
void I2C_Init(I2C_Handle_t* pI2CHandle);

/**
 * @brief Configure I2C interrupts
 * @param[in] IRQNumber IRQ Number from the NVIC
 * @param[in] EnorDi Enable or disable interrupt
 */
void I2C_IRQ_InterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);

/**
 * @brief Configure I2C IRQ priority config
 * @param[in] IRQNumber IRQ number
 * @param[in] IRQPriority Interrupt priority
 */
void I2C_IRQ_PriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

/**
 * @brief Enable I2C peripheral clock
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] EnOrDi Enable/Disable
 */
void I2C_Peripheral_Control(I2C_Handle_t* pI2CHandle, uint8_t EnOrDi);

/**
 * @brief Send I2C data as the master device
 * @note The I2C peripheral must be enabled using `I2C_Init`
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] slave_address Slave address (7-bit or 10-bit)
 * @param[in] buffer Pointer to TX data buffer
 * @param[in] length Number of bytes of the TX data buffer
 */
void I2C_Master_Send(I2C_Handle_t* pI2CHandle, uint16_t slave_address, uint8_t* buffer, uint16_t length);

SYSTEM_CLOCK_SWITCH RCC_get_systemclock_switch();
uint32_t RCC_get_systemclock_freq();
uint32_t RCC_get_ahb_freq();
uint32_t RCC_get_apb1_freq();

#endif // __STM32F401XX_I2C__