#include <Arduino.h>

/*
	Defining an aref voltage does nothing as the voltage is regulated by an internal source
	If a different value is wanted you will have to build an external circuit to supply a reference voltange
 */

 /*
#define aref_voltage 4.08
 */
//TEMP Pin
#define tempPin A2
//the resolution is 10 mV / degree centigrade with a
//500 mV offset to allow for negative temperatures
uint8_t tempReading;

// variable used to control the delay of the program
long timer;
uint8_t tDelay = 1000; // time in ms

// Calculate differantial of the voltage from a multimeter
// to the arduino
//int8_t dVolt = (0.518 * 1024) / 0.7421777;


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
