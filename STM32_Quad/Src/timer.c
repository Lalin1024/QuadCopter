/*
 * timer.c
 *
 *  Created on: Mar 30, 2026
 *      Author: LalinPrasadC
 */


#include "timer.h"

#define HSION	(1U<<8)
#define HSIRDY	(1U<<10)
#define TIM6EN	(1U<<4)
#define TIM2EN	(1U<<0)
#define GPIOAEN	(1U<<0)

void SetClock_16MHz()
{
	RCC->CR|=HSION;

	while(!(RCC->CR & HSIRDY)){}

	RCC->CFGR&=~(3U<<0);
	RCC->CFGR|=(1U<<0);

	RCC->CFGR&=~(3U<<2);
	while(!(RCC->CFGR & (1U<<2))){}

}


void delay(uint32_t	value)
{
	RCC->APB1ENR1|=TIM6EN;

	TIM6->PSC=15999;

	TIM6->ARR=(value-1);

	TIM6->CNT=0;

	TIM6->EGR|=(1U<<0);

	TIM6->CR1|=(1U<<0);

	TIM6->SR&=~(1U<<0);

	while(!(TIM6->SR & (1U<<0))){}
}


