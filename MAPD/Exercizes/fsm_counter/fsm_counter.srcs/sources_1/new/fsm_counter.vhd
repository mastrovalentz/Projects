----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/09/2019 05:55:51 PM
-- Design Name: 
-- Module Name: fsm_counter - Behavioral
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

entity fsm_counter is
    Port (  clk   : in  std_logic;
            rst   : in  std_logic;
            y_out : out std_logic_vector(2 downto 0));
end fsm_counter;

architecture Behavioral of fsm_counter is
    type state_t is (s_000, s_001, s_010, s_011, s_100, s_101, s_110, s_111 ); --this is like a c++ enumerator
    signal state      : state_t; -- state can assume only state_t values
    signal next_state : state_t; -- state can assume only state_t values
    signal slow_counter : unsigned (2  downto 0);
    signal counter : unsigned (27 downto 0);
    signal clk_rst : std_logic;

begin
    state_update : process (state, rst) is 
    begin
        if rst = '1' then 
            next_state <= s_000;
            slow_counter(0) <= '0';
            slow_counter(1) <= '0';
            slow_counter(2) <= '0';
        else 
            case state is
                when s_000 =>
                    slow_counter(0) <= '0';
                    slow_counter(1) <= '0';
                    slow_counter(2) <= '0';
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_001;
                    end if;
                when s_001 =>
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_010;
                    end if;
                when s_010 =>
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_011;
                    end if;
                when s_011 =>
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_100;
                    end if;
                when s_100 =>
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_101;
                    end if;
                when s_101 =>
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_110;
                    end if;
                when s_110 =>
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_111;
                    end if;
                when s_111 =>
                    if (rising_edge(counter(26))) then
                        slow_counter <= slow_counter +1;
                        next_state <= s_000;
                    end if;
                when others => null;  --better specify unwanted cases no differences in sim but important in implementation
            end case;
         end if;
    end process state_update;
    
    
    state_memory : process (clk) is
    begin
        if rising_edge(clk) then
            if rst = '1' then --syncronous reset
                state <= s_000;
                counter <= (others => '0');
            --elsif (rising_edge(counter(26))) then
            --    counter <= (others => '0');
            else
                counter <= counter +1;               
                state<=next_state;
                --if clk_rst = '0' then
                --    clk_rst <= '1';
                --end if;
            end if;
         end if;
     end process state_memory;      
    
    y_out <= std_logic_vector(slow_counter);         

end Behavioral;



