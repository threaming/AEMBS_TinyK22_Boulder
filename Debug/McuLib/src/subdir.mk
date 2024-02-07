################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../McuLib/src/C11.c \
../McuLib/src/C21.c \
../McuLib/src/Clock1.c \
../McuLib/src/DQ1.c \
../McuLib/src/DbgRd1.c \
../McuLib/src/Input1.c \
../McuLib/src/InputRB1.c \
../McuLib/src/McuArmTools.c \
../McuLib/src/McuButton.c \
../McuLib/src/McuCRC_CreateTable.c \
../McuLib/src/McuCRC_Generator.c \
../McuLib/src/McuCriticalSection.c \
../McuLib/src/McuDS18B20.c \
../McuLib/src/McuDebounce.c \
../McuLib/src/McuEE24.c \
../McuLib/src/McuESP32.c \
../McuLib/src/McuEvents.c \
../McuLib/src/McuExtRTC.c \
../McuLib/src/McuFXOS8700.c \
../McuLib/src/McuFontDisplay.c \
../McuLib/src/McuGDisplaySSD1306.c \
../McuLib/src/McuGFont.c \
../McuLib/src/McuGPIO.c \
../McuLib/src/McuGenericI2C.c \
../McuLib/src/McuGenericSWI2C.c \
../McuLib/src/McuGenericSWSPI.c \
../McuLib/src/McuHardFault.c \
../McuLib/src/McuI2CSpy.c \
../McuLib/src/McuI2cLib.c \
../McuLib/src/McuLC709203F.c \
../McuLib/src/McuLED.c \
../McuLib/src/McuLib.c \
../McuLib/src/McuLog.c \
../McuLib/src/McuOneWire.c \
../McuLib/src/McuPCF85063A.c \
../McuLib/src/McuPidFloat.c \
../McuLib/src/McuPidInt.c \
../McuLib/src/McuQuadCounter.c \
../McuLib/src/McuRB.c \
../McuLib/src/McuRTOS.c \
../McuLib/src/McuRTT.c \
../McuLib/src/McuRingbuffer.c \
../McuLib/src/McuSHT31.c \
../McuLib/src/McuSHT40.c \
../McuLib/src/McuSPI.c \
../McuLib/src/McuSSD1306.c \
../McuLib/src/McuSTM32HALI2C.c \
../McuLib/src/McuSWO.c \
../McuLib/src/McuSemihost.c \
../McuLib/src/McuShell.c \
../McuLib/src/McuShellUart.c \
../McuLib/src/McuTimeDate.c \
../McuLib/src/McuTimeout.c \
../McuLib/src/McuTrigger.c \
../McuLib/src/McuULN2003.c \
../McuLib/src/McuUart485.c \
../McuLib/src/McuUtility.c \
../McuLib/src/McuW25Q128.c \
../McuLib/src/McuWait.c \
../McuLib/src/McuX12_017.c \
../McuLib/src/McuXFormat.c \
../McuLib/src/Output1.c \
../McuLib/src/SCL1.c \
../McuLib/src/SDA1.c \
../McuLib/src/WPpin1.c 

