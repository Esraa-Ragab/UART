
/**************************************************************************************
*        File name: UART.c
*        Author: Esraa Ahmed
*        Created: 9/11/2018 4:19:03 AM
*        Description:
*                        This file contains:
*                        - Base Addresses of The UART peripherals
*                        - Implementation of functions used to access UART registers
*        Microcontroller: ATMEGA32
***************************************************************************************/
#include"UART.h"
#include"UART_CFG.h"

typedef volatile uint8_t* const UART_RegAddType;   // typedef for the uart register addreses which are pointer to 8 bits 

/*-----------------------------------------------------------------------------------------------------
************                            Accessing the UART Registers                      ************
------------------------------------------------------------------------------------------------------*/
// calculate the address of each register and cast it to the Typedef data type (UART_RegAddType)
// then dereference that address to be ready to write in the required register.

#define UART_BRRL_R               (*((UART_RegAddType )0x29))  // UART Baud Rate Low Register
#define UART_BRRH_R               (*((UART_RegAddType )0x40))  // UART Baud Rate High Register
#define UART_CSRC_R               (*((UART_RegAddType )0x40))  //UART Control & Status  C Register
#define UART_CSRB_R               (*((UART_RegAddType )0x2A))  //UART Control & Status  B Register
#define UART_CSRA_R               (*((UART_RegAddType )0x2B))  //UART Control & Status  A Register
#define UART_DR_R                 (*((UART_RegAddType )0x2C))  //UART Data Register

/*-----------------------------------------------------------*/

/*-------------------------------------
****        UART States           ****
-------------------------------------*/
#define UART_STATE_UNINIT        0x00
#define UART_STATE_INIT          0x01
/*----------------------------------------------------------------*/

// variable to save the states of all the UART
uint8_t UartDriverState= 0;

/*--------------------------------------------------------------------------------------
************                    Driver APIs Implementation                  ************
---------------------------------------------------------------------------------------*/

/*A function to initialize the UART channel with the configuration set in USART_Cfg*/
UART_ChkType UART_Init(void)
{
	UART_ChkType RetVar;              // variable for the return value
	const UART_ConfigType* CfgPtr;   // pointer to UART_ConfigType to save the address of the configuration structure
	CfgPtr = &UART_ConfigParam;
	/*Checking for a valid configuration*/
	if((CfgPtr->DataSize <= UART_8_BITS) && (CfgPtr->Parity <= ODDPARITY) && (CfgPtr->StopBits <=STOP_TWO))
	{
		//Enable the Tx and Rx pins
		UART_CSRB_R = (1<<TXEN)|(1<<RXEN);
		
		//use the BBRH REGISTER
		UART_CSRC_R &=~(1<<URSEL);
		
		// set the baud rate
		UART_BRRH_R= (uint8_t)((CfgPtr->BaudRate)>>8);
		UART_BRRL_R= (uint8_t)(CfgPtr->BaudRate);
		
		//use the UCSRC REGISTER
		UART_CSRC_R|=(1<<URSEL);

		// set the DATA length
		UART_CSRC_R &=~ (3 << UCSZ0);
		UART_CSRC_R |= ((CfgPtr->DataSize) <<UCSZ0);

		// set the number of stop bits
		UART_CSRC_R &=~ (1 << USBS);
		UART_CSRC_R|= ((CfgPtr->StopBits) << USBS);

		// set the parity bits
		UART_CSRC_R &= ~(3<< UPM0);
		UART_CSRC_R |= ((CfgPtr->Parity) <<UPM0);

		/*Change the UART State*/
		UartDriverState = UART_STATE_INIT;
		RetVar = UART_OK;
	}
	else
	{
		UartDriverState = UART_STATE_UNINIT;
		RetVar = UART_NOK;
	}
	
	return RetVar;
}

/* A function to transmit a string */
/*Inputs:
- String: pointer to the string to be transmitted*/
UART_ChkType UART_Transmitstring(unsigned char *String)
{
	UART_ChkType RetVar;
	uint8_t StringIndex= 0;
	/*Check if the channel Ready to start transmission*/
	if((UartDriverState & UART_STATE_INIT) == UART_STATE_INIT)
	{
		while(String[StringIndex]!='\0')  //loop till the end of string
		{
			UART_TransmitChar(String[StringIndex]) ;
			StringIndex++;
		}
		// return UART Ok
		RetVar = UART_OK;
	}
	else
	{
		RetVar = UART_NOK;
	}
	
	return RetVar;
}

/* A function to transmit a char */
/*Inputs:
- Data: the char to be transmitted*/

UART_ChkType UART_TransmitChar(unsigned char Data)
{
	 UART_ChkType RetVar; // variable for the return value
	/* Wait for empty transmit buffer */
	if ( ( UART_CSRA_R & (1<<UDRE))==1)
	/* Put data into buffer, sends the data */
	{
			UART_DR_R =Data;
			RetVar = UART_OK;
	}
	else
	{
		RetVar = UART_NOK;
	}
	return RetVar;
}

/*A function to Request a Reception*/
/*
 Inputs:
 ReceivedData: Pointer to the location in which the received data will be saved
 */

UART_ChkType UART_Read(uint8_t *ReceivedData)
{ 
	UART_ChkType RetVar;   // variable for the return value
	if( (UART_CSRA_R & (1<<RXC)) ==1) //wait until the receiving complete RXCn
	{
			*ReceivedData = UART_DR_R;
			RetVar = UART_OK;
	}
	else
	{
			RetVar = UART_NOK;
	}			
	return RetVar;

}
























