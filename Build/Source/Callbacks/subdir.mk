################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Callbacks/CallbackQueue.cpp 

OBJS += \
./Source/Callbacks/CallbackQueue.o 

CPP_DEPS += \
./Source/Callbacks/CallbackQueue.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Callbacks/%.o: ../Source/Callbacks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