C_DEPS += \
./McuLib/src/C11.d \
./McuLib/src/C21.d \
./McuLib/src/Clock1.d \
./McuLib/src/DQ1.d \
./McuLib/src/DbgRd1.d \
./McuLib/src/Input1.d \
./McuLib/src/InputRB1.d \
./McuLib/src/McuArmTools.d \
./McuLib/src/McuButton.d \
./McuLib/src/McuCRC_CreateTable.d \
./McuLib/src/McuCRC_Generator.d \
./McuLib/src/McuCriticalSection.d \
./McuLib/src/McuDS18B20.d \
./McuLib/src/McuDebounce.d \
./McuLib/src/McuEE24.d \
./McuLib/src/McuESP32.d \
./McuLib/src/McuEvents.d \
./McuLib/src/McuExtRTC.d \
./McuLib/src/McuFXOS8700.d \
./McuLib/src/McuFontDisplay.d \
./McuLib/src/McuGDisplaySSD1306.d \
./McuLib/src/McuGFont.d \
./McuLib/src/McuGPIO.d \
./McuLib/src/McuGenericI2C.d \
./McuLib/src/McuGenericSWI2C.d \
./McuLib/src/McuGenericSWSPI.d \
./McuLib/src/McuHardFault.d \
./McuLib/src/McuI2CSpy.d \
./McuLib/src/McuI2cLib.d \
./McuLib/src/McuLC709203F.d \
./McuLib/src/McuLED.d \
./McuLib/src/McuLib.d \
./McuLib/src/McuLog.d \
./McuLib/src/McuOneWire.d \
./McuLib/src/McuPCF85063A.d \
./McuLib/src/McuPidFloat.d \
./McuLib/src/McuPidInt.d \
./McuLib/src/McuQuadCounter.d \
./McuLib/src/McuRB.d \
./McuLib/src/McuRTOS.d \
./McuLib/src/McuRTT.d \
./McuLib/src/McuRingbuffer.d \
./McuLib/src/McuSHT31.d \
./McuLib/src/McuSHT40.d \
./McuLib/src/McuSPI.d \
./McuLib/src/McuSSD1306.d \
./McuLib/src/McuSTM32HALI2C.d \
./McuLib/src/McuSWO.d \
./McuLib/src/McuSemihost.d \
./McuLib/src/McuShell.d \
./McuLib/src/McuShellUart.d \
./McuLib/src/McuTimeDate.d \
./McuLib/src/McuTimeout.d \
./McuLib/src/McuTrigger.d \
./McuLib/src/McuULN2003.d \
./McuLib/src/McuUart485.d \
./McuLib/src/McuUtility.d \
./McuLib/src/McuW25Q128.d \
./McuLib/src/McuWait.d \
./McuLib/src/McuX12_017.d \
./McuLib/src/McuXFormat.d \
./McuLib/src/Output1.d \
./McuLib/src/SCL1.d \
./McuLib/src/SDA1.d \
./McuLib/src/WPpin1.d 

OBJS += \
./McuLib/src/C11.o \
./McuLib/src/C21.o \
./McuLib/src/Clock1.o \
./McuLib/src/DQ1.o \
./McuLib/src/DbgRd1.o \
./McuLib/src/Input1.o \
./McuLib/src/InputRB1.o \
./McuLib/src/McuArmTools.o \
./McuLib/src/McuButton.o \
./McuLib/src/McuCRC_CreateTable.o \
./McuLib/src/McuCRC_Generator.o \
./McuLib/src/McuCriticalSection.o \
./McuLib/src/McuDS18B20.o \
./McuLib/src/McuDebounce.o \
./McuLib/src/McuEE24.o \
./McuLib/src/McuESP32.o \
./McuLib/src/McuEvents.o \
./McuLib/src/McuExtRTC.o \
./McuLib/src/McuFXOS8700.o \
./McuLib/src/McuFontDisplay.o \
./McuLib/src/McuGDisplaySSD1306.o \
./McuLib/src/McuGFont.o \
./McuLib/src/McuGPIO.o \
./McuLib/src/McuGenericI2C.o \
./McuLib/src/McuGenericSWI2C.o \
./McuLib/src/McuGenericSWSPI.o \
./McuLib/src/McuHardFault.o \
./McuLib/src/McuI2CSpy.o \
./McuLib/src/McuI2cLib.o \
./McuLib/src/McuLC709203F.o \
./McuLib/src/McuLED.o \
./McuLib/src/McuLib.o \
./McuLib/src/McuLog.o \
./McuLib/src/McuOneWire.o \
./McuLib/src/McuPCF85063A.o \
./McuLib/src/McuPidFloat.o \
./McuLib/src/McuPidInt.o \
./McuLib/src/McuQuadCounter.o \
./McuLib/src/McuRB.o \
./McuLib/src/McuRTOS.o \
./McuLib/src/McuRTT.o \
./McuLib/src/McuRingbuffer.o \
./McuLib/src/McuSHT31.o \
./McuLib/src/McuSHT40.o \
./McuLib/src/McuSPI.o \
./McuLib/src/McuSSD1306.o \
./McuLib/src/McuSTM32HALI2C.o \
./McuLib/src/McuSWO.o \
./McuLib/src/McuSemihost.o \
./McuLib/src/McuShell.o \
./McuLib/src/McuShellUart.o \
./McuLib/src/McuTimeDate.o \
./McuLib/src/McuTimeout.o \
./McuLib/src/McuTrigger.o \
./McuLib/src/McuULN2003.o \
./McuLib/src/McuUart485.o \
./McuLib/src/McuUtility.o \
./McuLib/src/McuW25Q128.o \
./McuLib/src/McuWait.o \
./McuLib/src/McuX12_017.o \
./McuLib/src/McuXFormat.o \
./McuLib/src/Output1.o \
./McuLib/src/SCL1.o \
./McuLib/src/SDA1.o \
./McuLib/src/WPpin1.o 


