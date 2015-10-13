#include "functions.h"


bool matrix[5][14];
int	matrix_slice[5][1];

void shift_Matrix_right(int delay_iteration, int ammount) {

	for (int counter = 0; counter < ammount; counter++) {
		// Copy the first element into a buffer
		for (int i = 0; i < 5; i++) {
			matrix_slice[i][0] = matrix[i][0];
		}
		// Shift all elements left
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 14; j++) {
				matrix[i][j] = matrix[i][j + 1];
			}
		}
		// Copy the last element from the buffer
		for (int i = 0; i < 5; i++) {
			matrix[i][13] = matrix_slice[i][0];
		}

		delay(delay_iteration);
	}
		
}

uint16_t displayMatrix() {
	int i = 0;
	int j = 0;
	uint16_t shift_out = 0xffe0;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 11; j++) {
			if (matrix[i][j]) {
				shift_out |=	1 << (4 - i);	// Map the appropriate Row
				shift_out &= ~( 1 << (15 - j));	// Map the appropriate Column
			}
		}
		shift(shift_out);		// Shift out one row
		shift_out = 0xffe0;		// Initialise next row
	}
	shift(shift_out);
	return shift_out;
}

void shift(uint16_t input) {
	int bit_number = 0;
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

		bit_number++;
	}

	digitalWrite(latch_pin, HIGH);			// Clock the collected data into the storage register to make it visible	
	digitalWrite(latch_pin, LOW);			// (falling edge is needed)
	digitalWrite(data_pin, LOW);			// Take Data Pin low just to be sure.
}

int insertLetter(int letter) {
	uint32_t current_letter = ascii[letter];
	uint8_t current_nibble = 0;
	uint8_t max_width = 0;

	//Serial.print("Current Letter: ");
	//Serial.println(current_letter);
	// Calculate max_width
	for (int i = 0; i < 5; i++) {
		current_nibble = (current_letter >> (16 - 4 * i)) & 0x0f;
		for (int j = 0; j < 4; j++) {
			if ((current_nibble & (1 << j)) && max_width < j) {
				max_width = j+1;
			}
		}
	}

	for (int i = 0; i < 5; i++){
		current_nibble = (current_letter >> (16 - 4 * i)) & 0x0f;
		current_nibble = current_nibble << (4 - max_width);
		//Serial.print("Current Nibble : ");
		//Serial.println(current_nibble);

		for (int j = 0; j < 4; j++)
		{	
			matrix[i][10 + j] = (current_nibble  >> (3 - j)) & 0x01;
			//Serial.print("Current Bit: ");
			//Serial.println(matrix[i][10 + j]);
		}
	}
	return max_width;
}

void insertSpace() {
	for (int i = 0; i < 5; i++)
	{
		matrix[i][13] = 0;
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
			insertSpace();
			letter_width = insertLetter(message[i]);
			shift_Matrix_right(delay_iteration,1);
			insertSpace();
			shift_Matrix_right(delay_iteration,letter_width);
			i++;
		}
}