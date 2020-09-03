/*
 * DC.c
 *
 *  Created on: 22 Jun 2020
 *      Author: mirna
 */
#include "STDTYPES.h"
#include "GPIO.h"
#include "RCC.h"
#include "DC_interface.h"
#include "DC_config.h"

PinParam_t DC_motor_ForwardPin;
PinParam_t DC_motor_BackwardPin;

void DC_init(void)
{
//	if (FORWARD_PIN_PORT == PORTA)
//		RCC_EnableAPB2Peripheral(IOPA);
//	else if (FORWARD_PIN_PORT == PORTB)
//		RCC_EnableAPB2Peripheral(IOPB);
//	else if (FORWARD_PIN_PORT == PORTC)
//		RCC_EnableAPB2Peripheral(IOPC);

	DC_motor_ForwardPin.Mode = OUTPUT_2MHZ_PUSH_PULL;
	DC_motor_ForwardPin.Pin = FORWARD_PIN_PIN;
	DC_motor_ForwardPin.Port = FORWARD_PIN_PORT;

	DC_motor_BackwardPin.Mode = OUTPUT_2MHZ_PUSH_PULL;
	DC_motor_BackwardPin.Pin = BACKWARD_PIN_PIN;
	DC_motor_BackwardPin.Port = BACKWARD_PIN_PORT;

	DIO_Init(&DC_motor_ForwardPin);
	DIO_Init(&DC_motor_BackwardPin);

}

void DC_GoForward(void)
{
	DC_motor_ForwardPin.Pin = FORWARD_PIN_PIN_SET;
	DC_motor_BackwardPin.Pin = BACKWARD_PIN_PIN_SET;
	DIO_SetPinValue(&DC_motor_ForwardPin,1);
	DIO_SetPinValue(&DC_motor_BackwardPin,0);
}

void DC_GoBackward(void)
{
	DC_motor_ForwardPin.Pin = FORWARD_PIN_PIN_SET;
	DC_motor_BackwardPin.Pin = BACKWARD_PIN_PIN_SET;
	DIO_SetPinValue(&DC_motor_ForwardPin,0);
	DIO_SetPinValue(&DC_motor_BackwardPin,1);
}
