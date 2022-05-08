#include "stm32f401-rcc.h"

/**
 * @brief APB clock prescaler values
 */
const uint8_t RCC_APB_PRESCALER_DIV[] = {2, 4, 8, 16};

/**
 * @brief AHB clock prescaler values
 */
const uint16_t RCC_AHB_PRESCALER_DIV[] = {2, 4, 8, 16, 64, 128, 256, 512};

SYSTEM_CLOCK_SWITCH RCC_get_systemclock_switch()
{
    return (RCC->CFGR >> RCC_CFGR_SWS) & 0b11;
}

uint32_t RCC_get_systemclock_freq()
{
    uint32_t freq;
    
    // Get the source clock from the system clock switch
    SYSTEM_CLOCK_SWITCH clock_source = RCC_get_systemclock_switch();

    switch (clock_source)
    {
    case SYSTEM_CLOCK_SWITCH_HSE:
        // External clock
        freq = HSE_FREQ;
        break;
    case SYSTEM_CLOCK_SWITCH_HSI:
        // Internal 8 MHz clock
        freq = HSI_FREQ;
        break;
    case SYSTEM_CLOCK_SWITCH_PLL:
        // Phased-Locked Loop clock
        // TODO: IMPLEMENT get_pll_freq
        freq = -1;
        break;
    }

    return freq;
}

uint32_t RCC_get_ahb_freq()
{
    uint32_t freq;

    // Get the system clock frequency
    uint32_t systemclock_freq = RCC_get_systemclock_freq();

    // Get the AHB prescaler value
    uint8_t ahb1_prescaler_bits = (RCC->CFGR >> RCC_CFGR_HPRE) & 0b111;

    // Check if the prescaler is enabled
    uint8_t ahb1_prescaler_enable = RCC->CFGR >> (RCC_CFGR_HPRE + 3) & 0b1;

    if (ahb1_prescaler_enable)
    {
        // If the prescaler is enabled, apply the prescaler decimation
        uint16_t prescaler = RCC_AHB_PRESCALER_DIV[ahb1_prescaler_bits];
        freq = systemclock_freq / prescaler;
    }
    else
    {
        // If the prescaer is disabled, the AHB clock stays as the system clock
        freq = systemclock_freq;
    }

    return freq;
}

uint32_t RCC_get_apb1_freq()
{
    uint32_t freq;

    // Get the AHB frequenncy
    uint32_t ahb_freq = RCC_get_ahb_freq();

    // Get the prescaler value for the APB bus
    uint8_t apb1_prescaler_bits = (RCC->CFGR >> RCC_CFGR_PPRE1) & 0b011;

    // The third bit of the CFGR field indicates if the prescaler is enabled
    uint8_t apb1_prescaler_enable = RCC->CFGR >> (RCC_CFGR_PPRE1 + 2) & 0b1;

    if (apb1_prescaler_enable)
    {
        // If the prescaler is enabled, divide the input clock by the 
        // prescaler value
        uint8_t prescaler = RCC_APB_PRESCALER_DIV[apb1_prescaler_bits];
        freq = ahb_freq / prescaler;
    }
    else
    {
        // If the prescaler is disabled, the APB frequency stays as the
        // AHB frequency
        freq = ahb_freq;
    }

    return freq;
}
