/***************************************************************************************************************************************************/
/*                                                            CAN Driver file                                                                     */
/* File Name : CAN_Driver.c                                                                                                                       */
/* Aurthor   : Alaa Mohamed MOrsy                                                                                                                  */
/* Date      : 10 SEP 2021                                                                                                                         */
/* Version   : 2.0.0                                                                                                                               */
/* MC        : Tiva TM4C123GH6PM                                                                                                                  */    
/***************************************************************************************************************************************************/


#include "CAN_CONFIG.h"
/*
* This is the frist time in my life to make a driver :')
* So i tried hard to make the it is 
* This driver is implimented without using interrupts
* I used the declaration of both CAN0 & CAN1 Base Addresses which wasn't the best way
* to make this driver.
* 
*/
/***************************************************************************************************************************************************/
// Function
void Delay (uint32_t counter)
{
	uint32_t i=0 ; 
	for (i ; i<counter ; i++);
}
/***************************************************************************************************************************************************/
/*                                                             Initialization                                                                      */
/***************************************************************************************************************************************************/

void GPIO_Init(u8 CAN_MOD)
{
	if (CAN_MOD == CAN_MOD0){
/***************************************************************************************************************************************************/
/*                                                              CAN Module 0                                                                       */
/***************************************************************************************************************************************************/
    SET_BIT ( RCGC0 , CAN0_CGC );      // the module receives a clock and functions, so a read or write to the module does not generate a bus fault.
	RCGC2 = CAN0_GPIO_C_EN      ;      // Enable the clock to the appropriate GPIO module -> ports (B,E,F) 
    SET_BIT ( RCGCCAN, HEX0    );	
	Delay(HEX3);                        // delay 3 system clock
	
	/* Set the GPIO AFSEL bits for the appropriate pins where :
	     CAN0_RX -> PB4 , PE0 , PF0
		 CAN0_TX -> PB5 , PE5 ,PF1
	*/
	
	GPIOAFSEL_B = HEX30        ;       //Enable Alternate fun. for pins PB4 ,PB5
	GPIOAFSEL_E = HEX21        ;       //                               PE0 ,PE5
	GPIOAFSEL_F = HEX3         ;       //                               PF0 ,PF1
	
	GPIOPCTL_B = PMC_45        ;       //Select CAN peripheral function for pins PB4, PB5
	GPIOPCTL_E = PMC_05        ;       //                                        PE0 ,PE5
	GPIOPCTL_F = PMC_01        ;       //                                        PF0 ,PF1
	
	GPIODEN_B  = HEX30         ;       //Make  pins PB4 ,PB5 digital to drive a logic value on the pin and 
	GPIODEN_E  = HEX21         ;       //           PE0 ,PE5            allow the pin voltage into the GPIO receiver.
	GPIODEN_F  = HEX3          ;       //           PF0 ,PF1
	}
	else {
/***************************************************************************************************************************************************/
/*                                                              CAN Module 1                                                                       */
/***************************************************************************************************************************************************/
    SET_BIT ( RCGC0 , CAN1_CGC );      // the module receives a clock and functions, so a read or write to the module does not generate a bus fault.
	SET_BIT ( RCGC2 , HEX0     );      // Enable the clock to the appropriate GPIO module -> ports (A)  
	SET_BIT ( RCGCCAN, HEX1    );
	Delay(HEX3);                       // delay 3 system clock
	
	/* Set the GPIO AFSEL bits for the appropriate pins where :
	     CAN1_RX -> PA0
		 CAN1_TX -> PA1
	*/
	  
    GPIOAFSEL_A = HEX3         ;        //Enable Alternate fun. for pins PA0 ,PA1
	GPIOPCTL_A  = PMC_01       ;        //Select CAN peripheral function for pins PA0,PA1
	GPIODEN_A   = HEX3         ;        //Make pins PA0 ,PA1 digital
	
	}	
}



