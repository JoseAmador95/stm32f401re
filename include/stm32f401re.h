/**
 * @file 	STM32F401RE.h
 * @author 	Jose Augusto Amador Demeneghi
 * @brief 	This file contains the base definitions for the STM32F401RE
 * 			microcontroller.
 * @version 0.1
 * @date 	2021-07-24
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef __STM32F401RE_H_
#define __STM32F401RE_H_

#include <stddef.h>
#include <stdint.h>

#define __weak __attribute__((weak)) // Weak definition
typedef volatile uint32_t Register;  // Typedef for peripherial registers

/**
 * @defgroup	Memory_Map Memory Map
 * @brief		Memory map of the STM32F401RE
 * @details		This group contains all the items in the STM32F401RE memory map.
 * 				* Flash
 * 				* RAM
 * 				* Peripherals
 * 				* Buses
 * 				* Cortex-M4 specfic
 * @{
 */

/**
 * @defgroup 	FLASH FLASH
 * @brief		512kB Flash memory
 * @details		The Flash memory has the following main features:
 *				* Capacity up to 256 Kbytes for STM32F401xB/C and up to 512 KBytes
 for STM32F401xD/E *				* 128 bits wide data read
 *				* Byte, half-word, word and double word write
 *				* Sector and mass erase
 *				* Low-power modes (for details refer to the Power control (PWR)
 section of the
 * 				reference manual)
 *				* Memory organization
 * 					* A main memory block divided into 4 sectors of 16 KBytes, 1
 sector of
 * 					64 KBytes, 1 sector of 128 KBytes (`STM32F401xB/C`) or 3
 sectors of
 * 					128 Kbytes (STM32F401xD/E)
 * 					* System memory from which the device boots in System memory
 boot mode
 * 					* 512 OTP (one-time programmable) bytes for user data
 * 					* The OTP area contains 16 additional bytes used to lock the
 corresponding
 * 					OTP data block.
 * 					* Option bytes to configure read and write protection, BOR
 level, watchdog
 * 					software/hardware and reset when the device is in Standby or
 Stop mode.
 *
 * @{
 */

#define FLASH_BASEADDR 0x08000000U //!< Base addres of Flash memory
#define SYSTEM_MEMORY 0x1FFF0000U  //!< base address of the system memory

/**
 * @}
 * @defgroup	RAM RAM
 * @brief		96 kB SRAM
 * @details		STM32F401xB/C devices feature 64 Kbytes and STM32F401xD/E devices
 *feature 96 Kbytes of system SRAM. The embedded SRAM can be accessed as bytes,
 *half-words (16 bits) or full words (32 bits). Read and write operations are
 *performed at CPU speed with 0 wait state. The CPU can access the embedded SRAM
 *through the System Bus or through the I- Code/D-Code buses when boot from SRAM
 *is selected or when physical remap is selected. To get the max performance on
 *SRAM execution, physical remap should be selected (boot or software
 *selection).
 * @{
 */
#define SRAM1_BASEADDR 0x20000000U //!< Base address of Static RAM1
#define SRAM1 SRAM1_BASEADDR       //!< Base address of Static RAM 1

/**
 * @}
 * @defgroup	BUSES Buses
 * @brief		Peripherals under the APB & AHB buses
 * @details		The two AHB/APB bridges, APB1 and APB2, provide full synchronous
 *connections between the AHB and the two APB buses, allowing flexible selection
 *of the peripheral frequency. Refer to the device datasheets for more details
 *on APB1 and APB2 maximum frequencies, and to Table 1  for the address mapping
 *of AHB and APB peripherals. After each device reset, all peripheral clocks are
 *disabled (except for the SRAM and Flash memory interface). Before using a
 *peripheral you have to enable its clock in the `RCC_AHBxENR` or `RCC_APBxENR`
 *register.
 * @{
 */

#define PERIPH_BASEADDR 0x40000000U //!< Base address of all peripherals.
#define APB1PERIPH_BASEADDR PERIPH_BASEADDR //!< Base address of APB1
#define APB2PERIPH_BASEADDR 0x40010000U     //!< Base address of APB2
#define AHB1PERIPH_BASEADDR 0x40020000U     //!< Base address of AHB1
#define AHB2PERIPH_BASEADDR 0x50000000U     //!< Base address of AHB2

/**
 * @defgroup	APB1 Advanced Peripheral Bus 1
 * @brief		Peripherals in APB1
 * @{
 */
#define TIM2_BASEADDR                                                          \
    (APB1PERIPH_BASEADDR + 0x0000U) //!< Base address of Timer 2
#define TIM3_BASEADDR                                                          \
    (APB1PERIPH_BASEADDR + 0x0400U) //!< Base address of Timer 3
#define TIM4_BASEADDR                                                          \
    (APB1PERIPH_BASEADDR + 0x0800U) //!< Base address of Timer 4
#define TIM5_BASEADDR                                                          \
    (APB1PERIPH_BASEADDR + 0x0C00U) //!< Base address of Timer 5
#define RTC_BASEADDR (APB1PERIPH_BASEADDR + 0x2800U) //!< Base address of RTC
#define WWDG_BASEADDR                                                          \
    (APB1PERIPH_BASEADDR + 0x2C00U) //!< Base address of Window Watchdog
