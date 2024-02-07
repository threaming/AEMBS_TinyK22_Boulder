################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../McuLib/fonts/McuFontCour08Bold.c \
../McuLib/fonts/McuFontCour08Normal.c \
../McuLib/fonts/McuFontCour10Bold.c \
../McuLib/fonts/McuFontCour10Normal.c \
../McuLib/fonts/McuFontCour12Bold.c \
../McuLib/fonts/McuFontCour12Normal.c \
../McuLib/fonts/McuFontCour14Bold.c \
../McuLib/fonts/McuFontCour14Normal.c \
../McuLib/fonts/McuFontCour18Bold.c \
../McuLib/fonts/McuFontCour18Normal.c \
../McuLib/fonts/McuFontCour24Bold.c \
../McuLib/fonts/McuFontCour24Normal.c \
../McuLib/fonts/McuFontHelv08Bold.c \
../McuLib/fonts/McuFontHelv08Normal.c \
../McuLib/fonts/McuFontHelv10Bold.c \
../McuLib/fonts/McuFontHelv10Normal.c \
../McuLib/fonts/McuFontHelv12Bold.c \
../McuLib/fonts/McuFontHelv12Normal.c \
../McuLib/fonts/McuFontHelv14Bold.c \
../McuLib/fonts/McuFontHelv14Normal.c \
../McuLib/fonts/McuFontHelv18Bold.c \
../McuLib/fonts/McuFontHelv18Normal.c \
../McuLib/fonts/McuFontHelv24Bold.c \
../McuLib/fonts/McuFontHelv24Normal.c 

C_DEPS += \
./McuLib/fonts/McuFontCour08Bold.d \
./McuLib/fonts/McuFontCour08Normal.d \
./McuLib/fonts/McuFontCour10Bold.d \
./McuLib/fonts/McuFontCour10Normal.d \
./McuLib/fonts/McuFontCour12Bold.d \
./McuLib/fonts/McuFontCour12Normal.d \
./McuLib/fonts/McuFontCour14Bold.d \
./McuLib/fonts/McuFontCour14Normal.d \
./McuLib/fonts/McuFontCour18Bold.d \
./McuLib/fonts/McuFontCour18Normal.d \
./McuLib/fonts/McuFontCour24Bold.d \
./McuLib/fonts/McuFontCour24Normal.d \
./McuLib/fonts/McuFontHelv08Bold.d \
./McuLib/fonts/McuFontHelv08Normal.d \
./McuLib/fonts/McuFontHelv10Bold.d \
./McuLib/fonts/McuFontHelv10Normal.d \
./McuLib/fonts/McuFontHelv12Bold.d \
./McuLib/fonts/McuFontHelv12Normal.d \
./McuLib/fonts/McuFontHelv14Bold.d \
./McuLib/fonts/McuFontHelv14Normal.d \
./McuLib/fonts/McuFontHelv18Bold.d \
./McuLib/fonts/McuFontHelv18Normal.d \
./McuLib/fonts/McuFontHelv24Bold.d \
./McuLib/fonts/McuFontHelv24Normal.d 

OBJS += \
./McuLib/fonts/McuFontCour08Bold.o \
./McuLib/fonts/McuFontCour08Normal.o \
./McuLib/fonts/McuFontCour10Bold.o \
./McuLib/fonts/McuFontCour10Normal.o \
./McuLib/fonts/McuFontCour12Bold.o \
./McuLib/fonts/McuFontCour12Normal.o \
./McuLib/fonts/McuFontCour14Bold.o \
./McuLib/fonts/McuFontCour14Normal.o \
./McuLib/fonts/McuFontCour18Bold.o \
./McuLib/fonts/McuFontCour18Normal.o \
./McuLib/fonts/McuFontCour24Bold.o \
./McuLib/fonts/McuFontCour24Normal.o \
./McuLib/fonts/McuFontHelv08Bold.o \
./McuLib/fonts/McuFontHelv08Normal.o \
./McuLib/fonts/McuFontHelv10Bold.o \
./McuLib/fonts/McuFontHelv10Normal.o \
./McuLib/fonts/McuFontHelv12Bold.o \
./McuLib/fonts/McuFontHelv12Normal.o \
./McuLib/fonts/McuFontHelv14Bold.o \
./McuLib/fonts/McuFontHelv14Normal.o \
./McuLib/fonts/McuFontHelv18Bold.o \
./McuLib/fonts/McuFontHelv18Normal.o \
./McuLib/fonts/McuFontHelv24Bold.o \
./McuLib/fonts/McuFontHelv24Normal.o 


