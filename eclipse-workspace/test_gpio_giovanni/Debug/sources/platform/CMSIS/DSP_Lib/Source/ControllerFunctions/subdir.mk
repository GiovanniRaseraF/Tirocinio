################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_f32.c \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q15.c \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.c \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_f32.c \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q15.c \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.c \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_f32.c \
../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_f32.o \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q15.o \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.o \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_f32.o \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q15.o \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.o \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_f32.o \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_q31.o 

C_DEPS += \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_f32.d \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q15.d \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.d \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_f32.d \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q15.d \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.d \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_f32.d \
./sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/%.o: ../sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-builtin  -g3 -DCPU_MCIMX7D_M4 -DARM_MATH_CM4 -D__DEBUG -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/examples/imx7_colibri_m4" -I/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/CMSIS/Include -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/startup" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/include" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/utilities/inc" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/drivers/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


