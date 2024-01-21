/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

missile header file

contains functions relating to the missiles (both friendly and enemy). 
This includes initialisation new missiles, moving missiles across the
screen, and checking for collisions.
*/

#ifndef MISSILE_H
#define MISSILE_H

#include <stdint.h>

//defines constants for the missile module
#define MAX_MISSILE_FRIENDLY 5
#define MAX_MISSILE_ENEMY 5
#define BACK_OF_SCREEN_Y_COORD 6
#define START_OF_SCREEN_Y_COORD 0
#define IS_FRIENDLY true
#define IS_NOT_FRIENDLY false

/*enum to define the different missile types. VOID indicates a null missile
(equivalent to no missile) which is not displayed on the screen and can't
cause collisions*/
typedef enum {
    VOID = -1,
    ROCK,
    PAPER,
    SCISSORS
} missile_type_t;

/*defines a missile struct containing the missile type (rock, paper, or 
scissors), and the missile's x & y coordinates on the screen*/
typedef struct {
    missile_type_t type;
    uint8_t x_pos;
    uint8_t y_pos;
} missile_t;

/*initialises the friendly missile array*/
void friendly_missile_array_init(void);

/*initialises the enemy missile array*/
void enemy_missile_array_init(void);

/*initialises a new friendly missile shoot by the player*/
void friendly_missile_init(uint8_t player_coord, missile_type_t type);

/*initialises a new enemy missile shot by the opponent*/
void enemy_missile_init(uint8_t player_coord, missile_type_t type);

/*displays all friendly missiles on screen*/
void draw_friendly_missiles(void);

/*displays all enemy missiles on screen*/
void draw_enemy_missiles(void);

/*checks for collisions between missiles*/
void missile_check_collision(void);

#endif /* MISSILE_H */