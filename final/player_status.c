/** @file   player_status.c
    @author Nobu Sato, Andrew Heaslip
    @date   9 October 2017
    @brief  Synchronize game status by sending a character.
*/
#include "system.h"
#include "ir_uart.h"
#include "player_status.h"
#include "pacer.h"

/** Initialize the player_status.*/
void player_status_init (void)
{
    ir_uart_init();
}

/** Send current game status to the opponent's UCFK4 Fun kit.
    @param status A single character which indicates the current status of the game.*/
void update_game_status (char status)
{
    ir_uart_putc(status);
}

/** UCFK4 fun kit receives the updated game status.
    @return Single character which indicates the current status of the game. Returns '0' by default.*/
char game_status (void)
{
    if (ir_uart_read_ready_p()) {
        return ir_uart_getc();
    }
    return '0';

}
