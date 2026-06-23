/*
 * interrupt.h
 *
 *  Created on: Jun 22, 2026
 *      Author: LalinPrasadC
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "stm32l433xx.h"

void dma_monitor_intr();

void dma_gps_intr();

void dma_receive_intr();

void usart3_interrupt();

#endif /* INTERRUPT_H_ */
