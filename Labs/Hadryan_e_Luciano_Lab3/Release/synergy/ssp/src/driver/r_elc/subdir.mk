################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/driver/r_elc/r_elc.c 

C_DEPS += \
./synergy/ssp/src/driver/r_elc/r_elc.d 

OBJS += \
./synergy/ssp/src/driver/r_elc/r_elc.o 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/driver/r_elc/%.o: ../synergy/ssp/src/driver/r_elc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g -D_RENESAS_SYNERGY_ -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\synergy_cfg\ssp_cfg\bsp" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\synergy_cfg\ssp_cfg\driver" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\synergy\ssp\inc" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\synergy\ssp\inc\bsp" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\synergy\ssp\inc\driver\api" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\synergy\ssp\inc\driver\instances" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\src" -I"C:\Users\lucia\Desktop\ELF74\ELF74_lab\Labs\Hadryan_e_Luciano_Lab3\src\synergy_gen" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '

