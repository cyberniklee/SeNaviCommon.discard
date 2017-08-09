################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Mission/Executor.cpp \
../Source/Mission/Issuer.cpp 

OBJS += \
./Source/Mission/Executor.o \
./Source/Mission/Issuer.o 

CPP_DEPS += \
./Source/Mission/Executor.d \
./Source/Mission/Issuer.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Mission/%.o: ../Source/Mission/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-openwrt-linux-muslgnueabi-g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
