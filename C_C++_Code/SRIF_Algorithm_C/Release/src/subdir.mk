################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MyQRDecompose.cpp \
../src/MySRIF.cpp \
../src/testCPP.cpp 

OBJS += \
./src/MyQRDecompose.o \
./src/MySRIF.o \
./src/testCPP.o 

CPP_DEPS += \
./src/MyQRDecompose.d \
./src/MySRIF.d \
./src/testCPP.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Intel C++ Compiler'
	icpc -O2 -mkl=parallel -I/opt/intel/mkl/include -I/home/david/MySoft/myeigen -I/home/david/MySoft/Eigen3 -qopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


