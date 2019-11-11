/** @file   paddle.h
    @author Nobu Sato, Andrew Heaslip
    @date   10 October 2017
    @brief  Functionality of the paddle
*/

#include "system.h"

#ifndef PADDLE_H
#define PADDLE_H

/** Front side of the paddle.*/
int start_pos;

/** Back side of the paddle.*/
int end_pos;

/** Set the position of the paddle to the origin position.*/
void set_paddle_origin_pos (void);

/** Draws the current position of the paddle on the UCFK Fun Kit.*/
void paddle_pos (void);

#endif /* PADDLE_H */
