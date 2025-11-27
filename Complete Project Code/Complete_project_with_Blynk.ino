/*************Blynk templates and modules*************/

#define BLYNK_TEMPLATE_ID "TMPL36iH5oeLd"
#define BLYNK_TEMPLATE_NAME "Baby monitoring system"
#define BLYNK_AUTH_TOKEN "vM-fCob27zrRtoTraelQYMAJ3RceyWm3"

/*************************************************/

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "MAX30105.h"
#include "spo2_algorithm.h"

#include "DHT.h"

/*************** WiFi Credentials **************/

// char ssid[] = "Emerging_iot_5G";
// char pass[] = "ESP32@2023";

char ssid[] = "Airtel_bisw_4895";
char pass[] = "Air@27541";

/*************** OLED SETUP ********************/

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/*************** SENSOR SETUP ******************/

MAX30105 particleSensor;

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define RAIN_PIN 35

// SPO2 variables
uint32_t irBuffer[100], redBuffer[100];
int32_t spo2 = 0, heartRate = 0;
int8_t validSpo2 = 0, validHeartRate = 0;

const uint32_t FINGER_THRESHOLD = 5000;

/*************** BLYNK SEND TIMER **************/

BlynkTimer timer;

/*************************************************
 * Send data to Blynk every 2 seconds
 * (PIN MAPPING FIXED to match your dashboard)
 *
 * V0 -> Heart Rate (BPM)
 * V2 -> SpO2 (%)
 * V4 -> Moisture % (rain)
 * V3 -> Temperature (°C)
 * V1 -> Humidity (%)
 * V5 -> Wetness Alert (0/1)
 * V6 -> Status message
 *************************************************/

void sendToBlynk() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int rainRaw = analogRead(RAIN_PIN);
  int rainPercent = map(rainRaw, 0, 4095, 0, 100);
  if (rainPercent < 0) rainPercent = 0;
  if (rainPercent > 100) rainPercent = 100;

  // IMPORTANT: write to the pins your dashboard expects
  Blynk.virtualWrite(V0, heartRate);        // Heart Rate
  Blynk.virtualWrite(V2, spo2);             // SpO2
  Blynk.virtualWrite(V4, rainPercent);      // Moisture %
  Blynk.virtualWrite(V3, temperature);      // Temperature
  Blynk.virtualWrite(V1, humidity);         // Humidity

  // Wetness alert boolean + status message (V6 will be updated in loop too)
  bool wetAlert = (rainPercent > 60);       // tune threshold if needed
  Blynk.virtualWrite(V5, wetAlert ? 1 : 0); // V5 LED
}

/*************************************************
 * Setup
 *************************************************/

void setup() {
  Serial.begin(115200);
  Wire.begin();

  /******** OLED INIT ********/
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND");
    while (1);
  }
  display.clearDisplay();
  display.display();

  /******** DHT INIT *********/
  dht.begin();

  /******** MAX30102 INIT ********/
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 NOT FOUND!");
    while (1);
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeIR(0x1F);
  particleSensor.setPulseAmplitudeRed(0x1F);

  // ADC attenuation for rain pin (ESP32) - recommended
  analogSetPinAttenuation(RAIN_PIN, ADC_11db);

  /******** BLYNK INIT ********/
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // schedule periodic Blynk updates
  timer.setInterval(2000L, sendToBlynk);

  // send initial values immediately so dashboard isn't empty on open
  sendToBlynk();

  delay(1000);
}

/*************************************************
 * Loop
 *************************************************/
void loop() {
  Blynk.run();
  timer.run();

  // READ SENSORS
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int rainValue = analogRead(RAIN_PIN);
  uint32_t irValue = particleSensor.getIR();

  /************* MAX30102 FINGER LOGIC ************/
  
  if (irValue > FINGER_THRESHOLD) {
    for (int i = 0; i < 100; i++) {
      while (!particleSensor.available())
        particleSensor.check();

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample();
    }

    maxim_heart_rate_and_oxygen_saturation(
      irBuffer, 100, redBuffer,
      &spo2, &validSpo2,
      &heartRate, &validHeartRate
    );

    if (!validHeartRate) heartRate = 0;
    if (!validSpo2) spo2 = 0;

  } else {
    heartRate = 0;
    spo2 = 0;
  }

  /************* SERIAL OUTPUT *************/
  
  Serial.println("-------------------------");
  Serial.print("Temp: "); Serial.println(temperature);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Rain ADC: "); Serial.println(rainValue);

  if (irValue > FINGER_THRESHOLD) {
    Serial.print("Heart Rate: "); Serial.println(heartRate);
    Serial.print("SpO2: "); Serial.println(spo2);
  } else {
    Serial.println("NO FINGER DETECTED");
    Serial.println("Heart Rate: 0");
    Serial.println("SpO2: 0");
  }
  Serial.println("-------------------------");

  /************* OLED OUTPUT *************/
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("Health Monitoring");
  display.println("---------------------");

  display.print("Temp: "); display.print(temperature); display.println(" C");
  display.print("Humidity: "); display.print(humidity); display.println(" %");
  display.print("Rain ADC: "); display.println(rainValue);

  if (irValue > FINGER_THRESHOLD) {
    display.print("Heart Rate: ");
    display.print(heartRate);
    display.println(" BPM");

    display.print("SpO2: ");
    display.print(spo2);
    display.println(" %");
  } else {
    display.println("No Finger Detected");
    display.println("Heart Rate: 0");
    display.println("SpO2: 0");
  }

  /*************** MESSAGE LOGIC BLOCK ***************/
  // Builds status strings based on current sensor values and sends to Serial + Blynk (V6)

  String healthMessage = "";
  String wetMessage = "";
  String tempMessage = "";
  String finalMessage = "";

  // 1. HEART + SPO2 ABNORMAL check (tune thresholds as needed)
  bool heartAbnormal = (heartRate < 60 || heartRate > 140);
  bool spo2Abnormal  = (spo2 > 0 && spo2 < 92);
  
  // NO FINGER PLACED CONDITION
  if (heartRate == 0 && spo2 == 0 && temperature < 38.0) {
    healthMessage = "No Finger Placed";
  }
  // FINGER PLACED CONDITION
  else if (heartAbnormal || spo2Abnormal) {
    healthMessage = "Health issue alert due to Heart & SpO2";
  } else {
    healthMessage = "Normal";
  }

  // 2. RAIN SENSOR (WET/DRY) - tune threshold if you calibrated differently
  int rainPercent = map(rainValue, 0, 4095, 0, 100);
  if (rainPercent < 0) rainPercent = 0;
  if (rainPercent > 100) rainPercent = 100;
  if (rainPercent > 50) {
    wetMessage = "Dry";
  } else {
    wetMessage = "Wet";
  }

  // 3. TEMPERATURE HIGH
  if (temperature > 38.0) {   // high temperature threshold (tune as needed)
    tempMessage = "Alert! High Temperature";
  } else {
    tempMessage = "Temperature Normal";
  }

  // Final combined message
  finalMessage = healthMessage + " | " + wetMessage + " | " + tempMessage;

  // Print messages to Serial
  Serial.println("------ STATUS MESSAGES ------");
  Serial.println("Health Status: " + healthMessage);
  Serial.println("Wetness Status: " + wetMessage);
  Serial.println("Temperature Status: " + tempMessage);
  Serial.println("Combined Message: " + finalMessage);
  Serial.println("--------------------------------");

  // Send final message to Blynk (V6)
  Blynk.virtualWrite(V6, finalMessage);

  display.display();
  delay(1000);

}








