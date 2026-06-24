/*
 * dma.c
 *
 *  Created on: Jun 20, 2026
 *      Author: lalin
 */

#include "dma.h"


void dma_monitor(const char* msg,uint8_t size)
{
	RCC->AHB1ENR|=(1U<<0);
	DMA1_Channel7->CPAR=(uint32_t)&(USART2->TDR);

	DMA1_Channel7->CMAR=(uint32_t)msg;

	DMA1_Channel7->CNDTR=size;

	DMA1_Channel7->CCR|=((1U<<12)|(1U<<4)|(0U<<5)|(1U<<7)|(0U<<8)|(0U<<10)|(1U<<1));

	DMA1_CSELR->CSELR|=(1U<<25);

	DMA1_Channel7->CCR|=(1U<<0); //Enable DMA
}



void dma_gps_receive(const char *data,uint8_t size)
{
	RCC->AHB1ENR|=(1U<<0);

	DMA1_Channel3->CPAR=(uint32_t)&(USART3->RDR);

	DMA1_Channel3->CMAR=(uint32_t)data;

	DMA1_Channel3->CNDTR=size;

	DMA1_Channel3->CCR|=((1U<<13)|(0U<<4)|(1U<<5)|(1U<<7)|(0U<<8)|(0U<<8)|(0U<<10)|(1U<<1));

	DMA1_CSELR->CSELR|=(1U<<9);

	DMA1_Channel3->CCR|=(1U<<0);

}

void DMA1_Channel7_IRQHandler()
{
	if(DMA1->ISR & (1U<<25))
	{
		DMA1->IFCR|=(1U<<25);
	}
}






