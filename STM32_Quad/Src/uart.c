/*
 * uart.c
 *
 *  Created on: Jun 17, 2026
 *      Author: LalinPrasadC
 */


#include "uart.h"

#define GPIOA_EN	(1U<<0)
#define GPIOB_EN	(1U<<1)
#define SYSCLK		16000000

static void set_baud(USART_TypeDef *UART,uint32_t baud);

void uart_init( )
{
	/*PA2=USART2_TX,PB10=USART3_TX,PB11=USART3_RX*/

	/*Since the reset value is 0 no need to set bit 28 and 12 as we need 8N1*/
	RCC->AHB2ENR|=((GPIOA_EN|GPIOB_EN));
	RCC->APB1ENR1|=((1U<<17)|(1U<<18));

	GPIOA->MODER&=~(3U<<4);
	GPIOB->MODER&=~((3U<<20)|(3U<<22));

	GPIOA->MODER|=(1U<<5);
	GPIOB->MODER|=((1U<<21)|(1U<<23));

	GPIOA->OSPEEDR|=(1U<<4);
	GPIOB->OSPEEDR|=((1U<<20)|(1U<<22));

	GPIOA->AFR[0]|=(7U<<8);
	GPIOB->AFR[1]|=((7U<<8)|(7U<<12));

	set_baud(USART2,115200);
	set_baud(USART3,9600);

	/*Since the reset value for CR2  is 0 no need to configure stop bits*/

	USART2->CR1|=(1U<<0); //Enabling USART
	USART3->CR1|=(1U<<0);

	USART2->CR3|=(1U<<7);//Enabling DMA for USART2_TX
	//USART3->CR3|=(1U<<7);//Enabling DMA for USART3_TX
	USART3->CR3|=(1U<<6);//Enabling DMA for USART3_RX

	USART2->CR1|=(1U<<3);
	USART3->CR1|=(1U<<3);
	USART3->CR1 |= (1U<<2);
	//USART3->CR1|=(1U<<5);//Enabling interrupt for reception
}

void uart_write(const char* value)
{
	while(*value)
		{
		while(!(USART2->ISR & (1U<<7))){}

		USART2->TDR=(*value++);
	}
}


void disable_gnss(uint8_t  *arr,uint8_t size)
{
	for(int i=0;i<size;i++)
	{
		while(!(USART3->ISR & (1U<<7))){}
					USART3->TDR=arr[i];
	}
}


void uart_write_int(uint32_t num)
{
	char buff[12];
	int i=0;

	/* Handle zero explicitly */
	if(num==0)
	{
		uart_write("0");
		return;
	}
	else
	{
		/* Convert integer to ASCII (reverse order) */
		while(num!=0)
		{
			buff[i++]=(num%10)+'0';
			num/=10;
		}

		/* Null-terminate the string */
		buff[i]='\0';

		/* Reverse the string to correct digit order */
		for(int j=0;j<i/2;j++)
		{
			char tmp=buff[j];
			buff[j]=buff[i-1-j];
			buff[i-1-j]=tmp;
		}

		/* Transmit the formatted string */
		uart_write(buff);
	}
}

static void set_baud(USART_TypeDef *UART,uint32_t baud)
{
	UART->BRR=(SYSCLK/baud);
}
