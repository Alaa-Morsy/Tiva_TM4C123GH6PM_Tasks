/***************************************************************************************************************************************************/
/*                                                             Bit Math Library                                                              */
/* File Name : BIT_MATH.h                                                                                                                         */
/* Aurthor   : Alaa Mohamed MOrsy                                                                                                                  */
/* Date      : 10 SEP 2021                                                                                                                         */
/* Version   : 1.0.0                                                                                                                               */
/* MC        : Tiva™ TM4C123GH6PM                                                                                                                  */                                                                                                                              
/***************************************************************************************************************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

  #define SET_BIT(REG,BIT_NO)        (REG) |=  (1<<(BIT_NO))
  #define CLR_BIT(REG,BIT_NO)        (REG) &= ~(1<<(BIT_NO))
  
  
#endif