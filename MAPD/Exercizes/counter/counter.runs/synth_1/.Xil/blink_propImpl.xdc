set_property SRC_FILE_INFO {cfile:/home/student03/projects/counter/counter.srcs/constrs_1/new/mappa.xdc rfile:../../../counter.srcs/constrs_1/new/mappa.xdc id:1} [current_design]
set_property src_info {type:XDC file:1 line:1 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports {clk}];
set_property src_info {type:XDC file:1 line:2 export:INPUT save:INPUT read:READ} [current_design]
create_clock -add -name sys_clk_pin -period 1.00 -waveform {0 5} [get_ports{clk}];
set_property src_info {type:XDC file:1 line:5 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN D9  IOSTANDARD LVCMOS33 } [get_ports {rst}];
set_property src_info {type:XDC file:1 line:13 export:INPUT save:INPUT read:READ} [current_design]
set_property -dict { PACKAGE_PIN E1  IOSTANDARD LVCMOS33 } [get_ports {y_out}];
