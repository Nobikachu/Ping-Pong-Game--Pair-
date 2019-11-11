/** @file   message.h
    @author Nobu Sato, Andrew Heaslip
    @date   10 October 2017
    @brief  Displays message on the UCFK4 fun kit
*/

#include "system.h"

#ifndef MESSAGE_H
#define MESSAGE_H

/** Initialize the message.*/
void message_init (void);

/** Displays the message.*/
void display_message (void);

/** Change the message
    @param text Array of characters.*/
void set_message (char* text);

/** Clears the message.*/
void message_clear (void);

#endif /* MESSAGE_H */
