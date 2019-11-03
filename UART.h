
/**************************************************************************************
*        File name:  USART.h
*        Author: Esraa Ahmed 
*        Created: 9/11/2018 4:19:25 AM
*        Description:
*                        This file contains:
*                        - macros to access the UART register
*                        - prototypes of functions used to access UART register
*        Microcontroller: ATMEGA32
***************************************************************************************/


#ifndef UART_H
#define UART_H
#include<stdint.h>
#include"UART_CFG.h"

/*---------------------------------------------------------------------------------------------------
**********					Enums Used by user to Configure the UART periferal			   **********
---------------------------------------------------------------------------------------------------*/
// enum for the return value of functions either Ok or NOK
typedef enum {UART_OK =0, UART_NOK}UART_ChkType; 
// enum for Parity parameter in UART_ConfigType structure
typedef enum {NOPARITY =0, EVENPARITY = 2, ODDPARITY = 3} UART_ParityType;
// enum for StopBits parameter in UART_ConfigType structure  
typedef enum {STOP_ONE =0, STOP_TWO}UART_StopBitsType;
// enum for DataSize parameter in UART_ConfigType structure
typedef enum {UART_5_BITS=0,UART_6_BITS=1,UART_7_BITS=2,UART_8_BITS=3}UART_DataSizeType;

/*-----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
**********		A structure type to contain all the required configuration		**********
----------------------------------------------------------------------------------------*/
typedef struct
{

        /*Channel BaudRate*/
        // BR9600 	==> 9600 	bps
        // BR19200 	==> 19200 	bps
        // BR38400 	==> 38400 	bps
        // BR115200 ==> 115200 	bps
        // BR460800 ==> 460800 	bps
        uint16_t BaudRate;

        /*Channel ParityType*/
        /* Values Can be:
        	- NOPARITY
        	- EVENPARITY
        	- ODDPARITY*/
        UART_ParityType Parity;

        /*Channel Stop Bits*/
        /* Values Can be:
        	- STOP_ONE
        	- STOP_TWO*/
        UART_StopBitsType StopBits;

        /*Channel frame Data Size*/
        /* Values Can be:
		    - UART_5_BITS
			- UART_6_BITS
			- UART_7_BITS
        	- UART_8_BITS	
        		*/
        UART_DataSizeType DataSize;
        
}UART_ConfigType;
/*--------------------------------------------------------------------------------------*/

/*************************************************************************************
**********		Macros for BAUD RATE values for frequency FOSC MHz            **********
*************************************************************************************/	

#define BR115200        F_CPU/16/115200-1
#define BR460800        F_CPU/16/460800-1
#define BR230400        F_CPU/16/230400-1
#define BR921600        F_CPU/16/921600-1
#define BR19200         F_CPU/16/19200-1
#define BR38400         F_CPU/16/38400-1
#define BR57600         F_CPU/16/57600-1
#define BR9600          F_CPU/16/9600-1
#define BR1200          F_CPU/16/1200-1
#define BR4800          F_CPU/16/4800-1
#define BR2400          F_CPU/16/2400-1
#define BR300           F_CPU/16/300-1
#define BR150           F_CPU/16/150-1
#define BR110           F_CPU/16/110-1

/*------------------------------------------------------------------------------------
**********					UART Registers Bit definetions					**********
------------------------------------------------------------------------------------*/

/*************************************************************************************
**********	  the bit fields in the UCSRB register               **********
*************************************************************************************/
//      Bit name   Bit NUMBER IN THE REGISTER
#define RXCIE      7
#define TXCIE      6
#define UDRIE      5
#define RXEN       4
#define TXEN       3
#define UCSZ2      2
#define RXB8       1
#define TXB8       0

/*************************************************************************************
**********				the bit fields in the UCSRA register                 **********
*************************************************************************************/
//      Bit name   Bit NUMBER IN THE REGISTER
#define RXC        7
#define TXC        6
#define UDRE       5
#define FE         4
#define DOR        3
#define PE         2
#define U2X        1
#define MPCM       0   


/*************************************************************************************
**********				the bit fields in the UCSRC register                 **********
*************************************************************************************/
//      Bit name   Bit NUMBER IN THE REGISTER
 
#define URSEL      7
#define UMSEL      6
#define UPM1       5
#define UPM0       4
#define USBS       3
#define UCSZ1      2
#define UCSZ0      1
#define UCPOL      0  		        		

/*---------------------------------------------------------------------------------------*/


/* The structure in which the user configure the required UART periferal in UART_Cfg.c*/
extern const UART_ConfigType UART_ConfigParam;

/*-------------------------------------------------------------------------------------------
**********								Driver APIs								   **********
--------------------------------------------------------------------------------------------*/
// Return type of all functions is UART_ChkType which can be either UART_OK or UART_NOK

/*A function to initialize all the UART channels with the configuration set in UART_Cfg*/

UART_ChkType UART_Init(void);

/* A function to transmit a string */
/*Inputs:
- String: pointer to the string to be transmitted*/
UART_ChkType UART_Transmitstring(unsigned char *String);

/* A function to transmit a char */
/*Inputs:
- Data: the char to be transmitted*/

UART_ChkType UART_TransmitChar(unsigned char Data);

/*A function to Request a Reception*/
/*
 Inputs:'
 ReceivedData: Pointer to the location in which the received data will be saved
 */
UART_ChkType UART_Read(uint8_t *ReceivedData);

#endif
