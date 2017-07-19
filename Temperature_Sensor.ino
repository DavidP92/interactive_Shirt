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
int tempReading;

// variable used to control the delay of the program
long timer;
uint8_t tDelay = 250; // time in ms

// variable used to determin the delay in the light
long lTimer;
uint8_t lDelay = 1000;
uint8_t lightMul = 5000; // change this value lower/higher to change how long the light stays on/off
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
	
	// delay is used to allow all subsystems of the arduino to come online and get into working order
	// not always required but a good practice to get into to
	delay(1000);
}

void loop() {
	long time = millis();
	if (time - timer > tDelay) {
	  
		// put your main code here, to run repeatedly:
		tempReading = analogRead(tempPin);  //Get a temperaure reading from the temp sensor
		Serial.print("Temp reading = "); // allow the temp reading to appear in debugging > Serial Monitor
		Serial.print(tempReading);     // the raw analog reading
		// converting that reading to voltage, which is based off the reference voltage
		
		// The following does not work as would be expected without an external voltage reference
		// Change to use the internal arduino reference voltage
		// float voltage = tempReading * aref_voltage;
		
		// formula to conveert an analog reading into voltage using the internal arduino reference voltage
		float voltage = (tempPin * 5.0) / 1024.0; // change number inside to reference voltage
		
		//Print out Voltage
		Serial.print(" – ");
		Serial.print(voltage);
		Serial.println(" volts");

		// now print out the temperature
		//converting from 10 mv per degree with 500 mV offset
		float temperatureC = (voltage - 0.5) * 100;
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
