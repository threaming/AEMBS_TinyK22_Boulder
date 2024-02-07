################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_alien.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_default.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_material.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_mono.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_nemo.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_night.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_templ.c \
../McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_zen.c 

C_DEPS += \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_alien.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_default.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_material.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_mono.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_nemo.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_night.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_templ.d \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_zen.d 

OBJS += \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_alien.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_default.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_material.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_mono.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_nemo.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_night.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_templ.o \
./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_zen.o 


# Each subdirectory must supply rules for building sources it contributes
McuLib/LittlevGL/lvgl/src/lv_themes/%.o: ../McuLib/LittlevGL/lvgl/src/lv_themes/%.c McuLib/LittlevGL/lvgl/src/lv_themes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\source" -I../McuLib -I../McuLib/config -I../McuLib/config/fonts -I../McuLib/fonts -I../McuLib/src -I../McuLib/FreeRTOS/Source/include -I../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../McuLib/SEGGER_RTT -I../McuLib/SEGGER_Sysview -I../McuLib/TraceRecorder -I../McuLib/TraceRecorder/config -I../McuLib/TraceRecorder/include -I../McuLib/TraceRecorder/streamports/Jlink_RTT/include -I../McuLib/HD44780 -I../McuLib/FatFS -I../McuLib/FatFS/source -include"C:/Users/andre/OneDrive - Hochschule Luzern/00_Modules/FS23_AEMBS/00_Projects/01_AEMBY_tinyK22/source/IncludeMcuLibConfig.h" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-McuLib-2f-LittlevGL-2f-lvgl-2f-src-2f-lv_themes

clean-McuLib-2f-LittlevGL-2f-lvgl-2f-src-2f-lv_themes:
	-$(RM) ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_alien.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_alien.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_default.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_default.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_material.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_material.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_mono.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_mono.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_nemo.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_nemo.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_night.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_night.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_templ.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_templ.o ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_zen.d ./McuLib/LittlevGL/lvgl/src/lv_themes/lv_theme_zen.o

.PHONY: clean-McuLib-2f-LittlevGL-2f-lvgl-2f-src-2f-lv_themes

