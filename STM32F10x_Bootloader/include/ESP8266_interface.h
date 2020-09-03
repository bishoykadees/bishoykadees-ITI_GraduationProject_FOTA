/* Module Name : ESP8266
 * File Name   : ESP8266_program.c
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 12/06/2020 */

#ifndef ESP8266_INTERFACE_H_
#define ESP8266_INTERFACE_H_

#include "STD_TYPES.h"

typedef void (*SendCBF_t)(void);
typedef void (*ReceiveCBF_t)(void);

extern void ESP8266_Init(void);
extern Status ESP8266_Send(u8* copy_pu8Buffer, u16 copy_u16BufferSize);
extern Status ESP8266_Receive(u8* copy_pu8Buffer, u16* copy_pu16BufferSize);
extern void ESP8266_SetReceiveCBF(ReceiveCBF_t copy_ReceiveCallBackFunc);

extern void ESP8266_AppInit(void);

#endif /* ESP8266_INTERFACE_H_ */
