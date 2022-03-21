/***************************************************************************************************************************************************/
/*                                                             CAN Private Declarations Library                                                   */
/* File Name : CAN_PRIVAT_DEC.h                                                                                                                   */
/* Aurthor   : Alaa Mohamed MOrsy                                                                                                                  */
/* Date      : 03 SEP 2021                                                                                                                         */
/* Version   : 1.0.0                                                                                                                               */
/* MC        : Tiva TM4C123GH6PM                                                                                                                   */
/* Layer     : MCAL				 																	    										   */                                                                                                                                   
/***************************************************************************************************************************************************/


#ifndef CAN_PRIVAT_DEC_H
#define CAN_PRIVAT_DEC_H

/***************************************************************************************************************************************************/
 /*                                                             Base Addresses                                                                     */
 /***************************************************************************************************************************************************/
 
 #define SYSCTL      0x400FE000 //Base system control
 /* GPIO ports */
 #define GPIOA       0x40058000 //Base GPIO PORT A (AHB)
 #define GPIOB       0x40058000 //Base GPIO PORT B (AHB)
 #define GPIOE       0x4005C000 //Base GPIO PORT E (AHB)
 #define GPIOF       0x4005D000 //Base GPIO PORT F (AHB)
 /*CAN base address*/
 #define CAN0        0x40040000 
 #define CAN1        0x40041000
 /***************************************************************************************************************************************************/
 /*                                                              Registers                                                                          */
 /***************************************************************************************************************************************************/
   
   #define RCGC0         *((vuint32_t*)(uint32_t*)(SYSCTL + 0x100)) //Run Mode Clock Gating Control Register 0
   #define RCGC2         *((vuint32_t*)(uint32_t*)(SYSCTL + 0x108)) //Run Mode Clock Gating Control Register 2
   #define RCGCCAN       *((vuint32_t*)(uint32_t*)(SYSCTL + 0x634)) //Controller Area Network Run Mode Clock Gating Control
   #define RCC           *((vuint32_t*)(uint32_t*)(SYSCTL + 0x060)) //Run-Mode Clock Configuration Register
   #define RCC2          *((vuint32_t*)(uint32_t*)(SYSCTL + 0x070)) //Run-Mode Clock Configuration Register 2
   
 /*  GPIO Alternate Function Select */
    #define GPIOAFSEL_A   *((vuint32_t*)(uint32_t*)(GPIOA  + 0x420))     //_PORT A
    #define GPIOAFSEL_B   *((vuint32_t*)(uint32_t*)(GPIOB  + 0x420))     //_PORT B
	#define GPIOAFSEL_E   *((vuint32_t*)(uint32_t*)(GPIOE  + 0x420))     //_PORT E
	#define GPIOAFSEL_F   *((vuint32_t*)(uint32_t*)(GPIOF  + 0x420))     //_PORT F
/*  GPIO Port Control              */
    #define GPIOPCTL_A     *((vuint32_t*)(uint32_t*)(GPIOA  + 0x52C))     //_PORT A
    #define GPIOPCTL_B     *((vuint32_t*)(uint32_t*)(GPIOB  + 0x52C))     //_PORT B
	#define GPIOPCTL_E     *((vuint32_t*)(uint32_t*)(GPIOE  + 0x52C))     //_PORT E
	#define GPIOPCTL_F     *((vuint32_t*)(uint32_t*)(GPIOF  + 0x52C))     //_PORT F
