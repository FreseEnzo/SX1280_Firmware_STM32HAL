################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Components/SerialDebug.cpp \
../Core/Src/Components/Start.cpp \
../Core/Src/Components/StaticFIFO.cpp 

OBJS += \
./Core/Src/Components/SerialDebug.o \
./Core/Src/Components/Start.o \
./Core/Src/Components/StaticFIFO.o 

CPP_DEPS += \
./Core/Src/Components/SerialDebug.d \
./Core/Src/Components/Start.d \
./Core/Src/Components/StaticFIFO.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Components/%.o Core/Src/Components/%.su Core/Src/Components/%.cyclo: ../Core/Src/Components/%.cpp Core/Src/Components/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Components

clean-Core-2f-Src-2f-Components:
	-$(RM) ./Core/Src/Components/SerialDebug.cyclo ./Core/Src/Components/SerialDebug.d ./Core/Src/Components/SerialDebug.o ./Core/Src/Components/SerialDebug.su ./Core/Src/Components/Start.cyclo ./Core/Src/Components/Start.d ./Core/Src/Components/Start.o ./Core/Src/Components/Start.su ./Core/Src/Components/StaticFIFO.cyclo ./Core/Src/Components/StaticFIFO.d ./Core/Src/Components/StaticFIFO.o ./Core/Src/Components/StaticFIFO.su

.PHONY: clean-Core-2f-Src-2f-Components

