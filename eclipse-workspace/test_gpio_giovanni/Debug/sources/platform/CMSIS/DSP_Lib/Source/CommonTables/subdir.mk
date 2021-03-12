################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sources/platform/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.c \
../sources/platform/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.c 

OBJS += \
./sources/platform/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.o \
./sources/platform/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.o 

C_DEPS += \
./sources/platform/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.d \
./sources/platform/CMSIS/DSP_Lib/Source/CommonTables/arm_const_structs.d 


# Each subdirectory must supply rules for building sources it contributes
sources/platform/CMSIS/DSP_Lib/Source/CommonTables/%.o: ../sources/platform/CMSIS/DSP_Lib/Source/CommonTables/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-builtin  -g3 -DCPU_MCIMX7D_M4 -DARM_MATH_CM4 -D__DEBUG -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/examples/imx7_colibri_m4" -I/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/CMSIS/Include -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/startup" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/include" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/utilities/inc" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/drivers/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


