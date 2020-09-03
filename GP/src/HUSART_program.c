/* Module Name : HUSART
 * File Name   : HUSART_program.c
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 09/05/2020 */

#define NUMBER_OF_USART_CHANNELS         5

#include "STDTYPES.h"
#include "RCC.h"
#include "GPIO.h"
#include "NVIC_interface.h"
#include "USART_interface.h"
#include "HUSART_interface.h"

typedef struct
{
	u8* pdata;
	u32 position;
	u32 size;
	u8  state;
}dataBuffer_t;

SetBreakFlagCBF_t HUSART_SetBreakFlag;

/* define array of tx buffers as there is more than one channel */
static dataBuffer_t txBuffer[NUMBER_OF_USART_CHANNELS];
/* define array of rx buffers as there is more than one channel */
static dataBuffer_t rxBuffer[NUMBER_OF_USART_CHANNELS];

/* define array of app notify functions called when the HUSART completes sending */
static TxCBF_t appTxNotify[NUMBER_OF_USART_CHANNELS];
/* define array of app notify functions called when the HUSART completes receiving */
static RxCBF_t appRxNotify[NUMBER_OF_USART_CHANNELS];


/************************************************ HUSART_Init *******************************************************/
extern Status HUSART_Init(u8 copy_u8USARTNum)
{
	Status Local_Status = IDLE;
	/* define tx GPIO pin struct */
	PinParam_t Tx_Pin;
	/* define rx GPIO pin struct */
	PinParam_t Rx_Pin;
	/* define NVIC struct of USART */
	NVIC_t NVIC_Struct;
	/* puts the pendingflag member as disable */
	NVIC_Struct.PendingFlag = DISABLE;
	/* puts the enablebit member as enable */
	NVIC_Struct.EnableBit   = ENABLE;
	/* puts tx GPIO pin mode as output 2 MHZ alternate function push/pull */
	Tx_Pin.Mode = OUTPUT_2MHZ_AF_PUSH_PULL;
	/* puts rx GPIO pin mode as input floating */
	Rx_Pin.Mode = INPUT_FLOATING;

	switch(copy_u8USARTNum)
	{
	case USART1:
	{
		/* puts tx GPIO port as PORTA */
		Tx_Pin.Port = PORTA;
		/* puts rx GPIO port as PORTA */
		Rx_Pin.Port = PORTA;
		/* puts tx GPIO pin as PIN9 */
		Tx_Pin.Pin = PIN9;
		/* puts rx GPIO pin as PIN10 */
		Rx_Pin.Pin = PIN10;
		/* calling this function enables clock on PORTA */
		RCC_EnableAPB2Peripheral(IOPA);
		/* calling this function enables clock on USART1 */
		RCC_EnableAPB2Peripheral(USART1EN);
		/* puts the ID member as NVIC_USART1 */
		NVIC_Struct.ID = NVIC_USART1;
	}break;
	case USART2:
	{
		/* puts tx GPIO port as PORTA */
		Tx_Pin.Port = PORTA;
		/* puts rx GPIO port as PORTA */
		Rx_Pin.Port = PORTA;
		/* puts tx GPIO pin as PIN9 */
		Tx_Pin.Pin = PIN2;
		/* puts rx GPIO pin as PIN10 */
		Rx_Pin.Pin = PIN3;
		/* calling this function enables clock on PORTA */
		RCC_EnableAPB2Peripheral(IOPA);
		/* calling this function enables clock on USART1 */
		RCC_EnableAPB1Peripheral(USART2EN);
		/* puts the ID member as NVIC_USART1 */
		NVIC_Struct.ID = NVIC_USART2;
		/*
		Tx_Pin.Port = PORTA;
		Rx_Pin.Port = PORTA;
		Tx_Pin.Pin = PIN2;
		Rx_Pin.Pin = PIN3;
		RCC_EnableAPB2Peripheral(IOPA);
		RCC_EnableAPB1Peripheral(USART2EN);
		NVIC_Struct.ID = NVIC_USART2;
		*/
	}break;
	case USART3:
	{
		Tx_Pin.Port = PORTB;
		Rx_Pin.Port = PORTB;
		Tx_Pin.Pin = PIN10;
		Rx_Pin.Pin = PIN11;
		RCC_EnableAPB2Peripheral(IOPB);
		RCC_EnableAPB1Peripheral(USART3EN);
		NVIC_Struct.ID = NVIC_USART3;
	}break;
	case USART4:
	{
		Local_Status = ERROR;
	}break;
	case USART5:
	{
		Local_Status = ERROR;
	}break;
	}
	/* calling this function initialize tx pin */
	DIO_Init(&Tx_Pin);
	/* calling this function initialize rx pin */
	DIO_Init(&Rx_Pin);

	/* calling this function clears pending flag */
	NVIC_ControlPendingFlag(&NVIC_Struct);
	/* calling this function enables USART interrupt */
	NVIC_ControlEnableInterrupt(&NVIC_Struct);
	/* calling USART driver init function */
	USART_Init(copy_u8USARTNum);

	return Local_Status;
}

