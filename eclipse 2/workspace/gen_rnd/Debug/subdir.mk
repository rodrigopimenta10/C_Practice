################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gen_rnd.c 

OBJS += \
./gen_rnd.o 

C_DEPS += \
./gen_rnd.d 


# Each subdirectory must supply rules for building sources it contributes
gen_rnd.o: ../gen_rnd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../m -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"gen_rnd.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


