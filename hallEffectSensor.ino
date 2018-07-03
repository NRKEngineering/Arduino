/*
HALL EFFECT SENSOR ALARM - ARDUINO

DESCRIPTION:
	This program alows reading the output of a 3144E 
	hall effect sensor (Switch type sensor) which switches
	on and off an led and buzzer.

AUTHOR:
	Nicholas Kent

DATE:
	July 2018
	
ARDUINO TYPE:
	Nano

*/

// Constants
const int hallIn = 2;			// Hall Effect input pin
const int ledOut = 13;			// Led output
const int buzzerOut = 9;		// Buzzer output

// Variables
int hallState = 0;				// Stores current state of sensor
int buzzTone = 1000;			// Buzzer tone in Hz

void setup() 
{	// Set the pin modes
	pinMode(hallIn, INPUT);		// Hall sensor input
	pinMode(ledOut, OUTPUT);	// led output
	pintMode(buzzerOut, OUTPUT);// Buzzer output
}



void loop() 
{	// Read state of hall effect input
	hallState = digitalRead(hallIn);
	
	if(hallIn == LOW)
	{	// Turn on LED and buzzer
		digitalWrite(ledPin, HIGH);
		tone(buzzerOut, buzzTone);
		// Buzz for one second
		delay(1000);
		// Turn off buzzer for one second
		noTone(buzzerOut);
		delay(1000);
	}
	else
	{	// Turn off LED and buzzer
		digtialWrite(ledPin, LOW);
		noTone(buzzerOut);
	}
}