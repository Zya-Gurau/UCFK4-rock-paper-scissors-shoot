/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

main file - contains the main function

this program codes an UCFK4 to play a paper, scissors, rock themed,
2-player missile shooter game.

This module initialises the game and controls the pacer which controls 
when and how frequently each task is completed 
*/

#include <system.h>
#include "player.h"
#include "pacer.h"
#include "missile.h"
#include "led.h"
#include "comms.h"
#include "game.h"
#include "../fonts/font3x5_1.h"

/*tracks the current game state (PLAYING or WAITING)*/
static game_state_t game_state;

/*initialises system, pacer, tinygl, navswitch, ir communication, 
player and friendly & enemy missiles */
void initialise (void)
{
    system_init();
    pacer_init(PACER_RATE);
    navswitch_init();
    ir_uart_init();
    led_init();
    
    //tinygl setup
    tinygl_init(DISPLAY_RATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_text_speed_set (TEXT_DISPLAY_RATE);
    
    //game setup
    friendly_missile_array_init();
    enemy_missile_array_init();
    player_init();
    game_state = WAITING;   
}

/*reinitialises player and friendly & enemy missiles in order to restart game*/
void reinitialise_game (void)
{
    friendly_missile_array_init();
    enemy_missile_array_init();
    player_init();
}

/*task to move both friendly and enemy missiles across the screen and check 
missile collisions*/
void missile_move_task(void)
{
    draw_friendly_missiles();
    missile_check_collision();
    draw_enemy_missiles();
    missile_check_collision();
}

/*task which allows the player to shot a rock, paper or scissors
missile*/
void player_shoot_task(void)
{
    player_shoot(); 
}

/*task which allows the player to move up and down the screen*/
void player_move_task(void)
{
    player_draw();
}

/*task which allows the UCFK4 to recieve ir data about missiles
and game state from the opponents UCFK4 board */
void recieve_task(void)
{
    uint8_t code;
    code = comms_receive_data();
    if (code == START_CODE) // starts game
    {
        tinygl_clear();
        reinitialise_game();
        game_state = PLAYING;
    }
    else if (code == WIN_CODE) // ends game for winner
    {
        comms_send_code(LOSE_CODE);
        game_state = WAITING;
        tinygl_clear();
        tinygl_text(WIN_MESSAGE);
        tinygl_update ();
    }
    else if (code == LOSE_CODE) // ends game for loser
    {
        game_state = WAITING;
        tinygl_clear();
        tinygl_text(LOSE_MESSAGE);
        tinygl_update ();
    }
}

/*main function which initialises the game and enters a while
loop which uses a pacer to call tasks at the appropriate time 
in order to play the game.*/
int main (void)
{
    initialise();
    tinygl_text(PUSH_TO_START_MESSAGE);
    
    //ticks to track task rates
    uint8_t player_shoot_tick = 0;
    uint8_t missile_move_tick = 0;
    uint8_t receive_tick = 0;

    while (1)
    {
        pacer_wait();
        //incrementing ticks for game tasks
        player_shoot_tick++;
        missile_move_tick++;
        receive_tick++;

        switch(game_state) {
            case WAITING : //waiting to start game
            led_set(LED1, LED_ON); //shows state of game is WAITING
                if (navswitch_push_event_p (NAVSWITCH_PUSH)) //starts game (from own funkit)
                {
                    reinitialise_game();
                    tinygl_clear();
                    game_state = PLAYING;
                    comms_send_code(START_CODE);
                }
                if(receive_tick == (PACER_RATE/RECEIVE_TASK_RATE)) { //starts game (from opponent funkit)
                    recieve_task();
                    receive_tick = 0;
                }
                break;

            case PLAYING : //playing game
                led_set(LED1, LED_OFF); //shows state of game is PLAYING

                //game tasks executed in pacer loop
                player_move_task();
                if(player_shoot_tick == (PACER_RATE/PLAYER_SHOOT_TASK_RATE)) {
                    player_shoot_task();
                    player_shoot_tick = 0;
                }
                if(missile_move_tick == (PACER_RATE/MISSILE_TASK_RATE)) {
                    missile_move_task();
                    missile_move_tick = 0;
                }
                if(receive_tick == (PACER_RATE/RECEIVE_TASK_RATE)) {
                    recieve_task();
                    receive_tick = 0;
                }
                break;
        }
        
        navswitch_update(); //updates navswitch
        tinygl_update(); //updates display
    }
}
