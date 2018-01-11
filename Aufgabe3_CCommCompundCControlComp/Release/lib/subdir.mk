################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/AComponentBase.cpp \
../lib/Assertion.cpp \
../lib/CBinarySemaphore.cpp \
../lib/CContainer.cpp \
../lib/CMutex.cpp \
../lib/CThread.cpp 

OBJS += \
./lib/AComponentBase.o \
./lib/Assertion.o \
./lib/CBinarySemaphore.o \
./lib/CContainer.o \
./lib/CMutex.o \
./lib/CThread.o 

CPP_DEPS += \
./lib/AComponentBase.d \
./lib/Assertion.d \
./lib/CBinarySemaphore.d \
./lib/CContainer.d \
./lib/CMutex.d \
./lib/CThread.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o: ../lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/Hardware" -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/lib" -I"/home/vmuser/workspace/Aufgabe3_CCommCompundCControlComp/socket" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


