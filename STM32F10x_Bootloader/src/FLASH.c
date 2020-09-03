/*
 * FLASH.c
 *
 *  Created on: May 29, 2020
 *      Author: Bishoy Nabil
 */

#include "FLASH.h"

#define FLASH                                         ((volatile FlashReg_t* const)0x40022000)
#define RDPRT                                         ((u16)0x00A5)
#define KEY1                                          ((u32)0x45670123)
#define KEY2                                          ((u32)0xCDEF89AB)
#define FLASH_LOCK_SET                                ((u32)0x00000080)
#define FLASH_LOCK_MASK                               ((u32)0x00000080)
#define FLASH_LOCK_BIT                                ((u8)7)
#define FLASH_PG_SET                                  ((u32)0x00000001)
#define FLASH_BSY_MASK                                ((u32)0x00000001)
#define FLASH_EOP_SET                                 ((u32)0x00000020)
#define FLASH_PER_SET                                 ((u32)0x00000002)
#define FLASH_STRT_SET                                ((u32)0x00000040)
#define FLASH_MER_SET                                 ((u32)0x00000004)
#define FLASH_PG_CLEAR                                ((u32)0xFFFFFFFE)
#define FLASH_PER_CLEAR                               ((u32)0xFFFFFFFD)
#define FLASH_MER_CLEAR                               ((u32)0xFFFFFFFB)

typedef struct{
	u32 ACR;
	u32 KEYR;
	u32 OPTKEYR;
	u32 SR;
	u32 CR;
	u32 AR;
	u32 Reserved;
	u32 OBR;
	u32 WRPR;
}FlashReg_t;

extern ErrorStatus FLASH_WriteWord(u32* copy_pu32Address, u32 copy_u32Data)
{
	ErrorStatus Local_ErrorStatus = OK;
	if((((FLASH->CR & FLASH_LOCK_MASK) >> FLASH_LOCK_BIT) == 0) && ((*copy_pu32Address) == 0xFFFFFFFF))
	{
		while(FLASH->SR & FLASH_BSY_MASK);
		FLASH->CR |= FLASH_PG_SET;
		*((u16*)copy_pu32Address) = ((u16)copy_u32Data);
		while(FLASH->SR & FLASH_BSY_MASK);
		FLASH->SR |= FLASH_EOP_SET;
		*((u16*)(copy_pu32Address)+1) = ((u16)(copy_u32Data >> 16));
		while(FLASH->SR & FLASH_BSY_MASK);
		FLASH->CR &= FLASH_PG_CLEAR;
		FLASH->SR |= FLASH_EOP_SET;
	}
	return Local_ErrorStatus;
}
extern ErrorStatus FLASH_WriteProgram(u32* copy_pu32SourceAddress, u32* copy_pu32DestinationAddress, u32 copy_u32NumberOfBytes)
{
	u32 Local_u32Index = 0;
	while(FLASH->SR & FLASH_BSY_MASK);
	FLASH->CR |= FLASH_PG_SET;
	for(Local_u32Index = 0;Local_u32Index < (copy_u32NumberOfBytes/2); Local_u32Index ++)
	{
		*(((u16*)copy_pu32DestinationAddress) + Local_u32Index) = *(((u16*)copy_pu32SourceAddress) + Local_u32Index);
		while(FLASH->SR & FLASH_BSY_MASK);
		FLASH->SR |= FLASH_EOP_SET;
	}
	FLASH->CR &= FLASH_PG_CLEAR;
	return OK;
}
extern ErrorStatus FLASH_Unlock(void)
{
	ErrorStatus Local_ErrorStatus = OK;
	FLASH->KEYR = KEY1;
	FLASH->KEYR = KEY2;
	if(((FLASH->CR & FLASH_LOCK_MASK) >> FLASH_LOCK_BIT) == 1)
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}
extern ErrorStatus FLASH_ErasePage(u32* copy_pu32Address)
{
	ErrorStatus Local_ErrorStatus = OK;
	u32 Local_u32LockBit = ((FLASH->CR & FLASH_LOCK_MASK) >> FLASH_LOCK_BIT);
	if(Local_u32LockBit == 0)
	{
		while(FLASH->SR & FLASH_BSY_MASK);
		FLASH->CR |= FLASH_PER_SET;
		FLASH->AR = (u32)copy_pu32Address;
		FLASH->CR |= FLASH_STRT_SET;
		while(FLASH->SR & FLASH_BSY_MASK);
		FLASH->CR &= FLASH_PER_CLEAR;
		FLASH->SR |= FLASH_EOP_SET;
		if((*copy_pu32Address) != 0xFFFFFFFF)
		{
			Local_ErrorStatus = NOK;
		}
	}
	else
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}
extern ErrorStatus FLASH_EraseMass(void)
{
	ErrorStatus Local_ErrorStatus = OK;
	while(FLASH->SR & FLASH_BSY_MASK);
	FLASH->CR |= FLASH_MER_SET;
	FLASH->CR |= FLASH_STRT_SET;
	while(FLASH->SR & FLASH_BSY_MASK);
	return Local_ErrorStatus;
}
extern ErrorStatus FLASH_Lock(void)
{
	ErrorStatus Local_ErrorStatus = OK;
	FLASH->CR |= FLASH_LOCK_SET;
	u32 Local_u32LockBit = ((FLASH->CR & FLASH_LOCK_MASK) >> FLASH_LOCK_BIT);
	if(Local_u32LockBit == 0)
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}
