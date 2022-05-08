#ifndef __STM32F401RE_REGISTER_BITS_H_
#define __STM32F401RE_REGISTER_BITS_H_

/**
 * @addtogroup CRC
 * @{
 * @name Registers
 * @{
 * @name DR
 * @{
 * @brief Data Register
 */
#define CRC_CR_DR 0 //!< [32-bit] Data Register bits
/** @} */

/**
 * @name IDR
 * @{
 * @brief Independent Data Register
 */
#define CRC_IDR_IDR //!< [8-bit] General purpose register bits
/** @} */

/**
 * @name CR
 * @{
 * @brief Control Register
 */
#define CRC_CR_RESET 0 //!< [1-bit] Reset bit 
/** @} */
/** @} */
/** @} */

/** 
 * @addtogroup PWR
 * @{
 * @name Registers
 * @{
 * @name CR
 * @{
 * @brief Control Register
 */
#define PWR_CR_LPDS 0     //!< [1-bit] Low-power deepsleep
#define PWR_CR_PDDS 1     //!< [1-bit] Power-down deepsleep
#define PWR_CR_CWUF 2     //!< [1-bit] Clear wakeup flag
#define PWR_CR_CSBF 3     //!< [1-bit] Clear standy flag
#define PWR_CR_PVDE 4     //!< [1-bit] Power voltage detector enable
#define PWR_CR_PLS 5      //!< [3-bit] Power voltage detection level selection
#define PWR_CR_DBP 8      //!< [1-bit] Disable backup domain write protection
#define PWR_CR_FPDS 9     //!< [1-bit] Flash power-down in stop mode
#define PWR_CR_LPLVDS 10  //!< [1-bit] Low-power regulator Low Voltage in Deep Sleep
#define PWR_CR_MRLVDS 11  //!< [1-bit] Main regulator Low voltage in Deep Sleep
#define PWR_CR_ADCD1 13   //!< [1-bit] ADCD1
#define PWR_CR_VOS 14     //!< [2//!< [1-bit] e WKUP pin
#define PWR_CSR_BRE 9     //!< [1-bit] Backup regulator enable
#define PWR_CSR_VOSRDY 14 //!< [1-bit] Regulator voltage scaling output selection ready bit
/** @} */
/** @} */
/** @} */


/**
 * @addtogroup RCC
 * @{
 * @name Registers
 * @{
 * @name CR
 * @{
 * @brief Control Register
 */
#define RCC_CR_HSION 0      //!< [1-bit] Internal high-speed clock enable
#define RCC_CR_HSIRDY 1     //!< [1-bit] Internal high-speed clock ready flag
#define RCC_CR_HSITRIM 3    //!< [5-bit] Internal high-speed clock trimming
#define RCC_CR_HSICAL 8     //!< [8-bit] Internal high-speed clock calibration
#define RCC_CR_HSEON 16     //!< [1-bit] HSE clock enable
#define RCC_CR_HSERDY 17    //!< [1-bit] HSE clock ready flag
#define RCC_CR_HSEBYP 18    //!< [1-bit] HSE clock bypass
#define RCC_CR_CSSON 19     //!< [1-bit] Clock security system enable
#define RCC_CR_PLLON 24     //!< [1-bit] Main PLL enable
#define RCC_CR_PLLRDY 25    //!< [1-bit] Main PLL clock ready flag
#define RCC_CR_PLLI2SON 26  //!< [1-bit] PLLI2S enable
#define RCC_CR_PLLI2SRDY 27 //!< [1-bit] PLLI2S clock ready flag
/** @} */

/**
 * @name PLLCFG
 * @{
 * @brief PLL Configuration Register
 */
#define RCC_PLLCFGR_PLLM 0    //!< [6-bit] Division factor for the main PLL and PLLI2S
#define RCC_PLLCFGR_PLLN 6    //!< [9-bit] Main PLL multiplication facotr for VCO
#define RCC_PLLCFGR_PLLP 16   //!< [2-bit] Main PLL division factor for main system clock
#define RCC_PLLCFGR_PLLSRC 22 //!< [1-bit] Main PLL and PLLI2S entry clock source
#define RCC_PLLCFGR_PLLQ 24   //!< [4-bit] Main PLL division factor for USB OTG, SDIO and Random number Gen
/** @} */

/** 
 * @name CFGR
 * @{
 * @brief Clock Configuration Register
 */
#define RCC_CFGR_SW 0       //!< [2-bit] System clock switch
#define RCC_CFGR_SWS 2      //!< [2-bit] System clock switch status
#define RCC_CFGR_HPRE 4     //!< [4-bit] AHB prescaler
#define RCC_CFGR_PPRE1 10   //!< [3-bit] APB1 low-speed prescaler
#define RCC_CFGR_PPRE2 13   //!< [3-bit] APB2 high-speed prescaler
#define RCC_CFGR_RTCPRE 16  //!< [5-bit] HSE dicision factor for RTC clock
#define RCC_CFGR_MCO1 21    //!< [2-bit] Microcontroller clock output 1
#define RCC_CFGR_I2SSRC 23  //!< [1-bit] I2S clock selection
#define RCC_CFGR_MCO1PRE 24 //!< [3-bit] MCO1 prescaler
#define RCC_CFGR_MCO2PRE 27 //!< [3-bit] MCO2 prescaler
#define RCC_CFGR_MCO2 30    //!< [2-bit] Microcontroller clock output 2
/** @} */

/**
 * @name CIR
 * @{
 * @brief Clock Interrupt Register
 */
#define RCC_CIR_LSIRDYF 0      //!< [1-bit] LSI ready interrupt flag
#define RCC_CIR_LSERDYF 1      //!< [1-bit] LSE ready interrupt flag
#define RCC_CIR_HSIRDYF 2      //!< [1-bit] HSI ready interrupt flag
#define RCC_CIR_HSERFYF 3      //!< [1-bit] HSE ready interrupt flag
#define RCC_CIR_PLLRDYF 4      //!< [1-bit] Main PLL ready interrupt flag
#define RCC_CIR_PLLI2SRDYF 5   //!< [1-bit] PLLI2S ready interrupt flag
#define RCC_CIR_CSSF 7         //!< [1-bit] CLock security system interrupt flag
#define RCC_CIR_LSIRDYIE 8     //!< [1-bit] LSI ready interrupt enable
#define RCC_CIR_LSERDYIE 9     //!< [1-bit] LSE ready interrupt enable
#define RCC_CIR_HSIRDYIE 10    //!< [1-bit] HSI ready interrupt enable
#define RCC_CIR_HSERDYIE 11    //!< [1-bit] HSE ready interrupt enable
#define RCC_CIR_PLLRDYUE 12    //!< [1-bit] Main PLL ready interrupt enable
#define RCC_CIR_PLLI2SRDYIE 13 //!< [1-bit] PLLI2C ready interrupt enable
#define RCC_CIR_LSIRDYC 16     //!< [1-bit] LSI ready interrupt clear
#define RCC_CIR_LSERDYC 17     //!< [1-bit] LSE ready interrupt clear
#define RCC_CIR_HSIRDYC 18     //!< [1-bit] HSI ready interrupt clear
#define RCC_CIR_HSERDYC 19     //!< [1-bit] HSE ready interrupt clear
#define RCC_CIR_PLLRDYC 20     //!< [1-bit] Main PLL ready interrupt clear
#define RCC_CIR_PLLI2CRDYC 21  //!< [1-bit] PLLI2C ready interrupt clear
#define RCC_CIR_CSSC 23        //!< [1-bit] Clock security system interrupt clear
/** @} */

/** 
 * @name AHB1RSTR
 * @{
 * @brief AHB1 Peripheral Reset Register
 */
#define RCC_AHB1RSTR_GPIOARST 0 //!< [1-bit] GPIO port A reset
#define RCC_AHB1RSTR_GPIOBRST 1 //!< [1-bit] GPIO port B reset
#define RCC_AHB1RSTR_GPIOCRST 2 //!< [1-bit] GPIO port C reset
#define RCC_AHB1RSTR_GPIODRST 3 //!< [1-bit] GPIO port D reset
#define RCC_AHB1RSTR_GPIOERST 4 //!< [1-bit] GPIO port E reset
#define RCC_AHB1RSTR_GPIOHRST 7 //!< [1-bit] GPIO port H reset
#define RCC_AHB1RSTR_CRCRST 12  //!< [1-bit] CRC reset
#define RCC_AHB1RSTR_DMA1RST 21 //!< [1-bit] DMA1 reset
#define RCC_AHB1RSTR_DMA2RST 22 //!< [1-bit] DMA2 reset
/** @} */

/**
 * @name AHB2RSTR
 * @{
 * @brief AHB2 Peripheral Reset Register
 */
#define RCC_AHB2RSTR_OTGFSRST 7 //!< [1-bit] USB OTG reset
/** @} */

/**
 * @name APB1RSTR
 * @{
 * @brief APB1 Peripheral Reset Register
 */
#define RCC_APB1RSTR_TIM2RST 0    //!< [1-bit] Timer 2 reset
#define RCC_APB1RSTR_TIM3RST 1    //!< [1-bit] Timer 3 reset
#define RCC_APB1RSTR_TIM4RST 2    //!< [1-bit] TImer 4 reset
#define RCC_APB1RSTR_TIM5RST 3    //!< [1-bit] Timer 5 reset
#define RCC_APB1RSTR_WWDGRST 11   //!< [1-bit] Window watchdog reset
#define RCC_APB1RSTR_SPI2RST 14   //!< [1-bit] SPI2 reset
#define RCC_APB1RSTR_SPI3RST 15   //!< [1-bit] SPI3 reset
#define RCC_APB1RSTR_USART2RST 17 //!< [1-bit] USART2 reset
#define RCC_APB1RSTR_I2C1RST 21   //!< [1-bit] I2C1 reset
#define RCC_APB1RSTR_I2C2RST 22   //!< [1-bit] I2C2 reset
#define RCC_APB1RSTR_I2C3RST 23   //!< [1-bit] I2C3 reset
#define RCC_APB1RSTR_PWRRST 28    //!< [1-bit] Power interface reset
/** @} */

/**
 * @name APB2RSTR
 * @{
 * @brief APB2 Peripheral Reset Register
 */
#define RCC_APB2RSTR_TIM1RST 0    //!< [1-bit] Timer 1 reset
#define RCC_APB2RSTR_USART1RST 4  //!< [1-bit] USART1 reset
#define RCC_APB2RSTR_USART6RST 5  //!< [1-bit] USART6 reset
#define RCC_APB2RSTR_ADC1RST 8    //!< [1-bit] ADC1 reset
#define RCC_APB2RSTR_SDIORST 11   //!< [1-bit] SDIO reset
#define RCC_APB2RSTR_SPI1RST 12   //!< [1-bit] SPI1 reset
#define RCC_APB2RSTR_SPI4RST 13   //!< [1-bit] SPI4 reset
#define RCC_APB2RSTR_SYSCFGRST 14 //!< [1-bit] System configuration controller reset
#define RCC_APB2RSTR_TIM9RST 16   //!< [1-bit] Timer 9 reset
#define RCC_APB2RSTR_TIM10RST 17  //!< [1-bit] Timer 10 reset
#define RCC_APB2RSTR_TIM11RST 18  //!< [1-bit] Timer 11 reset
/** @} */

