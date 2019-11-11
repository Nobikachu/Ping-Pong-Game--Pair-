/** @file   player_status.h
    @author Nobu Sato, Andrew Heaslip
    @date   9 October 2017
    @brief  Synchronize game status by sending a character.
*/

#include "system.h"

#ifndef PLAYER_STATUS_H
#define PLAYER_STATUS_H

/** Initialize the player_status.*/
void player_status_init (void);

/** Send current game status to the opponent's UCFK4 Fun kit.
    @param status a single character which indicates the current status of the game.*/
void update_game_status (char status);

/** UCFK4 fun kit receives the updated game status.
    @return Single character which indicates the current status of the game. Returns '0' by default.*/
char game_status (void);

#endif /* PLAYER_STATUS_H */
