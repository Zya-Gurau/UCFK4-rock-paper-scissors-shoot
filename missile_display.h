/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

missile_display header file

controls the drawing and remove of missiles on the screen
*/

#ifndef MISSILE_DISPLAY_H
#define MISSILE_DISPLAY_H

#include "tinygl.h"
#include <system.h>

/*definition of constants for showing/hiding missiles*/
#define DISPLAY_SHOW 1
#define DISPLAY_HIDE 0

/*displays a rock type missile on the screen*/
void show_rock(uint8_t x_coord, uint8_t y_coord);

/*displays a paper type missile on the screen*/
void show_paper(uint8_t x_coord, uint8_t y_coord);

/*displays a scissors type missile on the screen - takes a boolean value to determine 
if the scissors is friednly or not*/
void show_scissors(uint8_t x_coord, uint8_t y_coord, bool is_friendly);

/*removes a rock type missile from the screen*/
void remove_rock(uint8_t x_coord, uint8_t y_coord);

/*removes a paper type missile from the screen*/
void remove_paper(uint8_t x_coord, uint8_t y_coord);

/*removes a scissors type missile from the screen - takes a boolean value to determine 
if the scissors is friednly or not*/
void remove_scissors(uint8_t x_coord, uint8_t y_coord, bool is_friendly);

#endif /* MISSILE_DISPLAY_H */