/************************************************** HUSART_Send ***************************************************************/
extern Status HUSART_Send(u8 copy_u8USARTNum, u8* copy_pu8Buffer, u16 copy_u16Length)
{
	Status Local_Status = IDLE;
	/* check if USART number is between 1->5,
	 * buffer pointer not equal NULL,
	 * buffer length is less than 1000 byte */
	if((copy_u8USARTNum < 5) && (copy_pu8Buffer != NULL) && (copy_u16Length <= 1000))
		{
			/* if transmission state is idle */
			if(txBuffer[copy_u8USARTNum].state == IDLE)
			{
				/* assign buffer pointer to pdata member */
				txBuffer[copy_u8USARTNum].pdata = copy_pu8Buffer;
				/* assign buffer position to zero */
				txBuffer[copy_u8USARTNum].position = 0;
				/* assign buffer length to size member */
				txBuffer[copy_u8USARTNum].size = copy_u16Length;
				/* makes transmission state busy */
				txBuffer[copy_u8USARTNum].state = BUSY;

				/* set transmission enable flag */
				//USART_SetFlags(USART_1,TE);
				/* send first byte of buffer */
				USART_Send(copy_u8USARTNum,txBuffer[copy_u8USARTNum].pdata[txBuffer[copy_u8USARTNum].position]);
				/* increase buffer position by one */
				txBuffer[copy_u8USARTNum].position ++;
			}
			else
			{
				Local_Status = BUSY;
			}
		}
		else
		{
			Local_Status = ERROR;
		}
	return Local_Status;
}

/*************************************************** HUSART_Receive ***************************************************/
extern Status HUSART_Receive(u8 copy_u8USARTNum, u8* copy_pu8Buffer, u16 copy_u16Length)
{
	Status Local_Status = IDLE;
	/* check if USART number is between 1->5,
	 * buffer pointer not equal NULL,
	 * buffer length is less than 1000 byte */
	if((copy_u8USARTNum < 5) && (copy_pu8Buffer != NULL) && (copy_u16Length <= 1000))
	{
		/* if reception state is idle */
		if(rxBuffer[copy_u8USARTNum].state == IDLE)
		{
			/* assign buffer pointer to pdata member */
			rxBuffer[copy_u8USARTNum].pdata = copy_pu8Buffer;
			/* assign buffer position to zero */
			rxBuffer[copy_u8USARTNum].position = 0;
			/* assign buffer length to size member */
			rxBuffer[copy_u8USARTNum].size = copy_u16Length;
			/* makes transmission state busy */
			rxBuffer[copy_u8USARTNum].state = BUSY;

			/* set reception enable flag */
			//USART_SetFlags(USART_1,RE);
		}
		else
		{
			Local_Status = BUSY;
		}
	}
	else
	{
		Local_Status = ERROR;
	}
	return Local_Status;
}

/*************************************************** HUSART_SetTXCBF ************************************************/
extern Status HUSART_SetTxCBF(u8 copy_u8USARTNum, TxCBF_t copy_TxCBF)
{
	Status Local_Status = IDLE;
	/* check if USART number is between 1->5,
	 * call back pointer not equal NULL */
	if(copy_TxCBF && copy_u8USARTNum < 5)
	{
		/* set tx call back function */
		appTxNotify[copy_u8USARTNum] = copy_TxCBF;
	}
	else
	{
		Local_Status = ERROR;
	}
	return Local_Status;
}

/*************************************************** HUSART_SetRXCBF **************************************************/
extern Status HUSART_SetRxCBF(u8 copy_u8USARTNum, RxCBF_t copy_RxCBF)
{
	Status Local_Status = IDLE;
	/* check if USART number is between 1->5,
	 * call back pointer not equal NULL */
	if(copy_RxCBF && copy_u8USARTNum < 5)
	{

		/* set rx call back function */
		appRxNotify[copy_u8USARTNum] = copy_RxCBF;
	}
	else
	{
		Local_Status = ERROR;
	}
	return Local_Status;
}