/**
 * @name AHB1ENR
 * @{
 * @brief AHB1 Periheral Clock Enable Register
 */
#define RCC_AHB1ENR_GPIOAEN 0 //!< [1-bit] GPIO port A clock enable
#define RCC_AHB1ENR_GPIOBEN 1 //!< [1-bit] GPIO port B clock enable
#define RCC_AHB1ENR_GPIOCEN 2 //!< [1-bit] GPIO port C clock enable
#define RCC_AHB1ENR_GPIODEN 3 //!< [1-bit] GPIO port D clock enable
#define RCC_AHB1ENR_GPIOEEN 4 //!< [1-bit] GPIO port E clock enable
#define RCC_AHB1ENR_GPIOHEN 7 //!< [1-bit] GPIO port H clock enable
#define RCC_AHB1ENR_CRCEN 12  //!< [1-bit] CRC clock enable
#define RCC_AHB1ENR_DMA1EN 21 //!< [1-bit] DMA1 clock enable
#define RCC_AHB1ENR_DMA2EN 22 //!< [1-bit] DMA2 clock enable
/** @} */

/**
 * @name AHB2ENR
 * @{
 * @brief AHB2 Peripheral Clock Enable Register
 */
#define RCC_AHB2ENR_OTGFSEN 7 //!< [1-bit] USB OTG clock enable
/** @} */

/**
 * @name APB1ENR
 * @{
 * @brief APB1 Peripheral Clock Enable Register
 */
#define RCC_APB1ENR_TIM2EN 0    //!< [1-bit] Timer 2 clock enable
#define RCC_APB1ENR_TIM3EN 1    //!< [1-bit] Timer 3 clock enable
#define RCC_APB1ENR_TIM4EN 2    //!< [1-bit] TImer 4 clock enable
#define RCC_APB1ENR_TIM5EN 3    //!< [1-bit] Timer 5 clock enable
#define RCC_APB1ENR_WWDGEN 11   //!< [1-bit] Window watchdog clock enable
#define RCC_APB1ENR_SPI2EN 14   //!< [1-bit] SPI2 clock enable
#define RCC_APB1ENR_SPI3EN 15   //!< [1-bit] SPI3 clock enable
#define RCC_APB1ENR_USART2EN 17 //!< [1-bit] USART2 clock enable
#define RCC_APB1ENR_I2C1EN 21   //!< [1-bit] I2C1 clock enable
#define RCC_APB1ENR_I2C2EN 22   //!< [1-bit] I2C2 clock enable
#define RCC_APB1ENR_I2C3EN 23   //!< [1-bit] I2C3 clock enable
#define RCC_APB1ENR_PWREN 28    //!< [1-bit] Power interface clock enable
/** @} */

/**
 * @name APB2ENR
 * @{
 * @brief APB2 Peripheral Clock Enable Register
 */
#define RCC_APB2ENR_TIM1EN 0    //!< [1-bit] Timer 1 clock enable
#define RCC_APB2ENR_USART1EN 4  //!< [1-bit] USART1 clock enable
#define RCC_APB2ENR_USART6EN 5  //!< [1-bit] USART6 clock enable
#define RCC_APB2ENR_ADC1EN 8    //!< [1-bit] ADC1 clock enable
#define RCC_APB2ENR_SDIOEN 11   //!< [1-bit] SDIO clock enable
#define RCC_APB2ENR_SPI1EN 12   //!< [1-bit] SPI1 clock enable
#define RCC_APB2ENR_SPI4EN 13   //!< [1-bit] SPI4 clock enable
#define RCC_APB2ENR_SYSCFGEN 14 //!< [1-bit] System configuration controller clock enable
#define RCC_APB2ENR_TIM9EN 16   //!< [1-bit] Timer 9 clock enable
#define RCC_APB2ENR_TIM10EN 17  //!< [1-bit] Timer 10 clock enable
#define RCC_APB2ENR_TIM11EN 18  //!< [1-bit] Timer 11 clock enable
/** @} */

/**
 * @name AHB1LPENR
 * @{
 * @brief AHB1 Peripheral Clock Enable in Low Power Mode Register
 */
#define RCC_AHB1LPENR_GPIOALPEN 0  //!< [1-bit] GPIO port A clock enabled during sleep mode
#define RCC_AHB1LPENR_GPIOBLPEN 1  //!< [1-bit] GPIO port B clock enabled during sleep mode
#define RCC_AHB1LPENR_GPIOCLPEN 2  //!< [1-bit] GPIO port C clock enabled during sleep mode
#define RCC_AHB1LPENR_GPIODLPEN 3  //!< [1-bit] GPIO port D clock enabled during sleep mode
#define RCC_AHB1LPENR_GPIOELPEN 4  //!< [1-bit] GPIO port E clock enabled during sleep mode
#define RCC_AHB1LPENR_GPIOHLPEN 7  //!< [1-bit] GPIO port H clock enabled during sleep mode
#define RCC_AHB1LPENR_CRCLPEN 12   //!< [1-bit] CRC clock enabled during sleep mode
#define RCC_AHB1LPENR_FLITFLPEN 15 //!< [1-bit] Flash interface clock enabled during sleep mode
#define RCC_AHB1LPENR_SRAM1LPEN 16 //!< [1-bit] SRAM1 interface clock enabled during sleep mode
#define RCC_AHB1LPENR_DMA1LPEN 21  //!< [1-bit] DMA1 clock enabled during sleep mode
#define RCC_AHB1LPENR_DMA2LPEN 22  //!< [1-bit] DMA2 clock enabled during sleep mode
/** @} */

/**
 * @name AHB2LPENR
 * @{
 * @brief AHB2 Peripheral Clock Enable in Low Power Mode Register
 */
#define RCC_AHB2LPENR_OTGFSLPEN 7 //!< [1-bit] USB OTG FS clock enabled during sleep mode
/** @} */

/** 
 * @name APB1LPENR
 * @{
 * @brief APB1 Peripheral Clock Enable in Low Power Mode Register
 */
#define RCC_APB1LPENR_TIM2LPEN 0    //!< [1-bit] TIM2 clock enable dutin sleep mode
#define RCC_APB1LPENR_TIM3LPEN 1    //!< [1-bit] TIM3 clock enable dutin sleep mode
#define RCC_APB1LPENR_TIM4LPEN 2    //!< [1-bit] TIM4 clock enable dutin sleep mode
#define RCC_APB1LPENR_TIM5LPEN 3    //!< [1-bit] TIM5 clock enable dutin sleep mode
#define RCC_APB1LPENR_WWDGLPEN 11   //!< [1-bit] WWDG clock enable dutin sleep mode
#define RCC_APB1LPENR_SPI2LPEN 14   //!< [1-bit] SPI2 clock enable dutin sleep mode
#define RCC_APB1LPENR_SPI3LPEN 15   //!< [1-bit] SPI3 clock enable dutin sleep mode
#define RCC_APB1LPENR_USART2LPEN 17 //!< [1-bit] USART2 clock enable dutin sleep mode
#define RCC_APB1LPENR_I2C1LPEN 21   //!< [1-bit] I2C1 clock enable dutin sleep mode
#define RCC_APB1LPENR_I2C2LPEN 22   //!< [1-bit] I2C2 clock enable dutin sleep mode
#define RCC_APB1LPENR_I2C3LPEN 23   //!< [1-bit] I2C3 clock enable dutin sleep mode
#define RCC_APB1LPENR_PWRLPEN 28    //!< [1-bit] PWR clock enable dutin sleep mode
/** @} */

/**
 * @name APB2LPENR
 * @{
 * @brief APB2 Peripheral Clock Enable in Low Power Mode Register
 */
#define RCC_APB2LPENR_TIM1LPEN 0    //!< [1-bit] Timer 1 clock enable dutin sleep mode
#define RCC_APB2LPENR_USART1LPEN 4  //!< [1-bit] USART1 clock enable dutin sleep mode
#define RCC_APB2LPENR_USART6LPEN 5  //!< [1-bit] USART6 clock enable dutin sleep mode
#define RCC_APB2LPENR_ADC1LPEN 8    //!< [1-bit] ADC1 clock enable dutin sleep mode
#define RCC_APB2LPENR_SDIOLPEN 11   //!< [1-bit] SDIO clock enable dutin sleep mode
#define RCC_APB2LPENR_SPI1LPEN 12   //!< [1-bit] SPI1 clock enable dutin sleep mode
#define RCC_APB2LPENR_SPI4LPEN 13   //!< [1-bit] SPI4 clock enable dutin sleep mode
#define RCC_APB2LPENR_SYSCFGLPEN 14 //!< [1-bit] SYSCFG clock enable dutin sleep mode
#define RCC_APB2LPENR_TIM9LPEN 16   //!< [1-bit] Timer 9 clock enable dutin sleep mode
#define RCC_APB2LPENR_TIM10LPEN 17  //!< [1-bit] Timer 10 clock enable dutin sleep mode
#define RCC_APB2LPENR_TIM11LPEN 18  //!< [1-bit] Timer 11 clock enable dutin sleep mode
/** @} */

/**
 * @name BDCR
 * @{
 * @brief Backup Domain Control Register
 */
#define RCC_BDCR_LSEON 0  //!< [1-bit] External low-speed oscillator enable
#define RCC_BDCR_LSERDY 1 //!< [1-bit] External Low-speed oscillator ready
#define RCC_BDCR_LSEBYP 2 //!< [1-bit] External low-speed oscillator bypass
#define RCC_BDCR_RTCSEL 8 //!< [2-bit] RTC clock source selection
#define RCC_BDCR_RTCEN 15 //!< [1-bit] RTC clock enable
#define RCC_BDCR_BDRST 16 //!< [1-bit] Backup domain software reset
/** @} */

/**
 * @name CSR
 * @{
 * @brief Clock Control & Status Register
 */
#define RCC_CSR_LSION 0     //!< [1-bit] Internal low-speed oscillator enable
#define RCC_CSR_LSIRDY 1    //!< [1-bit] Internal low-speed oscillator ready
#define RCC_CSR_RMVF 24     //!< [1-bit] Remove reset flag
#define RCC_CSR_BORRSTF 25  //!< [1-bit] BOR reset flag
#define RCC_CSR_PINRSTF 26  //!< [1-bit] PIN reset flag
#define RCC_CSR_PORRSTF 27  //!< [1-bit] POR/PDR reset flag
#define RCC_CSR_SFTRSTF 28  //!< [1-bit] Software reset flag
#define RCC_CSR_IWDGRSTF 29 //!< [1-bit] Independent watchdog reset flag
#define RCC_CSR_WWDGRSTF 30 //!< [1-bit] Window watchdog reset flag
#define RCC_CSR_LPWRRSTF 31 //!< [1-bit] Low-power reset flag
/** @} */

