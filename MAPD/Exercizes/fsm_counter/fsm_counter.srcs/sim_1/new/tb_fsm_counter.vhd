----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/10/2019 09:53:28 AM
-- Design Name: 
-- Module Name: tb_fsm_counter - Behavioral
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

entity tb_fsm_counter is
--  Port ( );
end tb_fsm_counter;

architecture Behavioral of tb_fsm_counter is
component fsm_counter is
    Port (  clk   : in  std_logic;
            rst   : in  std_logic;
            y_out : out std_logic_vector(2 downto 0));
end component;

signal clk, rst : std_logic;
signal led : std_logic_vector(2 downto 0);

begin
uut : fsm_counter port map (clk => clk, rst => rst, y_out => led);

pl : process
    begin
        clk <= '0';
        wait for 5 ns;
        clk <= '1';
        wait for 5 ns;
    end process; --pl

reset : process
    begin
        rst <= '1'; wait for 15 ns; rst <= '0'; wait;
    end process; --reset
end Behavioral;
