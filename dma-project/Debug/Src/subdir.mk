################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/dma.c \
../Src/exti.c \
../Src/gpio.c \
../Src/main.c \
../Src/nvic.c \
../Src/svn_segment.c \
../Src/uart.c 

OBJS += \
./Src/dma.o \
./Src/exti.o \
./Src/gpio.o \
./Src/main.o \
./Src/nvic.o \
./Src/svn_segment.o \
./Src/uart.o 

C_DEPS += \
./Src/dma.d \
./Src/exti.d \
./Src/gpio.d \
./Src/main.d \
./Src/nvic.d \
./Src/svn_segment.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I"E:/My Workspace/C-sbme04t01-embedded-workspace/dma-project/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

