/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 14 oct 2023

comms header file

This module defines ir communication functions
for multiplayer functionality. Includes initialiser 
plus methods to send and recieve data
*/

#ifndef COMMS_H
#define COMMS_H

#include "ir_uart.h"
#include "missile.h"

/*defining ir transmission codes*/
#define WIN_CODE 28
#define LOSE_CODE 88
#define START_CODE 53
#define MISSILE_CODE 42
#define VOID_CODE 0

/*initalises ir*/
void comms_init(void);

/*send missile data through ir*/
void comms_send_missile_data(uint8_t x_coord, uint8_t type);

/*sends a given code through ir*/
void comms_send_code(uint8_t code);

/*recieves ir data - if missile code then initialise new
enemy missile with the recieved data - returns code*/
uint8_t comms_receive_data(void);

#endif /* COMMS_H */