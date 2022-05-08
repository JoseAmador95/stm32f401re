#include "cortex-m4.h"

void NVIC_IRQ_Interrupt_Config(uint8_t irq_number, uint8_t status)
{
	if (status)
	{
		if (irq_number < 32)
			*NVIC_ISER0 |= (1 << irq_number);
		else if (irq_number >= 32 && irq_number < 64)
			*NVIC_ISER1 |= (1 << (irq_number % 32));
		else if (irq_number >= 64 && irq_number < 96)
			*NVIC_ISER2 |= (1 << (irq_number % 64));
	}
	else
	{
		if (irq_number < 32)
			*NVIC_ICER0 |= (1 << irq_number);
		else if (irq_number >= 32 && irq_number < 64)
			*NVIC_ICER1 |= (1 << (irq_number % 32));
		else if (irq_number >= 64 && irq_number < 96)
			*NVIC_ICER2 |= (1 << (irq_number % 64));
	}
}

void NVIC_IRQ_Priority_Config(uint8_t irq_number, uint8_t IRQPriority)
{
	uint8_t iprx = irq_number / 4;
	uint8_t iprx_section = irq_number % 4;
	uint8_t ShiftAmmount = 8 * iprx_section + 8 - CORTEX_NO_PR_BITS;
	*(NVIC_IPR + iprx) |= IRQPriority << ShiftAmmount;
}
