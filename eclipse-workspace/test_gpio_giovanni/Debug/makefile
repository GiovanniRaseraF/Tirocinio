################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include sources/platform/utilities/src/subdir.mk
-include sources/platform/drivers/src/subdir.mk
-include sources/platform/devices/MCIMX7D/startup/gcc/subdir.mk
-include sources/platform/devices/MCIMX7D/startup/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/TransformFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/SupportFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/StatisticsFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/MatrixFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/FilteringFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/FastMathFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/ControllerFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/ComplexMathFunctions/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/CommonTables/subdir.mk
-include sources/platform/CMSIS/DSP_Lib/Source/BasicMathFunctions/subdir.mk
-include sources/examples/imx7_colibri_m4/subdir.mk
-include sources/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
test_gpio_giovanni.bin \

SECONDARY_SIZE += \
test_gpio_giovanni.siz \


# All Target
all: test_gpio_giovanni.elf secondary-outputs

# Tool invocations
test_gpio_giovanni.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU Arm Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-builtin  -g3 -T "MCIMX7D_M4_tcm.ld" -Xlinker --gc-sections -L/home/fdsa/eclipse-workspace/test_gpio_giovanni/sources/platform/devices/MCIMX7D/linker/gcc -Wl,-Map,"test_gpio_giovanni.map" --specs=nano.specs --specs=nosys.specs -o "test_gpio_giovanni.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

test_gpio_giovanni.bin: test_gpio_giovanni.elf
	@echo 'Invoking: GNU Arm Cross Create Flash Image'
	arm-none-eabi-objcopy -O binary "test_gpio_giovanni.elf"  "test_gpio_giovanni.bin"
	@echo 'Finished building: $@'
	@echo ' '

test_gpio_giovanni.siz: test_gpio_giovanni.elf
	@echo 'Invoking: GNU Arm Cross Print Size'
	arm-none-eabi-size --format=berkeley "test_gpio_giovanni.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) test_gpio_giovanni.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
