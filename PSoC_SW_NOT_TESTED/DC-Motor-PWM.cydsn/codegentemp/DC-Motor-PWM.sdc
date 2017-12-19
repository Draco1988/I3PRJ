# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\larsholm92\Documents\IKT\3. Semester\Projektgruppe16\I3PRJ\PSoC_SW_NOT_TESTED\DC-Motor-PWM.cydsn\DC-Motor-PWM.cyprj
# Date: Thu, 14 Dec 2017 17:40:42 GMT
#set_units -time ns
create_clock -name {ADC_SAR_B_theACLK(routed)} -period 541.66666666666663 -waveform {0 270.833333333333} [list [get_pins {ClockBlock/dclk_0}]]
create_clock -name {ADC_SAR_V_theACLK(routed)} -period 541.66666666666663 -waveform {0 270.833333333333} [list [get_pins {ClockBlock/dclk_1}]]
create_clock -name {CyILO} -period 1000000 -waveform {0 500000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 333.33333333333331 -waveform {0 166.666666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {ADC_SAR_B_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 13 27} -nominal_period 541.66666666666663 [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {ADC_SAR_V_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 13 27} -nominal_period 541.66666666666663 [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {UART_1_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 27 53} -nominal_period 1083.3333333333333 [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {SPI_Slave_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 241 481} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Clock_PWM} -source [get_pins {ClockBlock/clk_sync}] -edges {1 481 961} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {Clock_PWM_4} -source [get_pins {ClockBlock/clk_sync}] -edges {1 481 961} [list [get_pins {ClockBlock/dclk_glb_5}]]


# Component constraints for C:\Users\larsholm92\Documents\IKT\3. Semester\Projektgruppe16\I3PRJ\PSoC_SW_NOT_TESTED\DC-Motor-PWM.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\larsholm92\Documents\IKT\3. Semester\Projektgruppe16\I3PRJ\PSoC_SW_NOT_TESTED\DC-Motor-PWM.cydsn\DC-Motor-PWM.cyprj
# Date: Thu, 14 Dec 2017 17:40:26 GMT