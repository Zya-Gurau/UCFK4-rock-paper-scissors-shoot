/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

missile source file

contains functions relating to the missiles (both friendly and enemy). 
This includes initialisation new missiles, moving missiles across the
screen, and checking for collisions.
*/

#include <system.h>
#include <stdlib.h>
#include <stdint.h>
#include "missile.h"
#include "comms.h"
#include "missile_display.h"

/*declare static variables for friendly and enemy missile arrays*/
static missile_t* friendly_missiles;
static missile_t* enemy_missiles;  

/*define static variables representing the current index of the friendly an enemy missile arrays*/
static uint8_t current_index = 0;
static uint8_t current_enemy_index = 0;


/*Missile Initialisation*/

/*Private function - sets the missile at the given index in the friendly_missiles
array to a void missile */
static void set_friendly_missile_to_void(uint8_t index) 
{
    missile_t void_missile;
    void_missile.type = VOID;
    friendly_missiles[index] = void_missile;
}

/*Private function - sets the missile at the given index in the enemy_missiles
array to a void missile*/
static void set_enemy_missile_to_void(uint8_t index) 
{
    missile_t void_missile;
    void_missile.type = VOID;
    enemy_missiles[index] = void_missile;
}

/*initialises the friendly missile array and allocates space for it in memory*/
void friendly_missile_array_init(void)
{
    friendly_missiles = calloc(MAX_MISSILE_FRIENDLY, sizeof(missile_t));
    for(uint8_t i = 0; i<MAX_MISSILE_FRIENDLY; i++) {
        set_friendly_missile_to_void(i);
    }
}

/*initialises the enemy missile array and allocates space for it in memory*/
void enemy_missile_array_init(void)
{
    enemy_missiles = calloc(MAX_MISSILE_ENEMY, sizeof(missile_t));
    for(uint8_t i = 0; i<MAX_MISSILE_ENEMY; i++) {
        set_enemy_missile_to_void(i);
    }
}

/*initialises a new friendly missile of the given type and at the given 
x-coordinate. it then adds the missile to the friendly missile array*/
void friendly_missile_init(uint8_t player_coord, missile_type_t type)
{
    //resets array index to 0 if index is too big
    if (current_index >= MAX_MISSILE_FRIENDLY) 
    {
        current_index = 0;
    }
    //creates missile
    missile_t new_missile;
    new_missile.x_pos = player_coord;
    new_missile.y_pos = BACK_OF_SCREEN_Y_COORD;
    new_missile.type = type;

    friendly_missiles[current_index] = new_missile; //adds missile to friendly array
    current_index++;
}

/*initialises a new enemy missile of the given type and at the given 
x-coordinate. it then adds the missile to the enemy missile array*/
void enemy_missile_init(uint8_t x_coord, missile_type_t type)
{
    //resets array index to 0 if index is too big
    if (current_enemy_index >= MAX_MISSILE_FRIENDLY) 
    {
        current_enemy_index = 0;
    }
    //creates missile
    missile_t new_missile;
    new_missile.x_pos = x_coord;
    new_missile.y_pos = START_OF_SCREEN_Y_COORD;
    new_missile.type = type;

    enemy_missiles[current_enemy_index] = new_missile; //adds missile to enemy array
    current_enemy_index++;
}


/*Missile Collisions*/

/*Private function - resolves collisions between missiles using standard paper scissors 
rock logic*/
static void resolve_collision(uint8_t friendly_index, uint8_t enemy_index)
{
    missile_t friendly = friendly_missiles[friendly_index];
    missile_t enemy = enemy_missiles[enemy_index];
    
    if (friendly.type == ROCK) { //Rock collisions
        if (enemy.type == PAPER) 
        {
            remove_rock(friendly.x_pos, friendly.y_pos);
            set_friendly_missile_to_void(friendly_index);
        }
        if (enemy.type == SCISSORS)
        {
            remove_scissors(enemy.x_pos, enemy.y_pos, IS_NOT_FRIENDLY);
            set_enemy_missile_to_void(enemy_index);
        }
    }
    if (friendly.type == PAPER) { //paper collisions
        if (enemy.type == ROCK){
            remove_rock(enemy.x_pos, enemy.y_pos);
            set_enemy_missile_to_void(enemy_index);
        }
    if (enemy.type == SCISSORS)
        {
            remove_paper(friendly.x_pos, friendly.y_pos);
            set_friendly_missile_to_void(friendly_index);
        }
    }
    if (friendly.type == SCISSORS) { //scissors collisions
        if (enemy.type == ROCK){
            remove_scissors(friendly.x_pos, friendly.y_pos, IS_FRIENDLY);
            set_friendly_missile_to_void(friendly_index);
        }
        if (enemy.type == PAPER)
        {
            remove_paper(enemy.x_pos, enemy.y_pos);
            set_enemy_missile_to_void(enemy_index);
        }
    }  
}

/*checks for collisions between missiles and resolves them*/
void missile_check_collision(void)
{
    for(uint8_t i = 0; i<MAX_MISSILE_FRIENDLY; i++) { //loop through friendly missiles
        missile_t friendly = friendly_missiles[i];
        for(uint8_t j = 0; j<MAX_MISSILE_ENEMY; j++) { //loop through enemy missiles
            missile_t enemy = enemy_missiles[j];
            if ((friendly.y_pos == enemy.y_pos) & (friendly.x_pos == enemy.x_pos)) { //checks for direct collision
                resolve_collision(i, j);
            }
        }
    }
}

