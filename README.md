# 🫀 Health Monitoring System (ESP32-Based IoT Project)

A complete **IoT-based Health Monitoring System** developed as part of an Engineering Project.
The system monitors **Heart Rate**, **SpO₂**, **Temperature**, **Humidity**, and **Wetness**, displaying results on:

* 📟 **OLED Display**
* 💻 **Serial Monitor**
* 🌐 **Blynk IoT Dashboard**

With intelligent alert messages and real-time IoT connectivity.

---

## 🎥 Project Video

Paste your video link here ↓

### 👉 [PROJECT VIDEO: Click to Watch](#)

*(Replace `#` with your YouTube/Drive link — it will appear blue & clickable)*

---

## 🖼️ Image Gallery (Circuit + Blynk + Outputs)

### 🔌 **1. Circuit Diagram**

*Add your circuit schematic image here:*

```
![image](![Circuit Diagram - Health Monitoring](https://github.com/user-attachments/assets/9ea089f9-89e3-4649-8e4b-3bd6d1dcc12a))
```

---

### 🧪 **2. Actual Hardware Setup**

*Add real photos of your project:*

```
![Hardware Setup](images/circuit_photo1.jpg)
![Hardware Close-up](images/circuit_photo2.jpg)
```

---

### 📱 **3. Blynk Dashboard & Mobile Template**

*Add 4–5 screenshots of your Blynk web dashboard & mobile app:*

```
![Blynk Template](images/blynk_template1.png)
![Blynk Dashboard](images/blynk_dashboard1.png)
![Blynk Mobile](images/blynk_mobile1.jpg)
![Blynk Charts](images/blynk_chart_section.png)
```

---

### 📊 **4. Output Screens**

*Add display screenshots (OLED, Serial Monitor, Sensor values):*

```
![OLED Output](images/oled_output.jpg)
![Serial Output](images/serial_output.png)
![Sensor Values](images/sensor_values.png)
```

---

## 🛠️ Hardware Used

| Component            | Purpose                  |
| -------------------- | ------------------------ |
| ESP32 Dev Board      | Main controller          |
| MAX30102             | Heart Rate & SpO₂ sensor |
| DHT11                | Temperature & Humidity   |
| Rain Sensor (Analog) | Wetness detection        |
| OLED SSD1306         | Display                  |
| Jumper Wires         | Connections              |

---

## 📡 System Features

### ❤️ Heart & Oxygen Monitoring

* Heart Rate (BPM)
* SpO₂ (%)
* Automatic finger detection
* Clean output on OLED + Blynk

### 🌡️ Temperature & Humidity Monitoring

* DHT11 readings
* Heat alert system

### ☔ Wetness Detection

* Rain sensor converted to moisture %
* Wet/Dry alerts

### ⚠️ Smart Alerts

System automatically prints:

* **Health issue alert due to Heart & SpO₂**
* **Wet / Dry Alert**
* **High Temperature Warning**
* **Normal Condition**

Alerts appear on:

* Serial Monitor
* OLED
* Blynk Dashboard

---

## 📲 Blynk Virtual Pin Mapping

| Function                | V-Pin |
| ----------------------- | ----- |
| Heart Rate              | V0    |
| SpO₂                    | V2    |
| Moisture %              | V4    |
| Temperature             | V3    |
| Humidity                | V1    |
| Wetness Alert           | V5    |
| Combined Status Message | V6    |

---

## 📚 Required Libraries

Install these via Arduino Library Manager:

* **Blynk**
* **Adafruit SSD1306**
* **Adafruit GFX**
* **SparkFun MAX3010x**
* **DHT Sensor Library**
* **Wire**

---

## ▶️ How to Run

1. Install all required libraries
2. Add your WiFi credentials
3. Add Blynk Template ID, Template Name & Auth Token
4. Upload the Arduino code to ESP32
5. Open Serial Monitor @ 115200
6. Check OLED + Blynk Dashboard

---

## 🔮 Future Enhancements

* Push notifications (SMS/Email)
* Firebase / Cloud data logging
* Health history charts
* Buzzer/Alarm module

---

## 📄 License

This project is released under the **MIT License**.
