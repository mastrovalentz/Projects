----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/13/2019 04:09:56 PM
-- Design Name: 
-- Module Name: TwoTwoAdd - Behavioral
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

entity TwoTwoAdd is
    port ( btn_in :  in  std_logic_vector(3 downto 0);
           led_out : out std_logic_vector(2 downto 0));
end TwoTwoAdd;

architecture Behavioral of TwoTwoAdd is
begin
led_out(0) <= btn_in(0) xor btn_int(1);
led_out(1) <= (btn_in(1) xor btn_int(2)) xor (btn_in(0) and btn_int(1)); //da finire
led_out(2) <= btn_in(0) xor btn_int(1);

end Behavioral;
