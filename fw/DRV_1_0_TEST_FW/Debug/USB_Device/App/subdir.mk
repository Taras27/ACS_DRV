################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USB_Device/App/usb_device.c \
../USB_Device/App/usbd_cdc_if.c \
../USB_Device/App/usbd_desc.c 

OBJS += \
./USB_Device/App/usb_device.o \
./USB_Device/App/usbd_cdc_if.o \
./USB_Device/App/usbd_desc.o 

C_DEPS += \
./USB_Device/App/usb_device.d \
./USB_Device/App/usbd_cdc_if.d \
./USB_Device/App/usbd_desc.d 


# Each subdirectory must supply rules for building sources it contributes
USB_Device/App/%.o USB_Device/App/%.su USB_Device/App/%.cyclo: ../USB_Device/App/%.c USB_Device/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I../USB_Device/App -I../USB_Device/Target -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-USB_Device-2f-App

clean-USB_Device-2f-App:
	-$(RM) ./USB_Device/App/usb_device.cyclo ./USB_Device/App/usb_device.d ./USB_Device/App/usb_device.o ./USB_Device/App/usb_device.su ./USB_Device/App/usbd_cdc_if.cyclo ./USB_Device/App/usbd_cdc_if.d ./USB_Device/App/usbd_cdc_if.o ./USB_Device/App/usbd_cdc_if.su ./USB_Device/App/usbd_desc.cyclo ./USB_Device/App/usbd_desc.d ./USB_Device/App/usbd_desc.o ./USB_Device/App/usbd_desc.su

.PHONY: clean-USB_Device-2f-App