#define IWDG_BASEADDR                                                          \
    (APB1PERIPH_BASEADDR + 0x3000U) //!< Base address of Independent Watchdog
#define I2S2EXT_BASEADDR                                                       \
    (APB1PERIPH_BASEADDR + 0x3400U)                   //!< Base address of I2S 2
#define SPI2_BASEADDR (APB1PERIPH_BASEADDR + 0x3800U) //!< Base address of SPI 2
#define SPI3_BASEADDR (APB1PERIPH_BASEADDR + 0x3C00U) //!< Base address of SPI 3
#define I2S3EXT_BASEADDR                                                       \
    (APB1PERIPH_BASEADDR + 0x4000U) //!< Base address of I2S 3
#define USART2_BASEADDR                                                        \
    (APB1PERIPH_BASEADDR + 0x4400U) //!< Base address of USART 2
#define I2C1_BASEADDR (APB1PERIPH_BASEADDR + 0x5400U) //!< Base address of I2C 1
#define I2C2_BASEADDR (APB1PERIPH_BASEADDR + 0x5800U) //!< Base address of I2C 2
#define I2C3_BASEADDR (APB1PERIPH_BASEADDR + 0x5C00U) //!< Base address of I2C 3
#define PWR_BASEADDR                                                           \
    (APB1PERIPH_BASEADDR + 0x7000U) //!< Base address of Power Controller

/**
 * @}
 * @defgroup	APB2 Advanced Peripheral Bus 2
 * @brief		Peripherals in APB2
 * @{
 */
#define TIM1_BASEADDR                                                          \
    (APB2PERIPH_BASEADDR + 0x0000U) //!< Base address of Timer 1
#define TIM8_BASEADDR                                                          \
    (APB2PERIPH_BASEADDR + 0x0400U) //!< Base address of Timer 8
#define USART1_BASEADDR                                                        \
    (APB2PERIPH_BASEADDR + 0x1000U) //!< Base address of USART 1
#define USART6_BASEADDR                                                        \
    (APB2PERIPH_BASEADDR + 0x1400U) //!< Base address of USART 6
#define ADC1_BASEADDR (APB2PERIPH_BASEADDR + 0x2000U) //!< Base address of ADC 1
#define SDIO_BASEADDR (APB2PERIPH_BASEADDR + 0x2C00U) //!< Base address of SDIO
#define SPI1_BASEADDR (APB2PERIPH_BASEADDR + 0x3000U) //!< Base address of SPI 1
#define SPI4_BASEADDR (APB2PERIPH_BASEADDR + 0x3400U) //!< Base address of SPI 4
#define SYSCFG_BASEADDR                                                        \
    (APB2PERIPH_BASEADDR +                                                     \
     0x3800U) //!< Base address of System Configuration Controller
#define EXTI_BASEADDR                                                          \
    (APB2PERIPH_BASEADDR +                                                     \
     0x3C00U) //!< Base address of External Interrupt/Event Controller
#define TIM9_BASEADDR                                                          \
    (APB2PERIPH_BASEADDR + 0x4000U) //!< Base address of TImer 9
#define TIM10_BASEADDR                                                         \
    (APB2PERIPH_BASEADDR + 0x4400U) //!< Base address of Timer 10
#define TIM11_BASEADDR                                                         \
    (APB2PERIPH_BASEADDR + 0x4800U) //!< Base address of TImer 11

/**
 * @}
 * @defgroup	AHB1 Advanced High-Performance Bus 1
 * @brief		Peripherals in AHB1
 * @{
 */
#define GPIOA_BASEADDR                                                         \
    (AHB1PERIPH_BASEADDR + 0x0000U) //!< Base address of GPIOA
#define GPIOB_BASEADDR                                                         \
    (AHB1PERIPH_BASEADDR + 0x0400U) //!< Base address of GPIOB
#define GPIOC_BASEADDR                                                         \
    (AHB1PERIPH_BASEADDR + 0x0800U) //!< Base address of GPIOC
#define GPIOD_BASEADDR                                                         \
    (AHB1PERIPH_BASEADDR + 0x0C00U) //!< Base address of GPIOD
#define GPIOE_BASEADDR                                                         \
    (AHB1PERIPH_BASEADDR + 0x1000U) //!< Base address of GPIOE
#define GPIOH_BASEADDR                                                         \
    (AHB1PERIPH_BASEADDR + 0x1C00U) //!< Base address of GPIOH
#define CRC_BASEADDR                                                           \
    (AHB1PERIPH_BASEADDR + 0x3000U) //!< Base address of CRC Unit
#define RCC_BASEADDR                                                           \
    (AHB1PERIPH_BASEADDR + 0x3800U) //!< Base address of Reset and Clock Control
#define FIR_BASEADDR                                                           \
    (AHB1PERIPH_BASEADDR +                                                     \
     0x3C00U) //!< Base address of Flash Interface Register
#define DMA1_BASEADDR                                                          \
    (AHB1PERIPH_BASEADDR + 0x6000U) //!< Base address of Direct Memory Access 1
