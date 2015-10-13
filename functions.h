#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <Arduino.h>
#include "global_def.h"

void		shift_Matrix_right	(int delay_iteration, int ammount);
uint16_t	displayMatrix		();
void		shift				(uint16_t input);
int			insertLetter		(int letter);
void		insertSpace			();
void		displayMessage		(char* message, int delay_iteration);

extern bool matrix[5][14];
extern int	matrix_slice[5][1];

#endif