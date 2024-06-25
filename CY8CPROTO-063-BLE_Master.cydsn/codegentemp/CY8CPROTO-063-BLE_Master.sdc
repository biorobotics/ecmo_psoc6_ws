# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\15311\Desktop\PSoC_project\PSoC6_UDB_I2C_Master\CY8CPROTO-063-BLE_Master.cydsn\CY8CPROTO-063-BLE_Master.cyprj
# Date: Tue, 25 Jun 2024 17:15:45 GMT
#set_units -time ns
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyClk_LF} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyFLL} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyClk_HF0} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/hfclk_0}]]
create_clock -name {CyClk_Fast} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fastclk}]]
create_clock -name {CyClk_Peri} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CyClk_Slow} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {UART_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 37 73} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyPeriClk_App} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk_App}]]
create_generated_clock -name {CLK_App} -source [get_pins {ClockBlock/periclk_App}] -edges {1 31 63} [list [get_pins {ClockBlock/udb_div_0}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Users\15311\Desktop\PSoC_project\PSoC6_UDB_I2C_Master\CY8CPROTO-063-BLE_Master.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\15311\Desktop\PSoC_project\PSoC6_UDB_I2C_Master\CY8CPROTO-063-BLE_Master.cydsn\CY8CPROTO-063-BLE_Master.cyprj
# Date: Tue, 25 Jun 2024 17:15:16 GMT
