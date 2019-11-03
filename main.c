 /*--------------------------------------------------------------------------------------------
  * USART_DRIVER.c
  *
  * Created: 9/11/2018 4:17:45 AM
  *  Author: Esraa Ahmed 
  * This is a test code to the UART_DRIVER
  * Description:
  *                  it sends 1 and wait 1 second then send 0 and wait 1 second and so on 
  *                  to control a led in another microcontroller
  * ---------------------------------------------------------------------------------------------*/
#include"UART_CFG.h"
#include"UART.h"
#include <util/delay.h>

int main(void)
{

UART_Init();
while(1)
{
	//TODO:: Please write your application code
	UART_TransmitChar('1');
	_delay_ms(1000);
	UART_TransmitChar('0'); 
	_delay_ms(1000);
	
}

}