#define DMA2_BASEADDR                                                          \
    (AHB1PERIPH_BASEADDR + 0x6400U) //!< Base address of Direct Memory Access 2

/**
 * @}
 * @defgroup	AHB2 Advanced High-Performance Bus 2
 * @brief		Peripherals in AHB2
 * @{
 */
#define USBOTG_BASEADDR                                                        \
    (AHB2PERIPH_BASEADDR + 0x0000U) //!< Base addres of USB On The Go

/**
 * @}
 * @}
 * @}
 */

/***** Peripheral Register Definition Structures **************/

/**
 * @struct 	typedef_CRC_t
 * @brief 		Memory arrangement of the CRC peripheral
 * @details		The structure contains all the registers of the CRC peripheral.
 * @ingroup		CRC
 */
typedef struct
{
    Register DR;  //!< Data Register.
    Register IDR; //!< Independent data register.
    Register CR;  //!< Control register.
} typedef_CRC_t;

/**
 * @struct		typedef_PWR_t
 * @brief		Memory arrangement of the PWR peripheral
 * @details		The structure contains all the registers of the Power Controller
 * 				peripheral.
 * @ingroup		PWR
 */
typedef struct
{
    Register CR;  //!< Control Register.
    Register CSR; //!< Power Control/Status Register.
} typedef_PWR_t;

/**
 * @struct		typedef_RCC_t
 * @brief		Memory arrangemet of the RCC peripheral
 * @details		The structure contains the registers of the Reset and Clock
 * 				Control peripheral.
 * @ingroup		RCC
 * @note		The `rsvXX` elements of the structure are the reserved spaces
 * 				in the memory map.
 */
typedef struct
{
    Register CR;         //!< Clock control register.
    Register PLLCFGR;    //!< Configuration register
    Register CFGR;       //!< Clock configuration register
    Register CIR;        //!< Clock interrupt register
    Register AHB1RSTR;   //!< AHB1 peripheral reset register
    Register AHB2RSTR;   //!< AHB2 peripheral reset register
    Register rsv01;      //!< Reserved
    Register rsv02;      //!< Reserved
    Register APB1RSTR;   //!< APB1 peripheral reset register
    Register APB2RSTR;   //!< APB2 peripheral reset register
    Register rsv03;      //!< Reserved
    Register rsv04;      //!< Reserved
    Register AHB1ENR;    //!< AHB1 peripheral clock enable register
    Register AHB2ENR;    //!< AHB2 peripheral clock enable register
    Register rsv05;      //!< Reserverd
    Register rsv06;      //!< Reserverd
    Register APB1ENR;    //!< APB1 peripheral clock enable register
    Register APB2ENR;    //!< APB2 peripheral clock enable register
    Register rsv07;      //!< Reserved
    Register rsv08;      //!< Reserved
    Register AHB1LPENR;  //!< AHB1 Peripherial Clock Enabled in Low Power Mode
                         //!< Register
    Register AHB2LPENR;  //!< AHB2 Peripherial Clock Enabled in Low Power Mode
                         //!< Register
    Register rsv09;      //!< Reserved
    Register rsv10;      //!< Reserved
    Register APB1LPENR;  //!< APB1 Peripherial Clock Enabled in Low Power Mode
                         //!< Register
    Register APB2LPENR;  //!< APB2 Peripherial Clock Enabled in Low Power Mode
                         //!< Register
    Register rsv11;      //!< Reserved
    Register rsv12;      //!< Reserved
    Register BDCR;       //!< Backup Domain Control Register
    Register CSR;        //!< Clock & Control Status Register
    Register rsv13;      //!< Reserved
    Register rsv14;      //!< Reserved
    Register SSCGR;      //!< Spread Spectrum Clock Generation Register
    Register PLLI2SCFGR; //!< PLLI2S Configuration Register
    Register rsv15;      //!< Reserved
    Register DCKCFGR;    //!< Dedicated Clocks Configuration
} typedef_RCC_t;

/**
 * @struct 	typedef_SYSCFG_t
 * @brief		Memory arrangement of the SYSCFG peripheral
 * @details		The structure contains all the registers of the System
 * 				Configuration peripheral.
 * @ingroup		SYSCGF
 */
typedef struct
{
    Register MEMRMP;    //!< Memory Remap Register
    Register PMC;       //!< Peripheral Mode Configuration Register
    Register EXTICR[4]; //!< External Interrupt Configuration Register 4
    Register CMPCR;     //!< Compensation Cell Control Register
} typedef_SYSCFG_t;

/**
 * @struct		typedef_GPIO_t
 * @brief		Memory arrangement of the GPIO peripheral
 * @details 	The structure contains all the registers of the General
 * 				Purpose Input-Output peripheral.
 * @ingroup		GPIO
 */
typedef struct
{
    Register MODER;   //!< Port Mode Register
    Register OTYPER;  //!< Port Output Type Register
    Register OSPEEDR; //!< Port Output Speed Register
    Register PUPDR;   //!< Port Pull-Up/Pull-Down Register
    Register IDR;     //!< Port input Data Regster
    Register ODR;     //!< Port Output Data Register
    Register BSRR;    //!< Port Bit Set/Reset Register
    Register LCKR;    //!< Port Configuration Lock Register
    Register
        AFR[2]; //!< Alternate Function Register. indx 0 -> Low, indx 1 -> High
} typedef_GPIO_t;

