################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/keys_handler.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/keys_handler.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/keys_handler.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DDEBUG -DSTM32F446xx -DUSE_STDPERIPH_DRIVER -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/core" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/CMSIS/device" -I"C:/work/workspace_stm/nucleo-f446re_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/work/workspace_stm/tetris_446re/inc" -I"C:/work/workspace_stm/tetris_446re/src/FreeRTOS/include" -I"C:/work/workspace_stm/tetris_446re/src/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/work/workspace_stm/tetris_446re/src" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