/*Private function - checks if a enemy missile has gone off the end of the 
screen. If so removes the missile from enemy array and from the screen, then
ends the game*/
static void enemy_missile_off_screen_check(uint8_t missile_index)
{
    missile_t enemy = enemy_missiles[missile_index];
    if (enemy.y_pos == BACK_OF_SCREEN_Y_COORD)
    {
        if (enemy.type == ROCK)
        {
            remove_rock(enemy.x_pos, enemy.y_pos);
        }
        if (enemy.type == PAPER)
        {
            remove_paper(enemy.x_pos, enemy.y_pos);
        }
        if (enemy.type == SCISSORS)
        {
            remove_scissors(enemy.x_pos, enemy.y_pos, IS_NOT_FRIENDLY);
        }
        set_enemy_missile_to_void(missile_index); //removes enemy missile from enemy array
        comms_send_code(WIN_CODE); //sends code to end game
    }
}

/*Private function - checks if a friendly missile has gone off the end of the 
screen. If so removes the missile from friendly array and from the screen and 
sends missile data to opponents board*/
static void friendly_missile_off_screen_check(uint8_t missile_index)
{
    missile_t friendly = friendly_missiles[missile_index];
    if (friendly.y_pos == START_OF_SCREEN_Y_COORD)
    {
        if (friendly.type == ROCK)
        {
            remove_rock(friendly.x_pos, friendly.y_pos);
        }
        if (friendly.type == PAPER)
        {
            remove_paper(friendly.x_pos, friendly.y_pos);
        }
        if (friendly.type == SCISSORS)
        {
            remove_scissors(friendly.x_pos, friendly.y_pos, IS_FRIENDLY);
        }
        comms_send_missile_data(friendly.x_pos, friendly.type); //sends missile data
        set_friendly_missile_to_void(missile_index); // removes missile from friendly array
    }
}


/*Missile Movement*/

/*Private function - increments a friendly missiles y posistion*/
static void missile_move_friendly(uint8_t missile_index)
{
    friendly_missiles[missile_index].y_pos--; //note: due to orientation incrementing y posistion means decreasing y
}

/*Private function - decrements an enemy missiles y posistion*/
static void missile_move_enemy(uint8_t missile_index)
{
    enemy_missiles[missile_index].y_pos++; //note: due to orientation decrementing y posistion means increasing y
}

/*Private function - first checks if missile is off the screen. If not it draws the 
friendly missile on the screen. */
static void friendly_missile_draw(uint8_t missile_index)
{
    friendly_missile_off_screen_check(missile_index); 
    // draw rock missle
    if (friendly_missiles[missile_index].type == ROCK) {
        remove_rock(friendly_missiles[missile_index].x_pos, friendly_missiles[missile_index].y_pos);
        missile_move_friendly(missile_index);
        show_rock(friendly_missiles[missile_index].x_pos, friendly_missiles[missile_index].y_pos);
    }
    // draw paper missile
    else if (friendly_missiles[missile_index].type == PAPER) {
        remove_paper(friendly_missiles[missile_index].x_pos, friendly_missiles[missile_index].y_pos);
        missile_move_friendly(missile_index);
        show_paper(friendly_missiles[missile_index].x_pos, friendly_missiles[missile_index].y_pos);
    }
    //draw a scissors missile
    else if (friendly_missiles[missile_index].type == SCISSORS) {
        remove_scissors(friendly_missiles[missile_index].x_pos, friendly_missiles[missile_index].y_pos, IS_FRIENDLY);
        missile_move_friendly(missile_index);
        show_scissors(friendly_missiles[missile_index].x_pos, friendly_missiles[missile_index].y_pos, IS_FRIENDLY);
    }      
}

/*private function - draws each individual enemy missile on the screen
then checks if the missile is off the screen*/
static void enemy_missile_draw(uint8_t missile_index)
{
    // draw rock missle
    if (enemy_missiles[missile_index].type == ROCK) {
        remove_rock(enemy_missiles[missile_index].x_pos, enemy_missiles[missile_index].y_pos);
        missile_move_enemy(missile_index);
        show_rock(enemy_missiles[missile_index].x_pos, enemy_missiles[missile_index].y_pos);
    }
    // draw paper missile
    else if (enemy_missiles[missile_index].type == PAPER) {
        remove_paper(enemy_missiles[missile_index].x_pos, enemy_missiles[missile_index].y_pos);
        missile_move_enemy(missile_index);
        show_paper(enemy_missiles[missile_index].x_pos, enemy_missiles[missile_index].y_pos);
    }
    //draw a scissors missile
    else if (enemy_missiles[missile_index].type == SCISSORS) {
        remove_scissors(enemy_missiles[missile_index].x_pos, enemy_missiles[missile_index].y_pos, IS_NOT_FRIENDLY);
        missile_move_enemy(missile_index);
        show_scissors(enemy_missiles[missile_index].x_pos, enemy_missiles[missile_index].y_pos, IS_NOT_FRIENDLY);
    }
    
    enemy_missile_off_screen_check(missile_index); 
}

/*displays all friendly missiles on screen*/
void draw_friendly_missiles(void)
{
    for(uint8_t i = 0; i<MAX_MISSILE_FRIENDLY; i++)
    {
        if (friendly_missiles[i].type != VOID)
        {
            friendly_missile_draw(i);
        }
    } 
}

/*displays all enemy missiles on screen*/
void draw_enemy_missiles(void)
{
    for(uint8_t i = 0; i<MAX_MISSILE_FRIENDLY; i++)
    {
        if (enemy_missiles[i].type != VOID)
        {
            enemy_missile_draw(i);
        } 
    } 
}