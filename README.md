# 🫀 Health Monitoring System (ESP32-Based IoT Project)

A complete **IoT-based Health Monitoring System** developed as part of an Engineering Project.
The system continuously monitors **Heart Rate**, **SpO₂**, **Temperature**, **Humidity**, and **Skin Dryness**, displaying results on **OLED**, **Serial Monitor**, and **Blynk IoT Dashboard** with intelligent alert messages.

---

## 📌 **Project Overview**

This project uses ESP32 and multiple sensors to create a smart health monitoring solution.
It provides real-time data, alerts, and wireless monitoring via Blynk IoT.

## 🎥 **Project Video**

### 👉 [PROJECT VIDEO: Click to Watch](https://drive.google.com/file/d/1GC28OuMpl1OsVApRBo14bNPF3sxIeKYS/view?usp=sharing)

---

### 📦 **Hardware Components Used**

| Component | Quantity | Purpose |
|----------|----------|---------|
| **ESP32 Dev Module** | 1 | Main microcontroller with WiFi support |
| **MAX30102 Pulse Oximeter & Heart Rate Sensor** | 1 | Measures Heart Rate & SpO₂ |
| **DHT11 Temperature & Humidity Sensor** | 1 | Measures temperature & humidity |
| **Rain Sensor (Analog Type)** | 1 | Detects moisture/wetness |
| **OLED Display (SSD1306, I2C)** | 1 | Real-time visual display |
| **Power Cable (USB)** | 1 | Power + Programming |
| **Connecting Option 1:** Breadboard + Jumper Wires | — | Common prototyping method |
| **Connecting Option 2 (Used in This Project):** PCB Board + Header Pins + Wires | — | Stronger, permanent connection |

> **Note:**  
> This project was finally assembled using a **PCB board with header pins**, as it provides a more durable and secure wiring structure compared to a breadboard setup.

---

## 🔌 **I/O Pin Configuration (ESP32 Pin Mapping)**  

| Component / Module           | Signal / Function     | ESP32 Pin | Notes |
|-----------------------------|------------------------|-----------|-------|
| **DHT11 Sensor**            | Data                  | **GPIO 15** | Reads Temperature & Humidity |
| **Rain Sensor (Analog)**    | Analog Output         | **GPIO 35 (ADC1_CH7)** | Wetness detection |
| **MAX30102 Sensor**         | SDA                   | **GPIO 21** | I²C Data |
|                             | SCL                   | **GPIO 22** | I²C Clock |
|                             | VIN                   | 3.3V / 5V | Power |
|                             | GND                   | GND | Ground |
| **OLED Display (SSD1306)**  | SDA                   | **GPIO 21** | Shared I²C line |
|                             | SCL                   | **GPIO 22** | Shared I²C line |
|                             | VCC                   | 3.3V | Power |
|                             | GND                   | GND | Ground |
| **ESP32 Power**             | USB / 5V              | — | Main power input |
| **Other Notes**             | OLED I²C Address      | 0x3C | Default |
|                             | I²C Speed             | 400 kHz | FAST Mode |

---

### 🧩 **Quick Pin Summary**
- **I²C Bus (shared by MAX30102 + OLED):**  
  - SDA → **GPIO 21**  
  - SCL → **GPIO 22**

- **Analog Input:**  
  - Rain Sensor → **GPIO 35**

- **Digital Input:**  
  - DHT11 Data → **GPIO 15**

---

### 🔧 **Build Options**

#### ✔ **Option A – Breadboard + Jumper Wires**
- Best for prototyping  
- Easy to modify  
- Flexible layout but less durable  

#### ✔ **Option B – PCB Board + Header Pins + Wires (Used in This Project)**  
- Strong connections  
- Clean and compact layout  
- Suitable for final demonstration  
- Reduces loose-connection issues  

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

## 📡 **System Features**

### ❤️ Heart & Oxygen Monitoring

* Heart Rate (BPM)
* SpO₂ (% Oxygen Saturation)
* Auto-finger detection
* Real-time display on OLED + Blynk
* Remember - if (heartRate == 0 && spo2 == 0) => No Finger Placed, else if ((heartRate < 60 || heartRate > 140) && (spo2 > 0 && spo2 < 92)) => Health issue alert due to Heart & SpO2; Or else => Normal