# Each subdirectory must supply rules for building sources it contributes
McuLib/src/%.o: ../McuLib/src/%.c McuLib/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MK22FN512VLH12 -DCPU_MK22FN512VLH12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\drivers" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\device" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\CMSIS" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\serial_manager" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\utilities" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\uart" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\component\lists" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\board" -I"C:\Users\andre\OneDrive - Hochschule Luzern\00_Modules\FS23_AEMBS\00_Projects\01_AEMBY_tinyK22\source" -I../McuLib -I../McuLib/config -I../McuLib/config/fonts -I../McuLib/fonts -I../McuLib/src -I../McuLib/FreeRTOS/Source/include -I../McuLib/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../McuLib/SEGGER_RTT -I../McuLib/SEGGER_Sysview -I../McuLib/TraceRecorder -I../McuLib/TraceRecorder/config -I../McuLib/TraceRecorder/include -I../McuLib/TraceRecorder/streamports/Jlink_RTT/include -I../McuLib/HD44780 -I../McuLib/FatFS -I../McuLib/FatFS/source -include"C:/Users/andre/OneDrive - Hochschule Luzern/00_Modules/FS23_AEMBS/00_Projects/01_AEMBY_tinyK22/source/IncludeMcuLibConfig.h" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-McuLib-2f-src