/**
 * @name SSCGR
 * @{
 * @brief Spread Spectrum Clock Generation Register
 */
#define RCC_SSCGR_MODPER 0     //!< [13-bit] Modulation period
#define RCC_SSCGR_INCSTEP 13   //!< [15-bit] Incrementation step
#define RCC_SSCGR_SPREADSEL 30 //!< [1-bit] Spread Select
#define RCC_SSCGR_SSCGEN 31    //!< [1-bit] Spread Spectrum modulation enable
/** @} */

/**
 * @name PLLI2SCFG
 * @{
 * @brief PLLI2S Configuration Register
 */
#define RCC_PLLI2SCFGR_PLLI2SN 6  //!< [9-bit] PLLI2S multiplication factor for VCO
#define RCC_PLLI2SCFGR_PLLI2SR 28 //!< [3-bit] PLLI2S division factor I2S clocks
/** @} */

/**
 * @name DCKCFGR
 * @{
 * @brief Dedicated Clocks Configuration Register
 */
#define RCC_DCKCFGR_TIMPRE 24 //!< [1-bit] Timers clocks prescaler selection
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup SYSCFG
 * @{
 * @name Registers
 * @{
 * @name MEMRMP
 * @{
 * @brief Memory Remap Register
 */
#define SYSCFG_MEMRMP_MEM_MODE 0 //!< [2-bit] Memory mapping selection
/** @} */

/**
 * @name PMC
 * @{
 * @brief Peripheral Mode Configurator Register
 */
#define SYSCFG_PMC_ADCxDC2
/** @} */

/**
 * @name EXTICR1
 * @{
 * @brief External Configuration Register 1
 */
#define SYSCFG_EXTICR1_EXTIx 0 //!< [4-bit] EXTI x configuration
/** @} */

/**
 * @name EXTICR2
 * @{
 * @brief External Configuration Register 1
 */
#define SYSCFG_EXTICR2_EXTIx 0 //!< [4-bit] EXTI x configuration
/** @} */

/**
 * @name EXTICR3
 * @{
 * @brief External Configuration Register 1
 */
#define SYSCFG_EXTICR3_EXTIx 0 //!< [4-bit] EXTI x configuration
/** @} */

/**
 * @name EXTICR4
 * @{
 * @brief External Configuration Register 1
 */
#define SYSCFG_EXTICR4_EXTIx 0 //!< [4-bit] EXTI x configuration
/** @} */

/**
 * @name CMPCR
 * @{
 * @brief Compensation Cell Control Register
 */
#define SYSCFG_CMPCR_CMP_PD 0 //!< [1-bit] Compensation cell power-down
#define SYSCFG_CMPCR_READY 8  //!< [1-bit] Compensation cell ready flag
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup DMA
 * @{
 * @name Registers
 * @{
 * @name LISR
 * @{
 * @brief Low Interrupt Status Register
 */
#define DMA_LISR_FEIF0 0   //!< [1-bit] Stream 0 FIFO error interrupt flag
#define DMA_LISR_FEIF1 6   //!< [1-bit] Stream 1 FIFO error interrupt flag
#define DMA_LISR_FEIF2 16  //!< [1-bit] Stream 2 FIFO error interrupt flag
#define DMA_LISR_FEIF3 22  //!< [1-bit] Stream 3 FIFO error interrupt flag
#define DMA_LISR_DMEIF0 1  //!< [1-bit] Stream 0 direct mode error interrupt flag
#define DMA_LISR_DMEIF1 7  //!< [1-bit] Stream 1 direct mode error interrupt flag
#define DMA_LISR_DMEIF2 17 //!< [1-bit] Stream 2 direct mode error interrupt flag
#define DMA_LISR_DMEIF3 23 //!< [1-bit] Stream 3 direct mode error interrupt flag
#define DMA_LISR_HTIF0 4   //!< [1-bit] Stream 0 half transfer interrupt flag
#define DMA_LISR_HTIF1 10  //!< [1-bit] Stream 1 half transfer interrupt flag
#define DMA_LISR_HTIF2 20  //!< [1-bit] Stream 2 half transfer interrupt flag
#define DMA_LISR_HTIF3 26  //!< [1-bit] Stream 3 half transfer interrupt flag
#define DMA_LISR_TCIF0 5   //!< [1-bit] Stream 0 transfer complete interrupt flag
#define DMA_LISR_TCIF1 11  //!< [1-bit] Stream 1 transfer complete interrupt flag
#define DMA_LISR_TCIF2 21  //!< [1-bit] Stream 2 transfer complete interrupt flag
#define DMA_LISR_TCIF3 27  //!< [1-bit] Stream 3 transfer complete interrupt flag
/** @} */

/**
 * @name HISR
 * @{
 * @brief High Interrupt Status Register
 */
#define DMA_HISR_FEIF4 0   //!< [1-bit] Stream 4 FIFO error interrupt flag
#define DMA_HISR_FEIF5 6   //!< [1-bit] Stream 5 FIFO error interrupt flag
#define DMA_HISR_FEIF6 16  //!< [1-bit] Stream 6 FIFO error interrupt flag
#define DMA_HISR_FEIF7 22  //!< [1-bit] Stream 7 FIFO error interrupt flag
#define DMA_HISR_DMEIF4 1  //!< [1-bit] Stream 4 direct mode error interrupt flag
#define DMA_HISR_DMEIF5 7  //!< [1-bit] Stream 5 direct mode error interrupt flag
#define DMA_HISR_DMEIF6 17 //!< [1-bit] Stream 6 direct mode error interrupt flag
#define DMA_HISR_DMEIF7 23 //!< [1-bit] Stream 7 direct mode error interrupt flag
#define DMA_HISR_HTIF4 4   //!< [1-bit] Stream 4 half transfer interrupt flag
#define DMA_HISR_HTIF5 10  //!< [1-bit] Stream 5 half transfer interrupt flag
#define DMA_HISR_HTIF6 20  //!< [1-bit] Stream 6 half transfer interrupt flag
#define DMA_HISR_HTIF7 26  //!< [1-bit] Stream 7 half transfer interrupt flag
#define DMA_HISR_TCIF4 5   //!< [1-bit] Stream 4 transfer complete interrupt flag
#define DMA_HISR_TCIF5 11  //!< [1-bit] Stream 5 transfer complete interrupt flag
#define DMA_HISR_TCIF6 21  //!< [1-bit] Stream 6 transfer complete interrupt flag
#define DMA_HISR_TCIF7 27  //!< [1-bit] Stream 7 transfer complete interrupt flag
/** @} */

/**
 * @name LIFCR
 * @{
 * @brief Low Interrupt Flag Register
 */
#define DMA_LISR_CFEIF0 0   //!< [1-bit] Stream 0 clear FIFO error interrupt flag
#define DMA_LISR_CFEIF1 6   //!< [1-bit] Stream 1 clear FIFO error interrupt flag
#define DMA_LISR_CFEIF2 16  //!< [1-bit] Stream 2 clear FIFO error interrupt flag
#define DMA_LISR_CFEIF3 22  //!< [1-bit] Stream 3 clear FIFO error interrupt flag
#define DMA_LISR_CDMEIF0 2  //!< [1-bit] Stream 0 clear direct mode error interrupt flag
#define DMA_LISR_CDMEIF1 8  //!< [1-bit] Stream 1 clear direct mode error interrupt flag
#define DMA_LISR_CDMEIF2 18 //!< [1-bit] Stream 2 clear direct mode error interrupt flag
#define DMA_LISR_CDMEIF3 24 //!< [1-bit] Stream 3 clear direct mode error interrupt flag
#define DMA_LISR_CTEIF0 3   //!< [1-bit] Stream 0 clear transfer error interrupt flag
#define DMA_LISR_CTEIF1 9   //!< [1-bit] Stream 1 clear transfer error interrupt flag
#define DMA_LISR_CTEIF2 19  //!< [1-bit] Stream 2 clear transfer error interrupt flag
#define DMA_LISR_CTEIF3 24  //!< [1-bit] Stream 3 clear transfer error interrupt flag
#define DMA_LISR_CHTIF0 4   //!< [1-bit] Stream 0 clear half transfer interrupt flag
#define DMA_LISR_CHTIF1 10  //!< [1-bit] Stream 1 clear half transfer interrupt flag
#define DMA_LISR_CHTIF2 20  //!< [1-bit] Stream 2 clear half transfer interrupt flag
#define DMA_LISR_CHTIF3 26  //!< [1-bit] Stream 3 clear half transfer interrupt flag
#define DMA_LISR_CTCIF0 5   //!< [1-bit] Stream 0 clear transfer complete interrupt flag
#define DMA_LISR_CTCIF1 11  //!< [1-bit] Stream 1 clear transfer complete interrupt flag
#define DMA_LISR_CTCIF2 21  //!< [1-bit] Stream 2 clear transfer complete interrupt flag
#define DMA_LISR_CTCIF3 27  //!< [1-bit] Stream 3 clear transfer complete interrupt flag
/** @} */

/**
 * @name HIFCR
 * @{
 * @brief High Interrupt Flag Clear Register
 */
#define DMA_HISR_CFEIF4 0   //!< [1-bit] Stream 4 clear FIFO error interrupt flag
#define DMA_HISR_CFEIF5 6   //!< [1-bit] Stream 5 clear FIFO error interrupt flag
#define DMA_HISR_CFEIF6 16  //!< [1-bit] Stream 6 clear FIFO error interrupt flag
#define DMA_HISR_CFEIF7 22  //!< [1-bit] Stream 7 clear FIFO error interrupt flag
#define DMA_HISR_CDMEIF4 2  //!< [1-bit] Stream 4 clear direct mode error interrupt flag
#define DMA_HISR_CDMEIF5 8  //!< [1-bit] Stream 5 clear direct mode error interrupt flag
#define DMA_HISR_CDMEIF6 18 //!< [1-bit] Stream 6 clear direct mode error interrupt flag
#define DMA_HISR_CDMEIF7 24 //!< [1-bit] Stream 7 clear direct mode error interrupt flag
#define DMA_HISR_CTEIF4 3   //!< [1-bit] Stream 4 clear transfer error interrupt flag
#define DMA_HISR_CTEIF5 9   //!< [1-bit] Stream 5 clear transfer error interrupt flag
#define DMA_HISR_CTEIF6 19  //!< [1-bit] Stream 6 clear transfer error interrupt flag
#define DMA_HISR_CTEIF7 24  //!< [1-bit] Stream 7 clear transfer error interrupt flag
#define DMA_HISR_CHTIF4 4   //!< [1-bit] Stream 4 clear half transfer interrupt flag
#define DMA_HISR_CHTIF5 10  //!< [1-bit] Stream 5 clear half transfer interrupt flag
#define DMA_HISR_CHTIF6 20  //!< [1-bit] Stream 6 clear half transfer interrupt flag
#define DMA_HISR_CHTIF7 26  //!< [1-bit] Stream 7 clear half transfer interrupt flag
#define DMA_HISR_CTCIF4 5   //!< [1-bit] Stream 4 clear transfer complete interrupt flag
#define DMA_HISR_CTCIF5 11  //!< [1-bit] Stream 5 clear transfer complete interrupt flag
#define DMA_HISR_CTCIF6 21  //!< [1-bit] Stream 6 clear transfer complete interrupt flag
#define DMA_HISR_CTCIF7 27  //!< [1-bit] Stream 7 clear transfer complete interrupt flag
/** @} */

/**
 * @name SXCR
 * @{
 * @brief Stream X Configuration Register
 */
#define DMA_SXCR_CHSEL 25  //!< [3-bit] Channel selection
#define DMA_SXCR_MBURST 23 //!< [1-bit] Memory burst transfer configuration
#define DMA_SXCR_PBURST 21 //!< [2-bit] Peripheral burst trasnfer configuration
#define DMA_SXCR_CT 19     //!< [1-bit] Current target
#define DMA_SXCR_DBM 18    //!< [1-bit] Double buffer mode
#define DMA_SXCR_PL 16     //!< [1-bit] Priority level
#define DMA_SXCR_PINCOS 15 //!< [1-bit] Peripheral increment offset size
#define DMA_SXCR_MSIZE 13  //!< [2-bit] Memory data size
#define DMA_SXCR_PSIZE 11  //!< [2-bit] Peripheral data size
#define DMA_SXCR_MINC 10   //!< [1-bit] Memory increment mode
#define DMA_SXCR_PINC 9    //!< [1-bit] Perupheral increment mode
#define DMA_SXCR_CIRC 8    //!< [1-bit] Circular mode
#define DMA_SXCR_DIR 6     //!< [1-bit] Data transfer direction
#define DMA_SXCR_PFCTRL 5  //!< [1-bit] Peripheral flow controller
#define DMA_SXCR_TCIE 4    //!< [1-bit] Transfer complete interrupt enable
#define DMA_SXCR_HTIE 3    //!< [1-bit] Half transfer interrupt enable
#define DMA_SXCR_TEIE 2    //!< [1-bit] Transfer error interrupt enable
#define DMA_SXCR_DMEIE 1   //!< [1-bit] Direct mode error interrupt enable
#define DMA_SXCR_EN 0      //!< [1-bit] Stream enable
/** @} */

/**
 * @name SXNDTR
 * @{
 * @brief Stream X Number of Data Register
 */
#define DMA_SXDTR_NDT 0 //!< [16-bit] Number of data items to transfer
/** @} */

/**
 * @name SXPAR
 * @{
 * @brief Stream X Peripheral Address Register
 */
#define DMA_SXPAR_PAR 0 //!< [32-bit] Peripheral address
/** @} */

/**
 * @name SXM0AR
 * @{
 * @brief Stream X Memory 0 Address Register
 */
#define DMA_SXM0AR_M0A 0 //!< [32-bit] Memory 0 address
/** @} */


/**
 * @name SXM1AR
 * @{
 * @brief Stream X Memory 1 Address Register
 */
#define DMA_SXM1AR_M1A 0 //!< [32-bit] Memory 1 address
/** @} */

/**
 * @name SXFCR
 * @{
 * @brief Stream X FIFO Control Register
 */
#define DMA_SXFCR_FTH 0   //!< [2-bit] FIFO threshold selection
#define DMA_SXFCR_DMDIS 2 //!< [1-bit] Direct mode disable
#define DMA_SXFCR_DS 3    //!< [3-bit] FIFO status
#define DMA_SXFCR_FEIE 7  //!< [1-bit] FIFO error interrupt enable
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup ADC
 * @{
 * @name Registers
 * @{
 * @name SR
 * @{
 * @brief Status Register
 */
#define ADC_SR_AWD 0   //!< [1-bit] Analog watchog flag
#define ADC_SR_EOC 1   //!< [1-bit] Regular channel end of conversion
#define ADC_SR_JEOC 2  //!< [1-bit] Injected channel end of conversion
#define ADC_SR_JSTRT 3 //!< [1-bit] Injected channel start flag
#define ADC_SR_STRT 4  //!< [1-bit] Regular channel start flag
#define ADC_SR_OVR 5   //!< [1-bit] Overrun
/** @} */

/**
 * @name CR1
 * @{
 * @brief Control Register 1
 */
#define ADC_CR1_AWDCH 0    //!< [5-bit] Analog watchdog channel select bits
#define ADC_CR1_EOCIE 5    //!< [1-bit] Interrupt enable for EOC
#define ADC_CR1_AWDIE 6    //!< [1-bit] Analog watchdog interrupt enable
#define ADC_CR1_JEOCIE 7   //!< [1-bit] Interrupt enable for injected channels
#define ADC_CR1_SCAN 8     //!< [1-bit] Scan mode
#define ADC_CR1_AWDSGL 9   //!< [1-bit] Enable the watchdog on a single channel in scan mode
#define ADC_CR1_JAUTO 10   //!< [1-bit] Automatic injected group conversion
#define ADC_CR1_DISCEN 11  //!< [1-bit] Discontinous mode on regular channels
#define ADC_CR1_JDISCEN 12 //!< [1-bit] Discontinous mode on injected channels
#define ADC_CR1_DISCNUM 13 //!< [3-bit] Doscontinous mode channel count
#define ADC_CR1_JAWDEN 22  //!< [1-bit] Analog watchdog enable on injected channels
#define ADC_CR1_AWDEN 23   //!< [1-bit] Analog watchdog enable on regular channels
#define ADC_CR1_RES 24     //!< [2-bit] Resolution
#define ADC_CR1_OVRIE 26   //!< [1-bit] Overrun interrupt enable
/** @} */

/**
 * @name CR2
 * @{
 * @brief Control Register 2
 */
#define ADC_CR2_ADON 0      //!< [1-bit] A/D converter On/Off
#define ADC_CR2_CONT 1      //!< [1-bit] Continous conversion
#define ADC_CR2_DMA 8       //!< [1-bit] DMA mode
#define ADC_CR2_DDS 9       //!< [1-bit] DMA disable selection
#define ADC_CR2_EOCS 10     //!< [1-bit] End of conversion selection
#define ADC_CR2_ALIGN 11    //!< [1-bit] Data alignment
#define ADC_CR2_JEXTSEL 16  //!< [4-bit] External event select for injected group
#define ADC_CR2_JEXTEN 20   //!< [1-bit] External trigger enable for injected channels
#define ADC_CR2_JSWSTART 22 //!< [1-bit] Start conversion of injected channels
#define ADC_CR2_EXTSEL 24   //!< [4-bit] External event select for regular group
#define ADC_CR2_EXTEN 28    //!< [1-bit] External trugger enable for regualr channels
#define ADC_CR2_SWSTART 30  //!< [1-bit] Star conversion of regular channels
/** @} */

/**
 * @name SMPR1
 * @{
 * @brief Sample Time Register 1
 */
#define ADC_SMPR1_SMP10 0  //!< [3-bit] Channel 10 sampling time value
#define ADC_SMPR1_SMP11 3  //!< [3-bit] Channel 11 sampling time value
#define ADC_SMPR1_SMP12 6  //!< [3-bit] Channel 12 sampling time value
#define ADC_SMPR1_SMP13 9  //!< [3-bit] Channel 13 sampling time value
#define ADC_SMPR1_SMP14 12 //!< [3-bit] Channel 14 sampling time value
#define ADC_SMPR1_SMP15 15 //!< [3-bit] Channel 15 sampling time value
#define ADC_SMPR1_SMP16 18 //!< [3-bit] Channel 16 sampling time value
#define ADC_SMPR1_SMP17 21 //!< [3-bit] Channel 17 sampling time value
#define ADC_SMPR1_SMP18 24 //!< [3-bit] Channel 18 sampling time value
/** @} */

/**
 * @name SMPR2
 * @{
 * @brief Sample Time Register 2
 */
#define ADC_SMPR2_SMP0 0  //!< [3-bit] Channel 0 sampling time value
#define ADC_SMPR2_SMP1 3  //!< [3-bit] Channel 1 sampling time value
#define ADC_SMPR2_SMP2 6  //!< [3-bit] Channel 2 sampling time value
#define ADC_SMPR2_SMP3 9  //!< [3-bit] Channel 3 sampling time value
#define ADC_SMPR2_SMP4 12 //!< [3-bit] Channel 4 sampling time value
#define ADC_SMPR2_SMP5 15 //!< [3-bit] Channel 5 sampling time value
#define ADC_SMPR2_SMP6 18 //!< [3-bit] Channel 6 sampling time value
#define ADC_SMPR2_SMP7 21 //!< [3-bit] Channel 7 sampling time value
#define ADC_SMPR2_SMP8 24 //!< [3-bit] Channel 8 sampling time value
#define ADC_SMPR2_SMP9 27 //!< [3-bit] Channel 9 sampling time value
/** @} */

/**
 * @name HTR
 * @{
 * @brief Watchdog Higher Threshold Register
 */
#define ADC_HTR_HT 0 //!< [12-bit] Analog watchdog higher threshold
/** @} */

/**
 * @name LTR
 * @{
 * @brief Watchod Lower Threshold Register
 */
#define ADC_LTR_LT 0 //!< [12-bit] Analog watchdog lower threshold
/** @} */

/**
 * @name SQR1
 * @{
 * @brief Regular Sequence Register 1
 */
#define ADC_SQR1_SQ13 0  //!< [5-bit] 13th conversion in regular sequence
#define ADC_SQR1_SQ14 5  //!< [5-bit] 14th conversion in regular sequence
#define ADC_SQR1_SQ15 10 //!< [5-bit] 15th conversion in regular sequence
#define ADC_SQR1_SQ16 15 //!< [5-bit] 16th conversion in regular sequence
#define ADC_SQR1_L 20    //!< [4-bit] Regular channel sequence length
/** @} */

/**
 * @name SQR2
 * @{
 * @brief Regular Sequence Register 2
 */
#define ADC_SQR2_SQ7 0   //!< [5-bit] 7th conversion in regular sequence
#define ADC_SQR2_SQ8 5   //!< [5-bit] 8th conversion in regular sequence
#define ADC_SQR2_SQ9 10  //!< [5-bit] 9th conversion in regular sequence
#define ADC_SQR2_SQ10 15 //!< [5-bit] 10th conversion in regular sequence
#define ADC_SQR2_SQ11 20 //!< [5-bit] 11th conversion in regular sequence
#define ADC_SQR2_SQ12 25 //!< [5-bit] 12th conversion in regular sequence
/** @} */

/**
 * @name SQR3
 * @{
 * @brief Regular Sequence Register 3
 */
#define ADC_SQR3_SQ1 0  //!< [5-bit] 1th conversion in regular sequence
#define ADC_SQR3_SQ2 5  //!< [5-bit] 2th conversion in regular sequence
#define ADC_SQR3_SQ3 10 //!< [5-bit] 3th conversion in regular sequence
#define ADC_SQR3_SQ4 15 //!< [5-bit] 4th conversion in regular sequence
#define ADC_SQR3_SQ5 20 //!< [5-bit] 5th conversion in regular sequence
#define ADC_SQR3_SQ6 25 //!< [5-bit] 6th conversion in regular sequence
/** @} */

/**
 * @name JSQR
 * @{
 * @brief Injected Sequence Register
 */
#define ADC_JSQR_JSQ1 0  //!< [5-bit] 1st conversion in injected sequence
#define ADC_JSQR_JSQ2 5  //!< [5-bit] 2nd conversion in injected sequence
#define ADC_JSQR_JSQ3 10 //!< [5-bit] 3rd conversion in injected sequence
#define ADC_JSQR_JSQ4 15 //!< [5-bit] 4th conversion in injected sequence
#define ADC_JSQR_JL 20   //!< [2-bit] Injected sequence length
/** @} */

/**
 * @name JDRX
 * @{
 * @brief Injected Data Register
 */
#define ADC_JDRX_JDATA 0 // [16-bit] Injected data
/** @} */

/**
 * @name DR
 * @{
 * @brief Data Register
 */
#define ADC_DR_DATA 0 //!< [16-bit] Regular data
/** @} */

/**
 * @name CCR
 * @{
 * @brief Common Control Register
 */
#define ARC_CCR_ADCPRE 16  //!< [1-bit] ADC prescaler
#define ARC_CCR_VBATE 22   //!< [1-bit] \f$V_{bat}\f$ enable
#define ARC_CCR_TSVREFE 23 //!< [1-bit] Temperature sensor \f$V_{REFINT}\f$ enable
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup TIMX
 * @{
 * @name Registers
 * @{
 * @name CR1
 * @{
 * @brief Control Register 1
 */
#define TIMx_CR1_CEN 0  //!< [1-bit] Counter enable
#define TIMx_CR1_UDIS 1 //!< [1-bit] Update disable
#define TIMx_CR1_URS 2  //!< [1-bit] Update request source
#define TIMx_CR1_OPM 3  //!< [1-bit] One pulse mode
#define TIMx_CR1_DIR 4  //!< [1-bit] [Not in TIM9-10-11] Direction
#define TIMx_CR1_CMS 5  //!< [2-bit] [Not in TIM9-10-11] Center-aligned mode selection
#define TIMx_CR1_ARPE 7 //!< [1-bit] Auto-reload preload enable
#define TIMx_CR1_CKD 8  //!< [1-bit] Clock division
/** @} */

/**
 * @name CR2
 * @{
 * @brief Control Register 2
 * @note Not available for TIM9, TIM10 and TIM11
 */
#define TIMx_CR2_CCPC 0   //!< [1-bit] [TIM1 Only] Capture/compare preloaded control
#define TIMx_CR2_CCUS 2   //!< [1-bit] [TIM1 Only] Capture/compare control updae selection
#define TIMx_CR2_CCDS 3   //!< [1-bit] Capture/compare DMA selection
#define TIMx_CR2_MMS 4    //!< [3-bit] Master mode selection
#define TIMx_CR2_TI1S 7   //!< [1-bit] TI1 selection
#define TIMx_CR2_OIS1 8   //!< [1-bit] [TIM1 Only] Output idle state 1
#define TIMx_CR2_OIS1N 9  //!< [1-bit] [TIM1 Only] Output idle state 1
#define TIMx_CR2_OIS2 10  //!< [1-bit] [TIM1 Only] Output Idle state 2
#define TIMx_CR2_OIS2N 11 //!< [1-bit] [TIM1 Only] Output idle state 2
#define TIMx_CR2_OIS3 12  //!< [1-bit] [TIM1 Only] Output idle state 3
#define TIMx_CR2_OIS3N 13 //!< [1-bit] [TIM1 Only] Output idle state 3
#define TIMx_CR2_OIS4 14  //!< [1-bit] [TIM1 Only] Output idle state 4
/** @} */

/**
 * @name SMCR
 * @{
 * @brief Slave Mode Control Register
 * @note Not available for TIM10 and TIM11
 */
#define TIMx_SMCR_SMS 0   //!< [3-bit] Slave mode selection
#define TIMx_SMCR_TS 4    //!< [3-bit] Trigger selection
#define TIMx_SMCR_MSM 7   //!< [1-bit] Master/slave mode
#define TIMx_SMCR_EFT 8   //!< [4-bit] [Not in TIM9] External trigger filter
#define TIMx_SMCR_ETPS 12 //!< [2-bit] [Not in TIM9] External trigger prescaler
#define TIMx_SMCR_ECE 14  //!< [1-bit] [Not in TIM9] External clock enable
#define TIMx_SMCR_ETP 15  //!< [1-bit] [Not in TIM9] External trigger polarity
/** @} */

/**
 * @name DIER
 * @{
 * @brief DMA/Interrupt Enable Register
 */
#define TIMx_DIER_UIE 0    //!< [1-bit] Update Interrupt enable
#define TIMx_DIER_CC1IE 1  //!< [1-bit] Capture/compare 1 interrupt enable
#define TIMx_DIER_CC2IE 2  //!< [1-bit] [Not in TIM10-11] Capture/compare 2 interrupt enable
#define TIMx_DIER_CC3IE 3  //!< [1-bit] [Not in TIM10-11] Capture/compare 3 interrupt enable
#define TIMx_DIER_CC4IE 4  //!< [1-bit] [TIM1 Only] Capture/compare 4 interrupt enable
#define TIMx_DIER_COMIE 5  //!< [1-bit] [Not in TIM9-10-11] COM interrupt enable
#define TIMx_DIER_TIE 6    //!< [1-bit] [Not in TIM9-10-11] Trigger interrupt enable
#define TIMx_DIER_BIE 7    //!< [1-bit] [TIM1 Only] Break interrupt enable
#define TIMx_DIER_UDE 8    //!< [1-bit] [Not in TIM9-10-11]  Update DMA request enable
#define TIMx_DIER_CC1DE 9  //!< [1-bit] [Not in TIM9-10-11] Capture/compare 1 DMA request enable
#define TIMx_DIER_CC2DE 10 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 2 DMA request enable
#define TIMx_DIER_CC3DE 11 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 3 DMA request enable
#define TIMx_DIER_CC4DE 12 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 4 DMA request enable
#define TIMx_DIER_COMDE 13 //!< [1-bit] [Not in TIM9-10-11] [TIM1 Only] COM DMA request enable
#define TIMx_DIER_TDE 14   //!< [1-bit] [Not in TIM9-10-11] Trigger DMA request enable
/** @} */

/**
 * @name ST
 * @{
 * @brief Status Register
 */
#define TIMx_SR_UIF 0    //!< [1-bit] Update interrupt flag
#define TIMx_SR_CC1IF 1  //!< [1-bit] Capture/compare 1 interrupt flag
#define TIMx_SR_CC2IF 2  //!< [1-bit] [Not in TIM10-11] Capture/compare 2 interrupt flag
#define TIMx_SR_CC3IF 3  //!< [1-bit] [Not in TIM10-11] Capture/compare 3 interrupt flag
#define TIMx_SR_CC4IF 4  //!< [1-bit] [Not in TIM10-11] Capture/compare 4 interrupt flag
#define TIMx_SR_COMIF 5  //!< [1-bit] [TIM1 Only] COM interrupt flag
#define TIMx_SR_TIF 6    //!< [1-bit] [Not in TIM10-11] Trigger interrupt flag
#define TIMx_SR_BIF 7    //!< [1-bit] [TIM1 Only] break interrupt flag
#define TIMx_SR_CC1OF 9  //!< [1-bit] Capture/compare 1 overcapture flag
#define TIMx_SR_CC2OF 10 //!< [1-bit] [Not in TIM10-11] Capture/compare 2 overcapture flag
#define TIMx_SR_CC3OF 11 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 3 overcapture flag
#define TIMx_SR_CC4OF 12 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 4 overcapture flag
/** @} */

/**
 * @name EGR
 * @{
 * @brief Event Generation Register
 */
#define TIMx_EGR_UG 0   //!< [1-bit] Update generation
#define TIMx_EGR_CC1G 1 //!< [1-bit] Capture/compare 1 generation
#define TIMx_EGR_CC2G 2 //!< [1-bit] [Not in TIM10-11] Capture/compare 2 gereration
#define TIMx_EGR_CC3G 3 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 3 generation
#define TIMx_EGR_CC4G 4 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 4 generation
#define TIMx_EGR_COMG 5 //!< [1-bit] [TIM1 Only] Capture/compare control update generation
#define TIMx_EGR_TG 6   //!< [1-bit] [Not in TIM10-11] Trigger generation
#define TIMx_EGR_BG 7   //!< [1-bit] [TIM1 Only] Break generation
/** @} */

/**
 * @name CCMR1
 * @{
 * @brief Capture/Compare Mode Register 1
 * @name OCM
 * @{
 * @brief Output Compare Mode
 */
#define TIMx_CCMR1_OCM_CC1S 0   //!< [2-bit] Capture/compare 1 selection
#define TIMx_CCMR1_OCM_OC1FE 2  //!< [1-bit] Output compare 1 fast enable
#define TIMx_CCMR1_OCM_OC1PE 3  //!< [1-bit] Output Compare 1 preload enable
#define TIMx_CCMR1_OCM_OC1M 4   //!< [3-bit] Ouput compare 1 mode
#define TIMx_CCMR1_OCM_OC1CE 7  //!< [1-bit] [Not in TIM10-11] Output compare 1 clear enable
#define TIMx_CCMR1_OCM_CC2S 8   //!< [2-bit] [Not in TIM10-11] Capture/compare 2 selection
#define TIMx_CCMR1_OCM_OC2FE 10 //!< [1-bit] [Not in TIM10-11] Output compare 2 fast enable
#define TIMx_CCMR1_OCM_OC2PE 11 //!< [1-bit] [Not in TIM10-11] Output compare 2 preload enable
#define TIMx_CCMR1_OCM_OC2M 12  //!< [3-bit] [Not in TIM10-11] Output compare 2 mode
#define TIMx_CCMR1_OCM_OC2CE 15 //!< [1-bit] [Not in TIM10-11] Output compare 2 clear enable
/** @} */

/**
 * @name ICM
 * @{
 * @brief Input Capture Mode
 */
#define TIMx_CCMR1_ICM_CC1S 0    //!< [2-bit] Capture/compare 1 selection
#define TIMx_CCMR1_ICM_IC1PSC 2  //!< [2-bit] Input compare 1 prescaler
#define TIMx_CCMR1_ICM_IC1F 4    //!< [4-bit] Input Compare 1 filter
#define TIMx_CCMR1_ICM_CC2S 8    //!< [2-bit] [Not in TIM10-11] Capture/compare 2 selection
#define TIMx_CCMR1_ICM_IC2PSC 10 //!< [2-bit] [Not in TIM10-11] Input compare 2 prescaler
#define TIMx_CCMR1_ICM_IC2F 12   //!< [4-bit] [Not in TIM10-11] Input compare 2 filter
/** @} */
/** @} */

/**
 * @name CCMR2
 * @{
 * @brief Capture/Compare Mode Register 2
 * @note Not available for TIM9, TIM10 and TIM11
 * @name OCM
 * @{
 */
#define TIMx_CCMR2_OCM_CC3S 0   //!< [2-bit] Capture/compare 3 selection
#define TIMx_CCMR2_OCM_OC3FE 2  //!< [1-bit] Output compare 3 fast enable
#define TIMx_CCMR2_OCM_OC3PE 3  //!< [1-bit] Output compare 3 preload enable
#define TIMx_CCMR2_OCM_OC3M 4   //!< [3-bit] Output compare 3 mode
#define TIMx_CCMR2_OCM_OC3CE 7  //!< [1-bit] Output compare 3 clear enable
#define TIMx_CCMR2_OCM_CC4S 8   //!< [2-bit] Capture/compare 4 selection
#define TIMx_CCMR2_OCM_OC4FE 10 //!< [1-bit] Output compare fast enable
#define TIMx_CCMR2_OCM_OC4PE 11 //!< [1-bit] Output compare Preload enable
#define TIMx_CCMR2_OCM_OC4M 12  //!< [2-bit] Output compare 4 mode
#define TIMx_CCMR2_OCM_OC4CE 15 //!< [1-bit] Output compare clear enable
/** @} */

/**
 * @name ICM
 * @{
 * @brief Input Capture Mode
 */
#define TIMx_CCMR2_ICM_CC3S 0    //!< [1-bit] Capture/compare 3 selection
#define TIMx_CCMR2_ICM_IC3PSC 2  //!< [1-bit] Input capture  prescaler
#define TIMx_CCMR2_ICM_IC3F 4    //!< [1-bit] Input capture 3 filter
#define TIMx_CCMR2_ICM_CC4S 8    //!< [1-bit] Capture/compare 4 selection
#define TIMx_CCMR2_ICM_IC4PSC 10 //!< [1-bit] Input capture 4 prescaler
#define TIMx_CCMR2_ICM_IC4F 12   //!< [1-bit] Input capture 4 filter
/** @} */
/** @} */

/**
 * @name CCER
 * @{
 * @brief Capture/Compare Enable Register
 */
#define TIMx_CCER_CC1E 0   //!< [1-bit] Capture/compare 1 output enable
#define TIMx_CCER_CC1P 1   //!< [1-bit] Capture/compare 1 output polarity
#define TIMx_CCER_CC1NE 2  //!< [1-bit] [TIM1 Only] Capture/compare 1 complementary output enable
#define TIMx_CCER_CC1NP 3  //!< [1-bit] Capture/compare 1 complementary output polarity
#define TIMx_CCER_CC2E 4   //!< [1-bit] [Not in TIM10-11] Capture/compare 2 output enable
#define TIMx_CCER_CC2P 5   //!< [1-bit] [Not in TIM10-11] Capture/compare 2 output polarity
#define TIMx_CCER_CC2NE 6  //!< [1-bit] [TIM1 Only] Capture/compare 2 complementary output enable
#define TIMx_CCER_CC2NP 7  //!< [1-bit] [Not in TIM10-11] Capture/compare 2 complementary output polarity
#define TIMx_CCER_CC3E 8   //!< [1-bit] [Not in TIM9-10-11] Capture/compare 3 output enable
#define TIMx_CCER_CC3P 9   //!< [1-bit] [Not in TIM9-10-11] Capture/compare 3 output polarity
#define TIMx_CCER_CC3NE 10 //!< [1-bit] [TIM1 Only] Capture/compare 3 complementary output enable
#define TIMx_CCER_CC3NP 11 //!< [1-bit] [Not in TIM9-10-11] Capture/compare 3 complementary output polarity
#define TIMx_CCER_CC4E 12  //!< [1-bit] [Not in TIM9-10-11] Capture/compare 4 output enable
#define TIMx_CCER_CC4P 13  //!< [1-bit] [Not in TIM9-10-11] Capture/compare 4 output polarity
#define TIMx_CCER_CC4NP 15 //!< [1-bit] [TIM2-5 Only] Capture/compare 4 complementary output polarity
/** @} */

/**
 * @name BDTR
 * @{
 * @brief Break and Dead-Time Register
 * @note Avaiable for TIM1 only
 */
#define TIMx_BDTR_MOE 15  //!< [1-bit] Main output enable
#define TIMx_BDTR_AOE 14  //!< [1-bit] Automatic output enable
#define TIMx_BDTR_BKP 13  //!< [1-bit] Break polarity
#define TIMx_BDTR_BKE 12  //!< [1-bit] Break enable
#define TIMx_BDTR_OSSR 11 //!< [1-bit] Off-state selection for run ode
#define TIMx_BDTR_OSSI 10 //!< [1-bit] Off-state selection for idle mode
#define TIMx_BDTR_LOCK 8  //!< [2-bit] Lock configuration
#define TIMx_BDTR_DTG 0   //!< [8-bit] Dead-time generator setup
/** @} */

/**
 * @name DCR
 * @{
 * @brief DMA Control Register
 */
#define TIMx_DCR_DBA 0 //!< [5-bit] DMA base address
#define TIMx_DCR_DBL 8 //!< [5-bit] DMA burst length
/** @} */

/**
 * @name OR
 * @{
 * @brief Option Register
 * @note Only available for TIM2, TIM5 and TIM11
 */
#define TIMx_OR_TI1_RMP 0  //!< [2-bit] [TIM11 Only] TIM11 input remapping capability
#define TIMx_OR_ITR1_RMP 6 //!< [2-bit] [TIM5 Only] Timer input 4 remap
#define TIMx_OR_TI4_RMP 10 //!< [2-bit] [TIM2 Only] Internal trigger 1 remap
/** @} */
/** @} */
/** @} */

/** 
 * @addtogroup IWDG
 * @{
 * @name Registers
 * @{
 * @name SR
 * @{
 */
#define IWDG_SR_PVU 0 //!< [1-bit] Watchdog prescaler value update
#define IWDG_SR_RVU 1 //!< [1=bit] Watchdog counter reload update
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup WWDG
 * @{
 * @name Registers
 * @{
 * @name CR
 * @{
 * @brief Control Register
 */
#define WWDG_CR_T 0    //!< [7-bit] 7-bit counter
#define WWDG_CR_WDGA 7 //1< [1-bit] Activation bit
/** @} */

/**
 * @name CFG
 * @{
 * @brief Configuration Register
 */
#define WWDG_CFR_W 0     //!< [7-bit] 7-bit window value
#define WWDG_CFR_WDGTB 7 //!< [2-bit] Timer base
#define WWDG_CFR_EWI 9   //!< [1-bit] Early wakeup interrupt
/** @} */

/**
 * @name SR
 * @{
 * @brief Status Register
 */
#define WWDG_SR_EWIF 0 //!< [1-bit] Early wakeup interrupt flag
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup RTC
 * @{
 * @name Registers
 * @{
 * @name TR
 * @{
 * @brief Time Register
 */
#define RTC_TR_SU 0   //!< [4-bit] Seconds unit in BCD format
#define RTC_TR_ST 4   //!< [3-bit] Seconds tens in BCD format
#define RTC_TR_MNU 8  //!< [4-bit] Minute units in BCD format
#define RTC_TR_MNT 12 //!< [3-bit] Minute tens in BCD format
#define RTC_TR_HU 16  //!< [4-bit] Hour unit in BCD format
#define RTC_TR_HT 20  //!< [2-bit] Hour tens in BCD format
#define RTC_TR_PM 22  //!< [1-bit] AM/PM notation
/** @} */

/**
 * @name DR
 * @{
 * @brief Data Register
 * @{
 */
#define RTC_DR_DU 0   //!< [4-bit] Date units in BCD format
#define RTC_DR_DT 4   //!< [2-bit] Date tens in BCD format
#define RTC_DR_MU 8   //!< [4-bit] Month units in BCD format
#define RTC_DR_MT 12  //!< [1-bit] Month tens in BCD format
#define RTC_DR_WDU 13 //!< [3-bit] Week day units
#define RTC_DR_YU 16  //!< [4-bit] Year units in BCD format
#define RTC_DR_YT 20  //!< [4-bit] Year tens in BCD format
/** @} */

/**
 * @name CR
 * @{
 * @brief Control Register
 */
#define RTC_CR_WUCKSEL 0 //!< [3-bit] Wakeup clock selection
#define RTC_CR_TSEDGE 3  //!< [1-bit] Timestamp event active edge
#define RTC_CR_REFCKON 4 //!< [1-bit] Reference clock detection enable
#define RTC_CR_BYPSHAD 5 //!< [1-bit] Bypass the shadow registers
#define RTC_CR_FMT 6     //!< [1-bit] Hour format
#define RTC_CR_DCE 7     //!< [1-bit] Coarse digital calibration enable
#define RTC_CR_ALRAE 8   //!< [1-bit] Alarm A enable
#define RTC_CR_ALRBE 9   //!< [1-bit] Alarm B enable
#define RTC_CR_WUTE 10   //!< [1-bit] Wakeup timer enable
#define RTC_CR_TSE 11    //!< [1-bit] Time stamp enable
#define RTC_CR_ALRAIE 12 //!< [1-bit] Alarm A interrupt enable
#define RTC_CR_ALRBIE 13 //!< [1-bit] Alarm B interrutp enable
#define RTC_CR_WUTIE 14  //!< [1-bit] Wakeup timer interrupt enable
#define RTC_CR_TSIE 15   //!< [1-bit] Timestamp interrupt enable
#define RTC_CR_ADD1H 16  //!< [1-bit] Add 1 hour (summer time change)
#define RTC_CR_SUB1H 17  //!< [1-bit] Substract 1 hour (winter time change)
#define RTC_CR_BKP 18    //!< [1-bit] Backup
#define RTC_CR_COSEL 19  //!< [1-bit] Calibration putput selection
#define RTC_CR_POL 20    //!< [1-bit] Output polarity
#define RTC_CR_OSEL 21   //!< [2-bit] Output selection
#define RTC_CR_COE 23    //!< [1-bit] Calibration output enable
/** @} */

/**
 * @name ISR
 * @{
 * @brief Initialization and Status Register
 */
#define RTC_ISR_ALRAWF 0   //!< [1-bit] Alarm A write flag
#define RTC_ISR_ALRBWF 1   //!< [1-bit] Alarm B write flag
#define RTC_ISR_WUTWF 2    //!< [1-bit] Wakeup timer write flag
#define RTC_ISR_SHPF 3     //!< [1-bit] Shift operation pending
#define RTC_ISR_INITS 4    //!< [1-bit] Initialization status flag
#define RTC_ISR_RSF 5      //!< [1-bit] Registers synchronization flag
#define RTC_ISR_INITF 6    //!< [1-bit] Initialization flag
#define RTC_ISR_INIT 7     //!< [1-bit] Initialization mode
#define RTC_ISR_ALRAF 8    //!< [1-bit] Alarm A flag
#define RTC_ISR_ALRBG 9    //!< [1-bit] Alarm B flag
#define RTC_ISR_WUTF 10    //!< [1-bit] Wakeup timer flag
#define RTC_ISR_TSF 11     //!< [1-bit] Timesatamp flag
#define RTC_ISR_TSOVF 12   //!< [1-bit] Timestamp overflow flag
#define RTC_ISR_TAMP1F 13  //!< [1-bit] Tamper detection flag
#define RTC_ISR_RECALPF 16 //!< [1-bit] Recalibration pending flag
/** @} */

/**
 * @name PRER
 * @{
 * @brief Prescaler Register
 */
#define RTC_PRER_PREDIV_S 0  //!< [15-bit] Synchronous prescaler factor
#define RTC_PRER_PREDIV_A 16 //!< [7-bit] Asynchronous prescale factor
/** @} */

/**
 * @name CALIBR
 * @{
 * @brief Calibration Register
 */
#define RTC_CALIBR_DC 0  //!< [5-bit] Digital calibration
#define RTC_CALIBR_DCS 7 //!< [1-bit] Digital calibration sign
/** @} */

/**
 * @name ALRMXR
 * @{
 * @brief Alarm X Register
 */
#define RCT_ALRMxR_SU 0     //!< [4-bit] Second units in BCD format
#define RTC_ALRMxR_ST 4     //!< [3-bit] Second tens in BCD format
#define RTC_ALRMxR_MSK1 7   //!< [1-bit] Alarm A seconds mask
#define RTC_ALRMxR_MNU 8    //!< [4-bit] Minute units un BCD format
#define RTC_ALRMxR_MNT 12   //!< [3-bit] Minute tens in BCD format
#define RTC_ALRMxR_MSK2 15  //!< [1-bit] Alarm A minutes mask
#define RTC_ALRMxR_HU 16    //!< [4-bit] Hour units in BCD format
#define RTC_ALRMxR_HT 20    //!< [2-bit] Hour tesn in BCD format
#define RTC_ALRMxR_PM 22    //!< [1-bit] AM/PM Notation
#define RTC_ALRMxR_MSK3 23  //!< [1-bit] Alarm A hours mask
#define RTC_ALRMxR_DU 24    //!< [4-bit] Date units or day in BCD format
#define RTC_ALRMxR_DT 28    //!< [2-bit] Date tesns in BCD format
#define RTC_ALRMxR_WDSEL 30 //!< [1-bit] Week day selection
#define RTC_ALRMxR_MSK4 31  //!< [1-bit] Alarm A date mask
/** @} */

/**
 * @name SHIFTR
 * @{
 * @brief Shift Control Register
 */
#define RTC_SHIFTR_SUBFS 0  //!< [15-bit] Substract fraction of a second
#define RTC_SHIFTR_ADD1S 31 //!< [1-bit] Add one second
/** @} */

/**
 * @name TSTR
 * @{
 * @brief Time Stamp Time Register
 */
#define RTC_TSTR_SU 0   //!< [4-bit] Second units in BCD format
#define RTC_TSTR_ST 4   //!< [3-bit] Second tens in BCD format
#define RTC_TSTR_MNU 8  //!< [4-bit] Minute units in BCD format
#define RTC_TSTR_MNT 12 //!< [3-bit] Minut tens in BCD format
#define RTC_TSTR_HU 16  //!< [4-bit] Hour units in BCD format
#define RTC_TSTR_HT 20  //!< [2-bit] Hour tens in BCD format
#define RTC_TSTR_PM 22  //!< [1-bit] AM/PM notation
/** @} */

/**
 * @name TSDR
 * @{
 * @brief Time Stamp Date Register
 */
#define RTC_TSDR_DU 0   //!< [4-bit] Date units in BCD format
#define RTC_TSDR_DT 4   //!< [2-bit] Date tens in BCD format
#define RTC_TSDR_MU 8   //!< [4-bit] Month units in BCD format
#define RTC_TSDR_MT 12  //!< [1-bit] Month tens in BCD format
#define RTC_TSDR_WDU 13 //!< [3-bit] Week day units
/** @} */

/**
 * @name TSSSR
 * @{
 * @brief Calibration Register
 */
#define RTC_CALM_CAML 0    //!< [9-bit] Calibration minus
#define RTC_CALM_CALW16 13 //!< [1-bit] Use a 16-second calibration cycle period
#define RTC_CALM_CALW8 14  //!< [1-bit] Use an 8-second calibration cycle period
#define RTC_CALM_CALP 15   //!< [1-bit] Increase frequency of RTC by 488.5 ppm
/** @} */

/**
 * @name TAFCR
 * @{
 * @brief Tamper and Alternate Function Configuration Register
 */
#define RTC_TAFCT_TAMP1E 0        //!< [1-bit] Tamper 1 detection enable
#define RTC_TAFCT_TAMP1TRG 1      //!< [1-bit] Active level for tamper 1
#define RTC_TAFCT_TAMPIE 2        //!< [1-bit] Tamper interrupt enable
#define RTC_TAFCT_TAMPTS 7        //!< [1-bit] Activate timestamp on tamper detection event
#define RTC_TAFCT_TAMPFREQ 8      //!< [3-bit] Tamper sampling frequency
#define RTC_TAFCT_TAMPFLT 11      //!< [2-bit] Tamper filter count
#define RTC_TAFCT_TAMPPRCH 13     //!< [2-bit] Tamper precharge duration
#define RTC_TAFCT_TAMPPUDIS 15    //!< [1-bit] TAMPER pull-up disable
#define RTC_TAFCT_TAMP1INSEL 16   //!< [1-bit] TAMPER1 mapping
#define RTC_TAFCT_TSINSEL 17      //!< [1-bit] TIMESTAMP mapping
#define RTC_TAFCT_ALARMOUTTYPE 18 //!< [1-bit] RTC_ALARM output type
/** @} */

/**
 * @name ALRMXSSR
 * @{
 * @brief Alarm X Sub-Second Register
 */
#define RTC_ALRMxSSR_SS 0      //!< [15-bit] Sub second value
#define RTC_ALRMxSSR_MASKSS 24 //!< [4-bit] Mask the most significant bits starting at this bit
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup SPI_I2S
 * @{
 * @name Registers
 * @{
 * @name CR1
 * @{
 * @brief Control Register 1
 */
#define SPI_CR1_CPHA 0      //!< [1-bit] Clock Phase
#define SPI_CR1_CPOL 1      //!< [1-bit] Clock polarity
#define SPI_CR1_MSTR 2      //!< [1-bit] Master selection
#define SPI_CR1_BR 3        //!< [1-bit] Baud rate control
#define SPI_CR1_SPE 6       //!< [1-bit] SPI Enable
#define SPI_CR1_LSBFIRST 7  //!< [1-bit] Frame format
#define SPI_CR1_SSI 8       //!< [1-bit] Internal Slave Select
#define SPI_CR1_SSM 9       //!< [1-bit] Software Slave Management
#define SPI_CR1_RXONLY 10   //!< [1-bit] Receive Only
#define SPI_CR1_DFF 11      //!< [1-bit] Data frame format
#define SPI_CR1_CRCNEXT 12  //!< [1-bit] CRC transfer next
#define SPI_CR1_CRCEN 13    //!< [1-bit] Hardware CRC calculation enable
#define SPI_CR1_BIDIOE 14   //!< [1-bit] Output enable in bidirectional mode
#define SPI_CR1_BIDIMODE 15 //!< [1-bit] Bidirectional data mode enable
/** @} */

/**
 * @name CR2
 * @{
 * @brief Control Register 2
 */
#define SPI_I2S_I2S_CR2_RXDMAEN 0 //!< [1-bit] RX buffer DMA enable
#define SPI_I2S_CR2_TXDMAEN 1     //!< [1-bit] TX buffer DMA enable
#define SPI_I2S_CR2_SSOE 2        //!< [1-bit] SS output enable
#define SPI_I2S_CR2_FRF 4         //!< [1-bit] Frame Format
#define SPI_I2S_CR2_ERRIE 5       //!< [1-bit] Error interrupt enable
#define SPI_I2S_CR2_RXNEIE 6      //!< [1-bit] RX buffer not empty interrupt enable
#define SPI_I2S_CR2_TXEIE 7       //!< [1-bit] TX buffer empty interrupt enable
/** @} */

/**
 * @name SR
 * @{
 * @brief Status Register
 */
#define SPI_I2S_SR_RXNE 0   //!< [1-bit] RX buffer not empty
#define SPI_I2S_SR_TXE 1    //!< [1-bit] Tx buffer empty
#define SPI_I2S_SR_CHSIDE 2 //!< [1-bit] Channel Side
#define SPI_I2S_SR_UDR 3    //!< [1-bit] Underrun flag
#define SPI_I2S_SR_CRCERR 4 //!< [1-bit] CRC error flag
#define SPI_I2S_SR_MODF 5   //!< [1-bit] Mode fault
#define SPI_I2S_SR_OVR 6    //!< [1-bit] Overrun flag
#define SPI_I2S_SR_BSY 7    //!< [1-bit] Busy flag
#define SPI_I2S_SR_FRE 8    //!< [1-bit] Frame format error
/** @} */

/**
 * @name I2SCFGR
 * @{
 * @brief I2S Configuration Register
 */
#define SPI_I2S_I2SCFGR_CHLEN 0   //!< [1-bit] Channel length (bits per audio channel)
#define SPI_I2S_I2SCFGR_DATLEN 1  //!< [2-bit] Data length to be transfered
#define SPI_I2S_I2SCFGR_CKPOL 3   //!< [1-bit] Steady state clock polarity
#define SPI_I2S_I2SCFGR_I2SSTD 4  //!< [2-bit] I2S standard selection
#define SPI_I2S_I2SCFGR_PCMSYNC 7 //!< [1-bit] PCM frame synchronization
#define SPI_I2S_I2SCFGR_I2SCFG 8  //!< [2-bit] I2S configuration mode
#define SPI_I2S_I2SCFGR_I2SE 10   //!< [1-bit] I2S enable
#define SPI_I2S_I2SCFGR_I2SMOD 11 //!< [1-bit] I2S mode selection
/** @} */

/**
 * @name I2SPR
 * @{
 * @brief I2S Prescaler Register
 */
#define SPI_I2S_I2SPR_I2SDIV 0 //!< [8-bit] I2S linear prescaler
#define SPI_I2S_I2SPR_ODD 8    //!< [1-bit] Odd factor for the prescaler
#define SPI_I2S_I2SPR_MCKOE 9  //!< [1-bit] Master clock output enable
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup I2C
 * @{
 * @name Registers
 * @{
 * @name CR1
 * @{
 * @brief Control Register 1
 */
#define I2C_CR1_PE 0        //!< [1-bit] Peripheral enable
#define I2C_CR1_SMBUS 1     //!< [1-bit] SMBus mode
#define I2C_CR1_SMBTYPE 3   //!< [1-bit] SMBus type
#define I2C_CR1_ENARP 4     //!< [1-bit] APR enable
#define I2C_CR1_ENPEC 5     //!< [1-bit] PEC enable
#define I2C_CR1_ENGC 6      //!< [1-bit] General call enable
#define I2C_CR1_NOSTRETCH 7 //!< [1-bit] Clock stretching disable
#define I2C_CR1_START 8     //!< [1-bit] Start generation
#define I2C_CR1_STOP 9      //!< [1-bit] Stop generation
#define I2C_CR1_ACK 10      //!< [1-bit] Acknowledge enable
#define I2C_CR1_POS 11      //!< [1-bit] Acknowledge/PEC position
#define I2C_CR1_PEC 12      //!< [1-bit] Packet error checking
#define I2C_CR1_ALERT 13    //!< [1-bit] SMBus alert
#define I2C_CR1_SWRST 15    //!< [1-bit] Software reset
/** @} */

/**
 * @name CR2
 * @{
 * @brief Control Register 2
 */
#define I2C_CR2_FREQ 0     //!< [6-bit] Peripheral clock frequency
#define I2C_CR2_ITERREN 8  //!< [1-bit] Error interrupt enable
#define I2C_CR2_ITEVTEN 9  //!< [1-bit] Event interrupt enable
#define I2C_CR2_ITBUFEN 10 //!< [1-bit] Buffer interrupt enable
#define I2C_CR2_DMAEN 11   //!< [1-bit] DMA request enable
#define I2C_CR2_LAST 12    //!< [1-bit] DMA last transfer
/** @} */

/**
 * @name QAR1
 * @{
 * @brief Own Address Register 1
 */
#define I2C_OAR1_ADD0 0     //!< [1-bit] Interface address
#define I2C_OAR1_ADD71 1    //!< [7-bit] Interface address
#define I2C_OAR1_ADD98 8    //!< [2-bit] Interface address
#define I2C_OAR1_KEEP1 14   //!< [1-bit] Always set this bit
#define I2C_OAR1_ADDMODE 15 //!< [1-bit] Addressing mode
/** @} */

/**
 * @name OAR2
 * @{
 * @brief Own Address Register 2
 */
#define I2C_OAR2_ENDUAL 0 //!< [1-bit] Dual addressing mode enable
#define I2C_OAR2_ADD2 1   //!< [7-bit] Interface address
/** @} */

/**
 * @name DR
 * @{
 * @brief Data Register
 */
#define I2C_DR_DR 0 //!< [8-bit] 8-bit data register
/** @} */

/**
 * @name SR1
 * @{
 * @brief Status Register 1
 */
#define I2C_SR1_SB 0        //!< [1-bit] Start bit
#define I2C_SR1_ADDR 1      //!< [1-bit] Address sent
#define I2C_SR1_BTF 2       //!< [1-bit] Byte transfer finished
#define I2C_SR1_ADD10 3     //!< [1-bit] 10-bit header sent
#define I2C_SR1_STOPF 4     //!< [1-bit] Stop detection
#define I2C_SR1_RXNE 6      //!< [1-bit] Data register not empty
#define I2C_SR1_TXE 7       //!< [1-bit] Data register empty
#define I2C_SR1_BERR 8      //!< [1-bit] Bus error
#define I2C_SR1_ARLO 9      //!< [1-bit] Arbitration lost
#define I2C_SR1_AF 10       //!< [1-bit] Acknowledge failure
#define I2C_SR1_OVR 11      //!< [1-bit] Overrun/Underrun
#define I2C_SR1_PECERR 12   //!< [1-bit] PEC error in reception
#define I2C_SR1_TIMEOUT 14  //!< [1-bit] Timeout or TIow error
#define I2C_SR1_SMBALERT 15 //!< [1-bit] SMBus alert
/** @} */

/**
 * @name SR2
 * @{
 * @brief Status Register 2
 */
#define I2C_SR2_MSL 0        //!< [1-bit] Master/Slave
#define I2C_SR2_BUSY 1       //!< [1-bit] Bus busy
#define I2C_SR2_TRA 2        //!< [1-bit] Transmitter/Receiver
#define I2C_SR2_GENCALL 4    //!< [1-bit] General call address (Slave mode)
#define I2C_SR2_SMBDEFAULT 5 //!< [1-bit] SMBus device default address
#define I2C_SR2_DUALF 7      //!< [1-bit] Dual flag
#define I2C_SR2_PEC 8        //!< [8-bit] Packet error checking register
/** @} */

/**
 * @name CCR
 * @{
 * @brief Clock Control Register
 */
#define I2C_CCR_CCR 0   //!< [12-bit] Clock conrol register in Fm/Sm mode
#define I2C_CCR_DUTY 14 //!< [1-bit] Fm mode duty cycle
#define I2C_CCR_FS 15   //!< [1-bit] I2C master mode selection
/** @} */

/**
 * @name TRISE
 * @{
 * @brief TRISE Register
 */
#define I2C_TRISE_TRISE 0 //!< [6-bit] Maximum rise time in Fm/Sm mode
/** @} */

/**
 * @name FLTR
 * @{
 * @brief FLTR Register
 */
#define I2C_FLTR_DNF 0   //!< [4-bit] Digital noise filter
#define I2C_FLTR_ANOFF 4 //!< [1-bit] Analog noise filter off
/** @} */
/** @} */
/** @} */

/**
 * @addtogroup USART
 * @{
 * @name Registers
 * @{
 * @name SR
 * @{
 * @brief Status Register
 */
#define USART_SR_PE 0   //!< [1-bit] Parity error
#define USART_SR_FE 1   //!< [1-bit] Framing error
#define USART_SR_NF 2   //!< [1-bit] Noise detected flag
#define USART_SR_ORE 3  //!< [1-bit] Overrun error
#define USART_SR_IDLE 4 //!< [1-bit] IDLE line detected
#define USART_SR_RXNE 5 //!< [1-bit] Read data register not empty
#define USART_SR_TC 6   //!< [1-bit] Transmission complete
#define USART_SR_TXE 7  //!< [1-bit] Transmit data register empty
#define USART_SR_LBD 8  //!< [1-bit] LIN break detection flag
#define USART_SR_CTS 9  //!< [1-bit] CTS flag
/** @} */

/**
 * @name CR1
 * @{
 * @brief Control Register 1
 */
#define USART_CR1_SBK 0    //!< [1-bit] Send break
#define USART_CR1_RWU 1    //!< [1-bit] Receiver wakeup
#define USART_CR1_RE 2     //!< [1-bit] Receiver enable
#define USART_CR1_TE 3     //!< [1-bit] Transmitter enable
#define USART_CR1_IDLEIE 4 //!< [1-bit] IDLE interrupt enable
#define USART_CR1_RXNEIE 5 //!< [1-bit] RXNE interrupt enable
#define USART_CR1_TCIE 6   //!< [1-bit] Transmission complete interrupt enable
#define USART_CR1_TXEIE 7  //!< [1-bit] TXE interrupt enable
#define USART_CR1_PEIE 8   //!< [1-bit] PE interrupt enable
#define USART_CR1_PS 9     //!< [1-bit] Parity selection
#define USART_CR1_PCE 10   //!< [1-bit] Parity control enable
#define USART_CR1_WAKE 11  //!< [1-bit] Wakeup method
#define USART_CR1_M 12     //!< [1-bit] Word length
#define USART_CR1_UE 13    //!< [1-bit] USART enable
#define USART_CR1_OVER8 15 //!< [1-bit] Oversampling mode
/** @} */

/**
 * @name CR2
 * @{
 * @brief Control Register 2
 */
#define USART_CR2_ADD 0    //!< [1-bit] LIN break detection length
#define USART_CR2_LBDL 5   //!< [1-bit] LIN break detection interrupt enable
#define USART_CR2_LBDIE 6  //!< [1-bit] Last bit clock pulse
#define USART_CR2_LBCL 8   //!< [1-bit] Last bit clock pulse
#define USART_CR2_CPHA 9   //!< [1-bit] Clock phase
#define USART_CR2_CPOL 10  //!< [1-bit] Clock polarity
#define USART_CR2_CLKEN 11 //!< [1-bit] Clock enable
#define USART_CR2_STOP 12  //!< [1-bit] STOP bits
#define USART_CR2_LINEN 14 //!< [1-bit] LIN mode enable
/** @} */

/**
 * @name CR3
 * @{
 * @brief Control Register 3
 */
#define USART_CR3_EIE 0     //!< [1-bit] Error interrupt enable
#define USART_CR3_IREN 1    //!< [1-bit] IrDA mode enable
#define USART_CR3_IRLP 2    //!< [1-bit] IrDA low-power
#define USART_CR3_HDSEL 3   //!< [1-bit] Half-duplex selection
#define USART_CR3_NACK 4    //!< [1-bit] Smartcard NACK enable
#define USART_CR3_SCEN 5    //!< [1-bit] Smartcard mode enable
#define USART_CR3_DMAR 6    //!< [1-bit] DMA enable receiver
#define USART_CR3_DMAT 7    //!< [1-bit] DMA enable transmitter
#define USART_CR3_RTSE 8    //!< [1-bit] RTS enable
#define USART_CR3_CTSE 9    //!< [1-bit] CTS enable
#define USART_CR3_CTSIE 10  //!< [1-bit] CTS interrupt enable
#define USART_CR3_ONEBIT 11 //!< [1-bit] One bit sample method enable
/** @} */

/**
 * @name GTPR
 * @{
 * @brief Guard Time and Prescaler Register
 */
#define USART_GTPR_PSC 0 //!< [8-bit] Prescaler value
#define USART_GTPR_FT 8  //!< [8-bit] Guard time value
/** @} */
/** @} */
/** @} */

#endif
