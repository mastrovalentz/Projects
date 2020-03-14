----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/20/2019 03:42:39 PM
-- Design Name: 
-- Module Name: mux41 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity mux41 is
    Port (  bit_in : in  std_logic_vector (3 downto 0);
            sel_in : in  std_logic_vector (1 downto 0);
            y_out  : out std_logic );
end mux41;

architecture Behavioral of mux41 is

component mux21 is
    Port (  bit_in : in  std_logic_vector (1 downto 0);
            sel_in : in  std_logic;
            y_out  : out std_logic );
end component;

signal y_m1_m3 :std_logic;
signal y_m2_m4 :std_logic;

begin

m1 : mux21 port map( bit_in (0) => bit_in (0), bit_in (1) => bit_in (1), 
                     sel_in     => sel_in (0), y_out      => y_m1_m3 );
                     
m2 : mux21 port map( bit_in (0) => bit_in (2), bit_in (1) => bit_in (3), 
                     sel_in     => sel_in (0), y_out      => y_m2_m4 );
                     
m3 : mux21 port map( bit_in (0) => y_m1_m3   , bit_in (1) => y_m2_m4, 
                     sel_in     => sel_in (1), y_out      => y_out );
end Behavioral;
