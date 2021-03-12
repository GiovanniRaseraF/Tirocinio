################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../sources/platform/devices/MCIMX7D/startup/gcc/startup_MCIMX7D_M4.S 

OBJS += \
./sources/platform/devices/MCIMX7D/startup/gcc/startup_MCIMX7D_M4.o 

S_UPPER_DEPS += \
./sources/platform/devices/MCIMX7D/startup/gcc/startup_MCIMX7D_M4.d 


# Each subdirectory must supply rules for building sources it contributes
sources/platform/devices/MCIMX7D/startup/gcc/%.o: ../sources/platform/devices/MCIMX7D/startup/gcc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-builtin  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


