 
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports {clk}];
#create_clock -add -name sys_clk_pin -period 1.00 -waveform {0 5} [get_ports{clk}];

#input buttons
set_property -dict { PACKAGE_PIN D9  IOSTANDARD LVCMOS33 } [get_ports {rst}];
set_property -dict { PACKAGE_PIN C9  IOSTANDARD LVCMOS33 } [get_ports {start}];
set_property -dict { PACKAGE_PIN B9  IOSTANDARD LVCMOS33 } [get_ports {stop}];
#set_property -dict { PACKAGE_PIN B8  IOSTANDARD LVCMOS33 } [get_ports {bit_in[3]}];
##switch
#set_property -dict { PACKAGE_PIN A8  IOSTANDARD LVCMOS33 } [get_ports {sel_in[0]}];
#set_property -dict { PACKAGE_PIN C11 IOSTANDARD LVCMOS33 } [get_ports {sel_in[1]}];
#set_property -dict { PACKAGE_PIN C10 IOSTANDARD LVCMOS33 } [get_ports {sel_in[2]}];
#set_property -dict { PACKAGE_PIN A10 IOSTANDARD LVCMOS33 } [get_ports {sel_in[3]}];

## output
set_property -dict { PACKAGE_PIN E1  IOSTANDARD LVCMOS33 } [get_ports {y_blu[0]}];
set_property -dict { PACKAGE_PIN G4  IOSTANDARD LVCMOS33 } [get_ports {y_blu[1]}];
set_property -dict { PACKAGE_PIN H4  IOSTANDARD LVCMOS33 } [get_ports {y_blu[2]}];
set_property -dict { PACKAGE_PIN K2  IOSTANDARD LVCMOS33 } [get_ports {y_blu[3]}];

set_property -dict { PACKAGE_PIN G6  IOSTANDARD LVCMOS33 } [get_ports {y_red[0]}];
set_property -dict { PACKAGE_PIN G3  IOSTANDARD LVCMOS33 } [get_ports {y_red[1]}];
set_property -dict { PACKAGE_PIN J3  IOSTANDARD LVCMOS33 } [get_ports {y_red[2]}];
set_property -dict { PACKAGE_PIN K1  IOSTANDARD LVCMOS33 } [get_ports {y_red[3]}];