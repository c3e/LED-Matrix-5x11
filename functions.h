#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "global_def.h"

#define BLANK 0xffe0

void		shift_Matrix_left	(int delay_iteration, int ammount);
uint16_t	displayMatrix		();
void		shift				(uint16_t input);
int			insertLetter		(int letter, int delay_ms);
void		insertSpace			();
void		displayMessage		(char* message, int delay_iteration);

#endif