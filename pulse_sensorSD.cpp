#include <SPI.h>
#include <SD.h>

#define PROCESSING_VISUALIZER 1
#define SERIAL_PLOTTER  2

//  Variables
int pulsePin = A2;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

static int outputType = SERIAL_PLOTTER;

uint32_t timer = millis();

File data;

void save_data(float BPM, float IBI, float Signal) {
  data = SD.open("data.csv", FILE_WRITE);

  data.print("Beats Per Minute");
  data.print(',');
  data.print("IBI");
  data.print(',');
  data.println("Signal");
  data.print(',');
  data.print(BPM);
  data.print(',');
  data.print(IBI);
  data.print(',');
  data.println(Signal);
  
  data.close();
}

void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
   // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
   // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
  //analogReference(EXTERNAL);
Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  data = SD.open("data.csv", FILE_WRITE);

  if (data) {
    Serial.println("data.csv exists and is now closed");
    data.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data.csv");
  }
}


//  Where the Magic Happens
void loop(){

    serialOutput() ;

  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
        QS = false;
        Serial.print("Beat Per Minute");
        Serial.print(',');
        Serial.print("IBI");
        Serial.print(',');
        Serial.println("Signal");
        Serial.print(BPM);
        Serial.print(',');
        Serial.print(IBI);
        Serial.print(',');
        Serial.println(Signal);
       
        save_data(BPM,IBI,Signal);
  }
  delay(400);                             //  take a break
}
