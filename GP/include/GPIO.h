/* Module Name : GPIO
 * File Name   : GPIO_interface.h
 * Author      : Bishoy Nabil
 * Version     : 3.0
 * Date        : 2/3/2020 */

#ifndef GPIO_H
#define GPIO_H


#include "STDTYPES.h"

typedef struct
{
	volatile u32 *Port;
	         u32  Pin ;
	         u8   Mode;
}PinParam_t;

#define INPUT_ANALOG                          0b0000
#define INPUT_FLOATING                        0b0100
#define INPUT_PULLUP                          0b1000
#define INPUT_PULLDOWN                        0b1000
#define OUTPUT_2MHZ_PUSH_PULL                 0b0010
#define OUTPUT_2MHZ_OPENDRAIN                 0b0110
#define OUTPUT_2MHZ_AF_PUSH_PULL              0b1010
#define OUTPUT_2MHZ_AF_OPENDRAIN              0b1110
#define OUTPUT_10MHZ_PUSH_PULL                0b0001
#define OUTPUT_10MHZ_OPENDRAIN                0b0101
#define OUTPUT_10MHZ_AF_PUSH_PULL             0b1001
#define OUTPUT_10MHZ_AF_OPENDRAIN             0b1101
#define OUTPUT_50MHZ_PUSH_PULL                0b0011
#define OUTPUT_50MHZ_OPENDRAIN                0b0111
#define OUTPUT_50MHZ_AF_PUSH_PULL             0b1011
#define OUTPUT_50MHZ_AF_OPENDRAIN             0b1111

#define PIN0                                  0
#define PIN1                                  1
#define PIN2                                  2
#define PIN3                                  3
#define PIN4                                  4
#define PIN5                                  5
#define PIN6                                  6
#define PIN7                                  7
#define PIN8                                  8
#define PIN9                                  9
#define PIN10                                 10
#define PIN11                                 11
#define PIN12                                 12
#define PIN13                                 13
#define PIN14                                 14
#define PIN15                                 15


#define PORTA                                 ((volatile u32*)0x40010800)
#define PORTB                                 ((volatile u32*)0x40010C00)
#define PORTC                                 ((volatile u32*)0x40011000)

#define SET_PIN0                              0x00000001
#define SET_PIN1                              0x00000002
#define SET_PIN2                              0x00000004
#define SET_PIN3                              0x00000008
#define SET_PIN4                              0x00000010
#define SET_PIN5                              0x00000020
#define SET_PIN6                              0x00000040
#define SET_PIN7                              0x00000080
#define SET_PIN8                              0x00000100
#define SET_PIN9                              0x00000200
#define SET_PIN10                             0x00000400
#define SET_PIN11                             0x00000800
#define SET_PIN12                             0x00001000
#define SET_PIN13                             0x00002000
#define SET_PIN14                             0x00004000
#define SET_PIN15                             0x00008000

#define SET                                   1
#define RESET                                 0

/*
	Port: PORTA
		  PORTB
		  PORTC
		  
	Pin:  PIN0 
	      PIN1 
	      PIN2 
	      PIN3 
	      PIN4 
	      PIN5 
	      PIN6 
	      PIN7 
	      PIN8 
	      PIN9 
	      PIN10
	      PIN11
	      PIN12
	      PIN13
	      PIN14
	      PIN15
		  
	Mode: INPUT_ANALOG             
	      INPUT_FLOATING           
	      INPUT_PULLUP             
	      INPUT_PULLDOWN           
	      OUTPUT_2MHZ_PUSH_PULL    
	      OUTPUT_2MHZ_OPENDRAIN    
	      OUTPUT_2MHZ_AF_PUSH_PULL 
	      OUTPUT_2MHZ_AF_OPENDRAIN 
	      OUTPUT_10MHZ_PUSH_PULL   
	      OUTPUT_10MHZ_OPENDRAIN   
	      OUTPUT_10MHZ_AF_PUSH_PULL
	      OUTPUT_10MHZ_AF_OPENDRAIN
	      OUTPUT_50MHZ_PUSH_PULL   
	      OUTPUT_50MHZ_OPENDRAIN   
	      OUTPUT_50MHZ_AF_PUSH_PULL
	      OUTPUT_50MHZ_AF_OPENDRAIN
*/
extern ErrorStatus DIO_Init (PinParam_t *Copy_PinParam_tPinParamPtr);

/*
	Port: PORTA
		  PORTB
		  PORTC
		  
	Pin:  SET_PIN0
	      SET_PIN1
	      SET_PIN2
	      SET_PIN3
	      SET_PIN4
	      SET_PIN5
	      SET_PIN6
	      SET_PIN7
	      SET_PIN8
	      SET_PIN9
	      SET_PIN10
	      SET_PIN11
	      SET_PIN12
	      SET_PIN13
	      SET_PIN14
	      SET_PIN15
		  
	Copy_u8Value: SET
				  RESET
*/
extern ErrorStatus DIO_SetPinValue (PinParam_t *Copy_PinParam_tPinParamPtr, u8 Copy_u8Value);

/*
	Port: PORTA
		  PORTB
		  PORTC
		  
	Pin:  PIN0 
	      PIN1 
	      PIN2 
	      PIN3 
	      PIN4 
	      PIN5 
	      PIN6 
	      PIN7 
	      PIN8 
	      PIN9 
	      PIN10
	      PIN11
	      PIN12
	      PIN13
	      PIN14
	      PIN15
*/
extern ErrorStatus DIO_GetPinValue (PinParam_t *Copy_PinParam_tPinParamPtr, u8* Copy_u8ValuePtr);

#endif
