/** @file   ball.c
    @author Nobu Sato, Andrew Heaslip
    @date   10 October 2017
    @brief  Functionality of the ball
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../../fonts/font5x7_1.h"
#include "ball.h"
#include "player_status.h"
#include "communication.h"
#include "packet.h"

#define BALL_SPEED 75
#define WINNER 'W'
#define GAME_STARTED 'a'

/** Array containing all direction of the ball*/
static const char x_direction[] = {'l', 'r', 'f'}; //l = left, r = right, f = forward
static const char y_direction[] = {'u', 'd'}; // u = up and d = down

/** Keeps track of position of the ball.*/
int x_pos; //Public as it is used for decoding/encoding
static int y_pos = 0;

/** Keeps track of direction of the ball.*/
int x_dir; //Public as it is used for decoding/encoding
static int y_dir = 1;

/** Initialize the current time as zero.*/
static uint16_t time = 0;

/** Boolean to check if the ball currently displayed on the LED Matrix.*/
static bool ball_onscreen;

/** Boolean to check if the ball is still in play.*/
bool ball_inplay;

/** Boolean to check if the player won the game.*/
bool winner;

/** Encoded character.*/
char encoded;

/** Awaiting for an incoming ball from the opponent's UCFK4 fun kit.*/
static void waiting_ball (void)
{
    encoded = get_ball_pos_with_direction();
    if (encoded == WINNER) {
        winner = true;
    } else {
        decoding();
        if (encoded > 0) {
            tinygl_draw_point(tinygl_point(y_pos, x_pos), 2);
            tinygl_update ();
            ball_onscreen = true;
            y_dir = 1;
        }
    }
}

/** Applies certain condition, if the ball hits the boundary
    @param front_paddle Front side of the paddle.
    @param end_paddle Back side of the paddle.*/
static void ball_boundary_check (int front_paddle, int end_paddle)
{
    //Case when the ball is sent to the opponent's UCFK fun kit.
    if (y_pos == 0 && y_direction[y_dir] == 'u') {
        encoding();
        give_ball_with_position_direction(encoded);
        ball_onscreen = false;
        return;
    }

    //Change direction, when the ball hits wall.
    if ((x_pos == 0) && (x_direction[x_dir] == 'r')) {
        x_dir = 0;
    } else if ((x_pos == 6) && (x_direction[x_dir] == 'l')) {
        x_dir = 1;
    }

    //Ball past the paddle
    if (y_pos == 4) {
        ball_inplay = false;
    }

    //Checks if the ball hits the paddle
    if (y_pos == 3) {
        if (x_pos == front_paddle) {
            x_dir = 1;
            y_dir = 0;
        } else if (x_pos == end_paddle) {
            x_dir = 0;
            y_dir = 0;
        } else if (x_pos < end_paddle && x_pos > front_paddle) {
            x_dir = 2;
            y_dir = 0;
        }
    }
}

/** Updates position of the ball.*/
static void ball_movement (void)
{
    if (x_direction[x_dir] == 'f' && y_direction[y_dir] == 'd') {
        y_pos++;
    } else if (x_direction[x_dir] == 'f' && y_direction[y_dir] == 'u') {
        y_pos--;
    } else if (x_direction[x_dir] == 'l' && y_direction[y_dir] == 'u') {
        y_pos--;
        x_pos++;
    } else if (x_direction[x_dir] == 'r' && y_direction[y_dir] == 'u') {
        y_pos--;
        x_pos--;
    } else if (x_direction[x_dir] == 'l' && y_direction[y_dir] == 'd') {
        y_pos++;
        x_pos++;
    } else if (x_direction[x_dir] == 'r' && y_direction[y_dir] == 'd') {
        y_pos++;
        x_pos--;
    }
}

/** Handles behaviour of the ball.
    @param front_paddle Front side of the paddle.
    @param end_paddle Back side of the paddle.*/
void move_ball (int front_paddle, int end_paddle)
{
    if (!ball_onscreen) {
        waiting_ball();
    } else {
        tinygl_draw_point(tinygl_point(y_pos, x_pos), 2);
        tinygl_update ();
        if (time > BALL_SPEED) {
            time = 0;
            ball_boundary_check(front_paddle, end_paddle);
            ball_movement();
        }
        time++;
    }
}


/** Initialize the ball.
    @param player_serving Boolean to check whether the player is serving the ball.*/
void ball_init (bool player_serving)
{
    ball_inplay = true;
    winner = false;
    if (player_serving) {
        x_pos = 3;
        y_pos = 0;
        x_dir = 2;
        y_dir = 1;
        update_game_status(GAME_STARTED);
        ball_onscreen = true;
    } else {
        ball_onscreen = false;
    }
}


