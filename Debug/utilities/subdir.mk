################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_assert.c \
../utilities/fsl_debug_console.c \
../utilities/fsl_str.c 

C_DEPS += \
./utilities/fsl_assert.d \
./utilities/fsl_debug_console.d \
./utilities/fsl_str.d 

OBJS += \
./utilities/fsl_assert.o \
./utilities/fsl_debug_console.o \
./utilities/fsl_str.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\source" -I../McuLib -I../McuLib/config -I../McuLib/config/fonts -I../McuLib/fonts -I../McuLib/src -I../McuLib/FreeRTOS/Source/include -I../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../McuLib/SEGGER_RTT -I../McuLib/SEGGER_Sysview -I../McuLib/TraceRecorder -I../McuLib/TraceRecorder/config -I../McuLib/TraceRecorder/include -I../McuLib/TraceRecorder/streamports/Jlink_RTT/include -I../McuLib/HD44780 -I../McuLib/FatFS -I../McuLib/FatFS/source -include"C:/Users/andre/OneDrive - Hochschule Luzern/00_Modules/FS23_AEMBS/00_Projects/01_AEMBY_tinyK22/source/IncludeMcuLibConfig.h" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_assert.d ./utilities/fsl_assert.o ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o ./utilities/fsl_str.d ./utilities/fsl_str.o

.PHONY: clean-utilities