# Each subdirectory must supply rules for building sources it contributes
McuLib/fonts/%.o: ../McuLib/fonts/%.c McuLib/fonts/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\source" -I../McuLib -I../McuLib/config -I../McuLib/config/fonts -I../McuLib/fonts -I../McuLib/src -I../McuLib/FreeRTOS/Source/include -I../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../McuLib/SEGGER_RTT -I../McuLib/SEGGER_Sysview -I../McuLib/TraceRecorder -I../McuLib/TraceRecorder/config -I../McuLib/TraceRecorder/include -I../McuLib/TraceRecorder/streamports/Jlink_RTT/include -I../McuLib/HD44780 -I../McuLib/FatFS -I../McuLib/FatFS/source -include"C:/Users/andre/OneDrive - Hochschule Luzern/00_Modules/FS23_AEMBS/00_Projects/01_AEMBY_tinyK22/source/IncludeMcuLibConfig.h" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-McuLib-2f-fonts

clean-McuLib-2f-fonts:
	-$(RM) ./McuLib/fonts/McuFontCour08Bold.d ./McuLib/fonts/McuFontCour08Bold.o ./McuLib/fonts/McuFontCour08Normal.d ./McuLib/fonts/McuFontCour08Normal.o ./McuLib/fonts/McuFontCour10Bold.d ./McuLib/fonts/McuFontCour10Bold.o ./McuLib/fonts/McuFontCour10Normal.d ./McuLib/fonts/McuFontCour10Normal.o ./McuLib/fonts/McuFontCour12Bold.d ./McuLib/fonts/McuFontCour12Bold.o ./McuLib/fonts/McuFontCour12Normal.d ./McuLib/fonts/McuFontCour12Normal.o ./McuLib/fonts/McuFontCour14Bold.d ./McuLib/fonts/McuFontCour14Bold.o ./McuLib/fonts/McuFontCour14Normal.d ./McuLib/fonts/McuFontCour14Normal.o ./McuLib/fonts/McuFontCour18Bold.d ./McuLib/fonts/McuFontCour18Bold.o ./McuLib/fonts/McuFontCour18Normal.d ./McuLib/fonts/McuFontCour18Normal.o ./McuLib/fonts/McuFontCour24Bold.d ./McuLib/fonts/McuFontCour24Bold.o ./McuLib/fonts/McuFontCour24Normal.d ./McuLib/fonts/McuFontCour24Normal.o ./McuLib/fonts/McuFontHelv08Bold.d ./McuLib/fonts/McuFontHelv08Bold.o ./McuLib/fonts/McuFontHelv08Normal.d ./McuLib/fonts/McuFontHelv08Normal.o ./McuLib/fonts/McuFontHelv10Bold.d ./McuLib/fonts/McuFontHelv10Bold.o ./McuLib/fonts/McuFontHelv10Normal.d ./McuLib/fonts/McuFontHelv10Normal.o ./McuLib/fonts/McuFontHelv12Bold.d ./McuLib/fonts/McuFontHelv12Bold.o ./McuLib/fonts/McuFontHelv12Normal.d ./McuLib/fonts/McuFontHelv12Normal.o ./McuLib/fonts/McuFontHelv14Bold.d ./McuLib/fonts/McuFontHelv14Bold.o ./McuLib/fonts/McuFontHelv14Normal.d ./McuLib/fonts/McuFontHelv14Normal.o ./McuLib/fonts/McuFontHelv18Bold.d ./McuLib/fonts/McuFontHelv18Bold.o ./McuLib/fonts/McuFontHelv18Normal.d ./McuLib/fonts/McuFontHelv18Normal.o ./McuLib/fonts/McuFontHelv24Bold.d ./McuLib/fonts/McuFontHelv24Bold.o ./McuLib/fonts/McuFontHelv24Normal.d ./McuLib/fonts/McuFontHelv24Normal.o

.PHONY: clean-McuLib-2f-fonts