void CAN_Init (u8 CAN_MOD,CANBitClkParms *ClkParam) // CAN clock Parameters
{
	
   if (CAN_MOD == CAN_MOD0){
	/*****Software Initialization *****/
	CAN0CTL   = HEX41          ;      // INIT,CCE Bits initialization (INIT -> Initialization of CAN0 started)
	                                  //CCE -> Configuration Change Enable,Write accesses to the CANBIT register 
	/*
	* WE will work on the default RCC  configuration 
	* To change working with the Main Ocillator or any other parameters on Frequency
	* You may use CANTiming function
	*/
	CAN0BIT &= ~(HEXall);                                          // Clearing all Bits
	CAN0BIT |= (ClkParam->BRprescaler -HEX1);                      // Baud rate Prescaler
    CAN0BIT |= ((ClkParam -> SJW - HEX1) << HEX6);                 //Phase2_SEG SET 
    CAN0BIT |= ((ClkParam -> SyncPropPhase1Seg - HEX1) << HEX8);   //Prop_SEG + Phase1_SEG SET 
    CAN0BIT |=  ((ClkParam -> Phase2Seg - HEX1) << HEXC);          //SJW_SEG SET 
	
	CLR_BIT( CAN0CTL ,HEX0 );       //Clear INIT bit to end initialization
	
   }
   else{
	    /*****Software Initialization *****/
	CAN1CTL    = HEX41         ;         // INIT,CCE Bits initialization (INIT -> Initialization of CAN1 started)
	                                     //CCE -> Configuration Change Enable,Write accesses to the CANBIT register 
	/*
	* WE will work on the default RCC  configuration 
	* To change working with the Main Ocillator or any other parameters on Frequency
	* You may use CANTiming function
	*/
	CAN1BIT &= ~(HEXall);                                          // Clearing all Bits
	CAN1BIT |= (ClkParam->BRprescaler -HEX1);                      // Baud rate Prescaler
    CAN1BIT |= ((ClkParam -> SJW - HEX1) << HEX6);                 //Phase2_SEG SET 
    CAN1BIT |= ((ClkParam -> SyncPropPhase1Seg - HEX1) << HEX8);   //Prop_SEG + Phase1_SEG SET 
    CAN1BIT |=  ((ClkParam -> Phase2Seg - HEX1) << HEXC);          //SJW_SEG SET 
	
	CLR_BIT( CAN1CTL ,HEX0 );       //Clear INIT bit to end initialization
   }
}                           


/******************************* CAN Timing ****************************************************************/
void CANTiming (clk_type BYPASS_clk , clk_freq SYS_divisor,XTAL_crystal crystalFreq, OSC OSC_TYPE)
{
	
	RCC_t.BYPASS = BYPASS_clk ;
	RCC_t.SYSDIV = SYS_divisor;
	RCC_t.XTAL   = crystalFreq;
	RCC_t.OSCSRC = OSC_TYPE;
	
	if (OSC_TYPE == MOSC) //Main oscillator source
	{
		RCC_t.MOSCDIS = HEX0;  // The main oscillator is enabled.
	}
	else{
		RCC_t.MOSCDIS = HEX1;  //The main oscillator is disabled (default).
	}
	RCC_t.USEPWMDIV = HEX0;   // disable PWM Clock Divisor
	RCC_t.PWMDIV    = HEX7;   //default PWM Unit Clock Divisor 
	RCC_t.PWRDN     = HEX0;   //The PLL is operating normally
	RCC |= RCC_t.allFields  ;
	RCC2 &=~(HEX_LB); //ensure that bit USERCC2 is cleared, The RCC register fields are used, and the fields in RCC2 are ignored.
}