/**
 * @struct		typedef_DMA_t
 * @brief		Memory arrangement of the DMA peripheral
 * @details		The structure contains all the registers of the Direct
 * 				Memory Access peripheral.
 * @ingroup		DMA
 */
typedef struct
{
    Register LISR;   //!< Low Interrupt Status Register
    Register HISR;   //!< High Interrupt Status Register
    Register LIFCR;  //!< Low Interrupt Flag Clear
    Register HIFCR;  //!< High Interrupt Flag Clear
    Register S0CR;   //!< Stream X Configuration Register
    Register SXNDTR; //!< Stream X Number of Data Register
    Register SXPAR;  //!< Stream X Peripheral Address Register
    Register SXM0AR; //!< Stream X Memory 0 Address Register
    Register SXM1AR; //!< Stream X Memory 1 Address Register
    Register SXFCR;  //!< Stream X FIFO Control Register
} typedef_DMA_t;

/**
 * @struct		typedef_EXTI_t
 * @brief		Memory arrangement of the EXTI peripheral
 * @details		The structure contains all the registers of the External
 * 				Interrupt/Event peripheral.
 * @ingroup		EXTI
 */
typedef struct
{
    Register IMR;   //!< Interrupt Mask Register
    Register EMR;   //!< Event Mask Register
    Register RTSR;  //!< Rising Trigger Selection Register
    Register FTSR;  //!< Falling Trigger Selection Register
    Register SWIER; //!< Software Interrupt Event Register
    Register PR;    //!< Pending Registers
} typedef_EXTI_t;

/**
 * @struct		typedef_ADC_t
 * @brief		Memory arrangement of the ADC peripheral
 * @details		The structure contains all the registers of the Analog
 * 				to Digital Converter peripheral.
 * @ingroup		ADC
 */
typedef struct
{
    Register SR;    //!< Status Register
    Register CR1;   //!< Control Register 1
    Register CR2;   //!< Control Register 2
    Register SMPR1; //!< Sample Time Register 1
    Register SMPR2; //!< Sample Time Register 2
    Register JOFR1; //!< Injected Channel Data Offset Register 1
    Register JOFR2; //!< Injected Channel Data Offset Register 2
    Register JOFR3; //!< Injected Channel Data Offset Register 3
    Register JOFR4; //!< Injected Channel Data Offset Register 4
    Register HTR;   //!< Watchdog Higher Threshold Register
    Register LTR;   //!< Watchdog Lower Threshold Register
    Register SQR1;  //!< Regular Sequence Register 1
    Register SQR2;  //!< Regular Sequence Register 2
    Register SQR3;  //!< Regular Sequence Register 3
    Register JSQR;  //!< Injected Sequence Register
    Register JDR1;  //!< Injected Data Register 1
    Register JDR2;  //!< Injected Data Register 2
    Register JDR3;  //!< Injected Data Register 3
    Register JDR4;  //!< Injected Data Register 4
    Register DR;    //!< Regular Data Register
    Register CCR;   //!< Common Control Register
} typedef_ADC_t;

/**
 * @struct		typedef_TIM_t
 * @brief		Memory arrangement of the TIM1 and TIM2-5 peripherals
 * @details		The structure contains all the registers of the Advanced
 * 				Control Timer (TIM1) and the Generl Purpose Timers (TIM2-5).
 * @ingroup		TIM
 * @note		The memory arrangement in this structure is compatible with
 * 				Timers 1 to 5.
 */
typedef struct
{
    Register CR1;   //!< Control Register 1
    Register CR2;   //!< Control Register 2
    Register SMCR;  //!< Slave Mode Control Register
    Register DIER;  //!< DMA/INterrupt Enable Register
    Register SR;    //!< Status Register
    Register EGR;   //!< Event Generation Register
    Register CCMR1; //!< Capture/Compare Mode Register 1
    Register CCMR2; //!< Capture/Compare Mode Register 2
    Register CCER;  //!< Capture/Compare Enable Register
    Register CNT;   //!< Counter Register
    Register PSC;   //!< Prescaler Register
    Register ARR;   //!< Auto-Reload
    Register RCR;   //!< Repetition Counter Register. Only Timer 1.
    Register CCR1;  //!< Capture/Compare Register 1
    Register CCR2;  //!< Capture/Compare Register 2
    Register CCR3;  //!< Capture/Compare Register 3
    Register CCR4;  //!< Capture/Compare Register 4
    Register BDTR;  //!< Break and Dead-Time Register. Only Timer 1.
    Register DCR;   //!< DMA Control Register
    Register DMAR;  //!< DMA Address for Full Transfer
    Register OR;    //!< Option Register. Only Timer 2 & 5.
} typedef_TIM_t;

/**
 * @struct		typedef_IWDG_t
 * @brief		Memory arrangement of the IWDG peripheral
 * @details		The structure contains all the registers of the Independent
 * 				Watchdog peripheral.
 * @ingroup		IWDG
 */
