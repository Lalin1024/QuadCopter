#include "timer.h"
#include "uart.h"
#include "interrupt.h"
#include "dma.h"
#include "ubox.h"
#include "gnss.h"

const char* msg="Dragon\r\n";
char a;
volatile int i=0;
char buff[149];
uint8_t read_flag=0,j=0,gga_flag=0,rmc_flag=0;;

uint32_t output=0;

//gps gp1;

//void USART3_IRQHandler();
void DMA1_Channel3_IRQHandler();

void DMA1_Channel2_IRQHandler();

int main()
{
	SetClock_16MHz();
	uart_init();
	dma_receive_intr();
//	dma_gps_intr();
//	delay(2000);

	dma_gps_receive(buff,149);
	delay(200);
	disable_gnss(disable_gll,11);
	delay(200);
	disable_gnss(disable_gsa,sizeof(disable_gsa));
	delay(200);
	disable_gnss(disable_gsv,sizeof(disable_gsv));
	delay(200);
	disable_gnss(disable_vtg,sizeof(disable_vtg));
	delay(200);



    RCC->AHB2ENR|=(1U<<1);

    GPIOB->MODER&=~(3U<<26);
    GPIOB->MODER|=(1U<<26);



    while(1)
       {
    		if(read_flag)
    		{

    			uart_write(buff);
    			uart_write("\r\n");
    			read_flag=0;
    		}
       }




}



void DMA1_Channel3_IRQHandler()
{
	if(DMA1->ISR & (1U<<9))
	{
		DMA1->IFCR|=(1U<<9);
		read_flag=1;
	}
}

void DMA1_Channel2_IRQHandler()
{
	if(DMA1->ISR & (1U<<5))
	{
		DMA1->IFCR|=(1U<<5);
	}
}

//void USART3_IRQHandler()
//{
//	if(USART3->ISR & (1U<<5))
//		{
//			a=USART3->RDR;
//			buff[i++]=a;
//			if(a=='\n')
//			{
//				buff[i++]='\r';
//				buff[i++]='\n';
//				buff[i] = '\0';
//				i=0;
//				read_flag=1;
//			}
//		}
//}
