/** @file   packet.c
    @author Nobu Sato, Andrew Heaslip
    @date   9 October 2017
    @brief  Encode or decode the packet, so that the UCFK4 fun kit can send one byte rather than 2 bytes.
*/

#include "system.h"
#include "packet.h"
#include "ball.h"

#define MAX_POSITION_NUM 7
#define MAX_DIRECTION_NUM 3

static char position_prime;
static char direction_prime;
static char pos_array[MAX_POSITION_NUM] = {7, 11, 13, 17, 19, 23, 29};
static char dir_array[MAX_DIRECTION_NUM] = {2, 3, 5};

/** Encodes x_dir and x_pos to a single character using a unique prime product*/
void encoding (void)
{
    position_prime = pos_array[x_pos];
    direction_prime = dir_array[x_dir];
    encoded = position_prime * direction_prime;
}

/** Function checks whether input divides encoded
   @param divisor to check
   @returns 1 if it divides, 0 otherwise */
int divides_encoded (char divisor)
{
    if ((encoded % divisor) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/** Sets x_dir and x_pos using prime factorization of the encoded value*/
void decoding (void)
{
    int i;
    // Loop through to set x_pos from encoded value using its prime factorization
    for (i = 0; i < MAX_POSITION_NUM; i++) {
        if (divides_encoded(pos_array[i])) {
            x_pos = (MAX_POSITION_NUM - 1) - i;
        }
    }
    // Loop through to set x_dir from encoded value using its prime factorization
    for (i = 0; i < MAX_DIRECTION_NUM; i++) {
        if (divides_encoded(dir_array[i])) {
            x_dir =  i;
        }
    }
}
