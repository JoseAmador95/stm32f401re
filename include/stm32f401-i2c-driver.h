#ifndef __STM32F401XX_I2C__
#define __STM32F401XX_I2C__

#include "stm32f401re.h"
#include "stdbool.h"

typedef enum
{
    READ = 0,
    WRITE = 1
} RW;

#define I2C_FREQ_SM 100000
#define I2C_FREQ_FM 400000

#define I2C_ACK_ENABLE 1
#define I2C_ACK_DISABLE 0
#define I2C_ACK_DEFAULT I2C_ACK_ENABLE

typedef enum I2C_IRQ
{
    I2C_IRQ_I2C1_EV = IRQ_NO_I2C1_EV,
    I2C_IRQ_I2C1_ER = IRQ_NO_I2C1_ER,
    I2C_IRQ_I2C2_EV = IRQ_NO_I2C2_EV,
    I2C_IRQ_I2C2_ER = IRQ_NO_I2C2_ER,
    I2C_IRQ_I2C3_EV = IRQ_NO_I2C3_EV,
    I2C_IRQ_I2C3_ER = IRQ_NO_I2C3_ER
} I2C_IRQ;

typedef enum I2C_APP
{
    I2C_APP_EV_TX_COMPLETE,
    I2C_APP_EV_RX_COMPLETE,
    I2C_APP_EV_STOP,
    I2C_APP_ERROR_BERR,
    I2C_APP_ERROR_ARLO,
    I2C_APP_ERROR_AF,
    I2C_APP_ERROR_OVR,
    I2C_APP_ERROR_PECERR,
    I2C_APP_ERROR_TIMEOUT,
    I2C_APP_ERROR_SMBALERT
} I2C_APP;

typedef enum I2C_ROLE
{
    I2C_ROLE_MASTER,
    I2C_ROLE_SLAVE
} I2C_ROLE;

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

    uint32_t scl_freq;          //!< Serial Clock Speed
    uint16_t address;           //!< Device address (7-bit)
    uint8_t ack_enable;         //!< Acknowledge control
    I2C_FM_DC FM_DutyCycle;     //!< FM Duty Cycle
    bool enable_10_bit_address; // enable 10-bit address
    bool enable_dual_address;   // enable dual address
    uint8_t address2;           // Dual address
} I2C_Config_t;

typedef enum I2C_STATUS
{
    I2C_STATUS_READY,
    I2C_STATUS_BUSY_TX,
    I2C_STATUS_BUSY_RX
} I2C_STATUS;

/**
 * @brief Structure for I2C peripheral
 */
typedef struct
{
    typedef_I2C_t *pI2Cx;   //!< I2C peripheral register structure
    I2C_Config_t config;    //!< I2C peripheral configuration
    uint8_t *buffer_tx;     //!< I2C TX buffer
    uint8_t *buffer_rx;     //!< I2C RX buffer
    uint32_t length_tx;     //!< Size of the I2C TX buffer
    uint32_t length_rx;     //!< Size of the I2C RX buffer
    I2C_STATUS i2c_status;  //!< Communication state
    uint8_t device_address; //!< Slave/device address
    uint32_t size_rx;       //!< RX size
    uint8_t release_bus;    //!< Repeated start value
} I2C_Handle_t;

/**
 * @brief Enable or Disable the I2C perihperal clock
 * @param[in] pI2Cx I2C peripheral base address
 * @param[in] EnorDi Enable or Disable
 * @note This function should be called before doing any 
 *       other operation in the I2C peripheral.
 */
void I2C_PeriClockControl(typedef_I2C_t *pI2Cx, uint8_t EnorDi);

/**
 * @brief Disable a I2C peripheral
 * @param[in] pI2CHandle Pointer to I2C handle pointer
 */
void I2C_Deinit(I2C_Handle_t *pI2CHandle);

/**
 * @brief Enable a I2C peripheral
 * @param[in] pI2CHandle Pointer to I2C handle pointer
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);

/**
 * @brief Configure I2C interrupts
 * @param[in] IRQNumber IRQ Number from the NVIC
 * @param[in] EnorDi Enable or disable interrupt
 */
void I2C_IRQ_Interrupt_Config(I2C_IRQ irq_number, uint8_t status);

/**
 * @brief Configure I2C IRQ priority config
 * @param[in] IRQNumber IRQ number
 * @param[in] IRQPriority Interrupt priority
 */
void I2C_IRQ_Priority_Config(I2C_IRQ irq_number, uint32_t priority);

/**
 * @brief Enable I2C peripheral clock
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] EnOrDi Enable/Disable
 */
void I2C_Peripheral_Control(I2C_Handle_t *pI2CHandle, uint8_t EnOrDi);

/**
 * @brief Send I2C data as the master device 
 * @note The I2C peripheral must be enabled using `I2C_Init`
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] slave_address Slave address (7-bit or 10-bit)
 * @param[in] buffer Pointer to TX data buffer
 * @param[in] length Number of bytes of the TX data buffer
 */
