#ifndef GLOBAL_DEF_H
#define GLOBAL_DEF_H
#include <Arduino.h>


#define LETTER_WIDTH	5
#define LETTER_HEIGHT	5
#define MATRIX_HEIGHT	5
#define MATRIX_WIDTH	11
#define MATRIX_BUFFER	LETTER_WIDTH

extern bool matrix[MATRIX_HEIGHT][MATRIX_WIDTH+MATRIX_BUFFER];
extern int	matrix_slice[5][1];

extern int latch_pin;
extern int clock_pin;
extern int data_pin;

extern int iteration;

const uint32_t ascii[128] = {
#include "font.h"
};

#endif