/*************************************************** HUSART_InitLIN ***************************************************************/
extern ErrorStatus HUSART_InitLIN(u8 copy_u8USARTNum, SetBreakFlagCBF_t copy_SetBreakFlagCBF)
{
	ErrorStatus Local_ErrorStatus = OK;
	/* setting call back function which is called when LBD is fired (lin break character is completed) */
	HUSART_SetBreakFlag = copy_SetBreakFlagCBF;
	/* define tx GPIO pin struct */
	PinParam_t Tx_Pin;
	/* define rx GPIO pin struct */
	PinParam_t Rx_Pin;
	/* define NVIC struct of USART */
	NVIC_t NVIC_Struct;
	/* puts the pendingflag member as disable */
	NVIC_Struct.PendingFlag = DISABLE;
	/* puts the enablebit member as enable */
	NVIC_Struct.EnableBit   = ENABLE;
	/* puts tx GPIO pin mode as output 2 MHZ alternate function push/pull */
	Tx_Pin.Mode = OUTPUT_2MHZ_AF_PUSH_PULL;
	/* puts rx GPIO pin mode as input floating */
	Rx_Pin.Mode = INPUT_FLOATING;

	switch(copy_u8USARTNum)
	{
	case USART1:
	{
		/* puts tx GPIO port as PORTA */
		Tx_Pin.Port = PORTA;
		/* puts rx GPIO port as PORTA */
		Rx_Pin.Port = PORTA;
		/* puts tx GPIO pin as PIN9 */
		Tx_Pin.Pin = PIN9;
		/* puts rx GPIO pin as PIN10 */
		Rx_Pin.Pin = PIN10;
		/* calling this function enables clock on PORTA */
		RCC_EnableAPB2Peripheral(IOPA);
		/* calling this function enables clock on USART1 */
		RCC_EnableAPB2Peripheral(USART1EN);
		/* puts the ID member as NVIC_USART1 */
		NVIC_Struct.ID = NVIC_USART1;
	}break;
	case USART2:
	{
		Tx_Pin.Port = PORTA;
		Rx_Pin.Port = PORTA;
		Tx_Pin.Pin = PIN2;
		Rx_Pin.Pin = PIN3;
		RCC_EnableAPB2Peripheral(IOPA);
		RCC_EnableAPB1Peripheral(USART2EN);
		NVIC_Struct.ID = NVIC_USART2;
	}break;
	case USART3:
	{
		Tx_Pin.Port = PORTB;
		Rx_Pin.Port = PORTB;
		Tx_Pin.Pin = PIN10;
		Rx_Pin.Pin = PIN11;
		RCC_EnableAPB2Peripheral(IOPB);
		RCC_EnableAPB1Peripheral(USART3EN);
		NVIC_Struct.ID = NVIC_USART3;
	}break;
	case USART4:
	{
		Local_ErrorStatus = ERROR;
	}break;
	case USART5:
	{
		Local_ErrorStatus = ERROR;
	}break;
	}
	/* calling this function clears pending flag */
	NVIC_ControlPendingFlag(&NVIC_Struct);
	/* calling this function enables USART interrupt */
	NVIC_ControlEnableInterrupt(&NVIC_Struct);
	/* calling this function initialize tx pin */
	DIO_Init(&Tx_Pin);
	/* calling this function initialize rx pin */
	DIO_Init(&Rx_Pin);
	/* calling USART driver init function */
	USART_InitLIN(copy_u8USARTNum);
	return Local_ErrorStatus;
}

/*********************************************** HUSART_SetFlag *****************************************************/
extern ErrorStatus HUSART_SetFlag(u8 copy_u8USARTNum, u32 copy_u32Flag)
{
	USART_SetFlags(copy_u8USARTNum,copy_u32Flag);
	return OK;
}

