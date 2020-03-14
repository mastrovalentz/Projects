----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/20/2019 03:09:44 PM
-- Design Name: 
-- Module Name: mux21 - Behavioral
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

entity mux21 is
    Port ( bit_in : in  std_logic_vector (1 downto 0);
           sel_in : in  std_logic;
           y_out  : out std_logic );
end mux21;

architecture Behavioral of mux21 is

begin

process (bit_in(0), bit_in(1), sel_in) is
begin
    if sel_in = '0' then
        y_out <= bit_in(0);
     else
        y_out <= bit_in(1);
     end if; 
end process;
end Behavioral;
