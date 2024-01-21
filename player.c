/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

player source file

contains functions relating to the player. This includes
the player initialisation, allowing the player to shoot a 
missile, and moving up and down the screen
*/

#include <system.h>
#include "tinygl.h"
#include "player.h"
#include "navswitch.h"

/*defines staitc variables for the player and the player's x coordinate*/
static player_t player;
static uint8_t player_x_coord;

/*initialises the player and sets their x posistion in the middle of the screen*/
void player_init(void) 
{
    player_x_coord = PLAYER_START_X_COORD;
    player.position = tinygl_point(player_x_coord,PLAYER_Y_COORD);
}

/*private function - checks for movement inputs from the user and moves 
the player accordingly*/
static void player_move(void)
{
    //navswitch_update();
    if (navswitch_push_event_p (NAVSWITCH_WEST) && player_x_coord > MIN_X_COORD) 
    { //move player up
        player_x_coord--;
        player.position = tinygl_point(player_x_coord,PLAYER_Y_COORD);
    }
    if (navswitch_push_event_p (NAVSWITCH_EAST) && player_x_coord < MAX_X_COORD) 
    { //move player down
        player_x_coord++;
        player.position = tinygl_point(player_x_coord,PLAYER_Y_COORD);
    }
}

/*removes the player from the screen, checks for movement, then redraws
the player on the screen*/
void player_draw(void)
{
    tinygl_draw_point(player.position, DISPLAY_HIDE);
    player_move();
    tinygl_draw_point(player.position, DISPLAY_SHOW);
}

/*checks for shoot inputs from user and initialises a new missile accordingly*/
void player_shoot(void)
{
   if (navswitch_push_event_p (NAVSWITCH_PUSH)) 
    {
        friendly_missile_init(player_x_coord, ROCK); // creates a rock missile
    }
    else if (navswitch_push_event_p (NAVSWITCH_NORTH)) 
    {
        friendly_missile_init(player_x_coord, PAPER); // creates a paper missile
    }
    else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) 
    {
        friendly_missile_init(player_x_coord, SCISSORS); // creates a scissors missile
    }
}