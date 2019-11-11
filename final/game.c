/** @file   game.c
    @author Nobu Sato, Andrew Heaslip
    @date   9 October 2017
    @brief  Controller of the Ping Pong game.
*/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "message.h"
#include "../../fonts/font5x7_1.h"
#include "paddle.h"
#include "ball.h"
#include "player_status.h"

#define PACER_RATE 600
#define WINNER 'W'
#define GAME_STARTED 'a'
#define GAME_LOST 'L'

/** Boolean to check if the game is on play.*/
static bool game_on = false;

/** Boolean to check if the player serving.*/
static bool player_serving = true;

/** The current score of the match.*/
static int score = 0;

/** Current status of the game.*/
static char status;

/** Initialize the game.*/
void game_init (void)
{
    pacer_init(PACER_RATE);
    system_init();
    navswitch_init ();
    message_init();
    player_status_init();
    set_message("WELCOME TO PONG! PUSH DOWN!"); //Introduction message
}

/** Checks condition of the game before starting the game.*/
void game_condition (void)
{
    status = game_status();
    if (status == GAME_STARTED) {
        player_serving = false;
        winner = false;
        game_on = true;
    } else if (status == GAME_LOST) {
        score = 0;
        set_message("YOU GOT SMASHED!!! PRESS DOWN");
    } else if  (navswitch_push_event_p (NAVSWITCH_PUSH)) {
        if (player_serving) {
            player_serving = true;
            game_on = true;
        }
    }
}

/** Runs the ping pong game.*/
void game_mode (void)
{
    message_clear();
    ball_init(player_serving);
    set_paddle_origin_pos();
    while (game_on) {
        pacer_wait();
        move_ball(start_pos, end_pos);
        paddle_pos();
        if (!ball_inplay) {
            game_on = false;
            player_serving = true;
            set_message("LOSER! PUSH DOWN!");
            update_game_status(WINNER);
        }
        if (winner) {
            game_on = false;
            score++;
            if (score == 3) {
                score = 0;
                player_serving = false;
                set_message("YOU ARE THE GRAND CHAMPION!");
                update_game_status(GAME_LOST);
            } else {
                player_serving = false;
                set_message("WINNER!");
            }
        }
    }
}

/** Main function
    @return 0 when the program closes.*/
int main (void)
{
    game_init();
    while (1) {
        display_message();
        navswitch_update();
        game_condition();
        if (game_on) {
            game_mode();
        }
    }

    return 0;
}
