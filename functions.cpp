#include "functions.h"

void shift_Matrix_left(int delay_iteration, int ammount) {

	for (int counter = 0; counter < ammount; counter++) {
		// Copy the first element into a buffer
		for (int i = 0; i < MATRIX_HEIGHT; i++) {
			matrix_slice[i][0] = matrix[i][0];
		}
		// Shift all elements left
		for (int i = 0; i < MATRIX_HEIGHT; i++) {
			for (int j = 0; j < MATRIX_WIDTH+MATRIX_BUFFER-1; j++) {
				matrix[i][j] = matrix[i][j + 1];
			}
		}
		// Copy the last element from the buffer
		for (int i = 0; i < MATRIX_HEIGHT; i++) {
			matrix[i][MATRIX_WIDTH+MATRIX_BUFFER-1] = matrix_slice[i][0];
		}

		delay(delay_iteration);
	}
		
}

uint16_t displayMatrix() {
	int i = 0;
	int j = 0;
	uint16_t shift_out = BLANK;

	for (i = 0; i < MATRIX_HEIGHT; i++) {
		for (j = 0; j < MATRIX_WIDTH; j++) {
			if (matrix[i][j]) {
				shift_out |=	1 << (4 - i);	// Map the appropriate Row
				shift_out &= ~( 1 << (15 - j));	// Map the appropriate Column
			}
		}
		shift(shift_out);		// Shift out one row
		shift_out = BLANK;		// Initialise next row
	}
	shift(shift_out);
	return shift_out;
}

void shift(uint16_t input) {
	
	for (uint16_t bit_mask = 32768; bit_mask > 0; bit_mask = bit_mask / 2)
	{
		if (bit_mask & input) {				// Begin with MSB and approach LSB with each iteration
			digitalWrite(data_pin, HIGH);   // Set the output for shift-register HIGH
		}
		else {
			digitalWrite(data_pin, LOW);	// Set the output for shift-register LOW
		}

		digitalWrite(clock_pin, LOW);		// create a falling edge on the shift-registers SCKL Pin
		digitalWrite(clock_pin, HIGH);		// -> shift 1 bit into the registers storage

	}

	digitalWrite(latch_pin, HIGH);			// Clock the collected data into the storage register to make it visible	
	digitalWrite(latch_pin, LOW);			// (falling edge is needed)
	digitalWrite(data_pin, LOW);			// Take Data Pin low just to be sure.
}

int insertLetter(int letter, int delay_ms) {


	uint32_t current_letter = ascii[letter];
	uint8_t current_nibble = 0;
	uint8_t max_width = 1;
	uint8_t offset = 4 * LETTER_WIDTH;

	//Serial.print("Current Letter: ");
	//Serial.println(current_letter);

	// 0x 6    4    b    d    2    9, // A
	//    0110 01001 01111 01001 01001

	// 0x 6    9    f    9    9    // A
	// 0b 0110 1001 1111 1001 1001
	//    

	// Calculate max_width
	for (int i = 0; i < LETTER_HEIGHT; i++) {
		current_nibble = (current_letter >> (offset - (LETTER_WIDTH * i))) & 0x1f;
		for (int j = 0; j < LETTER_WIDTH; j++) {
			if ((current_nibble & (1 << j)) && max_width <= j) {
				// j starts with 0, max_width starts with 1
				max_width = j+1;
			}
		}
	}
	/*Serial.print("Letter Width: ");
	Serial.print(max_width);
	Serial.print(" Letter:");
	Serial.println(letter);*/
	// Clear the space for the next Letter
	/*for (int i = 0; i < max_width; i++) {
		insertSpace();
		shift_Matrix_left(delay_ms, 1);
	}*/
	shift_Matrix_left(delay_ms, max_width);

	// Write letter into Matrix
	for (int i = 0; i < LETTER_HEIGHT; i++){
		current_nibble = (current_letter >> (offset - (LETTER_WIDTH * i))) & 0x1f;
		//Serial.print("Current Nibble : ");
		//Serial.println(current_nibble);

		for (int j = 0; j < LETTER_WIDTH; j++)
		{	
			if (j < LETTER_WIDTH - max_width) {
				// empty space in front of the current letter, dont write this into the matrix
			}
			else {
				// 
				matrix[i][MATRIX_WIDTH - 1 + j] = (current_nibble >> (LETTER_WIDTH - 1 - j)) & 0x01;
				//Serial.print("Current Bit: ");
				//Serial.println(matrix[i][10 + j]);
			}
		}
	}
	
	return max_width;
}

void insertSpace() {
	for (int i = 0; i < MATRIX_HEIGHT; i++)
	{
		matrix[i][MATRIX_WIDTH+MATRIX_BUFFER-1] = 0;
	}
}

void displayMessage(char* message, int delay_iteration) {
	int i = 0;
	uint8_t letter_width = 0;

		//Serial.println("Trying to print Message.");
		while (message[i] != 0)
		{
			//Serial.print("Message(char) :");
			//Serial.println(message[i]);
			//letter_width = insertLetter(message[i]);
			insertLetter(message[i], 200);
			insertLetter(0, 200);
			//shift_Matrix_left(delay_iteration,1);
			//insertSpace();
			//shift_Matrix_right(delay_iteration,letter_width);
			i++;
		}
}