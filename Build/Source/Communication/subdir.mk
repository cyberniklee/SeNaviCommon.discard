################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/Communication/Communicator.cpp \
../Source/Communication/NetTranceiver.cpp 

OBJS += \
./Source/Communication/Communicator.o \
./Source/Communication/NetTranceiver.o 

CPP_DEPS += \
./Source/Communication/Communicator.d \
./Source/Communication/NetTranceiver.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Communication/%.o: ../Source/Communication/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


