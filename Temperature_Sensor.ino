#include <Arduino.h>

/*
	Defining an aref voltage does nothing as the voltage is regulated by an internal source
	If a different value is wanted you will have to build an external circuit to supply a reference voltange
 */

 /*
#define aref_voltage 4.08
 */
//Led Pin
#define LED 13
//TEMP Pin
#define tempPin A1
//the resolution is 10 mV / degree centigrade with a
//500 mV offset to allow for negative temperatures
uint8_t tempReading;

// variable used to control the delay of the program
long timer;
uint8_t tDelay = 1000; // time in ms

// variable used to determin the delay in the light
long lTimer;
uint8_t lDelay = 1000;
uint8_t lightMul = 5000; // change this value lower/higher to change how long the light stays on/off
bool lightState = false;

// Calculate differantial of the voltage from a multimeter
// to the arduino
//int8_t dVolt = (0.518 * 1024) / 0.7421777;

void lightSwitch() {
	lightState = !lightState; // flips the state of the light
	digitalWrite(LED, lightState? HIGH: LOW); // turns the light on and off based on the state
}


float getTemp() {
	// Returns temp in c
  double volt = analogRead(tempPin);

  //Serial.println("A_Read: " + (String)volt);
  volt /= 1024.0;

  //Serial.println("1_Conv: " + (String)volt);
  volt *= 3.3;
  Serial.print("Voltage: ");
  Serial.println(volt, 8);

  //volt = map(volt, 0, 1024, )

  return ((volt - 0.5035) * 100);
}

void setup() {
	// To send debugging information via the Serial monitor
	Serial.begin(9600);
	pinMode(LED, OUTPUT);

	// You have to start the pins you want to work with, including pins you want to take
	// measurements from
	pinMode(tempPin, INPUT);

	// if an external volatge refeference is desired change this option
	// https://www.arduino.cc/en/Reference/AnalogReference
	analogReference(DEFAULT);

	// Start the timer
	timer = millis();

	// delay is used to allow all subsystems of the arduino to come online and get into working order
	// not always required but a good practice to get into to
	delay(1000);
}

void loop() {
	long time = millis();
	if (time - timer > tDelay) {
		float temperatureC = getTemp();
		//to degrees ((voltage – 500mV) times 100)
		Serial.print(temperatureC);
		Serial.println(" degrees C");

		// now convert to Fahrenheight
		float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
		Serial.print(temperatureF);
		Serial.println(" degrees F");

		// this will give us an inverse function that will make the light blink faster as the temp increase
		// and slower as it decreases
		lDelay = lightMul * pow(temperatureF, -1);

		timer = millis(); // reset the timer
	}

	if (time - lTimer > lDelay) {
		lightSwitch();
		lTimer = millis();
	}
}
