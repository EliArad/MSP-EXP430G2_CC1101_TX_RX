################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_rx.obj: ../source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_rx.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/common" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/apps/cc1120_easyLink_vchip_boosterpack" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/common/msp430" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/devices/lcd_dogm128_6" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/targets/interface" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/targets/msp_exp430g2" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/include" --advice:power=all --define=__MSP430G2553__ --define=MSP_EXP430G2 --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_rx.d_raw" --obj_directory="source/apps/cc1120_easyLink_vchip_boosterpack" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_tx.obj: ../source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_tx.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/common" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/apps/cc1120_easyLink_vchip_boosterpack" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/common/msp430" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/devices/lcd_dogm128_6" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/targets/interface" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/targets/msp_exp430g2" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/include" --advice:power=all --define=__MSP430G2553__ --define=MSP_EXP430G2 --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="source/apps/cc1120_easyLink_vchip_boosterpack/cc110L_easy_link_msp_exp_430g2_tx.d_raw" --obj_directory="source/apps/cc1120_easyLink_vchip_boosterpack" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

source/apps/cc1120_easyLink_vchip_boosterpack/cc1120_vchip_easy_link_rx.obj: ../source/apps/cc1120_easyLink_vchip_boosterpack/cc1120_vchip_easy_link_rx.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/common" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/apps/cc1120_easyLink_vchip_boosterpack" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/common/msp430" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/devices/lcd_dogm128_6" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/targets/interface" --include_path="D:/Customers/novodes/AirBoosterpackFirmware/easylink/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS/CC1101_boosterpack_for_MS-EXPP430G2_launchpad_CCS_TX/source/components/targets/msp_exp430g2" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_16.9.7.LTS/include" --advice:power=all --define=__MSP430G2553__ --define=MSP_EXP430G2 --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="source/apps/cc1120_easyLink_vchip_boosterpack/cc1120_vchip_easy_link_rx.d_raw" --obj_directory="source/apps/cc1120_easyLink_vchip_boosterpack" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

