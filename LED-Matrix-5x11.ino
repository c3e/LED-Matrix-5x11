#include "global_def.h"
#include "functions.h"
#include <TimerOne.h>


 //#define DEBUG

void setup() {

 	//Serial.begin(115200);

	Timer1.initialize(3000);					// initialize timer1, and set a 3 milli second period
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
	
	displayMessage("ES FUNKTIONIERT!  ",50);

	for (int i = 0; i < 20; i++) {
		insertLetter(i, 100);
	}

	/*for (int i = 0; i < 100; i++) {
		insertLetter(i+27, i/10);
		
	}*/
}



