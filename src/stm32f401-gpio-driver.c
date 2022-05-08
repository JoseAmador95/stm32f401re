#include "stm32f401-gpio-driver.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinMode
               << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        pGPIOHandle->pGPIOx->MODER &=
            ~(3U << (2U * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx->MODER |= temp;
    }
    else
    {
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        uint8_t PortCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
        temp =
            PortCode << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4));
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4] |= temp;
        EXTI->IMR |= 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    }

    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed
           << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OSPEEDR &=
        ~(3U << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp = pGPIOHandle->GPIO_PinConfig.GPIO_pinPuPdControl
           << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->PUPDR &=
        ~(3U << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
           << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
    pGPIOHandle->pGPIOx->OTYPER &=
        ~(1U << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        temp = pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode
               << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8));
        pGPIOHandle->pGPIOx
            ->AFR[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8] &=
            ~(0xFU << (4 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
        pGPIOHandle->pGPIOx
            ->AFR[pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8] |= temp;
    }
}

void GPIO_Deninit(typedef_GPIO_t *pGPIOx)
{
    if (pGPIOx == GPIOA)
        GPIOA_REG_RESET();
    else if (pGPIOx == GPIOB)
        GPIOB_REG_RESET();
    else if (pGPIOx == GPIOC)
        GPIOC_REG_RESET();
    else if (pGPIOx == GPIOD)
        GPIOD_REG_RESET();
    else if (pGPIOx == GPIOE)
        GPIOE_REG_RESET();
    else if (pGPIOx == GPIOH)
        GPIOH_REG_RESET();
}

void GPIO_PeriClockControl(typedef_GPIO_t *pGPIOx, uint32_t Status)
{
    if (Status == ENABLE)
    {
        if (pGPIOx == GPIOA)
            GPIOA_PCLK_EN();
        else if (pGPIOx == GPIOB)
            GPIOB_PCLK_EN();
        else if (pGPIOx == GPIOC)
            GPIOC_PCLK_EN();
        else if (pGPIOx == GPIOD)
            GPIOD_PCLK_EN();
        else if (pGPIOx == GPIOE)
            GPIOE_PCLK_EN();
        else if (pGPIOx == GPIOH)
            GPIOH_PCLK_EN();
    }
    else if (Status == DISABLE)
    {
        if (pGPIOx == GPIOA)
            GPIOA_PCLK_DI();
        else if (pGPIOx == GPIOB)
            GPIOB_PCLK_DI();
        else if (pGPIOx == GPIOC)
            GPIOC_PCLK_DI();
        else if (pGPIOx == GPIOD)
            GPIOD_PCLK_DI();
        else if (pGPIOx == GPIOE)
            GPIOE_PCLK_DI();
        else if (pGPIOx == GPIOH)
            GPIOH_PCLK_DI();
    }
}

uint8_t GPIO_ReadFromInputPin(typedef_GPIO_t *pGPIOx, uint8_t PinNumber)
{
    return (pGPIOx->IDR >> PinNumber) & 0x00000001U;
}

uint16_t GPIO_ReadFromInputPort(typedef_GPIO_t *pGPIOx)
{
    return pGPIOx->IDR;
}

void GPIO_WriteToOutputPin(typedef_GPIO_t *pGPIOx, uint8_t PinNumber,
                           uint8_t Value)
{
    if (Value == GPIO_PIN_SET)
        pGPIOx->ODR |= (1 << PinNumber);
    else if (Value == GPIO_PIN_RESET)
        pGPIOx->ODR &= ~(1 << PinNumber);
}

void GPIO_WriteToOutputPort(typedef_GPIO_t *pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(typedef_GPIO_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= 1 << PinNumber;
}

// void GPIO_IRQ_InterruptConfig(uint8_t IRQNumber, uint8_t Status)
// {
//     if (Status == ENABLE)
//     {
//         if (IRQNumber < 32)
//             *NVIC_ISER0 |= (1 << IRQNumber);
//         else if (IRQNumber >= 32 && IRQNumber < 64)
//             *NVIC_ISER1 |= (1 << (IRQNumber % 32));
//         else if (IRQNumber >= 64 && IRQNumber < 96)
//             *NVIC_ISER2 |= (1 << (IRQNumber % 64));
//     }
//     else
//     {
//         if (IRQNumber < 32)
//             *NVIC_ICER0 |= (1 << IRQNumber);
//         else if (IRQNumber >= 32 && IRQNumber < 64)
//             *NVIC_ICER1 |= (1 << (IRQNumber % 32));
//         else if (IRQNumber >= 64 && IRQNumber < 96)
//             *NVIC_ICER2 |= (1 << (IRQNumber % 64));
//     }
// }

// void GPIO_IRQ_PriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
// {
//     uint8_t iprx = IRQNumber / 4;
//     uint8_t iprx_section = IRQNumber % 4;
//     uint8_t ShiftAmmount = 8 * iprx_section + 8 - CORTEX_NO_PR_BITS;
//     *(NVIC_IPR + iprx) |= IRQPriority << ShiftAmmount;
// }

void GPIO_IRQ_Handling(uint8_t PinNumber)
{
    if (EXTI->PR & (1 << PinNumber))
    {
        EXTI->PR |= 1 << PinNumber;
    }
}

GPIO_Handle_t GPIO_Setup(uint8_t pinNumber, typedef_GPIO_t *port, uint8_t mode,
                         uint8_t speed, uint8_t PuPd, uint8_t type)
{
    GPIO_Handle_t gpio;
    gpio.pGPIOx = port;
    gpio.GPIO_PinConfig.GPIO_PinMode = mode;
    gpio.GPIO_PinConfig.GPIO_PinNumber = pinNumber;
    gpio.GPIO_PinConfig.GPIO_PinOPType = type;
    gpio.GPIO_PinConfig.GPIO_pinPuPdControl = PuPd;
    gpio.GPIO_PinConfig.GPIO_PinSpeed = speed;
    GPIO_Init(&gpio);
    return gpio;
}
uint8_t GPIO_Read(GPIO_Handle_t *gpio)
{
    return GPIO_ReadFromInputPin(gpio->pGPIOx,
                                 gpio->GPIO_PinConfig.GPIO_PinNumber);
}

void GPIO_Write(GPIO_Handle_t *gpio, uint8_t value)
{
    GPIO_WriteToOutputPin(gpio->pGPIOx, gpio->GPIO_PinConfig.GPIO_PinNumber,
                          value);
}

void GPIO_Toggle(GPIO_Handle_t *gpio)
{
    GPIO_ToggleOutputPin(gpio->pGPIOx, gpio->GPIO_PinConfig.GPIO_PinNumber);
}