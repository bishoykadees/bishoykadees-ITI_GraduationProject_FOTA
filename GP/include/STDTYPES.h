/* Module Name : STD_TYPES
 * File Name   : STD_TYPES.h
 * Author      : Bishoy Nabil
 * Version     : 1.3
 * Date        : before 13/4/2020 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char      u8;
typedef unsigned short int u16;
typedef unsigned long int  u32;

typedef signed char        s8;
typedef signed short int   s16;
typedef signed long int    s32;

typedef float              f32;
typedef double             f64;
typedef long double        f96;

typedef unsigned char      ErrorStatus;
typedef unsigned char      Status;
#define OK                 1
#define NOK                0
#define IDLE               0
#define BUSY               1
#define ERROR              2
/*
typedef enum Error{
	OK,
	NOK,
	NULLPOINTER
}ErrorStatus;
*/

#define NULL    ((void*)0)

#endif
