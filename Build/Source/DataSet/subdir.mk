################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Source/DataSet/DataProcessQueue.cpp \
../Source/DataSet/DataQueue.cpp \
../Source/DataSet/Dispitcher.cpp 

OBJS += \
./Source/DataSet/DataProcessQueue.o \
./Source/DataSet/DataQueue.o \
./Source/DataSet/Dispitcher.o 

CPP_DEPS += \
./Source/DataSet/DataProcessQueue.d \
./Source/DataSet/DataQueue.d \
./Source/DataSet/Dispitcher.d 


# Each subdirectory must supply rules for building sources it contributes
Source/DataSet/%.o: ../Source/DataSet/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