uint8_t I2C_Master_Send(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                        uint8_t *buffer, uint16_t length, uint8_t release_bus);

/**
 * @brief Receive I2C data as the master 
 * @note The I2C peripheral must be enabled uisng `I2C_Init`
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] slave_address Slave address (7-bit or 10-bit)
 * @param[in] buffer Pointer to RX data buffer
 * @param[in] length Number of bytes of the RX data buffer
 * @details This function calls `I2C_Master_Receive_BLOCKING`
 *           or `I2C_Master_Receive_IT` depending on the 
 *          macro definition below.
 * 
 *          | Macro | Function | Default |
 *          | ----- | -------- | ------- |
 *          | I2C_API_BLOCKING | I2C_Master_Receive_BLOCKING | No |
 *          | I2C_API_IT | I2C_Master_Receive_IT | Yes |
 */
uint8_t I2C_Master_Receive(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                           uint8_t *buffer, uint16_t length,
                           uint8_t release_bus);

/**
 * @brief Send I2C data as the master device using the blocking API
 * @note The I2C peripheral must be enabled using `I2C_Init`
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] slave_address Slave address (7-bit or 10-bit)
 * @param[in] buffer Pointer to TX data buffer
 * @param[in] length Number of bytes of the TX data buffer
 * @details This function calls `I2C_Master_Receive_BLOCKING`
 *           or `I2C_Master_Receive_IT` depending on the 
 *          macro definition below.
 * 
 *          | Macro | Function | Default |
 *          | ----- | -------- | ------- |
 *          | I2C_API_BLOCKING | I2C_Master_Send_BLOCKING | No |
 *          | I2C_API_IT | I2C_Master_Send_IT | Yes |
 */
void I2C_Master_Send_BLOCK(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                           uint8_t *buffer, uint16_t length,
                           uint8_t release_bus);

/**
 * @brief Receive I2C data as the master device using the blocking API
 * @note The I2C peripheral must be enabled uisng `I2C_Init`
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] slave_address Slave address (7-bit or 10-bit)
 * @param[in] buffer Pointer to RX data buffer
 * @param[in] length Number of bytes of the RX data buffer
 */
void I2C_Master_Receive_BLOCK(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                              uint8_t *buffer, uint16_t length,
                              uint8_t release_bus);

/**
 * @brief Send I2C data as the master device using the interrupt-based API
 * @note The I2C peripheral must be enabled using `I2C_Init`
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] slave_address Slave address (7-bit or 10-bit)
 * @param[in] buffer Pointer to TX data buffer
 * @param[in] length Number of bytes of the TX data buffer
 */
uint8_t I2C_Master_Send_IT(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                           uint8_t *buffer, uint16_t length,
                           uint8_t release_bus);

/**
 * @brief Receive I2C data as the master device using the interrupt-based API
 * @note The I2C peripheral must be enabled uisng `I2C_Init`
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] slave_address Slave address (7-bit or 10-bit)
 * @param[in] buffer Pointer to RX data buffer
 * @param[in] length Number of bytes of the RX data buffer
 */
uint8_t I2C_Master_Receive_IT(I2C_Handle_t *pI2CHandle, uint16_t slave_address,
                              uint8_t *buffer, uint16_t length,
                              uint8_t release_bus);

// /**
//  * @brief Handles the I2C address phase
//  * @param[in] pI2CHandle Pointer to I2C handle
//  * @param[in] Set read/write command
//  * @detail Writes the slave address in the Data Register,
//  * including the command byte.
//  */
// void I2C_Address_Phase(typedef_I2C_t *pI2Cx, uint16_t slave_address, RW rw);

/**
 * @brief Enables or disables the ACK byte
 * @param[in] pI2Cx Pointer to I2C peripheral
 * @param[in] status Enable/Disable ack replies
 */
void I2C_ACK_Status(typedef_I2C_t *pI2Cx, uint8_t status);

/** 
 * @brief Handles all the I2C events
 * @param[in] pI2CHandle Pointer to I2C handle
 * @details This callback handles the I2C event (EV) and buffer (BUFF)
 *          events enabled by the ITBUFEN and ITEVEN in CR2
 */
void I2C_EV_Handler(I2C_Handle_t *pI2CHandle);

/**
 * @brief Handles all the I2C errors
 * @param[in] pI2CHandle Pointer to I2C handle
 * @details This callback handles the I2C errors (EV) enabled by the 
 *          ITERREN flag in CR2
 */
void I2C_ERR_Handler(I2C_Handle_t *pI2CHandle);

/**
 * @brief Close the I2C communication
 * @note This function is called by the `I2C_EV_Handler` function
 * @param[in] pI2CHandle Pointer to I2C handle
 * @param[in] stop_transfer Indicates if the I2C transfer should be stop
 *            (by generating a Stop Condition)
 */
void I2C_Close(I2C_Handle_t *pI2CHandle, uint8_t stop_transfer);

void I2C_Application_Event_Callback(I2C_Handle_t pI2CHandle, I2C_APP flag);

#endif // __STM32F401XX_I2C__
