#include "stm32f10x.h"         // Device header

#include <string.h>

void clockConfig(void);

void usart2Init(void);

void DMA1channel7Init(void);

void serialPrint(char* data, uint16_t bufLen);

uint8_t sendBuf[64];

int main(void)

{

	clockConfig();

	usart2Init();

	DMA1channel7Init();

	serialPrint("Hello Serial1\n\r", 15);

	while(1)

	{

	}

}

void serialPrint(char* data, uint16_t bufLen)

{

	memcpy(sendBuf, data, bufLen);

	// DMA1_Channel 7 number of transfer bytes

	DMA1_Channel7->CNDTR = bufLen;

	// Enable USART2_Tx DMA Request

	USART2->CR3 |= USART_CR3_DMAT;

}

void DMA1_Channel7_IRQHandler(void)

{

	if( DMA1->ISR & DMA_ISR_TCIF7 )

	{

		// Disable transfer complete flag

		DMA1->IFCR |= DMA_IFCR_CTCIF7;

		// Disable DMA request

		USART2->CR3 &= ~USART_CR3_DMAT;

	}

}

void usart2Init(void)

{

	// USART2_Tx: PA2

	// Enable clock access for port A

	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// Configure PA2 as AF push pull

	GPIOA->CRL |= GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2;

	GPIOA->CRL &= ~GPIO_CRL_CNF2_0;

	// Enable clock access for USART2

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	// @36MHz 9600bps

	USART2->BRR = 0xEA6;

	// Enable USART2_Tx

	USART2->CR1 |= USART_CR1_TE;

	// Enable USART2

	USART2->CR1 |= USART_CR1_UE;

}

void DMA1channel7Init(void)

{

	// Enable clock access for DMA1

	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	// Configure DMA1_Channel7

	// peripheral address

	DMA1_Channel7->CPAR = (uint32_t)&USART2->DR;

	// Memory address

	DMA1_Channel7->CMAR = (uint32_t)sendBuf;

	// Direction is from memory to peripheral

	DMA1_Channel7->CCR |= DMA_CCR7_DIR;

	// Memory increment

	DMA1_Channel7->CCR |= DMA_CCR7_MINC;

	// 1Byte memory and peripheral size

	DMA1_Channel7->CCR &= ~( DMA_CCR7_MSIZE | DMA_CCR7_PSIZE );

	// Enable transmission complete interrupt

	DMA1_Channel7->CCR |= DMA_CCR7_TCIE;

	NVIC_EnableIRQ(DMA1_Channel7_IRQn);

	// Enable DMA

	DMA1_Channel7->CCR |= DMA_CCR7_EN;

}

void clockConfig(void)

{

	// HSE ON

	RCC->CR |= 0x1<<16;

	// wait unit HSE is ready

	while(!(RCC->CR & (0x1<<17))){}

	// PLL OFF

	RCC->CR &= ~(0x1<<24);

	//HSE clock not divided

	RCC->CFGR &= ~(0x1<<17);

	// PLL SRC = HSE

	RCC->CFGR |= 0x1<<16;

	// PLL MUL, x9

	RCC->CFGR &= ~(0xF<<18);

	RCC->CFGR |= 0x7<<18;

	// PLL ON

	RCC->CR |= 0x1<<24;

	// wait until PLL is ready

	while(!(RCC->CR & (0x1 << 25))){}

	// choose PLL as Sys clock

	RCC->CFGR &= ~(0x3);

	RCC->CFGR |= 0x2;

	// AHB prescaler x1

	RCC->CFGR &= ~(0xF<<4);

	// APB1 (36MHz max ) prescaler /2

	RCC->CFGR &= ~(0x7<<8);

	RCC->CFGR |= (0x4<<8);

	// APB2(72MHz) prescaler x1

	RCC->CFGR &= ~(0x7<<11);

}
