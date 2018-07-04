/*
TRAFFIC LIGHT SIMULATOR - ARDUINO

DESCRIPTION:
	Simulates the operatoration of a set of traffic lights
	for a T intersection. A hall effect sensor provides 
	vehicle detection.
	
AUTHOR:
	Nicholas Kent

DATE:
	July 2018
	
ARDUINO TYPE:
	Uno

*/

// Constants
const int hallIn = 			 2;		// Hall Effect input pin
const int ledRedMainOut = 	 8;		// Led output Main Street Red
const int ledYellowMainOut = 9;		// Led output Main Street Yellow
const int ledGreenMainOut =  10;	// Led output Main Street Green
const int ledRedSideOut = 	 11;	// Led output Side Street Red
const int ledYellowSideOut = 12;	// Led output Side Street Yellow
const int ledGreenSideOut =  13;	// Led output Side Street Green

// Variables
int hallState = 0;					// Stores current state of sensor

void setup() 
{	// Set the pin modes
	pinMode(hallIn, INPUT);				// Hall sensor input
	pinMode(ledRedMainOut, OUTPUT);		// led output
	pinMode(ledYellowMainOut, OUTPUT);	// led output
	pinMode(ledGreenMainOut, OUTPUT);	// led output
	pinMode(ledRedSideOut, OUTPUT);		// led output
	pinMode(ledYellowSideOut, OUTPUT);	// led output
	pinMode(ledGreenSideOut, OUTPUT);	// led output
}

void loop() 
{	// Read state of hall effect input
	hallState = digitalRead(hallIn);
	
	if(hallIn == LOW && ledGreenMainOut == HIGH)
	{	// Start Main Light sequence
		// Set Main Yellow for four seconds
		digitalWrite(ledYellowMainOut, HIGH);
		digitalWrite(ledGreenMainOut, LOW);
		delay(4000);
		
		// Set Main red for two seconds
		digitalWrite(ledYellowMainOut, LOW);
		digitalWrite(ledRedMainOut, HIGH);
		delay(2000);
		
		// Set Side Green for ten seconds
		digitalWrite(ledRedSideOut, LOW);
		digitalWrite(ledGreenSideOut, HIGH);
		delay(10000);
	}
	else
	{	// Set Side Light Sequence
		// Set Side light yellow for four seconds
		digitalWrite(ledYellowSideOut, HIGH);
		digitalWrite(ledGreenSideOut, LOW);
		delay(4000);
		
		// Set Side red for two seconds
		digitalWrite(ledYellowSideOut, LOW);
		digitalWrite(ledRedSideOut, HIGH);
		delay(2000);
		
		// Set Side Green for ten seconds
		digitalWrite(ledRedMainOut, LOW);
		digitalWrite(ledGreenMainOut, HIGH);
		delay(10000);
	}
}