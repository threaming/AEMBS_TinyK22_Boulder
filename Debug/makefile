################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/hat/subdir.mk
-include source/game/images/subdir.mk
-include source/game/subdir.mk
-include source/buttons/subdir.mk
-include source/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
-include McuLib/src/subdir.mk
-include McuLib/fonts/subdir.mk
-include McuLib/SEGGER_Sysview/subdir.mk
-include McuLib/SEGGER_RTT/subdir.mk
-include McuLib/LittlevGL/lvgl/src/lv_themes/subdir.mk
-include McuLib/LittlevGL/lvgl/src/lv_objx/subdir.mk
-include McuLib/LittlevGL/lvgl/src/lv_misc/subdir.mk
-include McuLib/LittlevGL/lvgl/src/lv_hal/subdir.mk
-include McuLib/LittlevGL/lvgl/src/lv_font/subdir.mk
-include McuLib/LittlevGL/lvgl/src/lv_draw/subdir.mk
-include McuLib/LittlevGL/lvgl/src/lv_core/subdir.mk
-include McuLib/LittlevGL/lvgl/porting/subdir.mk
-include McuLib/FreeRTOS/Source/portable/MemMang/subdir.mk
-include McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include McuLib/FreeRTOS/Source/portable/Common/subdir.mk
-include McuLib/FreeRTOS/Source/subdir.mk
-include McuLib/FreeRTOS/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 01_AEMBS_tinyK22
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: 01_AEMBS_tinyK22.axf

# Tool invocations
01_AEMBS_tinyK22.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="01_AEMBS_tinyK22.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T 01_AEMBS_tinyK22_Debug.ld -o "01_AEMBS_tinyK22.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 01_AEMBS_tinyK22.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "01_AEMBS_tinyK22.axf"; # arm-none-eabi-objcopy -v -O binary "01_AEMBS_tinyK22.axf" "01_AEMBS_tinyK22.bin" ; # checksum -p MK22FN512xxx12 -d "01_AEMBS_tinyK22.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
