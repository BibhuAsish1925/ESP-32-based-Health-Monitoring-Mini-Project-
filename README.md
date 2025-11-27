# 🫀 Health Monitoring System (ESP32-Based IoT Project)

A complete **IoT-based Health Monitoring System** developed as part of an Engineering Project.
The system continuously monitors **Heart Rate**, **SpO₂**, **Temperature**, **Humidity**, and **Wetness**, displaying results on **OLED**, **Serial Monitor**, and **Blynk IoT Dashboard** with intelligent alert messages.

---

## 📌 **Project Overview**

This project uses ESP32 and multiple sensors to create a smart health monitoring solution.
It provides real-time data, alerts, and wireless monitoring via Blynk IoT.

---
🔌 1. Circuit Diagram

Add your circuit schematic image here:

![Circuit Diagram](images/circuit_diagram.png)

🧪 2. Actual Hardware Setup

Add real photos of your project:

![Hardware Setup](images/circuit_photo1.jpg)
![Hardware Close-up](images/circuit_photo2.jpg)

📱 3. Blynk Dashboard & Mobile Template

Add 4–5 screenshots of your Blynk web dashboard & mobile app:

![Blynk Template](images/blynk_template1.png)
![Blynk Dashboard](images/blynk_dashboard1.png)
![Blynk Mobile](images/blynk_mobile1.jpg)
![Blynk Charts](images/blynk_chart_section.png)

📊 4. Output Screens

Add display screenshots (OLED, Serial Monitor, Sensor values):

![OLED Output](images/oled_output.jpg)
![Serial Output](images/serial_output.png)
![Sensor Values](images/sensor_values.png)




<table align="center">
  <tr>
    <td>
      <figure>
        <img width="500" alt="ssp4" src="https://github.com/user-attachments/assets/02b9d263-fe49-4ede-918c-189329898ad7" />
        <div align="center"><figcaption> Xilinx dashboard</figcaption>
      </figure>
    </td>
    <td>
      <figure>
        <img width="500" alt="ssp1" src="https://github.com/user-attachments/assets/4e72139f-1344-4438-8f9f-0398128334d7" />
        <div align="center"><figcaption> Combinational Circuits </figcaption>
      </figure>
    </td>
  </tr>
  <tr>
    <td>
      <figure>
        <img width="500" alt="ssp2" src="https://github.com/user-attachments/assets/bdc0c0f0-8da2-4cc1-95f1-0c3331226c9b" />
        <div align="center"><figcaption> Sequencial Circuits </figcaption>
      </figure>
    </td>
    <td>
      <figure>
        <img width="500" alt="ssp3" src="![Circuit Diagram - Health Monitoring](https://github.com/user-attachments/assets/7b3393b6-293a-48a8-b4f3-09dbc22cf967)" />
        <div align="center"><figcaption> State Machines </figcaption>
      </figure>
    </td>
  </tr>
</table>




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

