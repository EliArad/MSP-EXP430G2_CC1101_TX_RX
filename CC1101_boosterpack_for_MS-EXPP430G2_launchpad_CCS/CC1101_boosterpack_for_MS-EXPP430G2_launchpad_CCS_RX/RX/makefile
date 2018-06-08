################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_rx.obj" \
"./source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_tx.obj" \
"./source/apps/cc1120_easyLink_vchip_boosterpack/cc1120_vchip_easy_link_rx.obj" \
"./source/components/common/hal_int.obj" \
"./source/components/devices/cc11x/cc11xL_spi.obj" \
"./source/components/devices/lcd_dogm128_6/lcd_dogm128_6.obj" \
"./source/components/devices/lcd_dogm128_6/lcd_dogm128_6_alphabet.obj" \
"./source/components/devices/lcd_dogm128_6/lcd_dogm128_6_ti_logo.obj" \
"./source/components/targets/msp_exp430g2/hal_board.obj" \
"./source/components/targets/msp_exp430g2/hal_digio2.obj" \
"./source/components/targets/msp_exp430g2/hal_int_rf_msp_exp430g2.obj" \
"./source/components/targets/msp_exp430g2/hal_msp_exp430g2_spi.obj" \
"../lnk_msp430g2553.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include source/apps/cc1120_easyLink_vchip_boosterpack/subdir_vars.mk
-include source/components/common/subdir_vars.mk
-include source/components/devices/cc11x/subdir_vars.mk
-include source/components/devices/lcd_dogm128_6/subdir_vars.mk
-include source/components/targets/msp_exp430g2/subdir_vars.mk
-include subdir_rules.mk
-include source/apps/cc1120_easyLink_vchip_boosterpack/subdir_rules.mk
-include source/components/common/subdir_rules.mk
-include source/components/devices/cc11x/subdir_rules.mk
-include source/components/devices/lcd_dogm128_6/subdir_rules.mk
-include source/components/targets/msp_exp430g2/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
cc1101_MSP-EXP430g2_TX.out \

EXE_OUTPUTS__QUOTED += \
"cc1101_MSP-EXP430g2_TX.out" \


# All Target
all: cc1101_MSP-EXP430g2_TX.out

# Tool invocations
cc1101_MSP-EXP430g2_TX.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/bin/cl430" -vmsp --abi=eabi -g --advice:power=all --define=__MSP430G2553__ --define=MSP_EXP430G2 --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z --stack_size=80 -m"cc1101_MSP-EXP430g2_TX.map" --heap_size=80 -i"C:/ti/ccsv8/ccs_base/msp430/include" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/lib" -i"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="cc1101_MSP-EXP430g2_TX_linkInfo.xml" --rom_model -o "cc1101_MSP-EXP430g2_TX.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "source\apps\cc1120_easyLink_vchip_boosterpack\cc110L_easy_link_msp_exp_430g2_rx.obj" "source\apps\cc1120_easyLink_vchip_boosterpack\cc110L_easy_link_msp_exp_430g2_tx.obj" "source\apps\cc1120_easyLink_vchip_boosterpack\cc1120_vchip_easy_link_rx.obj" "source\components\common\hal_int.obj" "source\components\devices\cc11x\cc11xL_spi.obj" "source\components\devices\lcd_dogm128_6\lcd_dogm128_6.obj" "source\components\devices\lcd_dogm128_6\lcd_dogm128_6_alphabet.obj" "source\components\devices\lcd_dogm128_6\lcd_dogm128_6_ti_logo.obj" "source\components\targets\msp_exp430g2\hal_board.obj" "source\components\targets\msp_exp430g2\hal_digio2.obj" "source\components\targets\msp_exp430g2\hal_int_rf_msp_exp430g2.obj" "source\components\targets\msp_exp430g2\hal_msp_exp430g2_spi.obj" 
	-$(RM) "source\apps\cc1120_easyLink_vchip_boosterpack\cc110L_easy_link_msp_exp_430g2_rx.d" "source\apps\cc1120_easyLink_vchip_boosterpack\cc110L_easy_link_msp_exp_430g2_tx.d" "source\apps\cc1120_easyLink_vchip_boosterpack\cc1120_vchip_easy_link_rx.d" "source\components\common\hal_int.d" "source\components\devices\cc11x\cc11xL_spi.d" "source\components\devices\lcd_dogm128_6\lcd_dogm128_6.d" "source\components\devices\lcd_dogm128_6\lcd_dogm128_6_alphabet.d" "source\components\devices\lcd_dogm128_6\lcd_dogm128_6_ti_logo.d" "source\components\targets\msp_exp430g2\hal_board.d" "source\components\targets\msp_exp430g2\hal_digio2.d" "source\components\targets\msp_exp430g2\hal_int_rf_msp_exp430g2.d" "source\components\targets\msp_exp430g2\hal_msp_exp430g2_spi.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

