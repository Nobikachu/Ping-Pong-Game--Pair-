/** @file   packet.h
    @author Nobu Sato, Andrew Heaslip
    @date   9 October 2017
    @brief  Encode or decode the packet, so that the UCFK4 fun kit can send one byte rather than 2 bytes.
*/

#include "system.h"

#ifndef PACKET_H
#define PACKET_H

/** Encodes x_dir and x_pos to a single character using a unique prime product*/
void encoding (void);

/** Send current game status to the opponent's UCFK4 Fun kit.
    @param status a single character which indicates the current status of the game.*/
int divides_encoded (char divisors);

/** Sets x_dir and x_pos using prime factorization of the encoded value*/
void decoding (void);

#endif /* PACKET_H */
