################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sources/examples/imx7_colibri_m4/board.c \
../sources/examples/imx7_colibri_m4/clock_freq.c \
../sources/examples/imx7_colibri_m4/gpio_pins.c \
../sources/examples/imx7_colibri_m4/pin_mux.c 

OBJS += \
./sources/examples/imx7_colibri_m4/board.o \
./sources/examples/imx7_colibri_m4/clock_freq.o \
./sources/examples/imx7_colibri_m4/gpio_pins.o \
./sources/examples/imx7_colibri_m4/pin_mux.o 

C_DEPS += \
./sources/examples/imx7_colibri_m4/board.d \
./sources/examples/imx7_colibri_m4/clock_freq.d \
./sources/examples/imx7_colibri_m4/gpio_pins.d \
./sources/examples/imx7_colibri_m4/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
sources/examples/imx7_colibri_m4/%.o: ../sources/examples/imx7_colibri_m4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-builtin  -g3 -DCPU_MCIMX7D_M4 -DARM_MATH_CM4 -D__DEBUG -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/examples/imx7_colibri_m4" -I/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/CMSIS/Include -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/startup" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/include" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/utilities/inc" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/drivers/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


