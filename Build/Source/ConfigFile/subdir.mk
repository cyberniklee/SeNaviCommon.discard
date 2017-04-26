################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/ConfigFile/ConfigFile.cpp 

OBJS += \
./Source/ConfigFile/ConfigFile.o 

CPP_DEPS += \
./Source/ConfigFile/ConfigFile.d 


# Each subdirectory must supply rules for building sources it contributes
Source/ConfigFile/%.o: ../Source/ConfigFile/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-openwrt-linux-muslgnueabi-g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


