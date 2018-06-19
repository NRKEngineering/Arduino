/*
Arduino Hall Effect Sensor
This program alows reading the output of a 3144E 
hall effect sensor (Switch type sensor)

Arduino type - Nano

*/

// Constants
hallIn = 2;		// Set input pin
ledOut = 13;	// Led output

// Variables
hallState = 0;	// Stores current state of sensor

void setup() 
{	// Set the pin modes
	pinMode(hallIn, INPUT);		// Hall sensor input
	pinMode(ledOut, OUTPUT);	// led output
}



void loop() 
{	// Read state of hall effect input
	hallState = digitalRead(hallIn);
	
	if(hallIn == LOW)
	{	// Turn on LED
		digitalWrite(ledPin, HIGH);
		
	}
	else
	{	// Turn off LED
		digtialWrite(ledPin, LOW);
	}
}