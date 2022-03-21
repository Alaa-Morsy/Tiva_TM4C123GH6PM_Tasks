/***************************************************************************************************************************************************/
/*                                                             UART Task C file                                                                    */
/* File Name : UART_Task_main.c                                                                                                                         */
/* Aurthor   : Alaa Mohamed MOrsy                                                                                                                  */
/* Date      : 31 AUG 2021                                                                                                                         */
/* Version   : 1.0.0                                                                                                                               */
/* MC        : Tiva TM4C123GH6PM                                                                                                                  */  
/***************************************************************************************************************************************************/

#include <stdio.h>
/* Own Driver Files */
#include "STD_TYPES.h"
#include "UART_PRIVAT_DEC.h"
#include "UART_interface.h"



void main(void)
{

	UART_Init();                 //UART Initialization
	Delay(1);
	Interrupt_enable ();         //Enable UART0 Enable
	Delay(10);
	
	while(1)
	{  
		
	   
	}
}
/**************************************************************************************************************************************************/
/*                                                         UART_Driver                                                                   */
/**************************************************************************************************************************************************/
void Delay (uint32_t counter)
{
	uint32_t i=0 ; 
	for (i ; i<counter ; i++);
}



void UART_Init(void)                       //Initialization 
{
	SET_BIT( RCGCUART , 0 );  //enable UART0
    SET_BIT( RCGCGPIO , 0 );  //enable GPIO PORT A -> UART0
	
	Delay(3);
	
	//GPIO PORT A CONFIG
	GPIODEN    |= 0x03        ;               // PA0 , PA1 as digital 
	GPIOAFSEL  |= 0x03        ;               // Use Alternate fun.
	GPIOPCTL   |= 0x00000011  ; 	    	  // Cofigure for UART module
	GPIOAMSEL   = 0           ;              // disable analog mode
	
	//UART0 CONFIG
	UARTCTL     = 0     ;    		  // Disable UART0
    UARTIBRD    = 104   ;            // for 9600 baud rate 
    UARTFBRD    = 11    ;            // for 9600 baud rate 
	UARTLCRH    = 0x60  ;            // data lenght 8-bit, not parity bit, no FIFO 
	UARTCC      = 0     ;            // Using System Clock
    UARTCTL     = 0x301 ;    		  // Enable UART0
}


char Recieve (void)                           // Reciveing without Interrupt
{   
	char data ;
	while ((UARTFR & 0x10) != 0);   // wait until Rx buffer is not full 
	 data = UARTDR ;               //to recieve from UART data but we want to recieve from PC
	 
	return (char)data;
	
}

void Transmit (char data)
{
	 while ((UARTFR & 0x20) != 0);  // wait until Tx buffer not full 
	 UARTDR = data;
}

void Interrupt_enable (void)
{
	   SET_BIT(UARTIM ,4)      ;       // Enable UART0 interrupt
	   UARTICR &= ~(0x0780)    ;       // Clear  recieve interrupt
	   SET_BIT( EN0, 5)         ;       // Enable UART0 Interrupt 
}

void UART0_Handler (void)                    // Reciveing with interrupt
{
	  char data ;
	  CLR_BIT( UARTICR,4)      ;       // Clear  recieve interrupt
	  data = UARTDR ;               //to recieve from UART data but we want to recieve from PC
	   if ((data >='a')&&(data <='z'))
		{
			data -= UPPER_CASE_CONV ;
			
			Transmit(data);
		}
}