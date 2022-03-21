/***************************************************************************************************************************************************/
/*                                                             UART Private Declarations Library                                                   */
/* File Name : UART_PRIVAT_DEC.h                                                                                                                   */
/* Aurthor   : Alaa Mohamed MOrsy                                                                                                                  */
/* Date      : 31 AUG 2021                                                                                                                         */
/* Version   : 1.0.0                                                                                                                               */
/* MC        : Tiva TM4C123GH6PM                                                                                                                  */                      
/***************************************************************************************************************************************************/


#ifndef UART_PRIVAT_DEC_H
#define UART_PRIVAT_DEC_H

   #define SYSCTL      0x400FE000 //Base system control
     #define RCGCUART    *((vuint32_t*)(uint32_t*)(SYSCTL + 0x618))       //Offset
     #define RCGCGPIO    *((vuint32_t*)(uint32_t*)(SYSCTL + 0x608))       //Offset General-Purpose Input/Output Run Mode Clock Gating Control
	 
   #define GPIOA       0x40058000 //Base GPIO PORT A (AHB)
     #define GPIOAFSEL   *((vuint32_t*)(uint32_t*)(GPIOA  + 0x420))     //Offset GPIO Alternate Function Select 
     #define GPIODEN     *((vuint32_t*)(uint32_t*)(GPIOA  + 0x51C))      //Offset GPIO Digital Enable
     #define GPIOPCTL    *((vuint32_t*)(uint32_t*)(GPIOA  + 0x52C))    //Offset GPIO Port Control 
     #define GPIOAMSEL   *((vuint32_t*)(uint32_t*)(GPIOA  + 0x528))      //Offset GPIO Analog Mode Select
	 
   #define UART0       0x4000C000 //Base UART0
     #define UARTCTL     *((vuint32_t*)(uint32_t*)(UART0 + 0x030))     // Offset UART Control
     #define UARTIBRD    *((vuint32_t*)(uint32_t*)(UART0 + 0x024))      // Offset UART Integer Baud-Rate Divisor
	 #define UARTFBRD    *((vuint32_t*)(uint32_t*)(UART0 + 0x028))      // Offset UART Fractional Baud-Rate Divisor
     #define UARTLCRH    *((vuint32_t*)(uint32_t*)(UART0 + 0x02C))      // Offset UART Line Control
     #define UARTCC      *((vuint32_t*)(uint32_t*)(UART0 + 0xFC8))      // Offset UART Clock Configuration
	 #define UARTFR      *((vuint32_t*)(uint32_t*)(UART0 + 0x018))      // Offset UART Flag
	 #define UARTDR      *((vuint32_t*)(uint32_t*)(UART0 + 0x000))      // Offset UART Data
     
	 #define UARTIM      *((vuint32_t*)(uint32_t*)(UART0 + 0x038))      // Offset UART Masked Interrupt Status 
     #define UARTICR     *((vuint32_t*)(uint32_t*)(UART0 + 0x044))      // Offset UART Interrupt Clear 
	 
	#define NVIC      0xE000E000  //Base Nested Vectored Interrupt Controller
	  #define EN0       *((vuint32_t*)(uint32_t*)(NVIC + 0x100))     //Offset Interrupt 0-31 Set Enable 
 #endif