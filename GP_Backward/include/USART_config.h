/* Module Name : USART
 * File Name   : USART_config.h
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 14/4/2020 */

#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#define USART1_BAUDRATE                 BR_115200_72MHZ
#define USART2_BAUDRATE                 BR_115200_36MHZ
#define PARITY                          NO_PARITY
#define STOP_BITS                       STOPBITS_ONE
#define WORD_LENGTH                     DATABITS_8
#define TXE_INTERRUPT                   TX_INTERRUPT_ENABLED
#define RXNE_INTERRUPT                  RX_INTERRUPT_ENABLED
#define LIN_BREAK_DETECTION_LENGTH      BREAK_DETECTION_11_BITS
#define LIN_BREAK_DETECTION_INTERRUPT   LBD_INTERRUPT_ENABLED

#endif /* USART_CONFIG_H_ */
