/* Hex Parser # definitions */
#define FLASH                                         0x00
#define EOF                                           0x01
#define EXTEND_ADDRESS                                0x04
#define ENTRY_POINT_ADDRESS                           0x05

/* Marker Values */
#define NO_APPLICATION                                ((u32)0xFFFFFFFF)
#define VALID_APPLICATION                             ((u32)0xAABBCCDD)

#define ONE_KILO_HEX                                  (0x400)
#define MARKER_BASE_ADDRESS                           (0x08004C00)
#define APPLICATION_AND_MARKER_MEMORY_SIZE_IN_KILO    (45)

/*  */
#include "STD_TYPES.h"
#include "BOOTLOADER.h"
#include "FLASH.h"
#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "HEX_PARSER.h"
#include "HUSART_interface.h"
#include "ESP8266_interface.h"


typedef void(* volatile vpv)(void);

__attribute__((section(".Marker"),used))
u32 mymarker = 0xFFFFFFFF;

__attribute__((section(".Marker"),used))
u32 EntryPoint;

typedef struct
{
	u8 DataLength;
	u8 Address1;
	u8 Address2;
	u8 RecordType;
	u8 Data[17];
}Record_t;

void ReceiveCBF(void);

u8 G_u8Flag;


int
main(int argc, char* argv[])
{
	u8  local_a50u8Buffer[50] = {0};
	u8  local_a50u8ParsedRecord[50] = {0};
	u8  local_u8ParsedRecordSize;
	u32 local_u32DestinationAddress = 0;
	u8  local_a3u8ITIBuffer[3] = "ITI";
	u8  local_u8Index = 0;
	u8  local_u8Flag = 0;
	u16 local_u16BufferSize = 0;
	u8  local_u8Counter = 0;

	switch(mymarker)
		{
		/**************************************** case NO APP **********************************************/
		case NO_APPLICATION:

			ESP8266_Init();
			ESP8266_SetReceiveCBF(ReceiveCBF);

			/* receive ITI string which indicates a new app to be flashed */
			ESP8266_Receive(local_a50u8Buffer,&local_u16BufferSize);
			while(G_u8Flag == 0);
			G_u8Flag = 0;

			for(local_u8Index = 0;local_u8Index < 3;)
			{
				if(local_a50u8Buffer[local_u8Index] == local_a3u8ITIBuffer[local_u8Index])
				{
					local_u8Index ++;
				}
			}

			if(local_u8Index == 3)
			{
				FLASH_Unlock();

				/* erase the entire flash memory of the app */
				for(local_u8Counter = 0; local_u8Counter < APPLICATION_AND_MARKER_MEMORY_SIZE_IN_KILO; local_u8Counter++)
				{
					FLASH_ErasePage((void*)MARKER_BASE_ADDRESS + (local_u8Counter * ONE_KILO_HEX));
				}

				ESP8266_Send((u8*)"YES",3);

				do{
					ESP8266_Receive(local_a50u8Buffer,&local_u16BufferSize);
					while(G_u8Flag == 0);
					G_u8Flag = 0;

					HEX_PARSER(local_a50u8Buffer, local_u16BufferSize, local_a50u8ParsedRecord , &local_u8ParsedRecordSize );

					switch( ((Record_t*)local_a50u8ParsedRecord)->RecordType )
					{
					case FLASH:
						FLASH_WriteProgram( (u32 *)(((Record_t*)local_a50u8ParsedRecord)->Data) , (u32 *)(local_u32DestinationAddress | ((u32)(((Record_t*)local_a50u8ParsedRecord)->Address1 << 8) | (u32)(((Record_t*)local_a50u8ParsedRecord)->Address2)) ),((Record_t*)local_a50u8ParsedRecord)->DataLength);
						ESP8266_Send((u8*)"YES",3);
						break;
					case EOF:
//						ESP8266_Send((u8*)"B",1);
						local_u8Flag = 1;
						break;
					case EXTEND_ADDRESS:
						local_u32DestinationAddress = ((u32)(((Record_t*)local_a50u8ParsedRecord)->Data[0] << 24)) | ((u32)(((Record_t*)local_a50u8ParsedRecord)->Data[1] << 16));
						ESP8266_Send((u8*)"YES",3);
						break;
					case ENTRY_POINT_ADDRESS:
						FLASH_WriteWord(&EntryPoint, (u32) ( ((((Record_t*)local_a50u8ParsedRecord)->Data[0]) << 24) | ((((Record_t*)local_a50u8ParsedRecord)->Data[1]) << 16) | ((((Record_t*)local_a50u8ParsedRecord)->Data[2]) << 8) | ((((Record_t*)local_a50u8ParsedRecord)->Data[3])) ));
						ESP8266_Send((u8*)"YES",3);
						break;
					}

				}while(local_u8Flag == 0);

				local_u8Flag = 0;

				/* update mymarker with valid app before reset */
				FLASH_WriteWord(&mymarker, VALID_APPLICATION);

				FLASH_Lock();

				SCB_AIRCR = (VECTKEY | SYSRSTREQ);
			}
			break;
		/****************************************************** case valid APP *****************************/
		case VALID_APPLICATION:
			((vpv)EntryPoint)();
			break;
		/****************************************************** case APP overwrite *************************/
		case APPLICATION_OVERWRITE:

//			ESP8266_Init();
			HUSART_Init(USART2);
			ESP8266_SetReceiveCBF(ReceiveCBF);

			FLASH_Unlock();

			/* erase the entire flash memory of the app */
			for(local_u8Counter = 0; local_u8Counter < APPLICATION_AND_MARKER_MEMORY_SIZE_IN_KILO; local_u8Counter++)
			{
				FLASH_ErasePage((void*)MARKER_BASE_ADDRESS + (local_u8Counter * ONE_KILO_HEX));
			}

			ESP8266_Send((u8*)"YES",3);

			do{
				ESP8266_Receive(local_a50u8Buffer,&local_u16BufferSize);
				while(G_u8Flag == 0);
				G_u8Flag = 0;

				HEX_PARSER(local_a50u8Buffer, local_u16BufferSize, local_a50u8ParsedRecord , &local_u8ParsedRecordSize );

				switch( ((Record_t*)local_a50u8ParsedRecord)->RecordType )
				{
				case FLASH:
					FLASH_WriteProgram( (u32 *)(((Record_t*)local_a50u8ParsedRecord)->Data) , (u32 *)(local_u32DestinationAddress | ((u32)(((Record_t*)local_a50u8ParsedRecord)->Address1 << 8) | (u32)(((Record_t*)local_a50u8ParsedRecord)->Address2)) ),((Record_t*)local_a50u8ParsedRecord)->DataLength);
					ESP8266_Send((u8*)"YES",3);
					break;
				case EOF:
					local_u8Flag = 1;
//					ESP8266_Send((u8*)"YES",3);
					break;
				case EXTEND_ADDRESS:
					local_u32DestinationAddress = ((u32)(((Record_t*)local_a50u8ParsedRecord)->Data[0] << 24)) | ((u32)(((Record_t*)local_a50u8ParsedRecord)->Data[1] << 16));
					ESP8266_Send((u8*)"YES",3);
					break;
				case ENTRY_POINT_ADDRESS:
					FLASH_WriteWord(&EntryPoint, (u32) ( ((((Record_t*)local_a50u8ParsedRecord)->Data[0]) << 24) | ((((Record_t*)local_a50u8ParsedRecord)->Data[1]) << 16) | ((((Record_t*)local_a50u8ParsedRecord)->Data[2]) << 8) | ((((Record_t*)local_a50u8ParsedRecord)->Data[3])) ));
					ESP8266_Send((u8*)"YES",3);
					break;
				}
			}while(local_u8Flag == 0);

			local_u8Flag = 0;

			/* update mymarker with valid app before reset */
			FLASH_WriteWord(&mymarker, VALID_APPLICATION);

			FLASH_Lock();

			SCB_AIRCR = (VECTKEY | SYSRSTREQ);

			break;
		}

	while (1);
}

void ReceiveCBF(void)
{
	G_u8Flag = 1;
}
