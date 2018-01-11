################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CCommComp.cpp \
../CControlComp.cpp \
../calibrate.cpp \
../main.cpp 

OBJS += \
./CCommComp.o \
./CControlComp.o \
./calibrate.o \
./main.o 

CPP_DEPS += \
./CCommComp.d \
./CControlComp.d \
./calibrate.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/Hardware" -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/lib" -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/socket" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


