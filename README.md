# 🫀 Health Monitoring System (ESP32-Based IoT Project)

A complete **IoT-based Health Monitoring System** developed as part of an Engineering Project.
The system continuously monitors **Heart Rate**, **SpO₂**, **Temperature**, **Humidity**, and **Wetness**, displaying results on **OLED**, **Serial Monitor**, and **Blynk IoT Dashboard** with intelligent alert messages.

---

## 📌 **Project Overview**

This project uses ESP32 and multiple sensors to create a smart health monitoring solution.
It provides real-time data, alerts, and wireless monitoring via Blynk IoT.

---

## 🎥 **Project Video**

You can paste your project demo video link below.
Once added, the video text will turn **blue & clickable** (just like the screenshot you shared):

### 👉 [PROJECT VIDEO: Click to Watch](#)

*(Replace the `#` with your YouTube or Drive video link)*

---

## 🛠️ **Hardware Used**

| Component            | Purpose                  |
| -------------------- | ------------------------ |
| ESP32 Dev Board      | Main controller          |
| MAX30102             | Heart Rate & SpO₂ sensor |
| DHT11                | Temperature & Humidity   |
| Rain Sensor (Analog) | Wetness detection        |
| OLED SSD1306         | Status display           |
| PCB Board & wires    | Connections              |

---

## 📡 **System Features**

### ❤️ Heart & Oxygen Monitoring

* Heart Rate (BPM)
* SpO₂ (% Oxygen Saturation)
* Auto-finger detection
* Real-time display on OLED + Blynk

### 🌡️ Temperature & Humidity Monitoring

* Ambient temperature
* Humidity percentage

### ☔ Wetness Detection

* Detects moisture level
* Converts ADC → Percentage

### ⚠️ Smart Alerts

Displays intelligent messages based on sensor readings:

* **Health issue alert due to Heart & SpO₂**
* **Wet / Dry Alert**
* **High Temperature Warning**
* **Normal Condition**

Alerts appear on:

* Serial Monitor
* OLED
* Blynk Dashboard

---

## 📲 **Blynk Virtual Pin Mapping**

| Function                | V-Pin |
| ----------------------- | ----- |
| Heart Rate              | V0    |
| Humidity                | V1    |
| SpO₂                    | V2    |
| Temperature             | V3    |
| Moisture %              | V4    |
| Wetness Alert           | V5    |
| Combined Status Message | V6    |

---

## 📚 **Required Libraries**

Install these from Arduino Library Manager:

* Blynk
* Adafruit SSD1306
* Adafruit GFX
* DHT Sensor Library
* SparkFun MAX3010x Library
* Wire

---

## ▶️ **How to Run**

1. Install required libraries
2. Enter WiFi SSID & Password
3. Add Blynk Template ID, Name & Auth Token
4. Upload code to ESP32
5. Open Serial Monitor @ 115200
6. Check OLED and Blynk Dashboard

---

## 🔮 **Future Scope**

* Push Notifications (SMS/Email)
* Firebase cloud storage
* Health history tracking
* Buzzer alert system

---

## 📄 License

This project is open-source under the **MIT License**.

