#ifndef __CORTEX_M4_H__
#define __CORTEX_M4_H__

#include <stdint.h>

typedef volatile uint32_t Register; // Typedef for peripherial registers

/**
 * @defgroup CORTEX_M4 Cortex-M4
 * @brief 		ARM Cortex-M4 related objects
 * @details		This section contains all the objects related to the Cortex-M4
 * 				architecture.
 * @{
 */

/**
 * @defgroup 	NVIC Nested Vector Interrupt Controller
 * @brief		ARM Cortex-M4 Processor NVIC
 * @details		The Nested Vector Interrupt Controller (NVIC) provides an interface
 * between interrupt sources external to the core (peripherals and external
 * pins) and the core.
 *
 * 				The priority for each interrupt source is programmable. If two
 * 				pending interrupts share the same priority, priority is given to the
 * interrupt with the lowest exception number (lowest interrupt vector address).
 *
 * 				The NVIC supports up to 240 interrupts each with up to 256 levels
 * of priority. You can change the priority of an interrupt dynamically. The
 * NVIC and the processor core interface are closely coupled, to enable low
 * latency interrupt processing and efficient processing of late arriving
 * interrupts. The NVIC maintains knowledge of the stacked, or nested,
 * interrupts to enable tail-chaining of interrupts.
 * @note		You can only fully access the NVIC from privileged mode, but you can
 * cause interrupts to enter a pending state in user mode if you enable the
 * Configuration Control Register. Any other user mode access causes a bus
 * fault.
 * @note 		You can access all NVIC registers using byte, halfword, and word
 * accesses unless otherwise stated. NVIC registers are located within the SCS.
 * @note		All NVIC registers and system debug registers are little-endian
 * regardless of the endianness state of the processor.
 * @{
 */

/**
 * @defgroup	ISER ISER
 * @brief		Interrupt Set-Enable Register group
 * @details		The ISER register enable interrupts,  and show which interrupts are
 * enabled. 
 * | Bit Number | Name | Description | Access | 
 * | --- | --- | --- | ---| 
 * | 31:0 | SETENA | Interrupt set-enable bits | rw |
 * @{
 */
#define NVIC_ISER0 ((Register *)0xE000E100)
#define NVIC_ISER1 ((Register *)0xE000E104)
#define NVIC_ISER2 ((Register *)0xE000E108)
#define NVIC_ISER3 ((Register *)0xE000E10C)
#define NVIC_ISER4 ((Register *)0xE000E110)
#define NVIC_ISER5 ((Register *)0xE000E114)
#define NVIC_ISER6 ((Register *)0xE000E118)
#define NVIC_ISER7 ((Register *)0xE000E11C)

/**
 * @}
 * @defgroup 	ICER ICER
 * @brief		Interrupt Clear-Enable Register group
 * @details		The ICER registers disable interrupts, and show which interrupts
 * are enabled. 
 * | Bit Number | Name | Description | Access | 
 * | --- | --- | --- | --- | 
 * | 31:0 | CLRENA | Interrupt clear-enable bits | rw |
 * @{
 */
#define NVIC_ICER0 ((Register *)0xE000E180)
#define NVIC_ICER1 ((Register *)0xE000E184)
#define NVIC_ICER2 ((Register *)0xE000E188)
#define NVIC_ICER3 ((Register *)0xE000E18C)
#define NVIC_ICER4 ((Register *)0xE000E190)
#define NVIC_ICER5 ((Register *)0xE000E194)
#define NVIC_ICER6 ((Register *)0xE000E198)
#define NVIC_ICER7 ((Register *)0xE000E19C)

/**
 * @}
 * @defgroup	ISPR ISPR
 * @brief		Interrupt Set-Pending Register group
 * @details		The ISPR registers force interrupts into the pending state, and
 * show which interrupts are pending. 
 * | Bit Number | Name | Description | Access | 
 * | --- | --- | --- | --- | 
 * | 31:0 | SETPEND | Interrupt clear-pending bits | rw |
 * @{
 */
