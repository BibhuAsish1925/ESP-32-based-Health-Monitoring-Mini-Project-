#define BLYNK_TEMPLATE_ID "TMPL36iH5oeLd"
#define BLYNK_TEMPLATE_NAME "Baby monitoring system"
#define BLYNK_AUTH_TOKEN "5tJqs-4yRi9z4YNxnEIQ1sZsswbhOCRw"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Airtel_bisw_4895";
char pass[] = "Air@27541";

#define RAIN_A0 35
#define RAIN_D0 15

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(RAIN_D0, INPUT);
}

void loop() {
  Blynk.run();

  int analogVal = analogRead(RAIN_A0);
  int moisturePercent = map(analogVal, 0, 4095, 100, 0);  
  int wetAlert = digitalRead(RAIN_D0);

  Serial.print("Moisture: "); Serial.print(moisturePercent); Serial.println("%");
  Serial.print("Wet Alert: "); Serial.println(wetAlert);

  Blynk.virtualWrite(V4, moisturePercent);
  Blynk.virtualWrite(V5, wetAlert);

  delay(800);
}