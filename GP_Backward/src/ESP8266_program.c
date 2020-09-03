/* Module Name : ESP8266
 * File Name   : ESP8266_program.c
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 12/06/2020 */

#define INITIAL_STATE                           0
#define LINE_FEED_CHARACTER_FOUND_STATE         1
#define O_CHARACTER_FOUND_STATE                 2
#define K_CHARACTER_FOUND_STATE                 3
#define CARRIAGE_RETURN_CHARACTER_FOUND_STATE   4

#define PLUS_CHARACTER_FOUND_STATE              1
#define I_CHARACTER_FOUND_STATE                 2
#define P_CHARACTER_FOUND_STATE                 3
#define D_CHARACTER_FOUND_STATE                 4
#define FIRST_COMMA_CHARACTER_FOUND_STATE       5
#define ZERO_CHARACTER_FOUND_STATE              6
#define SECOND_COMMA_CHARACTER_FOUND_STATE      7
#define COLON_CHARACTER_FOUND_STATE             8

#define r_CHARACTER_FOUND_STATE                 2
#define e_CHARACTER_FOUND_STATE                 3
#define a_CHARACTER_FOUND_STATE                 4
#define d_CHARACTER_FOUND_STATE                 5
#define y_CHARACTER_FOUND_STATE                 6
#define CARRIAGE_RETURN1_CHARACTER_FOUND_STATE  7

#define ENABLED                                 1
#define DISABLED                                0
#define BOTH_AP_AND_STATION                     3
#define STATION_ONLY                            1
#define AP_ONLY                                 2
#define MULTIPLE_CONNECTION                     1
#define SINGLE_CONNECTION                       0
#define NOTHING

#define AT_RST                                  AT+RST
#define AT_ECHO                                 ATE
#define AT_MODE                                 AT+CWMODE
#define AT_CONNECTION_TYPE                      AT+CIPMUX
#define AT_CREATE_SERVER                        AT+CIPSERVER=1
#define AT_SEND                                 AT+CIPSEND=0
#define AT_SET_AP_IP                            AT+CIPAP_CUR

#define CONC2(x,y)                              CONC2_HELP(x,y)
#define CONC2_HELP(x,y)                         x##y
#define CONC3(x,y,z)                            CONC3_HELP(x,y,z)
#define CONC3_HELP(x,y,z)                       x##y##z
#define CONC4(a,b,c,d)                          CONC4_HELP(a,b,c,d)
#define CONC4_HELP(a,b,c,d)                     a##b##c##d
#define STRING(x)                               STRING_HELP(x)
#define STRING_HELP(x)                          #x"\r\n"
#define _STRING(x)                              _STRING_HELP(x)
#define _STRING_HELP(x...)       	            #x
#define EQUAL(x,y)                              x=y
#define COMMA(x,y)                              x,y

#include "STDTYPES.h"
#include "BOOTLOADER.h"
#include "FLASH.h"
#include "HUSART_interface.h"
#include "ESP8266_interface.h"
#include "ESP8266_config.h"

//testing
#include "RCC.h"
#include "GPIO.h"
u8 flag = 0;


u8   G_u8RxByte;
u8   G_u8RxBuffer[100];
u8*  G_pu8DataPointer;
u16* G_pu16SizePointer;
u8   G_u8Flag = 0;
u16  G_u16nBuffer[4] = {0};
u8   G_u8Flag1 = 0;
u8   G_a4u8AppBuffer[4];

void InitTxCBF(void);
void InitRxCBF1(void);
void ReceiveTxCBF(void);
void ReceiveRxCBF(void);
void SendTxCBF(void);
void SendRxCBF(void);
void InitRxCBF2(void);
void AppInitCBF(void);

ReceiveCBF_t RxCBF;

extern void ESP8266_SetReceiveCBF(ReceiveCBF_t copy_ReceiveCallBackFunc)
{
	if(copy_ReceiveCallBackFunc)
	{
		RxCBF = copy_ReceiveCallBackFunc;
	}
}



