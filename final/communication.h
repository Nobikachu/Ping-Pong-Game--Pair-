/** @file communication.h
    @author Nobu Sato, Andrew Heaslip
    @date 10 October 2017
    @brief Communicate between the two UCFK4 fun kits by sending or receiving the ball.
*/

#include "system.h"

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**  Sends encoded character to partner UCFK4
    @param encoded character to send to partner UCFK4 */
void give_ball_with_position_direction (char encoded);

/**  Receives encoded character from partner UCFK4
    @return encoded value retreived from UCFK4 */
char get_ball_pos_with_direction (void);

#endif /* COMMUNICATION_H */
