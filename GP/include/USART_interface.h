/* Module Name : USART
 * File Name   : USART_interface.h
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 13/4/2020 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "STDTYPES.h"

/* choose which USART you will use and pass it at copy_u8USARTNum */
#define USART_1                                 0
#define USART_2                                 1
#define USART_3                                 2
#define USART_4                                 3
#define USART_5                                 4
/* choose which flag you wanna read and pass it at copy_u8Flag */
#define USART_TC                                6
#define USART_RXNE                              5
#define USART_LBD                               8
/* choose which Baud Rate you wanna work with and pass it at copy_u32BaudRate (USART1(APB2), clock is 72MHz only) */
#define BR_2400_72MHZ                           ((u16)0x7530)
#define BR_9600_72MHZ                           ((u16)0x1D4C)
#define BR_19200_72MHZ                          ((u16)0x0EA6)
#define BR_57600_72MHZ                          ((u16)0x04E2)
#define BR_115200_72MHZ                         ((u16)0x0271)
#define BR_230400_72MHZ                         ((u16)0x0138)
#define BR_460800_72MHZ                         ((u16)0x009C)
#define BR_921600_72MHZ                         ((u16)0x004E)
#define BR_2250000_72MHZ                        ((u16)0x0020)
#define BR_45000000_72MHZ                       ((u16)0x0010)
#define BR_115200_36MHZ                         ((u16)0x0138)
#define BR_9600_36MHZ                           ((u16)0x0EA6)
/* choose which number of stop bits and pass it at copy_u8StopBits */
#define STOPBITS_ONE                            ((u32)0x00000000)
#define STOPBITS_HALF                           ((u32)0x00001000)
#define STOPBITS_TWO                            ((u32)0x00002000)
#define STOPBITS_ONE_AND_HALF                   ((u32)0x00003000)
/* choose which Parity system you wanna use and pass it at copy_u8Parity */
#define NO_PARITY                               ((u32)0x00000000)
#define EVEN_PARITY                             ((u32)0x00000400)
#define ODD_PARITY                              ((u32)0x00000600)
/* choose word length size and put it at copy_u32WordLength but take care that Parity bit if enabled will be part of the word length */
#define DATABITS_8                              ((u32)0x00000000)
#define DATABITS_9                              ((u32)0x00001000)
/* choose which flag you want to set and pass it at copy_u8Flag */
#define TE                                      ((u32)0x00000008)
#define RE                                      ((u32)0x00000004)
/* choose if you wanna enable TXE or RXNE interrupts or both */
#define TX_INTERRUPT_ENABLED                    ((u32)0x00000080)
#define RX_INTERRUPT_ENABLED                    ((u32)0x00000020)
#define TX_INTERRUPT_DISABLED                   ((u32)0x00000000)
#define RX_INTERRUPT_DISABLED                   ((u32)0x00000000)
/* choose which break detection length you wanna choose */
#define BREAK_DETECTION_11_BITS                 ((u32)0x00000020)
#define BREAK_DETECTION_10_BITS                 ((u32)0x00000000)

#define LBD_INTERRUPT_ENABLED                   ((u32)0x00000040)
#define LBD_INTERRUPT_DISABLED                  ((u32)0x00000000)

#define USART_LBD_CLEAR                         ((u32)0xFFFFFEFF)
#define USART_RXNE_CLEAR                        ((u32)0xFFFFFFDF)

#define USART_TE_SET                            ((u32)0x00000008)
#define USART_RE_SET                            ((u32)0x00000004)

#define USART_TC_INTERRUPT_SET                  ((u32)0x00000040)
#define USART_TC_FLAG                           ((u32)0xFFFFFFBF)

/* this init function enables the USART,
 * configures the baudrate defined in the config file,
 * configures the stopbits, parity and wordlength defined in the config file
 * enables the TXE and RXNE interrupts if they are enabled in the config file
 * and it is called only by the HUSART_Init function */
extern ErrorStatus USART_Init(u8 copy_u8USARTNum);

/* copies a specific byte in the data register */
extern ErrorStatus USART_Send(u8 copy_u8USARTNum, u8 copy_u8Data);

/* gets the byte received in the data register */
extern ErrorStatus USART_Receive(u8 copy_u8USARTNum, u8* copy_pu8ReceivedData);

/* is implemented to set the TE and RE flags only */
extern ErrorStatus USART_SetFlags(u8 copy_u8USARTNum, u32 copy_u32Flag);

/* is implemented to read the TXE and RXNE flags and is used in the ISR of the USART */
extern ErrorStatus USART_ReadFlags(u8 copy_u8USARTNum, u32 copy_u32Flag, u8* copy_pu8FlagValue);

/* is implemented to configure the baudrate, stopbits, parity and wordlength */
extern Status USART_Config(u8 copy_u8USARTNum, u16 copy_u16BaudRate, u32 copy_u32StopBits, u32 copy_u32Parity, u32 copy_u32WordLength);

extern ErrorStatus USART_InitLIN(u8 copy_u8USARTNum);

extern ErrorStatus USART_ClearFlag(u8 copy_u8USARTNum, u32 copy_u32Flag);

#endif /* UART_INTERFACE_H_ */
