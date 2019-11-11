/** @file   paddle.c
    @author Nobu Sato, Andrew Heaslip
    @date   10 October 2017
    @brief  Functionality of the paddle
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../../fonts/font5x7_1.h"
#include "paddle.h"
#include "navswitch.h"

#define PACER_RATE 600
#define Y_POS 4 //Y position of the paddle

/** Front side of the paddle.*/
int start_pos;

/** Back side of the paddle.*/
int end_pos;

/** Update the start and end position of the paddle.*/
static void paddle_move_right (void)
{
    if (start_pos > 0) {
        start_pos--;
        end_pos--;
    }
}

/** Update the start and end position of the paddle.*/
static void paddle_move_left (void)
{
    if (end_pos < 6) {
        start_pos++;
        end_pos++;
    }
}

/** Updates the paddle's position depending on the push event.*/
static void update_paddle_pos (void)
{
    navswitch_update();
    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        paddle_move_right();
    } else if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
        paddle_move_left();
    }
}

/** Set the position of the paddle to the origin position.*/
void set_paddle_origin_pos (void)
{
    start_pos = 2;
    end_pos = 4;
}

/** Draws the current position of the paddle on the UCFK Fun Kit.*/
void paddle_pos (void)
{
    update_paddle_pos();
    tinygl_draw_line (tinygl_point(Y_POS, start_pos), tinygl_point(Y_POS, end_pos), 1);
    tinygl_update ();
    tinygl_clear();
}
