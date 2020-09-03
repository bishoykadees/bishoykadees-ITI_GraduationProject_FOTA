/*
 * BOOTLOADER.h
 *
 *  Created on: Jun 24, 2020
 *      Author: Bishoy Nabil
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#define APPLICATION_OVERWRITE                         ((u32)0x01AA02BB)
#define SCB_AIRCR                                     (*((volatile u32 * const)0xE000ED0C))
#define SYSRSTREQ                                     ((u32)0x00000004)
#define VECTKEY                                       ((u32)0x05FA0000)
#define MARKER_ADDRESS                                ((u32*)0x08004C00)



#endif /* BOOTLOADER_H_ */
