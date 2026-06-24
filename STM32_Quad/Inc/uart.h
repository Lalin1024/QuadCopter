/*
 * uart.h
 *
 *  Created on: Apr 17, 2026
 *      Author: LalinPrasadC
 */

#ifndef UART_H_
#define UART_H_

#include "stm32l433xx.h"

void uart_init();
void uart_write(const char* value);
void uart_write_int(uint32_t num);
void disable_gnss(uint8_t  *arr,uint8_t size);

#endif /* UART_H_ */
