/*
ENCE260 game assignment
@team 505
@author Emily McGifford - 99588686
@author Zya Gurau - 64646583
date 5 oct 2023

missile_display source file

controls the drawing and remove of missiles on the screen
*/

#include "tinygl.h"
#include "missile_display.h"
#include <system.h>

/*removes a rock type missile from the screen*/
void remove_rock(uint8_t x_coord, uint8_t y_coord)
{
    tinygl_draw_point(tinygl_point(x_coord, y_coord), DISPLAY_HIDE);
}

/*removes a paper type missile from the screen*/
void remove_paper(uint8_t x_coord, uint8_t y_coord)
{
    tinygl_point_t line_start = tinygl_point(x_coord-1, y_coord);
    tinygl_point_t line_end = tinygl_point(x_coord+1, y_coord);
    tinygl_draw_line(line_start, line_end, DISPLAY_HIDE);
}

/*removes a scissors type missile from the screen - takes a boolean value to determine 
if the scissors is friednly or not*/
void remove_scissors(uint8_t x_coord, uint8_t y_coord, bool is_friendly)
{
    //if missile is friendly remove friendly missile, if not remove enemy missile
    if (is_friendly == true) 
    {
        tinygl_point_t line_bottom_friendly = tinygl_point(x_coord-1, y_coord-1);
        tinygl_point_t line_mid_friendly = tinygl_point(x_coord, y_coord);
        tinygl_point_t line_top_friendly = tinygl_point(x_coord+1, y_coord-1);
        tinygl_draw_line(line_mid_friendly, line_top_friendly, DISPLAY_HIDE);
        tinygl_draw_line(line_mid_friendly, line_bottom_friendly, DISPLAY_HIDE);
    } else {
        tinygl_point_t line_bottom_enemy = tinygl_point(x_coord-1, y_coord+1);
        tinygl_point_t line_mid_enemy = tinygl_point(x_coord, y_coord);
        tinygl_point_t line_top_enemy = tinygl_point(x_coord+1, y_coord+1);
        tinygl_draw_line(line_mid_enemy, line_top_enemy, DISPLAY_HIDE);
        tinygl_draw_line(line_mid_enemy, line_bottom_enemy, DISPLAY_HIDE);
    }   
}

/*displays a rock type missile on the screen*/
void show_rock(uint8_t x_coord, uint8_t y_coord)
{
    tinygl_draw_point(tinygl_point(x_coord, y_coord), DISPLAY_SHOW);
}

/*displays a paper type missile on the screen*/
void show_paper(uint8_t x_coord, uint8_t y_coord)
{
    tinygl_point_t line_start = tinygl_point(x_coord-1, y_coord);
    tinygl_point_t line_end = tinygl_point(x_coord+1, y_coord);
    tinygl_draw_line(line_start, line_end, DISPLAY_SHOW);
}

/*displays a scissors type missile on the screen - takes a boolean value to determine 
if the scissors is friednly or not*/
void show_scissors(uint8_t x_coord, uint8_t y_coord, bool is_friendly)
{
    //if missile is friendly show friendly missile, if not show enemy missile
    if (is_friendly == true)
    {
        tinygl_point_t line_bottom_friendly = tinygl_point(x_coord-1, y_coord-1);
        tinygl_point_t line_mid_friendly = tinygl_point(x_coord, y_coord);
        tinygl_point_t line_top_friendly = tinygl_point(x_coord+1, y_coord-1);
        tinygl_draw_line(line_mid_friendly, line_top_friendly, 1);
        tinygl_draw_line(line_mid_friendly, line_bottom_friendly, DISPLAY_SHOW);
    } else {
        tinygl_point_t line_bottom_enemy = tinygl_point(x_coord-1, y_coord+1);
        tinygl_point_t line_mid_enemy = tinygl_point(x_coord, y_coord);
        tinygl_point_t line_top_enemy = tinygl_point(x_coord+1, y_coord+1);
        tinygl_draw_line(line_mid_enemy, line_top_enemy, DISPLAY_SHOW);
        tinygl_draw_line(line_mid_enemy, line_bottom_enemy, DISPLAY_SHOW);
    }
}

