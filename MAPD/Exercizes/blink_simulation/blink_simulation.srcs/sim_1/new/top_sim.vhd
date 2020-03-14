----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/19/2019 09:31:24 AM
-- Design Name: 
-- Module Name: top_sim - Behavioral
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

entity top_sim is
--  Port ( );
end top_sim;

architecture Behavioral of top_sim is

component top is
    Port (btn_in  : in std_logic;
          led_out : out std_logic);
end component;

signal btn, led : std_logic;

begin

uut : top port map (btn_in=> btn, led_out =>led);

p1: process
    begin
        btn <= '0';
        wait for 200 ns;
        btn <= '1';
        wait for 200 ns;
        btn <= '0';
        wait for 200 ns;
     end process;
end Behavioral;