#define NVIC_ISPR0 ((Register *)0xE000E200)
#define NVIC_ISPR1 ((Register *)0xE000E204)
#define NVIC_ISPR2 ((Register *)0xE000E208)
#define NVIC_ISPR3 ((Register *)0xE000E20C)
#define NVIC_ISPR4 ((Register *)0xE000E210)
#define NVIC_ISPR5 ((Register *)0xE000E214)
#define NVIC_ISPR6 ((Register *)0xE000E218)
#define NVIC_ISPR7 ((Register *)0xE000E21C)

/**
 * @}
 * @defgroup	ICPR ICPR
 * @brief		Interrupt Clear-Pending Register group
 * @details		The ICPR registers remove the pending state from interrupts, and
 * 				show which interrupts are pending.
 * 				| Bit Number | Name | Description | Access |
 * 				| --- | --- | --- | --- |
 * 				| 31:0 | CLRPEND | Interrupt set-pending bits | rw |
 * @{
 */
#define NVIC_ICPR0 ((Register *)0xE000E280)
#define NVIC_ICPR1 ((Register *)0xE000E284)
#define NVIC_ICPR2 ((Register *)0xE000E288)
#define NVIC_ICPR3 ((Register *)0xE000E28C)
#define NVIC_ICPR4 ((Register *)0xE000E290)
#define NVIC_ICPR5 ((Register *)0xE000E294)
#define NVIC_ICPR6 ((Register *)0xE000E298)
#define NVIC_ICPR7 ((Register *)0xE000E29C)

/**
 * @}
 * @defgroup	IABR IABR
 * @brief		Interrupt Active Bit Register group
 * @details		The IABR registers remove the pending state from interrupts, and
 * 				show which interrupts are pending.
 * 				| Bit Number | Name | Description | Access |
 * 				| --- | --- | --- | --- |
 * 				| 31:0 | ACTIVE | Interrupt active flag | r |
 * @{
 */
#define NVIC_IABR0 ((Register *)0xE000E300)
#define NVIC_IABR1 ((Register *)0xE000E304)
#define NVIC_IABR2 ((Register *)0xE000E308)
#define NVIC_IABR3 ((Register *)0xE000E30C)
#define NVIC_IABR4 ((Register *)0xE000E310)
#define NVIC_IABR5 ((Register *)0xE000E314)
#define NVIC_IABR6 ((Register *)0xE000E318)
#define NVIC_IABR7 ((Register *)0xE000E31C)

/**
 * @}
 * @defgroup	IPR IPR
 * @brief		Interrupt Priority Register
 * @details		The IPR registers provide an 8-bit priority field for each
 *interrupt and each register holds four priority fields. These registers are
 *byte-accessible. 
 * | Bit Number | Name | Description | Access | 
 * | --- | --- | --- | --- | 
 * | 31:24 | PRI_(N+3) | Priority level, offset 3 | rw | 
 * | 23:16 | PRI_(N+2) | Priority level, offset 2 | rw | 
 * | 15:8  | PRI_(N+1) | Priority level, offset 1 | rw | 
 * | 7:0   | PRI_N | Priority level, offset 0 | rw |
 *
 * @note		Only the base address of the IPR0 register is given. Use the formula
 *to set a priority number to any IPR register.
 * @code{.c}
 * void setPriority(uint8_t IRQNumber, uint8_t IRQPriority)
 * {
 *  uint8_t iprx = IRQNumber / 4;
 *  uint8_t iprx_section = IRQNumber % 4;
 *  uint8_t ShiftAmmount = 8 * iprx_section + 8 - CORTEX_NO_PR_BITS;
 *  *(NVIC_IPR + iprx) |= IRQPriority << ShiftAmmount;
 * }
 * @endcode
 *
 * @{
 */
#define NVIC_IPR ((Register *)0xE000E400)
#define CORTEX_NO_PR_BITS 4 //!< IRQ interrupts in each IPR register

/**
 * @}
 * @defgroup	STIR STIR
 * @brief		Software Triggered Interrupt Register
 * @details		Write to the STIR to generate an interrupt from software.
 * 				| Bit Number | Name | Description | Access |
 * 				| --- | --- | --- | --- |
 * 				| 31:9 | - | Reserved | - |
 * 				| 0:8 | INTID | Interrupt ID from the interrupt to trigger | w |
 * @note		Only privileged software can enable unprivileged access to the
 * STIR.
 * @{
 */
#define NVIC_STIR                                                              \
    ((Register *)0xE000EF00) //!< NVIC Software Triggered Interrupt Register

/**
 * @}
 * @}
 * @}
 */

/**
 * @addtogroup		NVIC
 * @{
 * @name			NVIC IRQ Number Definitions
 * @{
 * @brief 			IRQ Numbers
 */
#define IRQ_NO_WWDG 0
#define IRQ_NO_PVD 1
#define IRQ_NO_TAMP_STAMP 2
#define IRQ_NO_RTC_WKUP 3
#define IRQ_NO_FLASH 4
#define IRQ_NO_RCC 5
#define IRQ_NO_EXTI0 6
#define IRQ_NO_EXTI1 7
#define IRQ_NO_EXTI2 8
#define IRQ_NO_EXTI3 9
#define IRQ_NO_EXTI4 10
#define IRQ_NO_DMA1_STREAM0 11
#define IRQ_NO_DMA1_STREAM1 12
#define IRQ_NO_DMA1_STREAM2 13
#define IRQ_NO_DMA1_STREAM3 14
#define IRQ_NO_DMA1_STREAM4 15
#define IRQ_NO_DMA1_STREAM5 16
#define IRQ_NO_DMA1_STREAM6 17
#define IRQ_NO_ADC 18
#define IRQ_NO_EXTI9_5 23
#define IRQ_NO_TIM1_BRK_TIM9 24
#define IRQ_NO_TIM1_UP_TIM10 25
#define IRQ_NO_TIM1_TRG_COM_TIM11 26
#define IRQ_NO_TIM1_CC 27
#define IRQ_NO_TIM2 28
#define IRQ_NO_TIM3 29
#define IRQ_NO_TIM4 30
#define IRQ_NO_I2C1_EV 31
#define IRQ_NO_I2C1_ER 32
#define IRQ_NO_I2C2_EV 33
#define IRQ_NO_I2C2_ER 34
#define IRQ_NO_SPI1 35
#define IRQ_NO_SPI2 36
#define IRQ_NO_USART1 37
#define IRQ_NO_USART2 38
#define IRQ_NO_EXTI15_10 40
#define IRQ_NO_RTC_ALARM 41
#define IRQ_NO_OTG_FS_WKUP 42
#define IRQ_NO_DMA1_STREAM7 47
#define IRQ_NO_SDIO 49
#define IRQ_NO_TIM5 50
#define IRQ_NO_SPI3 51
#define IRQ_NO_DMA2_STREAM0 56
#define IRQ_NO_DMA2_STREAM1 57
#define IRQ_NO_DMA2_STREAM2 58
#define IRQ_NO_DMA2_STREAM3 59
#define IRQ_NO_DMA2_STREAM4 60
#define IRQ_NO_OTG_FS 67
#define IRQ_NO_DMA2_STREAM5 68
#define IRQ_NO_DMA2_STREAM6 69
#define IRQ_NO_DMA2_STREAM7 70
#define IRQ_NO_USART6 71
#define IRQ_NO_I2C3_EV 72
#define IRQ_NO_I2C3_ER 73
#define IRQ_NO_FPU 81
#define IRQ_NO_SPI4 84

#define IRQ_NO_EXTI16 IRQ_NO_PVD
#define IRQ_NO_EXTI17 IRQ_NO_RTC_ALARM
#define IRQ_NO_EXTI18 IRQ_NO_OTG_FS_WKUP
#define IRQ_NO_EXTI21 IRQ_NO_TAMP_STAMP
#define IRQ_NO_EXTI22 IRQ_NO_RTC_WKUP
/**
 * @}
 * @}
 */

/**
 * @brief		Enables/Disables the given IRQ Number
 * @param[in]	irq_number GPIO port base address
 * @param[in]	status IRQ status to write
 * @return		None
 */
void NVIC_IRQ_Interrupt_Config(uint8_t irq_number, uint8_t status);

/**
 * @brief		Sets a priority to given IRQ Number
 * @param[in]	irq_number IRQ Number. See @NVIC_CORTEX
 * @param[in]	irq_priority IRQ Priority (0 - 15)
 * @return		None
 */
void NVIC_IRQ_Priority_Config(uint8_t irq_number, uint8_t irq_priority);

#endif