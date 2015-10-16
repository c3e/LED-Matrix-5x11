#include "global_def.h"

int latch_pin = 8;
int clock_pin = 4;
int data_pin = 10;

int iteration = 1;

bool matrix		[MATRIX_HEIGHT][MATRIX_WIDTH+MATRIX_BUFFER];
int	matrix_slice[MATRIX_HEIGHT][1];
