/* Module Name : GPIO
 * File Name   : GPIO_program.c
 * Author      : Bishoy Nabil
 * Version     : 3.0
 * Date        : 2/3/2020 */

#include "STDTYPES.h"

#include "GPIO.h"

#define CLEAR_MASK 0b1111

typedef struct
{
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
}GPIOReg_t;

/*************************** DIO_Init *****************************************************************************************/
extern ErrorStatus DIO_Init (PinParam_t *Copy_PinParam_tPinParamPtr)
{
	ErrorStatus Local_ErrorStatus = OK;
	GPIOReg_t* Local_GPIOReg_tGPIORegPtr = (GPIOReg_t*)(Copy_PinParam_tPinParamPtr -> Port);
	u32 Local_u32CR;
	if(Copy_PinParam_tPinParamPtr -> Pin <= 7)
	{
		Local_u32CR = Local_GPIOReg_tGPIORegPtr -> CRL;
		Local_u32CR &= (~(CLEAR_MASK << ((Copy_PinParam_tPinParamPtr -> Pin)*4)));
		Local_u32CR |= ((Copy_PinParam_tPinParamPtr -> Mode) << ((Copy_PinParam_tPinParamPtr -> Pin)*4));
		Local_GPIOReg_tGPIORegPtr -> CRL = Local_u32CR;
	}
	else if(Copy_PinParam_tPinParamPtr->Pin <= 15)
	{
		Copy_PinParam_tPinParamPtr->Pin -= 8;
		Local_u32CR = Local_GPIOReg_tGPIORegPtr -> CRH;
		Local_u32CR &= (~(CLEAR_MASK << ((Copy_PinParam_tPinParamPtr -> Pin)*4)));
		Local_u32CR |= ((Copy_PinParam_tPinParamPtr -> Mode) << ((Copy_PinParam_tPinParamPtr -> Pin)*4));
		Local_GPIOReg_tGPIORegPtr -> CRH = Local_u32CR;
	}
	else
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}

/*************************** DIO_SetPinValue *****************************************************************************************/
extern ErrorStatus DIO_SetPinValue (PinParam_t *Copy_PinParam_tPinParamPtr, u8 Copy_u8Value)
{
	ErrorStatus Local_ErrorStatus = OK;
	GPIOReg_t* Local_GPIOReg_tGPIORegPtr = (GPIOReg_t*)(Copy_PinParam_tPinParamPtr -> Port);
	u32 Local_u32Temp;
	if(Copy_u8Value != 0)
	{
		Local_u32Temp = Local_GPIOReg_tGPIORegPtr -> BSRR;
		Local_u32Temp |= Copy_PinParam_tPinParamPtr -> Pin;
		Local_GPIOReg_tGPIORegPtr -> BSRR = Local_u32Temp;
	}
	else if(Copy_u8Value == 0)
	{
		Local_u32Temp = Local_GPIOReg_tGPIORegPtr -> BRR;
		Local_u32Temp |= Copy_PinParam_tPinParamPtr -> Pin;
		Local_GPIOReg_tGPIORegPtr -> BRR = Local_u32Temp;
	}
	else
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}

/*************************** DIO_GetPinValue *****************************************************************************************/
extern ErrorStatus DIO_GetPinValue (PinParam_t *Copy_PinParam_tPinParamPtr, u8* Copy_u8ValuePtr)
{
	ErrorStatus Local_ErrorStatus = OK;
	GPIOReg_t* Local_GPIOReg_tGPIORegPtr = (GPIOReg_t*)(Copy_PinParam_tPinParamPtr -> Port);
	*Copy_u8ValuePtr = ((Local_GPIOReg_tGPIORegPtr -> IDR) >> (Copy_PinParam_tPinParamPtr -> Pin)) & (0x00000001);
	return Local_ErrorStatus;
}
