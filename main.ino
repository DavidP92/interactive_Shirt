#include "temp.cpp"
#include "pulse_sensor.cpp"

#define msPerMin 60000
//Led Pin
#define LED 13

// variable used to determin the delay in the light
long lTimer;
uint8_t lDelay = 1000;
bool lightState = false;

void lightSwitch() {
	lightState = !lightState; // flips the state of the light
	digitalWrite(LED, lightState? HIGH: LOW); // turns the light on and off based on the state
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
  pTimer = timer;
  pMinTimer = timer;
  pMSTimer = timer;

	// delay is used to allow all subsystems of the arduino to come online and get into working order
	// not always required but a good practice to get into to
	delay(1000);
}

void loop() {
	long _time = millis();

  // This if statement is used to calculate the real BPM
  if () {
    calRealBPM();
  }

  if ()
    if () {
      
    }

  // END editing here

	if (_time - timer > tDelay) {
		float temperatureC = getTemp();
		//to degrees ((voltage – 500mV) times 100)
		Serial.print(temperatureC);
		Serial.println(" degrees C");

		// now convert to Fahrenheight
		float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
		Serial.print(temperatureF);
		Serial.println(" degrees F");

		timer = millis(); // reset the timer
	}
}
