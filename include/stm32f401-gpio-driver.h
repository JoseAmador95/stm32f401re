#ifndef __STM32F401RE_GPIO_DRIVER_H_
#define __STM32F401RE_GPIO_DRIVER_H_

#include "STM32F401RE.h"

/**
 * @typedef @struct GPIO_PinConfig_t
 * @brief This struct template contains the attributes of the GPIO.
 * @details The structure contains the pin number, pin mode (Input, 
 * 			Output, Alt), speed, Pull Up/Down configuration, output 
 * 			pin mode, and alternative funtion mode.
 */
typedef struct
{
	uint32_t GPIO_PinNumber;
	uint32_t GPIO_PinMode;		  /*!< Possible Values from @GPIO_PIN_MODES >*/
	uint32_t GPIO_PinSpeed;		  /*!< Possible Values from @GPIO_SPEED_MODES >*/
	uint32_t GPIO_pinPuPdControl; /*!< Possible Values from @GPIO_PUPD_MODES >*/
	uint32_t GPIO_PinOPType;	  /*!< Possible Values from @GPIO_OP_MODES >*/
	uint32_t GPIO_PinAltFunMode;
} GPIO_PinConfig_t;

/**
 * @typedef GPIO_Handle_t
 * @brief 	This structure serves as a handle with all the configurations for 
 * 			particular pin.
 * @details The handle serves as an "object" with the attributes of a GPIO.
 * 
 * 
 */
typedef struct
{
	typedef_GPIO_t *pGPIOx; // Holds the base address of the GPIO port
	GPIO_PinConfig_t GPIO_PinConfig;
} GPIO_Handle_t;

/**
 * @GPIO_PIN_NUMBERS
 * GPIO Pin Numbers
 */
#define GPIO_PIN_0 0 	/*!< GPIO 0 of any port */
#define GPIO_PIN_1 1 	/*!< GPIO 1 of any port */
#define GPIO_PIN_2 2	/*!< GPIO 2 of any port */
#define GPIO_PIN_3 3	/*!< GPIO 3 of any port */
#define GPIO_PIN_4 4	/*!< GPIO 4 of any port */
#define GPIO_PIN_5 5	/*!< GPIO 5 of any port */
#define GPIO_PIN_6 6	/*!< GPIO 6 of any port */
#define GPIO_PIN_7 7	/*!< GPIO 7 of any port */
#define GPIO_PIN_8 8	/*!< GPIO 8 of any port */
#define GPIO_PIN_9 9	/*!< GPIO 9 of any port */
#define GPIO_PIN_10 10	/*!< GPIO 10 of any port */
#define GPIO_PIN_11 11	/*!< GPIO 11 of any port */
#define GPIO_PIN_12 12	/*!< GPIO 12 of any port */
#define GPIO_PIN_13 13	/*!< GPIO 13 of any port */
#define GPIO_PIN_14 14	/*!< GPIO 14 of any port */
#define GPIO_PIN_15 15	/*!< GPIO 15 of any port */

/**
 * @GPIO_PIN_MODES
 * GPIO Pin possible modes
 */
#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODE_IT_FT 4
#define GPIO_MODE_IT_RT 5
#define GPIO_MODE_IT_RFT 6

/**
 * @GPIO_OP_MODES
 * GPIO Pin possible output modes
 */
#define GPIO_OP_TYPE_PP 0
#define GPIO_OP_TYPE_OD 1

/**
 * @GPIO_SPEED_MODES
 * GPIO Pin possible Speeds
 */
#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_HIGH 2
#define GPIO_SPEED_VERYHIGH 3

/**
 * @GPIO_PUPD_MODES
 * GPIO Pin possible Pull Up/Pull Down modes
 */
#define GPIO_PUPD_NO 0
#define GPIO_PUPD_PU 1
#define GPIO_PUPD_PD 2

/**
 * @fn			GPIO_Init
 * @brief		Enables GPIO Port
 * @param[in]	GPIO_Handle_t GPIO port Handler
 * @return		None
 * @note		None
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

/**
 * @fn			GPIO_Deinit
 * @brief		Disables GPIO Port
 * @param[in]	typedef_GPIO_t GPIO Port Base Address
 * @return		None
 * @note		None
 */