void CANTransmitMessage (u8 CAN_MOD, MSgID ObjID, CANConfigTXMessage *MsgObject){
	if (CAN_MOD == CAN_MOD0){
		
		CLR_BIT(CAN0IF1ARB2, HEXF);    // To change the configuration of a message object during normal operation

		 CANFRAME_TYPE Frame_Type = STANDARD_FRAME;

		// Check the message ID
		if(((MsgObject -> Msg_ID) > CAN_MAX_STANDARD_ID) && ((MsgObject -> Msg_ID) < CAN_MAX_EXTENDED_ID) && (MsgObject->Flags & HEXE)){
			
			 Frame_Type = EXTENDED_FRAME;
			
		} else if((MsgObject -> Msg_ID) > CAN_MAX_EXTENDED_ID){
			 return;    //Unvalid Msg ID
		}

		SET_BIT(CAN0IF1CMSK, HEX7);		     // Set WRNRD bit = 1
		SET_BIT(CAN0IF1CMSK, HEX5);			 // Set ARB bit to enable access arbitration bits
		SET_BIT(CAN0IF1CMSK, HEX4);	        // Set Control bit to enable access control bits
		SET_BIT(CAN0IF1CMSK, HEX1);		    // Access Data Bytes 0 to 3
		SET_BIT(CAN0IF1CMSK, HEX0);		    // Access Data Bytes 4 to 7

		/*******************STANDARD FRAME*******************/
		if(Frame_Type == STANDARD_FRAME){
			
			CLR_BIT(CAN0IF1ARB2, HEXF);
			CLR_BIT(CAN0IF1MSK2, HEXF);
			
			CAN0IF1ARB2 &= ~(0x1FFF);								 // First clear ARB2 Field
			CAN0IF1ARB2 |= ((MsgObject->Msg_ID) << HEX2);	// Write the message ID
			
			
		}
		/*******************EXTENDED FRAME*******************/
		 else if (Frame_Type == EXTENDED_FRAME){
			
			SET_BIT(CAN0IF1ARB2, HEXF);
			CLR_BIT(CAN0IF2MSK2, HEXF);
			
			 CAN0IF1ARB1 &= ~HEXall;									   // First clear ARB1 Field
			 CAN0IF1ARB1 |= (MsgObject->Msg_ID & 0x0000FFFF);		      // Write first part of ID
			
			 CAN0IF1ARB2 &= ~(0x1FFF);									 // First clear ARB2 Field
			 CAN0IF1ARB2 |= ((MsgObject->Msg_ID & 0x1FFF0000) >> HEX10);	// Write Second part of ID
			
		}
		 
			// Set Direction bit to indicate transmit message object
			SET_BIT(CAN0IF1ARB2, HEXD);
			
			if(MsgObject->Flags & HEXB){
					SET_BIT(CAN0IF1MCTL, HEXB);				// enable interrupt on successful transmission
			}
			

		// Set message Valid bit
		SET_BIT(CAN0IF1ARB2, HEXF);
		// Mark this bit as end of buffer because no use of FIFOs in transmit mode
		SET_BIT(CAN0IF1MCTL, HEX7);
			

		  CAN0IF1MCTL &= ~HEXF;			            //First clear DLC Field
		  CAN0IF1MCTL |= MsgObject->Msg_Length;	// Write the message length code

		 (CAN0IF1CRQ) = ObjID;				// Write Message number into MNUM field to start transfer
	}
/***************************************************************************************************************************************************/
/*                                                              CAN Module 1                                                                       */
/***************************************************************************************************************************************************/
	else{
		CLR_BIT(CAN1IF1ARB2, HEXF);    // To change the configuration of a message object during normal operation

		 CANFRAME_TYPE Frame_Type = STANDARD_FRAME;

		// Check the message ID
		if(((MsgObject -> Msg_ID) > CAN_MAX_STANDARD_ID) && ((MsgObject -> Msg_ID) < CAN_MAX_EXTENDED_ID) && (MsgObject->Flags & HEXE)){
			
			 Frame_Type = EXTENDED_FRAME;
			
		} else if((MsgObject -> Msg_ID) > CAN_MAX_EXTENDED_ID){
			 return;    //Unvalid Msg ID
		}

		SET_BIT(CAN1IF1CMSK, HEX7);		     // Set WRNRD bit = 1
		SET_BIT(CAN1IF1CMSK, HEX5);			 // Set ARB bit to enable access arbitration bits
		SET_BIT(CAN1IF1CMSK, HEX4);	        // Set Control bit to enable access control bits
		SET_BIT(CAN1IF1CMSK, HEX1);		    // Access Data Bytes 0 to 3
		SET_BIT(CAN1IF1CMSK, HEX0);		    // Access Data Bytes 4 to 7

		/*******************STANDARD FRAME*******************/
		if(Frame_Type == STANDARD_FRAME){
			
			CLR_BIT(CAN1IF1ARB2, HEXF);
			CLR_BIT(CAN1IF1MSK2, HEXF);
			
			CAN1IF1ARB2 &= ~(0x1FFF);								 // First clear ARB2 Field
			CAN1IF1ARB2 |= ((MsgObject->Msg_ID) << HEX2);	// Write the message ID
			
			
		}
		/*******************EXTENDED FRAME*******************/
		 else if (Frame_Type == EXTENDED_FRAME){
			
			SET_BIT(CAN1IF1ARB2, HEXF);
			CLR_BIT(CAN1IF2MSK2, HEXF);
			
			 CAN1IF1ARB1 &= ~HEXall;									   // First clear ARB1 Field
			 CAN1IF1ARB1 |= (MsgObject->Msg_ID & 0x0000FFFF);		      // Write first part of ID
			
			 CAN1IF1ARB2 &= ~(0x1FFF);									 // First clear ARB2 Field
			 CAN1IF1ARB2 |= ((MsgObject->Msg_ID & 0x1FFF0000) >> HEX10);	// Write Second part of ID
			
		}
		 
			// Set Direction bit to indicate transmit message object
			SET_BIT(CAN1IF1ARB2, HEXD);
			
			if(MsgObject->Flags & HEXB){
					SET_BIT(CAN1IF1MCTL, HEXB);				// enable interrupt on successful transmission
			}
			

		// Set message Valid bit
		SET_BIT(CAN1IF1ARB2, HEXF);
		// Mark this bit as end of buffer because no use of FIFOs in transmit mode
		SET_BIT(CAN1IF1MCTL, HEX7);
			

		  CAN1IF1MCTL &= ~HEXF;			            //First clear DLC Field
		  CAN1IF1MCTL |= MsgObject->Msg_Length;	// Write the message length code

		 (CAN1IF1CRQ) = ObjID;				// Write Message number into MNUM field to start transfer
	
	}
	
}


