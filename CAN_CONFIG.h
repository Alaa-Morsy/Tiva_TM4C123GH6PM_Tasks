/***************************************************************************************************************************************************/
/*                                                             CAN Configuration Library                                                   */
/* File Name : CAN_CONFIG.h                                                                                                                   */
/* Aurthor   : Alaa Mohamed MOrsy                                                                                                                  */
/* Date      : 03 SEP 2021                                                                                                                         */
/* Version   : 1.0.0                                                                                                                               */
/* MC        : Tiva TM4C123GH6PM                                                                                                                   */
/* Layer     : MCAL				 																	    										   */                                                                                                                                   
/***************************************************************************************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "CAN_PRIVAT_DEC.h"

#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H

/*
    Enumerations to contrust on demand:
*/

typedef enum {      // in RCC register --> clock configuration
	sysclk,        //BYPASS =0 
	externalclk    //BYPASS =1 
}clk_type;

typedef enum {         //Possible System Clock Frequencies Using the SYSDIV Field
	SYSCTL_SYSDIV_1  ,
    SYSCTL_SYSDIV_2  ,
	SYSCTL_SYSDIV_3  ,
	SYSCTL_SYSDIV_4  ,
	SYSCTL_SYSDIV_5  ,
	SYSCTL_SYSDIV_6  , 
	SYSCTL_SYSDIV_7  ,
	SYSCTL_SYSDIV_8  ,
	SYSCTL_SYSDIV_9  ,
	SYSCTL_SYSDIV_10 , 
	SYSCTL_SYSDIV_11 ,
	SYSCTL_SYSDIV_12 ,
	SYSCTL_SYSDIV_13 ,
	SYSCTL_SYSDIV_14 ,
	SYSCTL_SYSDIV_15 ,
	SYSCTL_SYSDIV_16
	
}clk_freq;

typedef enum {       //used to Select the crystal value attached to the main oscillator
	XTAL6 =0x06 ,
	XTAL7=0x07 ,
	XTAL8=0x08 ,
	XTAL9=0x09 ,
	XTALA=0x0A ,
	XTALB=0x0B ,
	XTALC=0x0C ,
	XTALD=0x0D ,
	XTALE=0x0E ,
	XTALF=0x0F ,
	XTAL10=0x10 ,
	XTAL11=0x11 ,
	XTAL12=0x12 ,
	XTAL13=0x13 ,
	XTAL14=0x14 ,
	XTAL15=0x15 ,
	XTAL16=0x16 ,
	XTAL17=0x17 ,
	XTAL18=0x18 ,
    XTAL19=0x19 ,
    XTAL1A=0x1A
}XTAL_crystal;

typedef enum {  //Oscillator Source Selection
	MOSC= 0x0 ,  //Main oscillator
   PIOSC= 0x1 ,  //Precision internal oscillator (default)
   PIOSC4= 0x2 , // Precision internal oscillator / 4 
   LFIOSC= 0x3  //Low-frequency internal oscillator

}OSC ;

 union
{
  uint32_t allFields;
  struct {
	     vuint32_t MOSCDIS   :1  ;
	     vuint32_t reserved1 :3  ;
	     vuint32_t OSCSRC    :2  ;
	     vuint32_t XTAL      :5  ;
	     vuint32_t BYPASS    :1  ;
	     vuint32_t reserved2 :1  ;
	     vuint32_t PWRDN     :1  ;
	     vuint32_t reserved3 :3  ;
	     vuint32_t PWMDIV    :3  ;
 	     vuint32_t USEPWMDIV :1  ;
 	     vuint32_t SYSDIV    :4  ;
 	     vuint32_t ACG       :1  ;
	     vuint32_t reserved4 :4  ;
      } ;      //Configuration of Run-Mode Clock Configuration register (RCC)

}RCC_t;
 
typedef struct {
	uint32_t SyncPropPhase1Seg;
	uint32_t Phase2Seg;
	uint32_t SJW;
	uint32_t BRprescaler ; 
}CANBitClkParms;

typedef enum {
	MSg1 = 0x01,
	MSg2 = 0x02,
	MSg3 = 0x03,
	MSg4 = 0x04,
	MSg5 = 0x05,
	MSg6 = 0x06,
	MSg7 = 0x07,
	MSg8 = 0x08,
	MSg9 = 0x09,
	MSg10 = 0x0A,
	MSg11 = 0x0B,
	MSg12 = 0x0C,
	MSg13 = 0x0D,
	MSg14 = 0x0E,
	MSg15 = 0x0F,
	MSg16 = 0x10,
	MSg17 = 0x11,
	MSg18 = 0x12,
	MSg19 = 0x13,
	MSg20 = 0x14,
	MSg21 = 0x15,
	MSg22 = 0x16,
	MSg23 = 0x17,
	MSg24 = 0x18,
	MSg25 = 0x19,
	MSg26 = 0x1A,
	MSg27 = 0x1B,
	MSg28 = 0x1C,
	MSg29 = 0x1D,
	MSg30 = 0x1E,
	MSg31 = 0x1F,
	MSg32 = 0x20,
	
}MSgID;

typedef enum {
	ZERO_BYTE  = 0,
	ONE_BYTE   = 1,
	TWO_BYTE   = 2,
	THREE_BYTE = 3,
	FOUR_BYTE  = 4,
	FIVE_BYTE  = 5,
	SIX_BYTE   = 6,
	SEVEN_BYTE = 7,
	EIGHT_BYTE = 8,
}CAN_MSG_LENGTH;
        
typedef struct {
	
	uint32_t Msg_ID;
	uint32_t Flags;
	CAN_MSG_LENGTH Msg_Length;
	u8 *Msg_Data;		// Array
	
}CANConfigTXMessage;

typedef struct {
	
	CAN_MSG_LENGTH Msg_Length;
	u8 Msg_Data[CAN_MAX_DATA_LENGTH];		// Array
	
}CANReadRXData;


typedef enum {
	STANDARD_FRAME = 0,
	EXTENDED_FRAME = 1
}CANFRAME_TYPE;

typedef struct {
	
	uint32_t Msg_ID;
	uint32_t Msg_ID_MSK;
	uint32_t Flags;
	
}CANConfigRXMessage;

/***********************************************************************************************************/
/*                                              PROTOTYPES                                                 */
/***********************************************************************************************************/
void CANTiming (clk_type BYPASS_clk , clk_freq SYS_divisor,XTAL_crystal crystalFreq, OSC OSC_TYPE);
void GPIO_Init(u8 CAN_MOD);
void CAN_Init (u8 CAN_MOD,CANBitClkParms *ClkParam);
void CANTransmitMessage (u8 CAN_MOD, MSgID ObjID, CANConfigTXMessage *MsgObject);
void CANReceiveMessage (u8 CAN_MOD, MSgID ObjID, CANConfigRXMessage *MsgObject);
void CANMessageGet (u8 CAN_MOD, MSgID ObjID, CANReadRXData *psMsgObject);




#endif