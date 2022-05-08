#include "stm32f401-spi-driver.h"

/* Helper function prototypes */
static void spi_clear_ovr_flag(SPI_Handle_t* pSPIHandle);
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_clear_ovr_flag(SPI_Handle_t* pSPIHandle);
static void spi_close_tx(SPI_Handle_t* pSPIHandle);
static void spi_close_rx(SPI_Handle_t* pSPIHandle);


void SPI_PeriClockControl(typedef_SPI_t *pSPIx, uint8_t Status)
{
	if (Status == ENABLE)
	{
		if (pSPIx == SPI1)
			SPI1_PCLK_EN();
		else if (pSPIx == SPI2)
			SPI2_PCLK_EN();
		else if (pSPIx == SPI3)
			SPI3_PCLK_EN();
		else if (pSPIx == SPI4)
			SPI4_PCLK_EN();
	}
	else if (Status == DISABLE)
	{
		if (pSPIx == SPI1)
			SPI1_PCLK_DI();
		else if (pSPIx == SPI2)
			SPI2_PCLK_DI();
		else if (pSPIx == SPI3)
			SPI3_PCLK_DI();
		else if (pSPIx == SPI4)
			SPI4_PCLK_DI();
	}
}

/* Init and de-init */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	pSPIHandle->pSPIx->CR1 |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;
	pSPIHandle->pSPIx->CR1 |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;
	pSPIHandle->pSPIx->CR1 |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;
	pSPIHandle->pSPIx->CR1 |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;
	pSPIHandle->pSPIx->CR1 |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;
	pSPIHandle->pSPIx->CR1 |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	switch (pSPIHandle->SPIConfig.SPI_BusConfig)
	{
	case (SPI_BUS_CONFIG_FD):
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE);
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_RXONLY);
		break;
	case (SPI_BUS_CONFIG_HD):
		pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_BIDIMODE);
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_RXONLY);
		break;
	case (SPI_BUS_CONFIG_RXONLY):
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_BIDIMODE);
		pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_RXONLY);
		break;
	}
}

void SPI_DeInit(SPI_Handle_t *pSPIHandle)
{
	if (pSPIHandle->pSPIx == SPI1)
		SPI1_REG_RESET();
	else if (pSPIHandle->pSPIx == SPI2)
		SPI2_REG_RESET();
	else if (pSPIHandle->pSPIx == SPI3)
		SPI3_REG_RESET();
	else if (pSPIHandle->pSPIx == SPI4)
		SPI4_REG_RESET();
}

/* Data Send and Receive */
void SPI_Send_Block(SPI_Handle_t* pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	while (Len > 0)
	{
		while (SPI_GetFlagStatus(pSPIHandle->pSPIx, SPI_FLAG_TXE) == FLAG_RESET);
		if (pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			/* 16 bit SPI mode */
			pSPIHandle->pSPIx->DR = *((uint16_t *)pTxBuffer);
			(void)(uint16_t *) pTxBuffer++;
			Len -= 2;
		}
		else
		{
			/* 8 bit SPI mode */
			pSPIHandle->pSPIx->DR = *pTxBuffer;
			pTxBuffer++;
			--Len;
		}
	}
}

void SPI_Receive_Block(SPI_Handle_t* pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	while (Len > 0)
	{
		while (SPI_GetFlagStatus(pSPIHandle->pSPIx, SPI_FLAG_RXNE) == FLAG_RESET);
		if (pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			/* 16 bit SPI mode */
			*((uint16_t *)pRxBuffer) = pSPIHandle->pSPIx->DR;
			(uint16_t *) pRxBuffer++;
			Len -= 2;
		}
		else
		{
			/* 8 bit SPI mode */
			*pRxBuffer = pSPIHandle->pSPIx->DR;
			pRxBuffer++;
			--Len;
		}
	}
}

// void SPI_IRQ_InterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
// {
// 	if (EnorDi == ENABLE)
// 	{
// 		if (IRQNumber < 32)
// 			*NVIC_ISER0 |= 1 << IRQNumber;
// 		else if (IRQNumber >= 32 && IRQNumber < 64)
// 			*NVIC_ISER1 |= 1 << (IRQNumber % 32);
// 		else if (IRQNumber >= 64 && IRQNumber < 96)
// 			*NVIC_ISER2 |= 1 << (IRQNumber % 64);
// 	}
// 	else
// 	{
// 		if (IRQNumber < 32)
// 			*NVIC_ICER0 |= (1 << IRQNumber);
// 		else if (IRQNumber >= 32 && IRQNumber < 64)
// 			*NVIC_ICER1 |= 1 << (IRQNumber % 32);
// 		else if (IRQNumber >= 64 && IRQNumber < 96)
// 			*NVIC_ICER2 |= 1 << (IRQNumber % 64);
// 	}
// }

// void SPI_IRQ_PriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
// {
// 	uint8_t iprx = IRQNumber / 4;
// 	uint8_t iprx_Section = IRQNumber % 4;
// 	uint8_t ShiftAmmount = 8 * iprx_Section + 8 - CORTEX_NO_PR_BITS;
// 	*(NVIC_IPR + iprx) |= IRQPriority << ShiftAmmount;
// }

