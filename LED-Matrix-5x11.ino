#include "global_def.h"
#include "functions.h"
#include <TimerOne.h>


 //#define DEBUG

void setup() {

 	//Serial.begin(115200);

	Timer1.initialize(5000);					// initialize timer1, and set a 5 milli second period
	Timer1.attachInterrupt(updateDisplay);		// attaches callback() as a timer overflow interrupt

  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
 
  for (int i = 0; i < 5; i++) {
	  for (int j = 0; j < 11; j++) {
		  matrix[i][j] = false;
	  }
  }  
}

void updateDisplay() {
	iteration++;
	displayMatrix();
}

void loop() {
	/*for (int i = 30; i < 128; i++) {
		
		insertLetter(i, 200);
		insertLetter(0, 200);
	}*/
	displayMessage("ES FUNKTIONIERT!  ",150);
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



