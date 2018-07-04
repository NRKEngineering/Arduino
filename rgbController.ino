/*
RGB LED Controller - ARDUINO

DESCRIPTION:
	Cycles an RGB LED through the different colours
AUTHOR:
	Nicholas Kent

DATE:
	July 2018
	
ARDUINO TYPE:
	Uno

*/

// Constants - assign to PWM outputs
const int redPin = 7;
const int greenPin = 6;
const int bluePin = 5;

// Variables


void setup() 
{	// Set pin modes
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
}

void loop() 
{	
	unsigned int rgbColour[3];

	// Sart with red
	rgbColour[0] = 255;
	rgbColour[1] = 0;
	rgbColour[2] = 0;
	
	// Choose colours to change
	for(int decColour = 0; decColour < 3; decColour+=1)
	{	int incColour = decColour ==2 ? 0 : decColour + 1;

		for(int i = 0; i < = 255; i++)
		{	rgbColour[decColour] -= 1;
			rgbColour[incColour] += 1;
		}
	}
}

// Changes the PWM signal to the LED
void setRGBColour(unsigned int red, unsigned int  green, unsigned int  blue)
{	analogWrite(redPin, red);
	analogWrite(greenPin, green);
	analogWrite(bluePin, blue);
}
