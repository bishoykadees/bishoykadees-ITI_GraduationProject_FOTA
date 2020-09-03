################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader/src/ESP8266_program.c \
../Bootloader/src/FLASH.c \
../Bootloader/src/GPIO.c \
../Bootloader/src/HUSART_program.c \
../Bootloader/src/NVIC_program.c \
../Bootloader/src/RCC.c \
../Bootloader/src/USART_program.c 

OBJS += \
./Bootloader/src/ESP8266_program.o \
./Bootloader/src/FLASH.o \
./Bootloader/src/GPIO.o \
./Bootloader/src/HUSART_program.o \
./Bootloader/src/NVIC_program.o \
./Bootloader/src/RCC.o \
./Bootloader/src/USART_program.o 

C_DEPS += \
./Bootloader/src/ESP8266_program.d \
./Bootloader/src/FLASH.d \
./Bootloader/src/GPIO.d \
./Bootloader/src/HUSART_program.d \
./Bootloader/src/NVIC_program.d \
./Bootloader/src/RCC.d \
./Bootloader/src/USART_program.d 


# Each subdirectory must supply rules for building sources it contributes
Bootloader/src/%.o: ../Bootloader/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"D:\ITI\01-ASSAF\ARM_SDK\ARM_Projects\GP\Bootloader\include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