clean-McuLib-2f-src:
	-$(RM) ./McuLib/src/C11.d ./McuLib/src/C11.o ./McuLib/src/C21.d ./McuLib/src/C21.o ./McuLib/src/Clock1.d ./McuLib/src/Clock1.o ./McuLib/src/DQ1.d ./McuLib/src/DQ1.o ./McuLib/src/DbgRd1.d ./McuLib/src/DbgRd1.o ./McuLib/src/Input1.d ./McuLib/src/Input1.o ./McuLib/src/InputRB1.d ./McuLib/src/InputRB1.o ./McuLib/src/McuArmTools.d ./McuLib/src/McuArmTools.o ./McuLib/src/McuButton.d ./McuLib/src/McuButton.o ./McuLib/src/McuCRC_CreateTable.d ./McuLib/src/McuCRC_CreateTable.o ./McuLib/src/McuCRC_Generator.d ./McuLib/src/McuCRC_Generator.o ./McuLib/src/McuCriticalSection.d ./McuLib/src/McuCriticalSection.o ./McuLib/src/McuDS18B20.d ./McuLib/src/McuDS18B20.o ./McuLib/src/McuDebounce.d ./McuLib/src/McuDebounce.o ./McuLib/src/McuEE24.d ./McuLib/src/McuEE24.o ./McuLib/src/McuESP32.d ./McuLib/src/McuESP32.o ./McuLib/src/McuEvents.d ./McuLib/src/McuEvents.o ./McuLib/src/McuExtRTC.d ./McuLib/src/McuExtRTC.o ./McuLib/src/McuFXOS8700.d ./McuLib/src/McuFXOS8700.o ./McuLib/src/McuFontDisplay.d ./McuLib/src/McuFontDisplay.o ./McuLib/src/McuGDisplaySSD1306.d ./McuLib/src/McuGDisplaySSD1306.o ./McuLib/src/McuGFont.d ./McuLib/src/McuGFont.o ./McuLib/src/McuGPIO.d ./McuLib/src/McuGPIO.o ./McuLib/src/McuGenericI2C.d ./McuLib/src/McuGenericI2C.o ./McuLib/src/McuGenericSWI2C.d ./McuLib/src/McuGenericSWI2C.o ./McuLib/src/McuGenericSWSPI.d ./McuLib/src/McuGenericSWSPI.o ./McuLib/src/McuHardFault.d ./McuLib/src/McuHardFault.o ./McuLib/src/McuI2CSpy.d ./McuLib/src/McuI2CSpy.o ./McuLib/src/McuI2cLib.d ./McuLib/src/McuI2cLib.o ./McuLib/src/McuLC709203F.d ./McuLib/src/McuLC709203F.o ./McuLib/src/McuLED.d ./McuLib/src/McuLED.o ./McuLib/src/McuLib.d ./McuLib/src/McuLib.o ./McuLib/src/McuLog.d ./McuLib/src/McuLog.o ./McuLib/src/McuOneWire.d ./McuLib/src/McuOneWire.o ./McuLib/src/McuPCF85063A.d ./McuLib/src/McuPCF85063A.o ./McuLib/src/McuPidFloat.d ./McuLib/src/McuPidFloat.o ./McuLib/src/McuPidInt.d ./McuLib/src/McuPidInt.o ./McuLib/src/McuQuadCounter.d ./McuLib/src/McuQuadCounter.o ./McuLib/src/McuRB.d ./McuLib/src/McuRB.o ./McuLib/src/McuRTOS.d ./McuLib/src/McuRTOS.o ./McuLib/src/McuRTT.d ./McuLib/src/McuRTT.o ./McuLib/src/McuRingbuffer.d ./McuLib/src/McuRingbuffer.o ./McuLib/src/McuSHT31.d ./McuLib/src/McuSHT31.o ./McuLib/src/McuSHT40.d ./McuLib/src/McuSHT40.o ./McuLib/src/McuSPI.d ./McuLib/src/McuSPI.o ./McuLib/src/McuSSD1306.d ./McuLib/src/McuSSD1306.o ./McuLib/src/McuSTM32HALI2C.d ./McuLib/src/McuSTM32HALI2C.o ./McuLib/src/McuSWO.d ./McuLib/src/McuSWO.o ./McuLib/src/McuSemihost.d ./McuLib/src/McuSemihost.o ./McuLib/src/McuShell.d ./McuLib/src/McuShell.o ./McuLib/src/McuShellUart.d ./McuLib/src/McuShellUart.o ./McuLib/src/McuTimeDate.d ./McuLib/src/McuTimeDate.o ./McuLib/src/McuTimeout.d ./McuLib/src/McuTimeout.o ./McuLib/src/McuTrigger.d ./McuLib/src/McuTrigger.o ./McuLib/src/McuULN2003.d ./McuLib/src/McuULN2003.o ./McuLib/src/McuUart485.d ./McuLib/src/McuUart485.o ./McuLib/src/McuUtility.d ./McuLib/src/McuUtility.o ./McuLib/src/McuW25Q128.d ./McuLib/src/McuW25Q128.o ./McuLib/src/McuWait.d ./McuLib/src/McuWait.o ./McuLib/src/McuX12_017.d ./McuLib/src/McuX12_017.o ./McuLib/src/McuXFormat.d ./McuLib/src/McuXFormat.o ./McuLib/src/Output1.d ./McuLib/src/Output1.o ./McuLib/src/SCL1.d ./McuLib/src/SCL1.o ./McuLib/src/SDA1.d ./McuLib/src/SDA1.o ./McuLib/src/WPpin1.d ./McuLib/src/WPpin1.o

.PHONY: clean-McuLib-2f-src

