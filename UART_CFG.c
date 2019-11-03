/*
 * UART_CFG.c
 *
 * Created: 9/11/2018 5:13:00 PM
 *  Author: HP
 */ 

#include"UART.h"
#include"UART_CFG.h"
const UART_ConfigType UART_ConfigParam =
{

		BR9600,
		NOPARITY,
		STOP_ONE,
		UART_8_BITS

};
