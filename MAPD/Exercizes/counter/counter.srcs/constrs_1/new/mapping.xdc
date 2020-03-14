set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOSS33} [get_ports {clk}];
create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports{clk}];

#input buttons
set_property -dict { PACKAGE_PIN D9  IOSTANDARD LVCMOS33 } [get_ports {rst}];
#set_property -dict { PACKAGE_PIN C9  IOSTANDARD LVCMOS33 } [get_ports {bit_in[1]}];
#set_property -dict { PACKAGE_PIN B9  IOSTANDARD LVCMOS33 } [get_ports {bit_in[2]}];
#set_property -dict { PACKAGE_PIN B8  IOSTANDARD LVCMOS33 } [get_ports {bit_in[3]}];
##switch
#set_property -dict { PACKAGE_PIN A8  IOSTANDARD LVCMOS33 } [get_ports {sel_in[0]}];
#set_property -dict { PACKAGE_PIN C11 IOSTANDARD LVCMOS33 } [get_ports {sel_in[1]}];
## output
set_property -dict { PACKAGE_PIN E1  IOSTANDARD LVCMOS33 } [get_ports {y_out}];