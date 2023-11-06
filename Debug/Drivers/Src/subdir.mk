################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/STM32F411RE_GPIO.c \
../Drivers/Src/STM32F411RE_NVIC.c \
../Drivers/Src/STM32F411RE_RCC.c \
../Drivers/Src/STM32F411RE_TIMER.c 

OBJS += \
./Drivers/Src/STM32F411RE_GPIO.o \
./Drivers/Src/STM32F411RE_NVIC.o \
./Drivers/Src/STM32F411RE_RCC.o \
./Drivers/Src/STM32F411RE_TIMER.o 

C_DEPS += \
./Drivers/Src/STM32F411RE_GPIO.d \
./Drivers/Src/STM32F411RE_NVIC.d \
./Drivers/Src/STM32F411RE_RCC.d \
./Drivers/Src/STM32F411RE_TIMER.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -c -I../Inc -I"C:/Users/velazjor/Desktop/Proyectos/API/Drivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/STM32F411RE_GPIO.cyclo ./Drivers/Src/STM32F411RE_GPIO.d ./Drivers/Src/STM32F411RE_GPIO.o ./Drivers/Src/STM32F411RE_GPIO.su ./Drivers/Src/STM32F411RE_NVIC.cyclo ./Drivers/Src/STM32F411RE_NVIC.d ./Drivers/Src/STM32F411RE_NVIC.o ./Drivers/Src/STM32F411RE_NVIC.su ./Drivers/Src/STM32F411RE_RCC.cyclo ./Drivers/Src/STM32F411RE_RCC.d ./Drivers/Src/STM32F411RE_RCC.o ./Drivers/Src/STM32F411RE_RCC.su ./Drivers/Src/STM32F411RE_TIMER.cyclo ./Drivers/Src/STM32F411RE_TIMER.d ./Drivers/Src/STM32F411RE_TIMER.o ./Drivers/Src/STM32F411RE_TIMER.su

.PHONY: clean-Drivers-2f-Src