typedef struct
{
    Register KR;  //!< Key Register
    Register PR;  //!< Prescaler Register
    Register RLR; //!< Reload Register
    Register SR;  //!< Status Register
} typedef_IWDG_t;

/**
 * @struct		typedef_I2C_t
 * @brief 		Memory arrangement of the I2C peripherals
 * @details		The structure contains all the registers of the Inter-Integrated
 * 				Circuit peripheral.
 * @ingroup 	I2C
 */
typedef struct
{
    Register CR1;   //!< Control Register 1
    Register CR2;   //!< Control Register 2
    Register OAR1;  //!< Own Address Register 1
    Register OAR2;  //!< Own Address Register 2
    Register DR;    //!< Data Register
    Register SR1;   //!< Status Register 1
    Register SR2;   //!< Status Register 2
    Register CCR;   //!< Clock Control Register
    Register TRISE; //!< TRISE Register
    Register FLTR;  //!< FLTR Register
} typedef_I2C_t;

/**
 * @struct		typedef_USART_t
 * @brief		Memory arrangement of the USART peripherals
 * @details		The structure contains all the register of the Universal
 * 				Synchronous/Asynchronous Receiver Transmitter.
 * @ingroup		USART
 */
typedef struct
{
    Register SR;   //!< Status Register
    Register DR;   //!< Data Register
    Register BRR;  //!< Baudrate Register
    Register CR1;  //!< Control Register 1
    Register CR2;  //!< Control Register 2
    Register CR3;  //!< Control Register 3
    Register GTPR; //!< Guard Time Prescaler Register
} typedef_USART_t;

/**
 * @struct		typedef_SPI_t
 * @brief		Memory arrangement of the SPI peripherals
 * @details     The structure contains all the registers of the Serial
 *              Peripheral Interface.
 * @ingroup     SPI
 * @note        This arrangement is also used by the @I2S peripheral.
 *
 * @struct      typedef_I2S_t
 * @brief       Memory arrangement of the I2S peripheral
 * @details     The structure contains all the registers of the I2C
 *              Sound Bus.
 * @ingroup     I2S
 * @note        This arrangement is also used by the @SPI peripheral.
 */
typedef struct
{
    Register CR1;     //!< Control Register 1. Not in I2S.
    Register CR2;     //!< Control Register 2
    Register SR;      //!< Status Register
    Register DR;      //!< Data Register
    Register CRCPR;   //!< CRC Polynomial Register. Not in I2S.
    Register RXCRCR;  //!< RX CRC Register. Not in I2S.
    Register TXCRCR;  //!< TX CRC Register. Not in I2S.
    Register I2SCFGR; //!< I2S Configuration Register
    Register I2SPR;   //!< I2S Prescaler Register
} typedef_SPI_t, typedef_I2S_t;

/*************** Peripheral Typedef ***************************/

/**
 * @def         CRC
 * @brief       Registers of the CRC peripheral
 * @ingroup     CRC
 */
#define CRC ((typedef_CRC_t *)CRC_BASEADDR)

/**
 * @def         PWR
 * @brief       Registers of the PWR peripheral
 * @ingroup     PWR
 */
#define PWR ((typedef_PWR_t *)PWR_BASEADDR)

/**
 * @def         RCC
 * @brief       Registers of the RCC peripheral
 * @ingroup     RCC
 */
#define RCC ((typedef_RCC_t *)RCC_BASEADDR)

/**
 * @def         SYSCFG
 * @brief       Registers of the SYSCFG peripheral
 * @ingroup     SYSCFG
 */
#define SYSCFG ((typedef_SYSCFG_t *)SYSCFG_BASEADDR)

/**
 * @defgroup    GPIOx	GPIOx
 * @brief       Registers of the various GPIO peripherals
 * @ingroup     GPIO
 * @{
 */
#define GPIOA ((typedef_GPIO_t *)GPIOA_BASEADDR)
#define GPIOB ((typedef_GPIO_t *)GPIOB_BASEADDR)
#define GPIOC ((typedef_GPIO_t *)GPIOC_BASEADDR)
#define GPIOD ((typedef_GPIO_t *)GPIOD_BASEADDR)
#define GPIOE ((typedef_GPIO_t *)GPIOE_BASEADDR)
#define GPIOH ((typedef_GPIO_t *)GPIOH_BASEADDR)
/** @} */

/**
 * @defgroup	DMAx	DMAx
 * @brief		Registers of the DMA1 & DM2 peripherals
 * @ingroup		DMA
 * @{
 */
#define DMA1 ((typedef_DMA_t *)DMA1_BASEADDR)
#define DMA2 ((typedef_DMA_t *)DMA2_BASEADDR)
/** @} */

/**
 * @def			EXTI
 * @brief		Registers of the EXTI perihperal
 * @ingroup		EXTI
 */
#define EXTI ((typedef_EXTI_t *)EXTI_BASEADDR)

/**
 * @def			ADC1
 * @brief		Registers of the ADC1 peripheral
 * @ingroup		ADC
 */
#define ADC1 ((typedef_ADC_t *)ADC1_BASEADDR)

