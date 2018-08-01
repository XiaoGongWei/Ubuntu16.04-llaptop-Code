################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MyMatrix.cpp \
../src/SRIFAlgorithm.cpp \
../src/main.cpp 

OBJS += \
./src/MyMatrix.o \
./src/SRIFAlgorithm.o \
./src/main.o 

CPP_DEPS += \
./src/MyMatrix.d \
./src/SRIFAlgorithm.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/david/MySoft/Eigen3 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


