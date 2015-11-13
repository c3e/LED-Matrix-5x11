#include "global_def.h"
#include "functions.h"
#include <TimerOne.h>


 //#define DEBUG

void setup() {

 	//Serial.begin(115200);

	configure_pinning(7,8,9);
	matrix_init();
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



