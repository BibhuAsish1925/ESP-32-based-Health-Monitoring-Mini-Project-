#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "MAX30105.h"
#include "spo2_algorithm.h"

#include "DHT.h"

// ---------------- OLED SETUP ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- SENSOR SETUP ----------------
MAX30105 particleSensor;

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define RAIN_PIN 35   // Analog Rain Sensor Pin

uint32_t irBuffer[100], redBuffer[100];
int32_t spo2 = 0, heartRate = 0;
int8_t validSpo2 = 0, validHeartRate = 0;

// Finger detection threshold
const uint32_t FINGER_THRESHOLD = 5000;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED NOT FOUND!");
    while (1);
  }
  display.clearDisplay();
  display.display();

  // Initialize DHT
  dht.begin();

  // Initialize MAX30102
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 NOT FOUND!");
    while (1);
  }

  particleSensor.setup();
  particleSensor.setPulseAmplitudeIR(0x1F);
  particleSensor.setPulseAmplitudeRed(0x1F);

  delay(1000);
}

void loop() {

  // ------------ Read Temperature + Humidity ------------
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // ------------ Read Rain Sensor ------------
  int rainValue = analogRead(RAIN_PIN);

  // ------------ Read MAX30102 IR Value ------------
  uint32_t irValue = particleSensor.getIR();

  // ------------ Handle MAX30102 Based on Finger Presence ------------
  if (irValue > FINGER_THRESHOLD) {

    // Collect IR & RED samples
    for (int i = 0; i < 100; i++) {
      while (!particleSensor.available()) {
        particleSensor.check();
      }
      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample();
    }

    // Compute HR + SpO2
    maxim_heart_rate_and_oxygen_saturation(
      irBuffer, 100, redBuffer,
      &spo2, &validSpo2,
      &heartRate, &validHeartRate
    );

    if (!validHeartRate) heartRate = 0;
    if (!validSpo2) spo2 = 0;

  } else {
    // No finger → but keep screen constant
    heartRate = 0;
    spo2 = 0;
  }

  // ---------------- SERIAL OUTPUT ----------------
  Serial.println("------------------------");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Rain ADC: "); Serial.println(rainValue);

  if (irValue > FINGER_THRESHOLD) {
    Serial.print("Heart Rate: "); Serial.println(heartRate);
    Serial.print("SpO2: "); Serial.println(spo2);
  } else {
    Serial.println("MAX30102: No Finger");
    Serial.println("Heart Rate: 0");
    Serial.println("SpO2: 0");
  }
  Serial.println("------------------------");


  // ---------------- OLED OUTPUT ----------------
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.println("Baby Monitoring System");
  display.println("----------------------");

  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.print("Rain ADC: ");
  display.println(rainValue);

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

  display.display();
  delay(400); // smooth refresh
}