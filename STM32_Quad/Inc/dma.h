/*
 * dma.h
 *
 *  Created on: Jun 22, 2026
 *      Author: LalinPrasadC
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32l433xx.h"

void dma_monitor(const char* msg,uint8_t size);

void dma_gps_receive(const char *data,uint8_t size);

void DMA1_Channel7_IRQHandler();



#endif /* DMA_H_ */
