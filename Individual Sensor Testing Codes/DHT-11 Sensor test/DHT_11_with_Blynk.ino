#define BLYNK_TEMPLATE_ID "TMPL36iH5oeLd"
#define BLYNK_TEMPLATE_NAME "Baby monitoring system"
#define BLYNK_AUTH_TOKEN "hPRXntJW8dG4LefTB-GdRX1FFj5WxFjk"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char ssid[] = "Emerging_iot_5G";
char pass[] = "ESP32@2023";

// char ssid[] = "Airtel_bisw_4895";
// char pass[] = "Air@27541";

#define DHTPIN 15      // GPIO2 (D4 on ESP32 boards)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastSend = 0;

String lastMessage = "";

void setup() {
  Serial.begin(115200);
  Serial.println("Starting DHT11 + Blynk...");

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  if (millis() - lastSend < 2000) return; 
  lastSend = millis();

  float hum = dht.readHumidity();
  float temp = dht.readTemperature(); // Celsius

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT11!");
    return;
  }

  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" °C  Humidity: "); Serial.print(hum);
  Serial.println(" %");

  // --- SEND TO BLYNK ---
  Blynk.virtualWrite(V3, temp);  // Temperature gauge

  // --- SEND MESSAGE TO V6 BASED ON TEMPERATURE ---
  String msg;

  if (temp < 20) msg = "Too Cold!";
  else if (temp <= 32) msg = "Normal Temperature";
  else msg = "High Temperature!";

  if (msg != lastMessage) {   // avoid spamming
    Blynk.virtualWrite(V6, msg);
    lastMessage = msg;
  }
}