/******************************************************************************* ESP8266_Init **********************************************/
extern void ESP8266_Init(void)
{
	u8  local_u8Index = 0;
	u8* local_pu8AT_Commands_Array[6];
	u8  local_pu8AT_Commands_Array_Size[6] = {8,6,13,30,13,16};

	/* Reset command */
	local_pu8AT_Commands_Array[0] = (u8*)(STRING(AT_RST));
	/* configure Echo command */
	local_pu8AT_Commands_Array[1] = (u8*)(STRING(CONC2(AT_ECHO,ECHO_STATUS)));
	/* configure ESP mode AP or station or both */
	local_pu8AT_Commands_Array[2] = (u8*)(STRING(EQUAL(AT_MODE,MODE)));
	/* set AP IP address */
	local_pu8AT_Commands_Array[3] = (u8*)(STRING(EQUAL(AT_SET_AP_IP,AP_IP)));
	/* set connection configuration multiple or single */
	local_pu8AT_Commands_Array[4] = (u8*)(STRING(EQUAL(AT_CONNECTION_TYPE,CONNECTION_TYPE)));
	/* create a server */
	local_pu8AT_Commands_Array[5] = (u8*)(STRING(AT_CREATE_SERVER));

	HUSART_SetRxCBF(USART2,InitRxCBF2);
	HUSART_SetTxCBF(USART2,InitTxCBF);
	HUSART_Init(USART2);

	/* receive one byte */
	HUSART_Receive(USART2, &G_u8RxByte, 1);
	/* send reset command to reset the ESP8266 */
	HUSART_Send(USART2, local_pu8AT_Commands_Array[0], local_pu8AT_Commands_Array_Size[0]);
	/* loop on a flag which is fired if uc receives ready */
	while(G_u8Flag == 0);
	/* set flag to zero again */
	G_u8Flag = 0;

	HUSART_SetRxCBF(USART2,InitRxCBF1);

	/* send each command after the reset command in the array local_pu8AT_Commands_Array */
	for(local_u8Index = 1;local_u8Index < 6;local_u8Index ++)
	{
		/* receive one byte */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		/* send a command */
		HUSART_Send(USART2, local_pu8AT_Commands_Array[local_u8Index], local_pu8AT_Commands_Array_Size[local_u8Index]);
		/* loop on a flag which is fired if uc receives OK */
		while(G_u8Flag == 0);
		/* set flag to zero again */
		G_u8Flag = 0;
	}
}
/******************************************************************************* ESP8266_Send **********************************************/
extern Status ESP8266_Send(u8* copy_pu8Buffer, u16 copy_u16BufferSize)
{
	u8  local_u8Status = IDLE;
	u8  local_u8ForLoopCounter = 0;
	u8  local_u8Buffer[4];
	u16 local_u16BufferSize = copy_u16BufferSize;
	u8* local_pu8AT_Commands_Array;
	u8  local_a2u8EndOfLine[2] = "\r\n";

	if((copy_pu8Buffer != NULL) && (copy_u16BufferSize <= 2048))
	{
		HUSART_SetRxCBF(USART2,SendRxCBF);
		HUSART_SetTxCBF(USART2,SendTxCBF);

		local_pu8AT_Commands_Array = (u8*)(_STRING(COMMA(AT_SEND,NOTHING)));					/* send command, link ID = 0 */

		for(local_u8ForLoopCounter = 0;local_u16BufferSize != 0;local_u8ForLoopCounter ++)		/* convert buffer size from integer number to string */
		{
			local_u8Buffer[local_u8ForLoopCounter] = (local_u16BufferSize % 10) + 48;			/* mod buffer size by 10 and add 48 */
			local_u16BufferSize /= 10 ;															/* divide size by 10 */
		}

		HUSART_Send(USART2, local_pu8AT_Commands_Array, 13);									/* send the send command "AT+CIPSEND=0," */
		while(G_u8Flag == 0);																	/* loop on a flag that is fired if send is complete */
		G_u8Flag = 0;																			/* put the flag to zero again */

		for(;local_u8ForLoopCounter > 0 ;local_u8ForLoopCounter --)								/* send each number of buffer size as ascii  */
		{
			HUSART_Send(USART2, (local_u8Buffer + local_u8ForLoopCounter - 1), 1);
			while(G_u8Flag == 0);
			G_u8Flag = 0;
		}

		HUSART_Receive(USART2, &G_u8RxByte, 1);													/* receive one byte and if not '>' recive again till find it */

		HUSART_Send(USART2, (u8*)&local_a2u8EndOfLine, 2);										/* send "\r\n" */
		while(G_u8Flag1 == 0);																	/* flag is fired if uc received '>' successfully */
		G_u8Flag1 = 0;

		HUSART_Send(USART2, copy_pu8Buffer, copy_u16BufferSize);								/* send the required data to be sent */
		while(G_u8Flag == 0);																	/* flag is fired if all data are sent */
		G_u8Flag = 0;

//		HUSART_Receive(USART2, &G_u8RxByte, 1);

//		HUSART_Send(USART2, &local_u8LineFeed, 1);												/* send line feed '\n' character at end of data */
//		while(G_u8Flag == 0);
//		G_u8Flag = 0;
	}
	else
	{
		local_u8Status = ERROR;
	}

	return local_u8Status;
}
/******************************************************************************* ESP8266_Receive **********************************************/
extern Status ESP8266_Receive(u8* copy_pu8Buffer, u16* copy_pu16BufferSize)
{

	//+IPD,0,n:
	/* maximum data can be received is 65000 bytes */
	u8 local_u8Status = IDLE;
	if((copy_pu8Buffer != NULL) && (copy_pu16BufferSize != NULL))
	{
		G_u8Flag = 0;
		HUSART_SetRxCBF(USART2,ReceiveRxCBF);
		HUSART_SetTxCBF(USART2,ReceiveTxCBF);

		G_pu8DataPointer = copy_pu8Buffer;
		G_pu16SizePointer = copy_pu16BufferSize;

		HUSART_Receive(USART2, &G_u8RxByte, 1);
	}
	else
	{
		local_u8Status = ERROR;
	}
	return local_u8Status;
}
/********************************************************************** SendTxCBF ***********************************************************************/
/* call back function called when transmission complete in ESP8266_Send function */
void SendTxCBF(void)
{
	G_u8Flag = 1;
}
/********************************************************************** SendRxCBF ***********************************************************************/
/* call back function called when reception complete in ESP8266_Send function */
void SendRxCBF(void)
{
	if(G_u8RxByte == '>')
	{
		G_u8Flag1 = 1;
	}
	else
	{
		HUSART_Receive(USART2, &G_u8RxByte, 1);
	}
}
/********************************************************************** ReceiveTxCBF ***********************************************************************/
/* call back function called when transmission complete in ESP8266_Receive function */
void ReceiveTxCBF(void)
{

}
/********************************************************************** ReceiveRxCBF ***********************************************************************/
/* call back function called when reception complete in ESP8266_Receive function */
void ReceiveRxCBF(void)
{
	/* index of the G_u8RxBuffer array */
	static u8  local_u8Index = 0;
	/* counter of state machine */
	static u8  local_u8Counter = 0;
	/* counter1 used in for loop */
	static u8  local_u8ForLoopCounter1 = 0;
	/* counter2 used in for loop */
	static u8  local_u8ForLoopCounter2 = 0;

	/* our state machine */
	switch(local_u8Counter)
	{
	case INITIAL_STATE:
		/* if + not found */
		if(G_u8RxByte != '+')
		{

		}
		/* if + found */
		else if(G_u8RxByte == '+')
		{
			/* go to PLUS_CHARACTER_FOUND_STATE */
			local_u8Counter = PLUS_CHARACTER_FOUND_STATE;
		}
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case PLUS_CHARACTER_FOUND_STATE:
		/* if I not found */
		if(G_u8RxByte != 'I')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if I found */
		else if(G_u8RxByte == 'I')
		{
			/* go to I_CHARACTER_FOUND_STATE */
			local_u8Counter = I_CHARACTER_FOUND_STATE;
		}
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case I_CHARACTER_FOUND_STATE:
		/* if P not found */
		if(G_u8RxByte != 'P')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if P found */
		else if(G_u8RxByte == 'P')
		{
			/* go to P_CHARACTER_FOUND_STATE */
			local_u8Counter = P_CHARACTER_FOUND_STATE;
		}
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case P_CHARACTER_FOUND_STATE:
		/* if D not found */
		if(G_u8RxByte != 'D')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if D found */
		else if(G_u8RxByte == 'D')
		{
			/* go to D_CHARACTER_FOUND_STATE */
			local_u8Counter = D_CHARACTER_FOUND_STATE;
		}
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case D_CHARACTER_FOUND_STATE:
		/* if , not found */
		if(G_u8RxByte != ',')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if , found */
		else if(G_u8RxByte == ',')
		{
			/* go to FIRST_COMMA_CHARACTER_FOUND_STATE */
			local_u8Counter = FIRST_COMMA_CHARACTER_FOUND_STATE;
		}
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case FIRST_COMMA_CHARACTER_FOUND_STATE:
		/* if 0 not found */
		if(G_u8RxByte != '0')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if 0 found */
		else if(G_u8RxByte == '0')
		{
			/* go to ZERO_CHARACTER_FOUND_STATE */
			local_u8Counter = ZERO_CHARACTER_FOUND_STATE;
		}
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case ZERO_CHARACTER_FOUND_STATE:
		/* if , not found */
		if(G_u8RxByte != ',')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if , found */
		else if(G_u8RxByte == ',')
		{
			/* go to SECOND_COMMA_CHARACTER_FOUND_STATE */
			local_u8Counter = SECOND_COMMA_CHARACTER_FOUND_STATE;
		}
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case SECOND_COMMA_CHARACTER_FOUND_STATE:
		/* if : not found */
		if(G_u8RxByte != ':')
		{
			/* subtract 48 decimal from each received byte to convert it to a number */
			G_u16nBuffer[local_u8Index] = G_u8RxByte - 48;
			local_u8Index ++;

			/* receive one byte again */
			HUSART_Receive(USART2, &G_u8RxByte, 1);
		}
		/* if : found */
		else if(G_u8RxByte == ':')
		{
			*(G_pu16SizePointer) = 0;
			/* go to COLON_CHARACTER_FOUND_STATE */
			local_u8Counter = COLON_CHARACTER_FOUND_STATE;
			for(local_u8ForLoopCounter1 = 0;local_u8ForLoopCounter1 < local_u8Index;local_u8ForLoopCounter1 ++)
			{
				for(local_u8ForLoopCounter2 = 0;local_u8ForLoopCounter2 < (local_u8Index - local_u8ForLoopCounter1 - 1);local_u8ForLoopCounter2 ++)
				{
					G_u16nBuffer[local_u8ForLoopCounter1] *= 10;
				}
			}
			for(local_u8ForLoopCounter1 = 0;local_u8ForLoopCounter1 < local_u8Index;local_u8ForLoopCounter1 ++)
			{
				*(G_pu16SizePointer) += G_u16nBuffer[local_u8ForLoopCounter1];
			}
			/* receive the data with the calculated size */
			HUSART_Receive(USART2, G_pu8DataPointer, *(G_pu16SizePointer));
		}
		break;
	case COLON_CHARACTER_FOUND_STATE:
		/* make G_u8Flag high to come out from while loop in ESP8266_Receive */
		local_u8Counter         = INITIAL_STATE;
		local_u8ForLoopCounter1 = 0;
		local_u8Index           = 0;
		local_u8ForLoopCounter2 = 0;
		RxCBF();
		break;
	}
}
/********************************************************************** InitTxCBF ************************************************************/
/* call back function called when transmission complete in ESP8266_Init function */
void InitTxCBF(void)
{

}
/********************************************************************** InitRxCBF1 ***********************************************************/
/* call back function called when reception complete in ESP8266_Init function */
void InitRxCBF1(void)
{
	/* index of the G_u8RxBuffer array */
	static u8  local_u8Index = 0;
	/* counter of state machine */
	static u8  local_u8Counter = 0;

	/* our state machine */
	switch(local_u8Counter)
	{
	case INITIAL_STATE:
		/* if \n not found */
		if(G_u8RxByte != '\n')
		{
			/* do nothing */
		}
		/* if \n found */
		else if(G_u8RxByte == '\n')
		{
			/* go to LINE_FEED_CHARACTER_FOUND_STATE */
			local_u8Counter = LINE_FEED_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case LINE_FEED_CHARACTER_FOUND_STATE:
		/* if O not found */
		if(G_u8RxByte != 'O')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if O found */
		else if(G_u8RxByte == 'O')
		{
			/* go to O_CHARACTER_FOUND_STATE */
			local_u8Counter = O_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case O_CHARACTER_FOUND_STATE:
		/* if K not found */
		if(G_u8RxByte != 'K')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if K found */
		else if(G_u8RxByte == 'K')
		{
			/* go to K_CHARACTER_FOUND_STATE */
			local_u8Counter = K_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case K_CHARACTER_FOUND_STATE:
		/* if \r not found */
		if(G_u8RxByte != '\r')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if \r found */
		else if(G_u8RxByte == '\r')
		{
			/* go to CARRIAGE_RETURN_CHARACTER_FOUND_STATE */
			local_u8Counter = CARRIAGE_RETURN_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case CARRIAGE_RETURN_CHARACTER_FOUND_STATE:
		/* go to INITIAL_STATE */
		local_u8Counter = INITIAL_STATE;
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* if \n not found */
		if(G_u8RxByte != '\n')
		{
			/* receive one byte again */
			HUSART_Receive(USART2, &G_u8RxByte, 1);
		}
		/* if \n found */
		else if(G_u8RxByte == '\n')
		{
			/* make G_u8Flag high to come out from while loop in ESP8266_Init */
			G_u8Flag = 1;
//			local_u8Index = 0;
		}
	}
}

/********************************************************************** InitRxCBF2 ***********************************************************/
/* call back function called when reception complete in ESP8266_Init function */
void InitRxCBF2(void)
{
	/* index of the G_u8RxBuffer array */
	static u8  local_u8Index = 0;
	/* counter of state machine */
	static u8  local_u8Counter = 0;

	/* our state machine */
	switch(local_u8Counter)
	{
	case INITIAL_STATE:
		/* if \n not found */
		if(G_u8RxByte != '\n')
		{
			/* do nothing */
		}
		/* if \n found */
		else if(G_u8RxByte == '\n')
		{
			/* go to LINE_FEED_CHARACTER_FOUND_STATE */
			local_u8Counter = LINE_FEED_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case LINE_FEED_CHARACTER_FOUND_STATE:
		/* if r not found */
		if(G_u8RxByte != 'r')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if r found */
		else if(G_u8RxByte == 'r')
		{
			/* go to r_CHARACTER_FOUND_STATE */
			local_u8Counter = r_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case r_CHARACTER_FOUND_STATE:
		/* if e not found */
		if(G_u8RxByte != 'e')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if e found */
		else if(G_u8RxByte == 'e')
		{
			/* go to e_CHARACTER_FOUND_STATE */
			local_u8Counter = e_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case e_CHARACTER_FOUND_STATE:
		/* if a not found */
		if(G_u8RxByte != 'a')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if a found */
		else if(G_u8RxByte == 'a')
		{
			/* go to a_CHARACTER_FOUND_STATE */
			local_u8Counter = a_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case a_CHARACTER_FOUND_STATE:
		/* if d not found */
		if(G_u8RxByte != 'd')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if d found */
		else if(G_u8RxByte == 'd')
		{
			/* go to d_CHARACTER_FOUND_STATE */
			local_u8Counter = d_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case d_CHARACTER_FOUND_STATE:
		/* if y not found */
		if(G_u8RxByte != 'y')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if y found */
		else if(G_u8RxByte == 'y')
		{
			/* go to y_CHARACTER_FOUND_STATE */
			local_u8Counter = y_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case y_CHARACTER_FOUND_STATE:
		/* if \r not found */
		if(G_u8RxByte != '\r')
		{
			/* go to INITIAL_STATE */
			local_u8Counter = INITIAL_STATE;
		}
		/* if \r found */
		else if(G_u8RxByte == '\r')
		{
			/* go to CARRIAGE_RETURN1_CHARACTER_FOUND_STATE */
			local_u8Counter = CARRIAGE_RETURN1_CHARACTER_FOUND_STATE;
		}
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* receive one byte again */
		HUSART_Receive(USART2, &G_u8RxByte, 1);
		break;
	case CARRIAGE_RETURN1_CHARACTER_FOUND_STATE:
		/* go to INITIAL_STATE */
		local_u8Counter = INITIAL_STATE;
		/* save received byte in the buffer */
		G_u8RxBuffer[local_u8Index] = G_u8RxByte;
		/* increment index by 1 */
		local_u8Index ++;
		/* if \n not found */
		if(G_u8RxByte != '\n')
		{
			/* receive one byte again */
			HUSART_Receive(USART2, &G_u8RxByte, 1);
		}
		/* if \n found */
		else if(G_u8RxByte == '\n')
		{
			/* make G_u8Flag high to come out from while loop in ESP8266_Init */
			G_u8Flag = 1;
//			local_u8Index = 0;
		}
	}
}
/***********************************************ESP8266_AppInit*********************************************/
extern void ESP8266_AppInit(void)
{
	u16 local_u16BufferSize = 0;

	ESP8266_Init();
	ESP8266_SetReceiveCBF(AppInitCBF);
	ESP8266_Receive(G_a4u8AppBuffer, &local_u16BufferSize);
//	while(flag == 0);
//	flag = 0;


}

void AppInitCBF(void)
{
	u8 local_u8Index = 0;
	u8  local_a3u8ITIBuffer[3] = "ITI";

	for(local_u8Index = 0;local_u8Index < 3;)
	{
		if(G_a4u8AppBuffer[local_u8Index] == local_a3u8ITIBuffer[local_u8Index])
		{
			local_u8Index ++;
		}
	}

	if(local_u8Index == 3)
	{

	//testing
//	flag = 1;
//	PinParam_t gpio;
//	RCC_EnableAPB2Peripheral(IOPB);
//	gpio.Mode = OUTPUT_2MHZ_PUSH_PULL;
//	gpio.Pin  = PIN11;
//	gpio.Port = PORTB;
//	DIO_Init(& gpio);
//	gpio.Pin  = SET_PIN11;
//	DIO_SetPinValue(& gpio, 1);

		FLASH_Unlock();
		FLASH_ErasePage(MARKER_ADDRESS);
		FLASH_WriteWord(MARKER_ADDRESS, APPLICATION_OVERWRITE);
		FLASH_WriteWord(MARKER_ADDRESS + 2,(u32)((G_a4u8AppBuffer[0]) | (G_a4u8AppBuffer[1] << 8) | (G_a4u8AppBuffer[2] << 16)));
		FLASH_Lock();

		SCB_AIRCR = (VECTKEY | SYSRSTREQ);
	}
}
