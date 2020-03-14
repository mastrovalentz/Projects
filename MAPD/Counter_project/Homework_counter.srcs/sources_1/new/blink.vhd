----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/26/2019 08:54:07 AM
-- Design Name: 
-- Module Name: blink - rtl
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity blink is
    Port (  clk   : in  std_logic;
            rst   : in  std_logic;
            sel_in: in  std_logic_vector(3 downto 0);
            y_blu : out std_logic_vector(3 downto 0);
            y_red : out std_logic_vector(3 downto 0));
end blink;

architecture rtl of blink is
signal slow_clk, slow_clk_p: std_logic;
signal counter      : unsigned (28 downto 0);
signal slow_counter : unsigned (3  downto 0);
begin
p_cnt : process(clk, rst) is 
begin
    if rst = '1' then
        counter <= (others => '0');
    elsif rising_edge(clk) then
        counter <= counter +1;
    end if;
end process;

--    slow_clk <= counter(26);

get_freq : process (sel_in, slow_clk) is
begin
if sel_in(0) = '0' then
    if sel_in(1) = '0' then
        if sel_in(2) = '0' then
            slow_clk <= counter(26);
        else
            slow_clk <= counter(25);
        end if;
    else
        if sel_in(2) = '0' then
            slow_clk <= counter(24);
        else
            slow_clk <= counter(23);
        end if;
    end if;
  else
    if sel_in(1) = '0' then
        if sel_in(2) = '0' then
            slow_clk <= counter(22);
        else
            slow_clk <= counter(21);
        end if;
    else
        if sel_in(2) = '0' then
            slow_clk <= counter(20);
        else
            slow_clk <= counter(19);
        end if;
    end if;
 end if;
 end process;

p_slow_cnt: process (clk, rst, slow_clk) is 
begin
    if rst = '1' then
        slow_counter <= (others => '0');
    elsif rising_edge(clk) then
        slow_clk_p <= slow_clk;
        if slow_clk= '1' and slow_clk_p = '0' then
            slow_counter <= slow_counter +1;
           end if;
    end if;
end process;

out_assign : process (sel_in) is
begin
    if sel_in(3)= '0' then
        y_blu <= std_logic_vector(slow_counter);
        y_red <= (others => '0');
    else
        y_blu <= (others => '0');
        y_red <= std_logic_vector(slow_counter);
    end if;
end process;
end rtl;