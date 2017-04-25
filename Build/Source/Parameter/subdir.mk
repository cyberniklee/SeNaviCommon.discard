################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Parameter/Parameter.cpp \
../Source/Parameter/XMLParser.cpp 

OBJS += \
./Source/Parameter/Parameter.o \
./Source/Parameter/XMLParser.o 

CPP_DEPS += \
./Source/Parameter/Parameter.d \
./Source/Parameter/XMLParser.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Parameter/%.o: ../Source/Parameter/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


