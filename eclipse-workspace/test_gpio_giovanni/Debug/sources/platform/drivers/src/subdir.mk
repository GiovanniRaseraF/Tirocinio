################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../sources/platform/drivers/src/adc_imx7d.c \
../sources/platform/drivers/src/ccm_analog_imx7d.c \
../sources/platform/drivers/src/ccm_imx7d.c \
../sources/platform/drivers/src/ecspi.c \
../sources/platform/drivers/src/flexcan.c \
../sources/platform/drivers/src/gpio_imx.c \
../sources/platform/drivers/src/gpt.c \
../sources/platform/drivers/src/i2c_imx.c \
../sources/platform/drivers/src/lmem.c \
../sources/platform/drivers/src/mu_imx.c \
../sources/platform/drivers/src/rdc.c \
../sources/platform/drivers/src/rdc_semaphore.c \
../sources/platform/drivers/src/sema4.c \
../sources/platform/drivers/src/uart_imx.c \
../sources/platform/drivers/src/wdog_imx.c 

OBJS += \
./sources/platform/drivers/src/adc_imx7d.o \
./sources/platform/drivers/src/ccm_analog_imx7d.o \
./sources/platform/drivers/src/ccm_imx7d.o \
./sources/platform/drivers/src/ecspi.o \
./sources/platform/drivers/src/flexcan.o \
./sources/platform/drivers/src/gpio_imx.o \
./sources/platform/drivers/src/gpt.o \
./sources/platform/drivers/src/i2c_imx.o \
./sources/platform/drivers/src/lmem.o \
./sources/platform/drivers/src/mu_imx.o \
./sources/platform/drivers/src/rdc.o \
./sources/platform/drivers/src/rdc_semaphore.o \
./sources/platform/drivers/src/sema4.o \
./sources/platform/drivers/src/uart_imx.o \
./sources/platform/drivers/src/wdog_imx.o 

C_DEPS += \
./sources/platform/drivers/src/adc_imx7d.d \
./sources/platform/drivers/src/ccm_analog_imx7d.d \
./sources/platform/drivers/src/ccm_imx7d.d \
./sources/platform/drivers/src/ecspi.d \
./sources/platform/drivers/src/flexcan.d \
./sources/platform/drivers/src/gpio_imx.d \
./sources/platform/drivers/src/gpt.d \
./sources/platform/drivers/src/i2c_imx.d \
./sources/platform/drivers/src/lmem.d \
./sources/platform/drivers/src/mu_imx.d \
./sources/platform/drivers/src/rdc.d \
./sources/platform/drivers/src/rdc_semaphore.d \
./sources/platform/drivers/src/sema4.d \
./sources/platform/drivers/src/uart_imx.d \
./sources/platform/drivers/src/wdog_imx.d 


# Each subdirectory must supply rules for building sources it contributes
sources/platform/drivers/src/%.o: ../sources/platform/drivers/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-builtin  -g3 -DCPU_MCIMX7D_M4 -DARM_MATH_CM4 -D__DEBUG -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/examples/imx7_colibri_m4" -I/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/CMSIS/Include -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/startup" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/include" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/utilities/inc" -I"/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/drivers/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


