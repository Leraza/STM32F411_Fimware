################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/TIM_Interrupcion_Basic.c 

OBJS += \
./Src/TIM_Interrupcion_Basic.o 

C_DEPS += \
./Src/TIM_Interrupcion_Basic.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -c -I../Inc -I"C:/Users/velazjor/Desktop/Proyectos/API/Drivers/Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/TIM_Interrupcion_Basic.cyclo ./Src/TIM_Interrupcion_Basic.d ./Src/TIM_Interrupcion_Basic.o ./Src/TIM_Interrupcion_Basic.su

.PHONY: clean-Src

