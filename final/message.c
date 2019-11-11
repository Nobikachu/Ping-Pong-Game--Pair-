/** @file   message.c
    @author Nobu Sato, Andrew Heaslip
    @date   10 October 2017
    @brief  Displays message on the UCFK4 fun kit
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../../fonts/font5x7_1.h"
#include "message.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20

/** Initialize the message.*/
void message_init (void)
{
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    pacer_init (PACER_RATE);
}

/** Displays the message.*/
void display_message (void)
{
    pacer_wait();
    tinygl_update ();
}

/** Change the message
    @param text Array of characters.*/
void set_message (char* text)
{
    tinygl_text (text);
}

/** Clears the message.*/
void message_clear (void)
{
    tinygl_clear();
    tinygl_update();
}