/**
 * @defgroup	TMRx TIMx
 * @brief		Registers of the TIM1 & TIM2-5 peripherals
 * @ingroup		TIM
 * @{
 */
#define TMR1 ((typedef_Timer_t *)TMR1_BASEADDR)
#define TMR2 ((typedef_Timer_t *)TMR2_BASEADDR)
#define TMR3 ((typedef_Timer_t *)TMR3_BASEADDR)
#define TMR4 ((typedef_Timer_t *)TMR4_BASEADDR)
#define TMR5 ((typedef_Timer_t *)TMR5_BASEADDR)
/** @} */

/**
 * @def			IWDG
 * @brief		Register of the IWDG peripheral
 * @ingroup		IWDG
 */
#define IWDG ((typedef_IDWG_t *)IWDG_BASEADDR)

/**
 * @defgroup	I2Cx	I2C 1-3
 * @brief		Registers of the I2C1, I2C2 and I2C3 peripherals
 * @ingroup		I2C
 * @{
 */
#define I2C1 ((typedef_I2C_t *)I2C1_BASEADDR)
#define I2C2 ((typedef_I2C_t *)I2C2_BASEADDR)
#define I2C3 ((typedef_I2C_t *)I2C3_BASEADDR)
/** @} */

/**
 * @defgroup	USARTx	USART 1, 2 & 6
 * @brief		Registers of the USART1, USART2 and USART6 peripherals
 * @ingroup		USART
 * @{
 */
#define USART1 ((typedef_USART_t *)USART1_BASEADDR)
#define USART2 ((typedef_USART_t *)USART2_BASEADDR)
#define USART6 ((typedef_USART_t *)USART6_BASEADDR)
/** @} */

/**
 * @defgroup	SPIx	SPI 1-4
 * @brief		Registers of the SP1 - SPI4 peripherals
 * @ingroup		SPI
 * @{
 */
#define SPI1 ((typedef_SPI_t *)SPI1_BASEADDR)
#define SPI2 ((typedef_SPI_t *)SPI2_BASEADDR)
#define SPI3 ((typedef_SPI_t *)SPI3_BASEADDR)
#define SPI4 ((typedef_SPI_t *)SPI4_BASEADDR)
/** @} */

/************************* Function Macros *********************/

/**** GPIO ****/
/**
 * @addtogroup GPIOx
 * @{
 * @name GPIO Peripheral Clock Enble Macros
 * @{
 * @brief Macros for enabling the peripheral clock of each GPIO port
 */
#define GPIOA_PCLK_EN()                                                        \
    (RCC->AHB1ENR |= (1 << 0)) //!< Enable the GPIOA Peripheral Clock
#define GPIOB_PCLK_EN()                                                        \
    (RCC->AHB1ENR |= (1 << 1)) //!< Enable the GPIOB Peripheral Clock
#define GPIOC_PCLK_EN()                                                        \
    (RCC->AHB1ENR |= (1 << 2)) //!< Enable the GPIOC Peripheral Clock
#define GPIOD_PCLK_EN()                                                        \
    (RCC->AHB1ENR |= (1 << 3)) //!< Enable the GPIOD Peripheral Clock
#define GPIOE_PCLK_EN()                                                        \
    (RCC->AHB1ENR |= (1 << 4)) //!< Enable the GPIOE Peripheral Clock
