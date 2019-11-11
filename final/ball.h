/** @file   ball.h
    @author Nobu Sato, Andrew Heaslip
    @date   10 October 2017
    @brief  Functionality of the ball
*/

#include "system.h"

#ifndef BALL_H
#define BALL_H

/** Keeps track of x position of the ball.*/
int x_pos;

/** Keeps track of x direction of the ball.*/
int x_dir;

/** Boolean to check if the ball is still in play.*/
bool ball_inplay;

/** Boolean to check if the player won the game.*/
bool winner;

/** Encoded character.*/
char encoded;

/** Handles behaviour of the ball.
    @param front_paddle Front side of the paddle.
    @param end_paddle Back side of the paddle.*/
void move_ball (int front_paddle, int end_paddle);

/** Initialize the ball.
    @param player_serving Boolean to check whether the player is serving the ball.*/
void ball_init (bool player1);

#endif /* BALL_H */
