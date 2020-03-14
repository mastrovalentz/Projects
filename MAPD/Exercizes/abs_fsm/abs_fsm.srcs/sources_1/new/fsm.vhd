----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/09/2019 04:56:13 PM
-- Design Name: 
-- Module Name: fsm - Behavioral
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

entity fsm is
    port (
        a_in : in std_logic;
        b_in : in std_logic;
        c_in : in std_logic;
        y_out : out std_logic_vector(2 downto 0);
        reset : in std_logic;
        clk : in std_logic);
end fsm;

architecture Behavioral of fsm is
    type state_t is (idle, running, completed); --this is like a c++ enumerator
    signal state      : state_t; -- state can assume only state_t values
    signal next_state : state_t; -- state can assume only state_t values

begin
    state_update : process (a_in, b_in, c_in, state) is 
    begin
        case state is
            when idle =>
                y_out(0)<='1';
                y_out(1)<='0';
                y_out(2)<='0';
                if a_in = '1' then
                    next_state <= running;    
                end if;
            when running =>
                y_out(0)<='0';
                y_out(1)<='1';
                y_out(2)<='0';
                if b_in = '1' then
                    next_state <= completed;  
                end if;    
            when completed =>
                y_out(0)<='0';
                y_out(1)<='0';
                y_out(2)<='1';
                if c_in = '1' then
                    next_state <= idle;
                end if;
            when others => null;  --better specify unwanted cases no differences in sim but important in implementation
        end case;
    end process state_update;
    
    
    state_memory : process (clk) is
    begin
        if rising_edge(clk) then
            if reset = '1' then --syncronous reset
                state <= idle;
            else
                state<=next_state;
            end if;
         end if;
     end process state_memory;
                
end Behavioral;
