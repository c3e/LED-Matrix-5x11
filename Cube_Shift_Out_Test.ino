#include "global_def.h"
#include "functions.h"
#include <TimerOne.h>


 //#define DEBUG

void setup() {

 	//Serial.begin(9600);

	Timer1.initialize(5000);		// initialize timer1, and set a 10 milli second period
	Timer1.attachInterrupt(updateDisplay);		// attaches callback() as a timer overflow interrupt

  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
 
	
  for (int i = 0; i < 5; i++) {
	  for (int j = 0; j < 11; j++) {
		  matrix[i][j] = false;
	  }
  }
  /**
  matrix[0][0] = true;
  matrix[1][1] = true;
  matrix[2][2] = true;
  matrix[3][3] = true;
  matrix[4][4] = true;
  matrix[3][5] = true;
  matrix[2][6] = true;
  matrix[1][7] = true;
  matrix[0][8] = true;
  matrix[1][9] = true;
  */
  matrix[2][10] = true;
  matrix[3][11] = true;
  matrix[4][12] = true;
  matrix[3][13] = true;
    
}

void updateDisplay() {
	iteration++;
	displayMatrix();
}

void loop() {

	displayMessage("GAMMLA IST DER BESTE ", 100);
	/*
	if (iteration % 400 == 0) {
		insertLetter(letter);
		shift_Matrix_right(1);
		insertSpace();
		letter++;

		Serial.println(letter);
	}
	*/

}



