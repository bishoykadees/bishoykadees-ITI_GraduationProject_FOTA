/* Module Name : HUSART
 * File Name   : HUSART_interface.h
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 09/05/2020 */

#ifndef HUART_INTERFACE_H_
#define HUART_INTERFACE_H_

#include "STDTYPES.h"

/* choose which USART you wanna use and pass it at copy_u8USARTNum */
#define USART1                                                            ((u8)0)
#define USART2                                                            ((u8)1)
#define USART3                                                            ((u8)2)
#define USART4                                                            ((u8)3)
#define USART5                                                            ((u8)4)

#define HUSART_SBK_FLAG                                                   ((u32)0x00000001)
#define HUSART_RE_FLAG                                                    ((u32)0x00000004)
#define HUSART_TE_FLAG                                                    ((u32)0x00000008)

typedef void(*SetBreakFlagCBF_t)(void);
typedef void (*TxCBF_t)(void);
typedef void (*RxCBF_t)(void);

/* this function enables RCC on GPIO pins used by USART,
 * enables RCC on USART peripheral
 * calls init function of USART driver,
 * clear pending flag and enables global interrupt of USART
 * and initialize GPIO pins used by USART */
extern Status HUSART_Init(u8 copy_u8USARTNum);

/* this function takes buffer array and its size,
 * sets TE flag and sends the first byte of buffer */
extern Status HUSART_Send(u8 copy_u8USARTNum, u8* copy_pu8Buffer, u16 copy_u16Length);

/* this function takes buffer to put in it received data and takes its size,
 * sets RE flag */
extern Status HUSART_Receive(u8 copy_u8USARTNum, u8* copy_pu8BufferPointer, u16 copy_u16BufferSize);

/* this function sets tx callback function */
extern Status HUSART_SetTxCBF(u8 copy_u8USARTNum, TxCBF_t copy_TxCBF);

/* this function sets rx callback function */
extern Status HUSART_SetRxCBF(u8 copy_u8USARTNum, RxCBF_t copy_RxCBF);

extern ErrorStatus HUSART_InitLIN(u8 copy_u8USARTNum,SetBreakFlagCBF_t copy_SetBreakFlagCBF);

extern ErrorStatus HUSART_SetFlag(u8 copy_u8USARTNum, u32 copy_u32Flag);

#endif /* HUART_INTERFACE_H_ */
