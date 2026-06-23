/*
 * interrupt.c
 *
 *  Created on: Jun 20, 2026
 *      Author: lalin
 */


#include "interrupt.h"


void dma_monitor_intr()
{
	NVIC_EnableIRQ(DMA1_Channel7_IRQn);
}

void dma_gps_intr()
{
	NVIC_EnableIRQ(DMA1_Channel2_IRQn);
}

void dma_receive_intr()
{
	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
}

void usart3_interrupt()
{
	NVIC_EnableIRQ(USART3_IRQn);

}
