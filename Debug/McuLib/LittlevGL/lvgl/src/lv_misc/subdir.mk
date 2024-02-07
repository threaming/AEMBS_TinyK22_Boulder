################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_anim.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_area.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_async.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_circ.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_color.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_fs.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_gc.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_ll.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_log.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_math.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_mem.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_task.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_templ.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_txt.c \
../McuLib/LittlevGL/lvgl/src/lv_misc/lv_utils.c 

C_DEPS += \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_anim.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_area.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_async.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_circ.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_color.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_fs.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_gc.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_ll.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_log.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_math.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_mem.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_task.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_templ.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_txt.d \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_utils.d 

OBJS += \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_anim.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_area.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_async.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_circ.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_color.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_fs.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_gc.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_ll.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_log.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_math.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_mem.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_task.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_templ.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_txt.o \
./McuLib/LittlevGL/lvgl/src/lv_misc/lv_utils.o 


# Each subdirectory must supply rules for building sources it contributes
McuLib/LittlevGL/lvgl/src/lv_misc/%.o: ../McuLib/LittlevGL/lvgl/src/lv_misc/%.c McuLib/LittlevGL/lvgl/src/lv_misc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\source" -I../McuLib -I../McuLib/config -I../McuLib/config/fonts -I../McuLib/fonts -I../McuLib/src -I../McuLib/FreeRTOS/Source/include -I../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../McuLib/SEGGER_RTT -I../McuLib/SEGGER_Sysview -I../McuLib/TraceRecorder -I../McuLib/TraceRecorder/config -I../McuLib/TraceRecorder/include -I../McuLib/TraceRecorder/streamports/Jlink_RTT/include -I../McuLib/HD44780 -I../McuLib/FatFS -I../McuLib/FatFS/source -include"C:/Users/andre/OneDrive - Hochschule Luzern/00_Modules/FS23_AEMBS/00_Projects/01_AEMBY_tinyK22/source/IncludeMcuLibConfig.h" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-McuLib-2f-LittlevGL-2f-lvgl-2f-src-2f-lv_misc

clean-McuLib-2f-LittlevGL-2f-lvgl-2f-src-2f-lv_misc:
	-$(RM) ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_anim.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_anim.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_area.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_area.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_async.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_async.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_circ.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_circ.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_color.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_color.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_fs.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_fs.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_gc.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_gc.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_ll.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_ll.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_log.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_log.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_math.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_math.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_mem.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_mem.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_task.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_task.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_templ.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_templ.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_txt.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_txt.o ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_utils.d ./McuLib/LittlevGL/lvgl/src/lv_misc/lv_utils.o

.PHONY: clean-McuLib-2f-LittlevGL-2f-lvgl-2f-src-2f-lv_misc

