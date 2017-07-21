#include <Arduino.h>

#define pulsePin A1
#define pulseThresh 550
#define maxHeartRate 250
#define pMSDelay

// ((seconds per min) * ms per second)
uint8_t pDelay = (60 * 1000) / 250;

long pTimer;
long pMSTimer;
long pMinTimer;
long timeDiffAvg = 0;
uint8_t beats = 0;
uint8_t realBPM = 0;
uint8_t avgBPM = 0;
long avgTime = 0;

void measureIfBeatHapped() {
  uint8_t pulse = analogRead(pulsePin);

  if (pulse >= pulseThresh)
    beats++;

  pTimer = millis();
  pMSTimer = pTimer;
}

uint8_t calRealBPM() {
  pMinTimer = millis();
  realBPM = beats;
  beats = 0;
  return realBPM;
}

float calAvgBPM(long lastBeat, long currentBeat) {
  long diff = currentBeat - lastBeat;

  if (timeDiffAvg != 0)
    timeDiffAvg = (timeDiffAvg + diff) / 2.0;
  else
    timeDiffAvg = diff;

  return (1000 / timeDiffAvg) * 60.0;
}