void CANReceiveMessage (u8 CAN_MOD, MSgID ObjID, CANConfigRXMessage *MsgObject){
	if (CAN_MOD == CAN_MOD0){
		CLR_BIT(CAN0IF2ARB2, HEXF);
	
		CANFRAME_TYPE Frame_Type = STANDARD_FRAME;
		
		// Check the message ID
		if(((MsgObject -> Msg_ID) > CAN_MAX_STANDARD_ID) && ((MsgObject -> Msg_ID) < CAN_MAX_EXTENDED_ID) && (MsgObject->Flags & HEXE)){
			
			 Frame_Type = EXTENDED_FRAME;
			
		} else if((MsgObject -> Msg_ID) > CAN_MAX_EXTENDED_ID){
			 return;    //UNValid Msg ID
		}
		
		// Check using mask or not
		if(MsgObject->Flags & HEXC){
			
			SET_BIT(CAN0IF2MCTL, HEXC);           //Use Acceptance Mask
			SET_BIT(CAN0IF2CMSK, HEX6);			 // Set Mask bit
		}
		
		SET_BIT(CAN0IF2CMSK, HEX7);		   // Set WRNRD bit = 1
		SET_BIT(CAN0IF2CMSK, HEX5);			 // Set ARB bit to enable access arbitration bits
		SET_BIT(CAN0IF2CMSK, HEX4);	         // Set Control bit to enable access control bits
		SET_BIT(CAN0IF2CMSK, HEX1);		     // Access Data Bytes 0 to 3
		SET_BIT(CAN0IF2CMSK, HEX0);		     // Access Data Bytes 4 to 7
		
		/*******************STANDARD FRAME*******************/
		if(Frame_Type == STANDARD_FRAME){
			
			CLR_BIT(CAN0IF2ARB2, HEXF);

			if(MsgObject->Flags & HEXD){
			
				 (CAN0IF2MSK2) &= ~(0x1FFF);						   // First clear Mask2 Field
				 (CAN0IF2MSK2) |= ((MsgObject->Msg_ID_MSK) << 2); // Write the ID mask
				CLR_BIT(CAN0IF2MSK2, HEXF);					 // Clear MXTD Bit
				SET_BIT(CAN0IF2MSK2, HEXE);					   // The message direction DIR bit is used for acceptance filtering
			}
			
			 CAN0IF2ARB2 &= ~(0x1FFF);								  // First clear ARB2 Field
			 CAN0IF2ARB2 |= ((MsgObject->Msg_ID) << HEX2);	// Write the message ID
			
		}
		/*******************EXTENDED FRAME*******************/
		 else if (Frame_Type == EXTENDED_FRAME){
			
			SET_BIT(CAN0IF2ARB2, HEXF);
			
			if(MsgObject->Flags & HEXD){
				
					 CAN0IF1CMSK1 &= ~HEXall;						                // First clear Mask1 Field
					 CAN0IF1CMSK1 |= (MsgObject->Msg_ID_MSK & 0x0000FFFF);	// Write first part of ID_MSK
					
					 CAN0IF2MSK2 &= ~(0x1FFF);						                // First clear Mask2 Field
					 CAN0IF2MSK2 |= ((MsgObject->Msg_ID_MSK & 0x1FFF0000) >> HEX10);	// Write Second part of ID_MSK
					SET_BIT(CAN0IF2MSK2, HEXF);						              // Set MXTD Bit
					SET_BIT(CAN0IF2MSK2, HEXE);					                // The message direction DIR bit is used for acceptance filtering
			}
			 CAN0IF2ARB1 &= ~HEXall;													      // First clear ARB1 Field
			 CAN0IF2ARB1 |= (MsgObject->Msg_ID & 0x0000FFFF);		      // Write first part of ID
			
			 CAN0IF2ARB2 &= ~(0x1FFF);													      // First clear ARB2 Field
			 CAN0IF2ARB2 |= ((MsgObject->Msg_ID & 0x1FFF0000) >> HEX10);	// Write Second part of ID
			
		}
		 
			// Clear Direction bit to indicate Receive message object
			CLR_BIT(CAN0IF2ARB2, HEXD);
			
			if(MsgObject->Flags & HEXB){
					SET_BIT(CAN0IF2MCTL, HEXB);		// enable interrupt on successful reception
			}
			
			
		// Set message Valid bit
		SET_BIT(CAN0IF2ARB2, HEXF);
		
		// Check using FIFO or not
		if(MsgObject->Flags & HEX1){
			CLR_BIT(CAN0IF2MCTL, HEX7);
		} else{
			SET_BIT(CAN0IF2MCTL, HEX7);
		}
		
		 CAN0IF2CRQ = ObjID;			 // Write Message number into MNUM field to start transfer
	}
/***************************************************************************************************************************************************/
/*                                                              CAN Module 1                                                                       */
/***************************************************************************************************************************************************/
	else{
		CLR_BIT(CAN1IF2ARB2, HEXF);
	
		CANFRAME_TYPE Frame_Type = STANDARD_FRAME;
		
		// Check the message ID
		if(((MsgObject -> Msg_ID) > CAN_MAX_STANDARD_ID) && ((MsgObject -> Msg_ID) < CAN_MAX_EXTENDED_ID) && (MsgObject->Flags & HEXE)){
			
			 Frame_Type = EXTENDED_FRAME;
			
		} else if((MsgObject -> Msg_ID) > CAN_MAX_EXTENDED_ID){
			 return;    //UNValid Msg ID
		}
		
		// Check using mask or not
		if(MsgObject->Flags & HEXC){
			
			SET_BIT(CAN1IF2MCTL, HEXC);                                   //Use Acceptance Mask
			SET_BIT(CAN1IF2CMSK, HEX6);			 // Set Mask bit
		}
		
		SET_BIT(CAN1IF2CMSK, HEX7);		   // Set WRNRD bit = 1
		SET_BIT(CAN1IF2CMSK, HEX5);			 // Set ARB bit to enable access arbitration bits
		SET_BIT(CAN1IF2CMSK, HEX4);	         // Set Control bit to enable access control bits
		SET_BIT(CAN1IF2CMSK, HEX1);		     // Access Data Bytes 0 to 3
		SET_BIT(CAN1IF2CMSK, HEX0);		     // Access Data Bytes 4 to 7
		
		/*******************STANDARD FRAME*******************/
		if(Frame_Type == STANDARD_FRAME){
			
			CLR_BIT(CAN1IF2ARB2, HEXF);

			if(MsgObject->Flags & HEXD){
			
				 (CAN1IF2MSK2) &= ~(0x1FFF);						   // First clear Mask2 Field
				 (CAN1IF2MSK2) |= ((MsgObject->Msg_ID_MSK) << 2); // Write the ID mask
				CLR_BIT(CAN1IF2MSK2, HEXF);					 // Clear MXTD Bit
				SET_BIT(CAN1IF2MSK2, HEXE);					   // The message direction DIR bit is used for acceptance filtering
			}
			
			 CAN1IF2ARB2 &= ~(0x1FFF);								  // First clear ARB2 Field
			 CAN1IF2ARB2 |= ((MsgObject->Msg_ID) << HEX2);	// Write the message ID
			
		}
		/*******************EXTENDED FRAME*******************/
		 else if (Frame_Type == EXTENDED_FRAME){
			
			SET_BIT(CAN1IF2ARB2, HEXF);
			
			if(MsgObject->Flags & HEXD){
				
					 CAN1IF1CMSK1 &= ~HEXall;						                // First clear Mask1 Field
					 CAN1IF1CMSK1 |= (MsgObject->Msg_ID_MSK & 0x0000FFFF);	// Write first part of ID_MSK
					
					 CAN1IF2MSK2 &= ~(0x1FFF);						                // First clear Mask2 Field
					 CAN1IF2MSK2 |= ((MsgObject->Msg_ID_MSK & 0x1FFF0000) >> HEX10);	// Write Second part of ID_MSK
					SET_BIT(CAN1IF2MSK2, HEXF);						              // Set MXTD Bit
					SET_BIT(CAN1IF2MSK2, HEXE);					                // The message direction DIR bit is used for acceptance filtering
			}
			 CAN1IF2ARB1 &= ~HEXall;													      // First clear ARB1 Field
			 CAN1IF2ARB1 |= (MsgObject->Msg_ID & 0x0000FFFF);		      // Write first part of ID
			
			 CAN1IF2ARB2 &= ~(0x1FFF);													      // First clear ARB2 Field
			 CAN1IF2ARB2 |= ((MsgObject->Msg_ID & 0x1FFF0000) >> HEX10);	// Write Second part of ID
			
		}
		 
			// Clear Direction bit to indicate Receive message object
			CLR_BIT(CAN1IF2ARB2, HEXD);
			
			if(MsgObject->Flags & HEXB){
					SET_BIT(CAN1IF2MCTL, HEXB);		// enable interrupt on successful reception
			}
			
			
		// Set message Valid bit
		SET_BIT(CAN1IF2ARB2, HEXF);
		
		// Check using FIFO or not
		if(MsgObject->Flags & HEX1){
			CLR_BIT(CAN1IF2MCTL, HEX7);
		} else{
			SET_BIT(CAN1IF2MCTL, HEX7);
		}
		
		 CAN1IF2CRQ = ObjID;
	}
}