void GPIO_Deninit(typedef_GPIO_t *pGPIOx);

/**
 * @fn			GPIO_PeriClockControl
 * @brief		Enables or disables peripheral clock for the given GPIO port
 * @param[in]	typedef_GPIO_t GPIO port base address 
 * @param[in]	uint32_t ENALBE or DISABLE macro
 * @return		None
 * @note		None
 */
void GPIO_PeriClockControl(typedef_GPIO_t *pGPIOx, uint32_t status);

/**
 * @fn			GPIO_ReadFromInputPin
 * @brief		Reads the current state of the given pin in GPIO port
 * @param[in]	typedef_GPIO_t GPIO port base address
 * @param[in]	uint8_t Pin Number in GPIO Port
 * @return		Digital pin measurement. 0 or 1.
 * @note		None
 */
uint8_t GPIO_ReadFromInputPin(typedef_GPIO_t *pGPIOHandle, uint8_t PinNumber);

/**
 * @fn			GPIO_ReadFromInputPort
 * @brief		Reads the entire port status for the given GPIO port
 * @param[in]	typedef_GPIO_t GPIO port base address
 * @return		16 bit integer. Each byte corresponds to a bit.
 * @note		None
 */
uint16_t GPIO_ReadFromInputPort(typedef_GPIO_t *pGPIOHandle);

/**
 * @fn			GPIO_WriteToOutputPin
 * @brief		Writes a given value to a given pin in GPIO port
 * @param[in]	typedef_GPIO_t GPIO port base addres
 * @param[in]	uint8_t Pin Number in GPIO port
 * @param[in]	uint8_t Pin state to write
 * @return		None
 * @note		None
 */
void GPIO_WriteToOutputPin(typedef_GPIO_t *pGPIOHandle, uint8_t PinNumber, uint8_t Value);

/**
 * @fn			GPIO_WriteToOutputPort
 * @brief		Writes a given value to the entire given GPIO port
 * @param[in]	typedef_GPIO_t GPIO port base address
 * @param[in]	uint16_t Port value to write
 * @return		None
 * @note		None
 */
void GPIO_WriteToOutputPort(typedef_GPIO_t *pGPIOHandle, uint16_t Value);

/**
 * @fn			GPIO_ToggleOutputPin
 * @brief		Toggles a given pin in GPIO port
 * @param[in]	typedef_GPIO_t GPIO port base address
 * @param[in]	uint8_t Pin Number to Toggle
 * @return		None
 * @note		None
 */
void GPIO_ToggleOutputPin(typedef_GPIO_t *pGPIOHandle, uint8_t PinNumber);

/**
 * @fn			GPIO_IRQ_InterruptConfig
 * @brief		Enables/Disables the given IRQ Number
 * @param[in]	uint8_t GPIO port base address
 * @param[in]	uint8_t IRQ status to write
 * @return		None
 * @note		None
 */
void GPIO_IRQ_InterruptConfig(uint8_t IRQNumber, uint8_t Status);

/**
 * @fn			GPIO_IRQ_PriorityConfig
 * @brief		Sets a priority to given IRQ Number
 * @param[in]	uint8_t IRQ Number. See @NVIC_CORTEX
 * @param[in]	uint8_t IRQ Priority (0 - 15)
 * @return		None
 * @note		None
 */
void GPIO_IRQ_PriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);

/**
 * @fn			GPIO_IRQ_Handling
 * @brief		Handles GPIO IRQ Interrupts
 * @param[in]	uint8_t IRQ Pin Number
 * @return		None
 * @note		None
 */
void GPIO_IRQ_Handling(uint8_t PinNumber);

/*
 * GPIO HAL
*/
GPIO_Handle_t GPIO_Setup(uint8_t pinNumber, typedef_GPIO_t* port, uint8_t mode, uint8_t speed, uint8_t PuPd, uint8_t type);
uint8_t GPIO_Read(GPIO_Handle_t* gpio);
void GPIO_Write(GPIO_Handle_t* gpio, uint8_t value);
void GPIO_Toggle(GPIO_Handle_t* gpio);

#endif