void SPI_IRQ_Handling(SPI_Handle_t *pSPIHandle)
{
	volatile uint8_t temp1, temp2;
	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_I2S_SR_TXE);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_I2S_CR2_TXEIE);

	if (temp1 && temp2)
	{
		spi_txe_interrupt_handle(pSPIHandle);
	}

	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_I2S_SR_RXNE);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_I2S_CR2_RXNEIE);

	if (temp1 && temp2)
	{
		spi_rxne_interrupt_handle(pSPIHandle);
	}

	temp1 = pSPIHandle->pSPIx->SR & (1 << SPI_I2S_SR_OVR);
	temp2 = pSPIHandle->pSPIx->CR2 & (1 << SPI_I2S_CR2_ERRIE);

	if (temp1 && temp2)
	{
		spi_ovr_err_interrupt_handle(pSPIHandle);
	}
}

uint8_t SPI_GetFlagStatus(typedef_SPI_t *pSPIx, uint32_t FlagName)
{
	if (pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	else
	{
		return FLAG_RESET;
	}
}

void SPI_PeripheralControl(SPI_Handle_t* pSPIHandle, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
		pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	else
		pSPIHandle->pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
}

void SPI_SSIConfig(typedef_SPI_t *pSPIx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	else
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
}

void SPI_SSOEConfig(typedef_SPI_t *pSPIx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
		pSPIx->CR2 |= (1 << SPI_I2S_CR2_SSOE);
	else
		pSPIx->CR2 &= ~(1 << SPI_I2S_CR2_SSOE);
}

/* Data Send and Receive (Interrupt)*/
uint8_t SPI_Send_IT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{

	uint8_t state = pSPIHandle->TxState;
	if (state != SPI_BUSY_IN_TX)
	{
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;
		pSPIHandle->TxState = SPI_BUSY_IN_TX;
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_I2S_CR2_TXEIE);
	}

	return state;
}

uint8_t SPI_Receive_IT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->RxState;
	if (state != SPI_BUSY_IN_RX)
	{
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;
		pSPIHandle->RxState = SPI_BUSY_IN_RX;
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_I2S_CR2_RXNEIE);
	}

	return state;
}

uint8_t SPI_Send(SPI_Handle_t* pSPIx, uint8_t* pTxBuffer, uint8_t Len)
{
	#ifndef SPI_API_BLOCKING
		return SPI_Send_IT(pSPIx, pTxBuffer, Len);
	#else
		SPI_Send_Block(pSPIx, pTxBuffer, Len);
		return 0;
	#endif
}

uint8_t SPI_Receive(SPI_Handle_t* pSPIx, uint8_t* pRxBuffer, uint8_t Len)
{
	#ifndef SPI_API_BLOCKING
		return SPI_Receive_IT(pSPIx, pRxBuffer, Len);
	#else
		SPI_Receive_Block(pSPIx, pRxBuffer, Len);
		return 0;
	#endif
}

/* SPI Helper Functions */
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
	{
		// 16-bit SPI mode
		pSPIHandle->pSPIx->DR = *((uint16_t*) pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen -= 2;
		(uint16_t*) ++pSPIHandle->pTxBuffer;  
	}
	else
	{
		// 8-bit SPI mode
		pSPIHandle->pSPIx->DR = *((uint8_t*) pSPIHandle->pTxBuffer);
		--pSPIHandle->TxLen;
		++pSPIHandle->pTxBuffer; 
	}

	spi_close_tx(pSPIHandle);
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_COMPLETE);
}

static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if (pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
	{
		/* 16 bit SPI mode */
		*((uint16_t *)pSPIHandle->pRxBuffer) = (uint16_t) pSPIHandle->pSPIx->DR;
		(uint16_t *) pSPIHandle->pRxBuffer++;
		pSPIHandle->RxLen -= 2;
	}
	else
	{
		/* 8 bit SPI mode */
		*pSPIHandle->pRxBuffer = pSPIHandle->pSPIx->DR;
		pSPIHandle->pRxBuffer++;
		--pSPIHandle->RxLen;
	}

	spi_close_rx(pSPIHandle);
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_COMPLETE);
}

static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if (pSPIHandle->TxState != SPI_BUSY_IN_TX){
		spi_clear_ovr_flag(pSPIHandle);
	}

	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_ERROR_OVR);
}

static void spi_clear_ovr_flag(SPI_Handle_t* pSPIHandle)
{
	// Clear the Overrun flag by reading the DR and SR register 
	uint32_t dummy;
	dummy= pSPIHandle->pSPIx->DR;
	dummy = pSPIHandle->pSPIx->SR;
	(void) dummy;
}

static void spi_close_tx(SPI_Handle_t* pSPIHandle)
{
	if (pSPIHandle->TxLen == 0)
	{	
		// Disable the TX Empty interrupt flag
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_I2S_CR2_TXEIE);
		pSPIHandle->pTxBuffer = NULL;
		pSPIHandle->TxState = SPI_READY;
	}
}

static void spi_close_rx(SPI_Handle_t* pSPIHandle)
{
	if (pSPIHandle->RxLen == 0)
	{	
		// Disable the RX Empty interrupt flag
		pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_I2S_CR2_RXNEIE);
		pSPIHandle->pRxBuffer = NULL;
		pSPIHandle->RxState = SPI_READY;
	}
}

__weak void SPI_ApplicationEventCallback(SPI_Handle_t* pSPIHandle, uint8_t event)
{
	// This is a weak implementation of the function
}