void CANMessageGet (u8 CAN_MOD, MSgID ObjID, CANReadRXData *psMsgObject)
{
   if (CAN_MOD == CAN_MOD0){
		CLR_BIT(CAN0IF2CMSK, HEX7);		// clear WRNRD bit = 0
		 CAN0IF2CRQ = ObjID;							// Set the MNUM field to the Message object ID
		
		
		// Reading data and store it into the message objsct data field
		psMsgObject->Msg_Data[0] = ( CAN0IF2DA1 & 0x000000FF);
		psMsgObject->Msg_Data[1] = (( CAN0IF2DA1 &0x0000FF00) >> HEX8);
	
		psMsgObject->Msg_Data[2] = ( CAN0IF2DA2 & 0x000000FF);
		psMsgObject->Msg_Data[3] = (( CAN0IF2DA2 & 0x0000FF00) >> HEX8);
	
		psMsgObject->Msg_Data[4] = ( CAN0IF2DB1 & 0x000000FF);
		psMsgObject->Msg_Data[5] = (( CAN0IF2DB1 & 0x0000FF00) >> HEX8);
	
		psMsgObject->Msg_Data[6] = ( CAN0IF2DB2 & 0x000000FF);
		psMsgObject->Msg_Data[7] = (( CAN0IF2DB2 & 0x0000FF00) >> HEX8);
		
		// Message Length
		psMsgObject->Msg_Length = ( CAN0IF2MCTL & HEXF);
   }
   /***************************************************************************************************************************************************/
   /*                                                              CAN Module 1                                                                       */
   /***************************************************************************************************************************************************/
	else{
		CLR_BIT(CAN1IF2CMSK, HEX7);		// clear WRNRD bit = 0
		 CAN1IF2CRQ = ObjID;							// Set the MNUM field to the Message object ID
		
		
		// Reading data and store it into the message objsct data field
		psMsgObject->Msg_Data[0] = ( CAN1IF2DA1 & 0x000000FF);
		psMsgObject->Msg_Data[1] = (( CAN1IF2DA1 &0x0000FF00) >> HEX8);
	
		psMsgObject->Msg_Data[2] = ( CAN1IF2DA2 & 0x000000FF);
		psMsgObject->Msg_Data[3] = (( CAN1IF2DA2 & 0x0000FF00) >> HEX8);
	
		psMsgObject->Msg_Data[4] = ( CAN1IF2DB1 & 0x000000FF);
		psMsgObject->Msg_Data[5] = (( CAN1IF2DB1 & 0x0000FF00) >> HEX8);
	
		psMsgObject->Msg_Data[6] = ( CAN1IF2DB2 & 0x000000FF);
		psMsgObject->Msg_Data[7] = (( CAN1IF2DB2 & 0x0000FF00) >> HEX8);
		
		// Message Length
		psMsgObject->Msg_Length = ( CAN1IF2MCTL & HEXF);
	}
   		
}
