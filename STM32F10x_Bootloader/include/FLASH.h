/* Module Name : FLASH
 * File Name   : FLASH.h
 * Author      : Bishoy Nabil
 * Version     : 1.0
 * Date        : 29/5/2020 */

#ifndef FLASH_H_
#define FLASH_H_

#include "STD_TYPES.h"

extern ErrorStatus FLASH_WriteWord(u32* copy_pu32Address, u32 copy_u32Data);
extern ErrorStatus FLASH_WriteProgram(u32* copy_pu32SourceAddress, u32* copy_pu32DestinationAddress, u32 copy_u32NumberOfBytes);
extern ErrorStatus FLASH_Unlock(void);
extern ErrorStatus FLASH_ErasePage(u32* copy_pu32Address);
extern ErrorStatus FLASH_EraseMass(void);
extern ErrorStatus FLASH_Lock(void);

#endif /* FLASH_H_ */
