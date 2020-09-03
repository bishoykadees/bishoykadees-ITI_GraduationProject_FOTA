/* Module Name : NVIC
 * File Name   : NVIC_interface.h
 * Author      : Bishoy Nabil
 * Version     : 2.0
 * Date        : before 13/4/2020 */

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

typedef struct
{
	u8 ID;                  /* 0 - 239 */
	u8 EnableBit;           /* 1->Enable, 0->Disable */
	u8 PendingFlag;         /* 1->Enable, 0->Disable */
	u8 ActiveStatus;        /* 1->Active, 0->NotActive */
	u8 Priority;            /* 0x00 - 0xFF */
	u8 PriorityGroupBits;
}NVIC_t;

#define NVIC_WWDG                              0
#define NVIC_PVD                               1
#define NVIC_TAMPER                            2
#define NVIC_RTC                               3
#define NVIC_FLASH                             4
#define NVIC_RCC                               5
#define NVIC_EXTI0                             6
#define NVIC_EXTI1                             7
#define NVIC_EXTI2                             8
#define NVIC_EXTI3                             9
#define NVIC_EXTI4                             10
#define NVIC_DMA1_CHANNEL1                     11
#define NVIC_DMA1_CHANNEL2                     12
#define NVIC_DMA1_CHANNEL3                     13
#define NVIC_DMA1_CHANNEL4                     14
#define NVIC_DMA1_CHANNEL5                     15
#define NVIC_DMA1_CHANNEL6                     16
#define NVIC_DMA1_CHANNEL7                     17
#define NVIC_ADC1_2                            18
#define NVIC_CAN1_TX                           19
#define NVIC_CAN1_RX0                          20
#define NVIC_CAN1_RX1                          21
#define NVIC_CAN1_SCE                          22
#define NVIC_EXTI9_5                           23
#define NVIC_TIM1_BRK                          24
#define NVIC_TIM1_UP                           25
#define NVIC_TIM1_TRG_COM                      26
#define NVIC_TIM1_CC                           27
#define NVIC_TIM2                              28
#define NVIC_TIM3                              29
#define NVIC_TIM4                              30
#define NVIC_I2C1_EV                           31
#define NVIC_I2C1_ER                           32
#define NVIC_I2C2_EV                           33
#define NVIC_I2C2_ER                           34
#define NVIC_SPI1                              35
#define NVIC_SPI2                              36
#define NVIC_USART1                            37
#define NVIC_USART2                            38
#define NVIC_USART3                            39
#define NVIC_EXTI15_10                         40
#define NVIC_RTCALARM                          41
#define NVIC_OTG_FS_WKUP                       42
#define NVIC_TIM5                              50
#define NVIC_SPI3                              51
#define NVIC_UART4                             52
#define NVIC_UART5                             53
#define NVIC_TIM6                              54
#define NVIC_TIM7                              55
#define NVIC_DMA2_CHANNEL1                     56
#define NVIC_DMA2_CHANNEL2                     57
#define NVIC_DMA2_CHANNEL3                     58
#define NVIC_DMA2_CHANNEL4                     59
#define NVIC_DMA2_CHANNEL5                     60
#define NVIC_ETH                               61
#define NVIC_ETH_WKUP                          62
#define NVIC_CAN2_TX                           63
#define NVIC_CAN2_RX0                          64
#define NVIC_CAN2_RX1                          65
#define NVIC_CAN2_SCE                          66
#define NVIC_OTG_FS                            67

#define ENABLE                            1
#define DISABLE                           0

#define PRIORITYGROUPEQUALS_0             0x00000000
#define PRIORITYGROUPEQUALS_1             0x00000100
#define PRIORITYGROUPEQUALS_2             0x00000200
#define PRIORITYGROUPEQUALS_3             0x00000300
#define PRIORITYGROUPEQUALS_4             0x00000400
#define PRIORITYGROUPEQUALS_5             0x00000500
#define PRIORITYGROUPEQUALS_6             0x00000600
#define PRIORITYGROUPEQUALS_7             0x00000700

ErrorStatus NVIC_ControlEnableInterrupt   (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_ControlPendingFlag       (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_InterruptActiveStatus    (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_SetInterruptPriority     (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_GetInterruptPriority     (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_SetPriorityGroupBits     (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_ControlAllInterrupts     (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_ControlAllFaults         (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_SetPriorityFilter        (NVIC_t *Copy_NVICStruct);
ErrorStatus NVIC_GenerateSoftwareInterrupt(NVIC_t *Copy_NVICStruct);

#endif

/*tarteeb el inclusion:
el libraries
el layers ely ta7tya
el files bt3ty
*/
