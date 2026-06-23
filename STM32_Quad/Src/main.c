#include "timer.h"
#include "uart.h"
#include "interrupt.h"
#include "dma.h"
#include "ubox.h"
#include "gnss.h"

const char* msg="Dragon\r\n";
char a;
volatile int i=0;
char buff[256];
uint8_t read_flag=0,j=0,gga_flag=0,rmc_flag=0;;

uint32_t output=0;

//gps gp1;

void USART3_IRQHandler();

int main()
{
	SetClock_16MHz();
	uart_init();
	dma_gps_receive(buff,255);
	usart3_interrupt();
	//dma_monitor_intr();
	dma_receive_intr();

    RCC->AHB2ENR|=(1U<<1);

    GPIOB->MODER&=~(3U<<26);
    GPIOB->MODER|=(1U<<26);



    while(1)
       {
    	if(read_flag)
    	{
    		if(buff[3]=='G')
    		{
    		    gga_flag=1;
    		read_gga(buff);
    		}
    		else if(buff[3]=='R')
    		{
    		    rmc_flag=1;
    		    read_rmc(buff);
    		}

    		if(gga_flag)
    		{
    			gga_flag=0;
    		    output=convert(gp1.alt);
    		    uart_write_int(output);
    		    uart_write("\r\n");


    		}
    		else if(rmc_flag)
    		{
    			rmc_flag=0;
    			output=convert(gp1.time);
    			uart_write_int(output);
    			uart_write("\r\n");

    		}
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
