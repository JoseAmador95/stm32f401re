#ifndef __STM32F401RE_SPI_DRIVER_H_
#define __STM32F401RE_SPI_DRIVER_H_

#include "STM32F401RE.h"
#include <stdint.h>
#include "STM32F401RE_REGISTER_BITS.h"

#define SPI_MODE_CPOL_LOW 0
#define SPI_MODE_CPOL_HIGH 1
#define SPI_MODE_CPHA_LOW 0
#define SPI_MODE_CPHA_HIGH 1
#define SPI_DEVICE_MODE_MASTER 1
#define SPI_DEVICE_MODE_SLAVE 0
#define SPI_SCLK_SPEED_DIV2 0
#define SPI_SCLK_SPEED_DIV4 1
#define SPI_SCLK_SPEED_DIV8 2
#define SPI_SCLK_SPEED_DIV16 3
#define SPI_SCLK_SPEED_DIV32 4
#define SPI_SCLK_SPEED_DIV64 5
#define SPI_SCLK_SPEED_DIV128 6
#define SPI_SCLK_SPEED_DIV256 7
#define SPI_STATUS_DISABLED 0
#define SPI_STATUS_ENABLED 1
#define SPI_FORMAT_MSB 0
#define SPI_FORMAT_LSB 1
#define SPI_SSM_DISABLE 0
#define SPI_SSM_ENABLE 1
#define SPI_BUS_CONFIG_FD 1
#define SPI_BUS_CONFIG_HD 2
#define SPI_BUS_CONFIG_RXONLY 3
#define SPI_DFF_8BITS 0
#define SPI_DFF_16BITS 1
#define SPI_SSM_SW 0
#define SPI_SSM_HW 1

#define SPI_FLAG_RXNE (1 << SPI_I2S_SR_RXNE)
#define SPI_FLAG_TXE (1 << SPI_I2S_SR_TXE)
#define SPI_FLAG_BUSY (1 << SPI_I2S_SR_BSY)

// SPI Application States
#define SPI_READY 0
#define SPI_BUSY_IN_RX 1
#define SPI_BUSY_IN_TX 2

// SPI Application Events
#define SPI_EVENT_TX_COMPLETE 1
#define SPI_EVENT_RX_COMPLETE 2
#define SPI_EVENT_ERROR_OVR 3
#define SPI_EVENT_ERROR_CRC 4

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
} SPI_Config_t;

typedef struct
{
	typedef_SPI_t *pSPIx;
	SPI_Config_t SPIConfig;
	/* SPI Status Global Variables */
	uint8_t *pTxBuffer;
	uint8_t *pRxBuffer;
	uint32_t TxLen;
	uint32_t RxLen;
	uint8_t TxState;
	uint8_t RxState;
} SPI_Handle_t;

/* Peripheral Clock Setup */
void SPI_PeriClockControl(typedef_SPI_t* pSPIx, uint8_t Status);

/* Init and de-init */
void SPI_Init(SPI_Handle_t* pSPIHandle);
void SPI_DeInit(SPI_Handle_t* pSPIHandle);

/* Data Send and Receive (Blocking) */
void SPI_Send_Block(SPI_Handle_t* pSPIHandle, uint8_t* pTxBuffer, uint32_t Len);
void SPI_Receive_Block(SPI_Handle_t* pSPIHandle, uint8_t* pRxBuffer, uint32_t Len);

/* Data Send and Receive (Interrupt) */
uint8_t SPI_Send_IT(SPI_Handle_t* pSPIx, uint8_t* pTxBuffer, uint32_t Len);
uint8_t SPI_Receive_IT(SPI_Handle_t* pSPIx, uint8_t* pRxBuffer, uint32_t Len);

/* Data Send and Receive (API) */
uint8_t SPI_Send(SPI_Handle_t* pSPIx, uint8_t* pTxBuffer, uint8_t Len);
uint8_t SPI_Receive(SPI_Handle_t* pSPIx, uint8_t* pRxBuffer, uint8_t Len);

/* IRQ Handling */
void SPI_IRQ_InterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQ_PriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQ_Handling(SPI_Handle_t* pSPIHandle);

uint8_t SPI_GetFlagStatus(typedef_SPI_t *pSPIx, uint32_t FlagName);

void SPI_PeripheralControl(SPI_Handle_t* pSPIHandle, uint8_t EnOrDi);
void SPI_SSIConfig(typedef_SPI_t* pSPIx, uint8_t EnOrDi);
void SPI_SSOEConfig(typedef_SPI_t* pSPIx, uint8_t EnOrDi);

void SPI_ApplicationEventCallback(SPI_Handle_t* pSPIHandle, uint8_t event);
#endif
