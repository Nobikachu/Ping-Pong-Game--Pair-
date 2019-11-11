/** @file communication.c
    @author Nobu Sato, Andrew Heaslip
    @date 10 October 2017
    @brief Communicate between the two UCFK4 fun kits by sending or receiving the ball.
*/

#include "system.h"
#include "communication.h"
#include "ir_uart.h"

/**  Sends encoded character to partner UCFK4
    @param encoded character to send to partner UCFK4 */
void give_ball_with_position_direction (char encoded)
{
    ir_uart_putc(encoded);
}

/**  Receives encoded character from partner UCFK4
    @return encoded value retreived from UCFK4 */
char get_ball_pos_with_direction (void)
{
    if (ir_uart_read_ready_p()) {
        return ir_uart_getc();
    }
    return 0;
}
