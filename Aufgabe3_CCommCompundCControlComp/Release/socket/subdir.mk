################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../socket/CServer.cpp 

OBJS += \
./socket/CServer.o 

CPP_DEPS += \
./socket/CServer.d 


# Each subdirectory must supply rules for building sources it contributes
socket/%.o: ../socket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/Hardware" -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/lib" -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/socket" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