#define GPIOH_PCLK_EN()                                                        \
    (RCC->AHB1ENR |= (1 << 7)) //!< Enable the GPIOH Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		GPIOx
 * @{
 * @name 			GPIO Peripheral Clock Disable Macros
 * @{
 * @brief 			Macros for disabling the peripheral clock of each GPIO port
 */
#define GPIOA_PCLK_DI()                                                        \
    (RCC->AHB1ENR &= ~(1 << 0)) //!< Disable the GPIOA Peripheral Clock
#define GPIOB_PCLK_DI()                                                        \
    (RCC->AHB1ENR &= ~(1 << 1)) //!< Disable the GPIOB Peripheral Clock
#define GPIOC_PCLK_DI()                                                        \
    (RCC->AHB1ENR &= ~(1 << 2)) //!< Disable the GPIOC Peripheral Clock
#define GPIOD_PCLK_DI()                                                        \
    (RCC->AHB1ENR &= ~(1 << 3)) //!< Disable the GPIOD Peripheral Clock
#define GPIOE_PCLK_DI()                                                        \
    (RCC->AHB1ENR &= ~(1 << 4)) //!< Disable the GPIOE Peripheral Clock
#define GPIOH_PCLK_DI()                                                        \
    (RCC->AHB1ENR &= ~(1 << 7)) //!< Disable the GPIOH Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		I2Cx
 * @{
 * @name 			I2C Peripheral Clock Enable Macros
 * @{
 * @brief 			Macros for enabling the I2C peripheral clock
 */
#define I2C1_PCLK_EN()                                                         \
    (RCC->APB1ENR |= (1 << 21)) //!< Enable the I2C1 Peripheral Clock
#define I2C2_PCLK_EN()                                                         \
    (RCC->APB1ENR |= (1 << 22)) //!< Enable the I2C1 Peripheral Clock
#define I2C3_PCLK_EN()                                                         \
    (RCC->APB1ENR |= (1 << 23)) //!< Enable the I2C3 Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		I2Cx
 * @{
 * @name 			I2C Peripheral Clock Disable Macros
 * @{
 * @brief 			Macros for disabling the I2C peripheral clock
 */
#define I2C1_PCLK_DI()                                                         \
    (RCC->APB1ENR &= ~(1 << 21)) //!< Disable the I2C1 Peripheral Clock
#define I2C2_PCLK_DI()                                                         \
    (RCC->APB1ENR &= ~(1 << 22)) //!< Disable the I2C2 Peripheral Clock
#define I2C3_PCLK_DI()                                                         \
    (RCC->APB1ENR &= ~(1 << 23)) //!< Disable the I2C3 Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		SPIx
 * @{
 * @name 			SPI Peripheral Clock Enable Macros
 * @{
 * @brief 			Macros for enabling the SPI peripheral clock
 */
#define SPI1_PCLK_EN()                                                         \
    (RCC->APB2ENR |= (1 << 12)) //!< Enable the the SPI1 Peripheral Clock
#define SPI2_PCLK_EN()                                                         \
    (RCC->APB1ENR |= (1 << 14)) //!< Enable the the SPI2 Peripheral Clock
#define SPI3_PCLK_EN()                                                         \
    (RCC->APB1ENR |= (1 << 15)) //!< Enable the the SPI3 Peripheral Clock
#define SPI4_PCLK_EN()                                                         \
    (RCC->APB2ENR |= (1 << 13)) //!< Enable the the SPI4 Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		SPIx
 * @{
 * @name 			SPI Peripheral Clock Disable Macros
 * @{
 * @brief 			Macros for disabling the SPI peripheral clock
 */
#define SPI1_PCLK_DI()                                                         \
    (RCC->APB2ENR &= ~(1 << 12)) //!< Disable the SPI1 Peripheral Clock
#define SPI2_PCLK_DI()                                                         \
    (RCC->APB1ENR &= ~(1 << 14)) //!< Disable the SPI2 Peripheral Clock
#define SPI3_PCLK_DI()                                                         \
    (RCC->APB1ENR &= ~(1 << 15)) //!< Disable the SPI3 Peripheral Clock
#define SPI4_PCLK_DI()                                                         \
    (RCC->APB2ENR &= ~(1 << 13)) //!< Disable the SPI4 Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		SYSCGF
 * @{
 * @name 			SYSCFG Peripheral Clock Enble-Disable Macros
 * @{
 * @brief 			Macros for enabling and disabling the SYSCFG peripheral
 * clock
 */
/**** SYSCGF ****/
#define SYSCFG_PCLK_EN()                                                       \
    (RCC->APB2ENR |= (1 << 14)) //!< Enable the SYSCFG Peripheral Clock
#define SYSCFG_PCLK_DI()                                                       \
    (RCC->APB2ENR &= ~(1 << 14)) //!< Disable the SYSCFG Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		USARTx
 * @{
 * @name 			USART Peripheral Clock Enable Macros
 * @{
 * @brief 			Macros for enabling the USART peripheral clock
 */
#define USART1_PCLK_EN()                                                       \
    (RCC->APB2ENR |= (1 << 4)) //!< Enable the USART1 Peripheral Clock
#define USART2_PCLK_EN()                                                       \
    (RCC->APB1ENR |= (1 << 17)) //!< Enable the USART2 Peripheral Clock
#define USART6_PCLK_EN()                                                       \
    (RCC->APB2ENR |= (1 << 5)) //!< Enable the USART6 Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup 		USARTx
 * @{
 * @name 			USART Peripheral Clock Disable Macros
 * @{
 * @brief 			Macros for disabling the USART peripheral clock
 */
#define USART1_PCLK_DI()                                                       \
    (RCC->APB2ENR &= ~(1 << 4)) //!< Disable the USART1 Peripheral Clock
#define USART2_PCLK_DI()                                                       \
    (RCC->APB1ENR &= ~(1 << 17)) //!< Disable the USART2 Peripheral Clock
#define USART6_PCLK_DI()                                                       \
    (RCC->APB2ENR &= ~(1 << 5)) //!< Disable the USART6 Peripheral Clock
/**
 * @}
 * @}
 */

/**
 * @addtogroup		GPIOx
 * @{
 * @name			GPIO Peripheral Reset Macros
 * @{
 * @brief 			Sets and Resets RCC AHB1 Reset Register
 */
//! Reset GPIOA
#define GPIOA_REG_RESET()                                                      \
    do                                                                         \
    {                                                                          \
        RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOARST);                         \
        RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOARST);                        \
    } while (0)

//! Reset GPIOB
#define GPIOB_REG_RESET()                                                      \
    do                                                                         \
    {                                                                          \
        RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOBRST);                         \
        RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOBRST);                        \
    } while (0)

//! Reset GPIOC
#define GPIOC_REG_RESET()                                                      \
    do                                                                         \
    {                                                                          \
        RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOCRST);                         \
        RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOCRST);                        \
    } while (0)

//! Reset GPIOD
#define GPIOD_REG_RESET()                                                      \
    do                                                                         \
    {                                                                          \
        RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIODRST);                         \
        RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIODRST);                        \
    } while (0)

//! Reset GPIOE
#define GPIOE_REG_RESET()                                                      \
    do                                                                         \
    {                                                                          \
        RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOERST);                         \
        RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOERST);                        \
    } while (0)

//! Reset GPIOH
#define GPIOH_REG_RESET()                                                      \
    do                                                                         \
    {                                                                          \
        RCC->AHB1RSTR |= (1 << RCC_AHB1RSTR_GPIOHRST);                         \
        RCC->AHB1RSTR &= ~(1 << RCC_AHB1RSTR_GPIOHRST);                        \
    } while (0)
/**
 * @}
 * @}
 */

/**
 * @addtogroup		GPIOx
 * @{
 * @name			GPIO Code
 * @{
 * @def				GPIO_BASEADDR_TO_CODE
 * @brief 			Convers a GPIO base address to GPIO Code number.
 * @details			Maps the GPIO port address to a Hex code using the following
 * table. | GPIO Port | GPIO Code | | --- | --- | | _GPIOA_ | `0x00` | | _GPIOB_
 * | `0x01` | | _GPIOC_ | `0x02` | | _GPIOD_ | `0x03` | | _GPIOE_ | `0x04` | |
 * _GPIOH_ | `0x07` |
 */
#define GPIO_BASEADDR_TO_CODE(port)                                            \
    ((port == GPIOA)   ? 0x00                                                  \
     : (port == GPIOB) ? 0x01                                                  \
     : (port == GPIOC) ? 0x02                                                  \
     : (port == GPIOD) ? 0x03                                                  \
     : (port == GPIOE) ? 0x04                                                  \
     : (port == GPIOH) ? 0x07                                                  \
                       : 0)
/**
 * @}
 * @}
 */

/**
 * @addtogroup		SPIx
 * @{
 * @name			SPI Peripheral Reset Macros
 * @{
 * @brief 			Reset RCC APB1 Reset Register
 */
//! Reset SPI1
#define SPI1_REG_RESET()                                                       \
    do                                                                         \
    {                                                                          \
        RCC->APB2RSTR |= (1 << RCC_APB2RSTR_SPI1RST);                          \
        RCC->APB2RSTR &= ~(1 << RCC_APB2RSTR_SPI1RST);                         \
    } while (0)

//! Reset SPI2
#define SPI2_REG_RESET()                                                       \
    do                                                                         \
    {                                                                          \
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_SPI2RST);                          \
        RCC->APB1RSTR &= ~(1 << RCC_APB1RSTR_SPI2RST);                         \
    } while (0)

//! Reset SPI3
#define SPI3_REG_RESET()                                                       \
    do                                                                         \
    {                                                                          \
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_SPI3RST);                          \
        RCC->APB1RSTR &= ~(1 << RCC_APB1RSTR_SPI3RST);                         \
    } while (0)

//! Reset SPI4
#define SPI4_REG_RESET()                                                       \
    do                                                                         \
    {                                                                          \
        RCC->APB1RSTR |= (1 << RCC_APB2RSTR_SPI4RST);                          \
        RCC->APB1RSTR &= ~(1 << RCC_APB2RSTR_SPI4RST);                         \
    } while (0)
/**
 * @}
 * @}
 */

/**
 * @addtogroup I2Cx
 * @{
 * @name I2C Peripheral Reset Macros
 * @{
 * @brief Reset RCC APB1 I2C Register
 */
#define I2C1_REG_RESET()                                                       \
    do                                                                         \
    {                                                                          \
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_I2C1RST);                          \
        RCC->APB1RSTR &= ~(1 << RCC_APB1RSTR_I2C1RST);                         \
    } while (0)

#define I2C2_REG_RESET()                                                       \
    do                                                                         \
    {                                                                          \
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_I2C2RST);                          \
        RCC->APB1RSTR &= ~(1 << RCC_APB1RSTR_I2C2RST);                         \
    } while (0)

#define I2C3_REG_RESET()                                                       \
    do                                                                         \
    {                                                                          \
        RCC->APB1RSTR |= (1 << RCC_APB1RSTR_I2C3RST);                          \
        RCC->APB1RSTR &= ~(1 << RCC_APB1RSTR_I2C3RST);                         \
    } while (0)
/**
 * @}
 * @}
 */

/**
 * @defgroup		misc	Generic Macros
 * @brief			Macros for common uses
 * @{
 */

#define ENABLE 1             //!< Enable
#define DISABLE 0            //!< Disable
#define SET ENABLE           //!< Set
#define RESET DISABLE        //!< Reset
#define GPIO_PIN_SET SET     //!< Set GPIO
#define GPIO_PIN_RESET RESET //!< Reset GPIO
#define FLAG_RESET RESET     //!< Reset Flag
#define FLAG_SET SET         //!< Set Flag
/** @} */

#include "cortex-m4.h"
#include "stm32f401-gpio-driver.h"
#include "stm32f401-spi-driver.h"
#include "stm32f401-i2c-driver.h"
#include "stm32f401-rcc.h"

#endif
