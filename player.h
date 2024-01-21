/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

player header file

contains functions relating to the player. This includes
the player initialisation, allowing the player to shoot a 
missile, and moving up and down the screen
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <system.h>
#include "tinygl.h"
#include "missile.h"
#include "navswitch.h"

/*definitions of player's min/max/initial x coordinates and player's y coordinate*/
#define PLAYER_START_X_COORD 2
#define MAX_X_COORD 4
#define MIN_X_COORD 0
#define PLAYER_Y_COORD 6

/*definition of constants for showing/hiding player*/
#define DISPLAY_SHOW 1
#define DISPLAY_HIDE 0

/*defines a player type which contains a posistion on the screen*/
typedef struct {
    tinygl_point_t position;
} player_t;

/*initialises a new player and set their initial position*/
void player_init(void);

/*shoots a missile*/
void player_shoot(void);

/*updates a players position on the screen*/
void player_draw(void);

#endif /* PLAYER_H */