### 🌡️ Temperature & Humidity Monitoring

* Ambient temperature
* Humidity percentage
* Remember - if (temperature > 38.0) => Alert! High Temperature, else => Temperature Normal (can be configured for body temperature)

### ☔ Skin Dryness level

* Detects moisture level
* Converts ADC → Percentage
* Remember - if (>50%) then skin is Dry, else skin is wet (can be configured)

### ⚠️ Smart Alerts

Displays intelligent messages based on sensor readings:

* **Health issue alert due to Heart & SpO₂**
* **Wet / Dry Alert**
* **High Temperature Warning**
* **Normal Condition**

Alerts appear on:

* Blynk Dashboard
* OLED
* Serial Monitor

---

## 🖼️ Image Gallery

### 🔌 Circuit Diagram and Hardware Setup

<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/9b6b3c69-12a1-4105-b28b-bd363c3ae034" alt="Serial Monitor output - 1" width="540"/><br/>
      <small>Circuit Diagram </small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/d2518f8e-00d4-49b9-94fa-383a0b887049" alt="Serial Monitor output - 2" width="540"/><br/>
      <small>Hardware Setup </small>
    </td>
  </tr>
</table>

---

## 📊 Outputs (Blynk Dashboard, OLED, Serial Monitor, Sensor values)

### 1) Hardware Simulation and OLED display
<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/f0ddb09b-4025-4a77-a151-89c06fb7ba36" alt="Hardware Simulation - 1" width="420"/><br/>
      <small>Hardware Simulation 1</small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/cd8b3111-0522-46ba-aa01-399fba315827" alt="Hardware Simulation - 2" width="420"/><br/>
      <small>Hardware Simulation 2</small>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/914928e3-f637-42e9-a5a3-c9f1e582e674" alt="Hardware Simulation - 3" width="420"/><br/>
      <small>Hardware Simulation 3</small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/fde13120-6fe4-4630-ab1b-c8ffdf3f0d72" alt="Hardware Simulation - 4" width="420"/><br/>
      <small>Setup Simulations </small>
    </td>
  </tr>
</table>

---

### 2) Blynk Dashboard 
<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/3554719f-38a0-41f3-ad8c-2accb19d7cec" alt="Blynk Dashboard Output - 0" width="360"/><br/>
      <small>Blynk - Screen 1</small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/85b379b0-2c5c-4d68-ac48-ede23f03cf08" alt="Blynk Dashboard Output - 1" width="360"/><br/>
      <small>Blynk - Screen 2</small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/0fc8e99e-0bdb-4437-ac1b-3752211f9c2f" alt="Blynk Dashboard Output - 2" width="360"/><br/>
      <small>Blynk - Screen 3</small>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/ae858e5b-a84f-4bb7-972f-3ab710b1ab71" alt="Blynk Dashboard Output - 3" width="360"/><br/>
      <small>Blynk - Screen 4</small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/22c9c38f-162f-4577-b837-3a25eb0193e6" alt="Blynk Dashboard Output - 4" width="360"/><br/>
      <small>Blynk - Screen 5</small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/12941019-fbf3-4c73-91d6-d0aa26d5f4d8" alt="Blynk Dashboard Output - 5" width="360"/><br/>
      <small>Blynk - Screen 6</small>
    </td>
  </tr>
</table>

---

### 3) Serial Monitor Outputs
<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/ee8d8dcd-782f-43d6-b3f8-1a6448baee7a" alt="Serial Monitor output - 1" width="540"/><br/>
      <small>Serial Monitor Output 1</small>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/ab3201e4-a4fc-435f-ad05-e926b15931a5" alt="Serial Monitor output - 2" width="540"/><br/>
      <small>Serial Monitor Output 2</small>
    </td>
  </tr>
</table>

---

## 🔮 **Future Scope**

* Push Notifications (SMS/Email)
* Firebase cloud storage
* Health history tracking
* Buzzer alert system

---

## 📄 License

This project is open-source under the **MIT License**.

