################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Components/sx1280/RangingCorrection.cpp \
../Core/Src/Components/sx1280/sx1280-hal.cpp \
../Core/Src/Components/sx1280/sx1280.cpp 

OBJS += \
./Core/Src/Components/sx1280/RangingCorrection.o \
./Core/Src/Components/sx1280/sx1280-hal.o \
./Core/Src/Components/sx1280/sx1280.o 

CPP_DEPS += \
./Core/Src/Components/sx1280/RangingCorrection.d \
./Core/Src/Components/sx1280/sx1280-hal.d \
./Core/Src/Components/sx1280/sx1280.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Components/sx1280/%.o Core/Src/Components/sx1280/%.su Core/Src/Components/sx1280/%.cyclo: ../Core/Src/Components/sx1280/%.cpp Core/Src/Components/sx1280/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Components-2f-sx1280

clean-Core-2f-Src-2f-Components-2f-sx1280:
	-$(RM) ./Core/Src/Components/sx1280/RangingCorrection.cyclo ./Core/Src/Components/sx1280/RangingCorrection.d ./Core/Src/Components/sx1280/RangingCorrection.o ./Core/Src/Components/sx1280/RangingCorrection.su ./Core/Src/Components/sx1280/sx1280-hal.cyclo ./Core/Src/Components/sx1280/sx1280-hal.d ./Core/Src/Components/sx1280/sx1280-hal.o ./Core/Src/Components/sx1280/sx1280-hal.su ./Core/Src/Components/sx1280/sx1280.cyclo ./Core/Src/Components/sx1280/sx1280.d ./Core/Src/Components/sx1280/sx1280.o ./Core/Src/Components/sx1280/sx1280.su

.PHONY: clean-Core-2f-Src-2f-Components-2f-sx1280

