################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Time/Duration.cpp \
../Source/Time/Rate.cpp \
../Source/Time/Time.cpp \
../Source/Time/Utils.cpp 

OBJS += \
./Source/Time/Duration.o \
./Source/Time/Rate.o \
./Source/Time/Time.o \
./Source/Time/Utils.o 

CPP_DEPS += \
./Source/Time/Duration.d \
./Source/Time/Rate.d \
./Source/Time/Time.d \
./Source/Time/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Time/%.o: ../Source/Time/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-openwrt-linux-muslgnueabi-g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


