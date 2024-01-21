/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

header file for game

this program codes an UCFK4 to play a paper, scissors, rock themed,
2-player missile shooter game.

This module initialises the game and controls the pacer which controls 
when and how frequently each task is completed 
*/

#ifndef GAME_H
#define GAME_H

/*define tasks and pacer rate*/
#define PLAYER_MOVE_TASK_RATE 250
#define PLAYER_SHOOT_TASK_RATE 250
#define MISSILE_TASK_RATE 4
#define RECEIVE_TASK_RATE 5
#define PACER_RATE 250
#define DISPLAY_RATE 250
#define TEXT_DISPLAY_RATE 20

/*defines display messages*/
#define PUSH_TO_START_MESSAGE "PUSH TO START\0"
#define WIN_MESSAGE "YOU WIN!\0"
#define LOSE_MESSAGE "YOU LOSE!\0"

/*defines led on/off constants*/
#define LED_ON 1
#define LED_OFF 0

/*defines a type for the different game states*/
typedef enum 
{
    WAITING=0,
    PLAYING
} game_state_t;

/*initialises system, pacer, tinygl, navswitch, ir communication, 
player and friendly & enemy missiles */
void initialise (void);

/*reinitialises game to start a new round*/
void reinitialise_game (void);

/*task to move both friendly and enemy missiles across the screen
and check missile collisions*/
void missile_move_task(void);

/*task which allows the player to shot a rock, paper or scissors
missile*/
void player_shoot_task(void);

/*task which allows the player to move up and down the screen*/
void player_move_task(void);

/*task which allows the UCFK4 to recieve ir data about missiles
and game state from the opponents UCFK4 board */
void recieve_task(void);

/*main function which runs the game */
int main(void);

#endif /* GAME_H */