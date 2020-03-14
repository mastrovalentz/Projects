##input buttons
set_property -dict { PACKAGE_PIN D9 IOSTANDARD LVCMOS33 } [get_ports {a_in}];
set_property -dict { PACKAGE_PIN C9 IOSTANDARD LVCMOS33 } [get_ports {b_in}];

#switch
set_property -dict { PACKAGE PIN A8 IOSTANDARD LVCMOS33 } [get_ports {sel_in}];


## output
set_property -dict { PACKAGE_PIN E1 IOSTANDARD LVCMOS33 } [get_ports { y_out}];
