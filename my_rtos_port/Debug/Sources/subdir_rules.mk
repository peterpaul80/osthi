################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Sources/main.obj: ../Sources/main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmspx --abi=eabi -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/Users/sreev/Documents/rtos_port/my_rtos_port/Sources" --include_path="C:/Users/sreev/Documents/rtos_port/my_rtos_port/FreeRTOS/Source" --include_path="C:/Users/sreev/Documents/rtos_port/my_rtos_port/FreeRTOS" --include_path="C:/Users/sreev/Documents/rtos_port/my_rtos_port/FreeRTOS/Source/include" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power=all --define=__MSP430F5418A__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="Sources/main.pp" --obj_directory="Sources" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

