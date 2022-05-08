#ifndef __STM32F401XX_RCC__
#define __STM32F401XX_RCC__

#include "stm32f401re.h"

#define HSI_FREQ 8000000  //!< Internal clock frequency (Hz)
#define HSE_FREQ 16000000 //!< External clock frequency (Hz)

typedef enum
{
    SYSTEM_CLOCK_SWITCH_HSI = 0,
    SYSTEM_CLOCK_SWITCH_HSE,
    SYSTEM_CLOCK_SWITCH_PLL
} SYSTEM_CLOCK_SWITCH;

SYSTEM_CLOCK_SWITCH RCC_get_systemclock_switch();
uint32_t RCC_get_systemclock_freq();
uint32_t RCC_get_ahb_freq();
uint32_t RCC_get_apb1_freq();

#endif
