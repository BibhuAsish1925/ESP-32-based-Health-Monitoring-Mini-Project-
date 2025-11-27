#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

typedef MAX30105 MAX30102; // alias so messages can say MAX30102
MAX30102 particleSensor;

#define SDA_PIN 21
#define SCL_PIN 22

void setup(){
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  delay(100);

  Serial.println("MAX30102 test starting...");
  if (!particleSensor.begin()) {
    Serial.println("MAX30102 not found. Check wiring/power (3.3V).");
    while(1){ delay(1000); }
  }
  Serial.println("MAX30102 found.");
  particleSensor.setup(); // defaults
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeIR(0x0A);
}

void loop(){
  // Read if available
  if (particleSensor.available()) {
    long red = particleSensor.getRed();
    long ir  = particleSensor.getIR();
    Serial.printf("IR=%ld RED=%ld\n", ir, red);

    static long lastBeat = 0;
    if (checkForBeat(ir)) {
      long now = millis();
      long delta = now - lastBeat;
      lastBeat = now;
      if (delta > 0) {
        int bpm = (int)(60000.0 / delta);
        Serial.printf("Beat! BPM=%d\n", bpm);
      }
    }
  } else {
    // not available: fetch some samples (non-blocking)
    delay(20);
  }
}