/*  GPIO Digital Enable            */	
	#define GPIODEN_A     *((vuint32_t*)(uint32_t*)(GPIOA  + 0x51C))     //_PORT A
    #define GPIODEN_B     *((vuint32_t*)(uint32_t*)(GPIOB  + 0x51C))     //_PORT B
	#define GPIODEN_E     *((vuint32_t*)(uint32_t*)(GPIOE  + 0x51C))     //_PORT E
	#define GPIODEN_F     *((vuint32_t*)(uint32_t*)(GPIOF  + 0x51C))     //_PORT F
	
 /*  CAN Registers      */
	#define CAN0CTL      *((vuint32_t*)(uint32_t*)(CAN0 + 0x000))        // CAN CONTROL 
	#define CAN1CTL      *((vuint32_t*)(uint32_t*)(CAN1 + 0x000))        //     This control register initializes the module
	#define CAN0BIT      *((vuint32_t*)(uint32_t*)(CAN0 + 0x00C))        // CAN Bit Timing
	#define CAN1BIT      *((vuint32_t*)(uint32_t*)(CAN1 + 0x00C))        
	#define CAN0IF1ARB1  *((vuint32_t*)(uint32_t*)(CAN0 + 0x030))        //CAN IF1 Arbitration 1
	#define CAN1IF1ARB1  *((vuint32_t*)(uint32_t*)(CAN1 + 0x030))        //      hold the identifiers for acceptance filtering
	#define CAN0IF2ARB1  *((vuint32_t*)(uint32_t*)(CAN0 + 0x090))        //CAN IF2 Arbitration 1
	#define CAN1IF2ARB1  *((vuint32_t*)(uint32_t*)(CAN1 + 0x090))
    #define CAN0IF1ARB2  *((vuint32_t*)(uint32_t*)(CAN0 + 0x034))        //CAN IF1 Arbitration 2
    #define CAN1IF1ARB2  *((vuint32_t*)(uint32_t*)(CAN1 + 0x034))
	#define CAN0IF2ARB2  *((vuint32_t*)(uint32_t*)(CAN0 + 0x094))        //CAN IF2 Arbitration 2
    #define CAN1IF2ARB2  *((vuint32_t*)(uint32_t*)(CAN1 + 0x094))
	#define CAN0IF1CMSK  *((vuint32_t*)(uint32_t*)(CAN0 + 0x024))       //CAN IF1 Command Mask 
	#define CAN1IF1CMSK  *((vuint32_t*)(uint32_t*)(CAN1 + 0x024)) 
    #define CAN0IF2CMSK  *((vuint32_t*)(uint32_t*)(CAN0 + 0x084))       //CAN IF2 Command Mask 
	#define CAN1IF2CMSK  *((vuint32_t*)(uint32_t*)(CAN1 + 0x084))
	#define CAN0IF1CMSK1  *((vuint32_t*)(uint32_t*)(CAN0 + 0x028))       //CAN IF1 Command Mask 1
	#define CAN1IF1CMSK1  *((vuint32_t*)(uint32_t*)(CAN1 + 0x028)) 
    #define CAN0IF2CMSK1  *((vuint32_t*)(uint32_t*)(CAN0 + 0x088))       //CAN IF2 Command Mask 1
	#define CAN1IF2CMSK1  *((vuint32_t*)(uint32_t*)(CAN1 + 0x088))
	#define CAN0IF1MSK2  *((vuint32_t*)(uint32_t*)(CAN0 + 0x02C))       //CAN IF1 Mask 2 
	#define CAN1IF1MSK2  *((vuint32_t*)(uint32_t*)(CAN1 + 0x02C))
	#define CAN0IF2MSK2  *((vuint32_t*)(uint32_t*)(CAN0 + 0x08C))       //CAN IF2 Mask 2
	#define CAN1IF2MSK2  *((vuint32_t*)(uint32_t*)(CAN1 + 0x08C))
	#define CAN0IF1MCTL  *((vuint32_t*)(uint32_t*)(CAN0 + 0x038))       //CAN IF1 Message Control
	#define CAN1IF1MCTL  *((vuint32_t*)(uint32_t*)(CAN1 + 0x038))
	#define CAN0IF2MCTL  *((vuint32_t*)(uint32_t*)(CAN0 + 0x098))       //CAN IF2 Message Control
	#define CAN1IF2MCTL  *((vuint32_t*)(uint32_t*)(CAN1 + 0x098))
	#define CAN0IF1CRQ   *((vuint32_t*)(uint32_t*)(CAN0 + 0x020))       //CAN IF1 Command Request
	#define CAN1IF1CRQ   *((vuint32_t*)(uint32_t*)(CAN1 + 0x020)) 
    #define CAN0IF2CRQ   *((vuint32_t*)(uint32_t*)(CAN0 + 0x080))       //CAN IF2 Command Request
	#define CAN1IF2CRQ   *((vuint32_t*)(uint32_t*)(CAN1 + 0x080)) 
	
	#define CAN0IF1DA1   *((vuint32_t*)(uint32_t*)(CAN0 + 0x03C))      //CAN IF1 Data A1 
	#define CAN0IF1DA2   *((vuint32_t*)(uint32_t*)(CAN0 + 0x040))      //CAN IF1 Data A2 
	#define CAN0IF1DB1   *((vuint32_t*)(uint32_t*)(CAN0 + 0x044))
	#define CAN0IF1DB2   *((vuint32_t*)(uint32_t*)(CAN0 + 0x048)) 
	#define CAN0IF2DA1   *((vuint32_t*)(uint32_t*)(CAN0 + 0x09C))      //CAN IF2 Data A2 
	#define CAN0IF2DA2   *((vuint32_t*)(uint32_t*)(CAN0 + 0x0A0))      //CAN IF2 Data A2 
	#define CAN0IF2DB1   *((vuint32_t*)(uint32_t*)(CAN0 + 0x0A4)) 
	#define CAN0IF2DB2   *((vuint32_t*)(uint32_t*)(CAN0 + 0x0A8))
	#define CAN1IF1DA1   *((vuint32_t*)(uint32_t*)(CAN1 + 0x03C))
	#define CAN1IF1DA2   *((vuint32_t*)(uint32_t*)(CAN1 + 0x040)) 
	#define CAN1IF1DB1   *((vuint32_t*)(uint32_t*)(CAN1 + 0x044))
	#define CAN1IF1DB2   *((vuint32_t*)(uint32_t*)(CAN1 + 0x048)) 
	#define CAN1IF2DA1   *((vuint32_t*)(uint32_t*)(CAN1 + 0x09C))
	#define CAN1IF2DA2   *((vuint32_t*)(uint32_t*)(CAN1 + 0x0A0))
	#define CAN1IF2DB1   *((vuint32_t*)(uint32_t*)(CAN1 + 0x0A4)) 
	#define CAN1IF2DB2   *((vuint32_t*)(uint32_t*)(CAN1 + 0x0A8))
   
 /***************************************************************************************************************************************************/
 /*                                                            Avoidance of Magic Numbers                                                           */
 /***************************************************************************************************************************************************/
 
 #define CAN_MOD0           0               //Choosing CAN Module CAN0 or CAN1
 #define CAN_MOD1           1
 #define CAN0_CGC        24                // CAN Module 0 Clock Gating Control bit in Run Mode Clock Gating Control Register 0
 #define CAN1_CGC        25                // CAN Module 1 Clock Gating Control bit in Run Mode Clock Gating Control Register 0
 #define CAN0_GPIO_C_EN  0x32         //CAN Module 0 GPIO ports Clock Gating Control Enable ports (B,E,F) 
 
 /****** Max Values ******/
 #define CAN_MAX_STANDARD_ID		0x7FF
 #define CAN_MAX_EXTENDED_ID		0x1FFFFFFF
 #define CAN_MAX_DATA_LENGTH		8
 
 #define HEX0            0x0
 #define HEX1            0x1
 #define HEX2            0x2
 #define HEX3            0x3
 #define HEX4            0x4
 #define HEX5            0x5
 #define HEX6            0x6
 #define HEX7            0x7
 #define HEX8            0x8
 #define HEX9            0x9
 #define HEXA            0xA
 #define HEXB            0xB
 #define HEXC            0xC
 #define HEXD            0xD
#define HEXE            0xE
 #define HEXF            0xF
 #define HEX10           0x10
 #define HEX30           0x30
 #define HEX21           0x21
 #define HEX41           0x41
 #define HEX_LB          0x7FFF  //access Last bit
 #define HEXall          0xFFFF
 
 #define   PMC_45       0x00880000     // Port Mux Control for pin 4 , 5
 #define   PMC_01       0x00000088     // Port Mux Control for pin 0 , 1
 #define   PMC_05       0x00800008     // Port Mux Control for pin 0 , 5

#endif