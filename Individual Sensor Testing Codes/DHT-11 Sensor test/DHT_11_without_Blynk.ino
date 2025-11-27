#include "DHT.h"

// Define the pin where the DHT11 is connected
#define DHTPIN 15      // You can change this to the pin you connected

// Define the type of DHT sensor
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("DHT11 Sensor Test");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Default is Celsius
  float temperatureF = dht.readTemperature(true); // Fahrenheit

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature) || isnan(temperatureF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index (optional)
  float heatIndexC = dht.computeHeatIndex(temperature, humidity, false);
  float heatIndexF = dht.computeHeatIndex(temperatureF, humidity);

  // Print results
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C ");
  Serial.print(temperatureF);
  Serial.print(" °F\t");

  Serial.print("Heat index: ");
  Serial.print(heatIndexC);
  Serial.print(" °C ");
  Serial.print(heatIndexF);
  Serial.println(" °F");
}