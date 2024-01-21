/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 14 oct 2023

comms source file

This module defines ir communication functions
for multiplayer functionality. Includes initialiser 
plus methods to send and recieve data
*/

#include "ir_uart.h"
#include "comms.h"
#include "missile.h"


/*initalises ir*/
void comms_init(void)
{
    ir_uart_init();
}

/*send missile data through ir*/
void comms_send_missile_data(uint8_t x_coord, uint8_t type)
{
    ir_uart_putc(MISSILE_CODE);
    ir_uart_putc(x_coord);
    ir_uart_putc(type);
}

/*sends a given code through ir*/
void comms_send_code(uint8_t code)
{
    ir_uart_putc(code);
}

/*recieves ir data - if missile code then initialise new
enemy missile with the recieved data - returns code*/
uint8_t comms_receive_data(void)
{
    uint8_t x_coord;
    missile_type_t type;
    uint8_t code = VOID_CODE;

    if (ir_uart_read_ready_p())
    {
        code = ir_uart_getc();

        if (code == MISSILE_CODE)
        {
            x_coord = ir_uart_getc();
            type = ir_uart_getc();
            enemy_missile_init(x_coord, type);
        }
    }
    return code;
}
