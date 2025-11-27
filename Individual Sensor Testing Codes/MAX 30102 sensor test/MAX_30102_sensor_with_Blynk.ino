#define BLYNK_TEMPLATE_ID "TMPL36iH5oeLd"
#define BLYNK_TEMPLATE_NAME "Baby monitoring system"
#define BLYNK_AUTH_TOKEN "8dbjSKcA-pHIjP1-IF51rtRpj909M_jG"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 sensor;

char ssid[] = "Airtel_bisw_4895";
char pass[] = "Air@27541";

bool fingerPresent = false;   // NEW FLAG

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  if (!sensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 Not Found");
    while (1);
  }

  sensor.setup();
  sensor.setPulseAmplitudeRed(0x0A);
  sensor.setPulseAmplitudeIR(0x0A);
}

void loop() {
  Blynk.run();

  long irValue = sensor.getIR();

  // ---------- FINGER NOT PRESENT ----------
  if (irValue < 5000) {
    if (fingerPresent == true) {
      Serial.println("Finger removed");
      fingerPresent = false;
    }

    // Print only once when finger is removed
    static bool messageShown = false;
    if (!messageShown) {
      Serial.println("Place finger");
      messageShown = true;
    }

    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V2, 0);
    return;
  }

  // ---------- FINGER PRESENT ----------
  if (!fingerPresent) {
    Serial.println("Finger detected");
    fingerPresent = true;
  }

  // Reset the "Place finger" printed flag
  static bool messageShown = false;
  messageShown = false;

  // Fake values (replace later with algorithm)
  int heartRate = random(80,120);
  int spo2 = random(90,99);

  Serial.print("HR: "); Serial.println(heartRate);
  Serial.print("SpO2: "); Serial.println(spo2);

  Blynk.virtualWrite(V0, heartRate);
  Blynk.virtualWrite(V2, spo2);

  delay(1000);
}