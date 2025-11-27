#define BLYNK_TEMPLATE_ID "TMPL36iH5oeLd"
#define BLYNK_TEMPLATE_NAME "Baby monitoring system"
#define BLYNK_AUTH_TOKEN "vrxzQXkemuV1PibWzA53wxmIOGqZTOQx"

#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

char ssid[] = "Airtel_bisw_4895";
char pass[] = "Air@27541";

// OLED configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// I2C pins (explicit)
#define SDA_PIN 21
#define SCL_PIN 22

// last shown message (avoid spamming same text repeatedly)
String lastShown = "";

void showMessageOnOLED(const String &msg) {
  // Trim message to fit (max ~ 4 lines * 21 chars ~ 84 chars) - adjust if you use different font/size
  String toShow = msg;
  if (toShow.length() > 80) toShow = toShow.substring(0, 80) + "...";

  // Avoid re-sending and re-printing identical message repeatedly
  if (toShow == lastShown) return;
  lastShown = toShow;

  // Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  // Split into lines ~20 chars per line for readability
  const int LINE_LEN = 20;
  int start = 0;
  while (start < (int)toShow.length()) {
    String line = toShow.substring(start, min(start + LINE_LEN, (int)toShow.length()));
    display.println(line);
    start += LINE_LEN;
  }
  display.display();

  // Send to Blynk V6 (App → Device mapping)
  Blynk.virtualWrite(V6, toShow);

  // Also log to serial
  Serial.print("[OLED] ");
  Serial.println(toShow);
}

// Blynk handler: when App writes to V6, show on OLED
BLYNK_WRITE(V6) {
  String s = param.asString();
  Serial.print("[BLYNK -> V6] Received: ");
  Serial.println(s);
  showMessageOnOLED(s);
}

void setup() {
  Serial.begin(115200);
  delay(50);
  Serial.println("OLED <-> Blynk V6 bridge starting...");

  // Initialize I2C on chosen pins
  Wire.begin(SDA_PIN, SCL_PIN);
  // Init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (1) delay(1000);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Show boot message (this will also send to Blynk V6)
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // start Blynk early so virtualWrite will work
  showMessageOnOLED("Booting...");

  // Short pause then show ready
  delay(600);
  showMessageOnOLED("OLED ready. Send text from Blynk V6 or call showMessageOnOLED(msg).");
}

void loop() {
  Blynk.run();

  // keep loop light
  delay(10);
}