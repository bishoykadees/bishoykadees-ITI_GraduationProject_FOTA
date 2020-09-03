/* Module Name : USART
 * File Name   : USART_register.h
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 13/4/2020 */

#ifndef USART_REGISTER_H
#define USART_REGISTER_H

#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* define USART1 addresses */
#define USART1                                ((volatile USARTReg_t * const)(0x40013800))
/* define USART2 addresses */
#define USART2                                ((volatile USARTReg_t * const)(0x40004400))
/* define USART3 addresses */
#define USART3                                ((volatile USARTReg_t * const)(0x40004800))
/* define USART4 addresses */
#define USART4                                ((volatile USARTReg_t * const)(0x40004C00))
/* define USART5 addresses */
#define USART5                                ((volatile USARTReg_t * const)(0x40005000))

typedef struct
{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;
}USARTReg_t;

#endif
