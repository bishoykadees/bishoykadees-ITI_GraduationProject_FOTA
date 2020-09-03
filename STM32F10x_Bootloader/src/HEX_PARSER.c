/*
 * HEX_PARSER.c
 *
 *  Created on: Jun 5, 2020
 *      Author: Bishoy Nabil
 */

#include "HEX_PARSER.h"

void HEX_PARSER( u8* copy_pu8Buffer, u8 copy_u8BufferSize, u8* copy_pu8ReturnBuffer, u8* copy_pu8ReturnBufferSize )
{
	u8 local_u8BufferIndex = 0;
	u8 local_u8ReturnBufferIndex = 0;

	if(copy_pu8Buffer[0] == ':')
	{
		/* convert each ascii character to a number 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F */
		for( local_u8BufferIndex = 1 ; local_u8BufferIndex < copy_u8BufferSize - 1 ; local_u8BufferIndex ++ )
		{
			if( ( copy_pu8Buffer[local_u8BufferIndex] <= 57 ) && ( copy_pu8Buffer[local_u8BufferIndex] >= 48 ) )
			{
				copy_pu8Buffer[local_u8BufferIndex] -= 48;
			}
			else if( ( copy_pu8Buffer[local_u8BufferIndex] <= 70 ) && ( copy_pu8Buffer[local_u8BufferIndex] >= 65 ) )
			{
				copy_pu8Buffer[local_u8BufferIndex] -= 55;
			}
		}
		for( local_u8BufferIndex = 1 , local_u8ReturnBufferIndex = 0 ; local_u8BufferIndex < copy_u8BufferSize - 1 ; local_u8BufferIndex += 2 , local_u8ReturnBufferIndex ++ )
		{
			copy_pu8Buffer[ local_u8BufferIndex ] = copy_pu8Buffer[ local_u8BufferIndex ] << 4;
			copy_pu8ReturnBuffer[ local_u8ReturnBufferIndex ] = copy_pu8Buffer[ local_u8BufferIndex ] | copy_pu8Buffer[ local_u8BufferIndex + 1 ];
		}

		(*copy_pu8ReturnBufferSize) = local_u8ReturnBufferIndex;
	}
}