/************************************************ USART1_ISR ***************************************************************/
void USART1_IRQHandler(void)
{
	u8 Local_TCValue = 0;
	u8 Local_RXNEValue = 0;
	u8 Local_LBDValue = 0;
	/* reads RXNE flag */
	USART_ReadFlags(USART_1,USART_RXNE,&Local_RXNEValue);
	/* reads TC flag */
	USART_ReadFlags(USART_1,USART_TC,&Local_TCValue);
	/* reads LBD flag */
	USART_ReadFlags(USART_1,USART_LBD,&Local_LBDValue);

	/* if TC flag is set */
	if(Local_TCValue != 0)
	{
		/* check if transmission state is idle(no transmission)
		 * and this condition is implemented to write in the data register
		 * and makes TC flag reset  */
		if(txBuffer[USART1].state == BUSY)
		{
			/* if buffer index has not reached size yet */
			if(txBuffer[USART1].size != txBuffer[USART1].position)
			{
				/* send next byte */
//				USART_ClearFlag(USART1, USART_TC_FLAG);
				USART_Send(USART_1,txBuffer[USART1].pdata[txBuffer[USART1].position]);
				txBuffer[USART1].position ++;
			}
			else
			{
				txBuffer[USART1].pdata = NULL;
				txBuffer[USART1].size = 0;
				txBuffer[USART1].position = 0;
				txBuffer[USART1].state = IDLE;
				/* call tx completion call back function */
				appTxNotify[USART1]();
			}
		}
		else
		{
			USART_ClearFlag(USART1, USART_TC_FLAG);
		}
	}
	/* if RXNE flag is set */
	if(Local_RXNEValue != 0)
	{
		/* check if reception state is busy */
		if(rxBuffer[USART1].state == BUSY)
		{
			/* receive next byte */
			USART_Receive(USART_1,&(rxBuffer[USART1].pdata[rxBuffer[USART1].position]));
			rxBuffer[USART1].position ++;

			if(rxBuffer[USART1].position == rxBuffer[USART1].size)
			{
				rxBuffer[USART1].pdata = NULL;
				rxBuffer[USART1].size = 0;
				rxBuffer[USART1].position = 0;
				rxBuffer[USART1].state = IDLE;
				/* call rx completion call back function */
				appRxNotify[USART1]();
			}
		}
		else
		{
			return;
		}
	}

	/* check if lin break is detected */
//	if(Local_LBDValue != 0)
//	{
//		USART_ClearFlag(USART1,USART_LBD_CLEAR);
//		HUSART_SetBreakFlag();
//	}

}
/************************************************ USART2_ISR ***************************************************************/
void USART2_IRQHandler(void)
{
	u8 Local_TCValue = 0;
	u8 Local_RXNEValue = 0;
	u8 Local_LBDValue = 0;
	/* reads RXNE flag */
	USART_ReadFlags(USART_2,USART_RXNE,&Local_RXNEValue);
	/* reads TC flag */
	USART_ReadFlags(USART_2,USART_TC,&Local_TCValue);
	/* reads LBD flag */
	USART_ReadFlags(USART_2,USART_LBD,&Local_LBDValue);

	/* if TC flag is set */
	if(Local_TCValue != 0)
	{
		/* check if transmission state is idle(no transmission)
		 * and this condition is implemented to write in the data register
		 * and makes TC flag reset  */
		if(txBuffer[USART2].state == BUSY)
		{
			/* if buffer index has not reached size yet */
			if(txBuffer[USART2].size != txBuffer[USART2].position)
			{
				/* send next byte */
//				USART_ClearFlag(USART2, USART_TC_FLAG);
				USART_Send(USART_2,txBuffer[USART2].pdata[txBuffer[USART2].position]);
				txBuffer[USART2].position ++;
			}
			else
			{
				txBuffer[USART2].pdata = NULL;
				txBuffer[USART2].size = 0;
				txBuffer[USART2].position = 0;
				txBuffer[USART2].state = IDLE;
				/* call tx completion call back function */
				appTxNotify[USART2]();
			}
		}
		else
		{
			USART_ClearFlag(USART2, USART_TC_FLAG);
		}
	}
	/* if RXNE flag is set */
	if(Local_RXNEValue != 0)
	{
		/* check if reception state is busy */
		if(rxBuffer[USART2].state == BUSY)
		{
			/* receive next byte */
			USART_Receive(USART_2,&(rxBuffer[USART2].pdata[rxBuffer[USART2].position]));
			rxBuffer[USART2].position ++;

			if(rxBuffer[USART2].position == rxBuffer[USART2].size)
			{
				rxBuffer[USART2].pdata = NULL;
				rxBuffer[USART2].size = 0;
				rxBuffer[USART2].position = 0;
				rxBuffer[USART2].state = IDLE;
				/* call rx completion call back function */
				appRxNotify[USART2]();
			}
		}
		else
		{
			return;
		}
	}

	/* check if lin break is detected */
//	if(Local_LBDValue != 0)
//	{
//		USART_ClearFlag(USART1,USART_LBD_CLEAR);
//		HUSART_SetBreakFlag();
//	}

}


