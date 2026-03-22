# 🚗 Pothole Detection Robot (ESP32 + Ultrasonic Sensors)

A Bluetooth-controlled robot that detects potholes in real-time using dual ultrasonic sensors and prevents falling into large pits. The system displays live distance data and road condition on an OLED screen while ensuring safe navigation.

---

## 📌 Features

* 📱 Bluetooth control using mobile app
* 🔄 Basic movement: Forward, Backward, Left, Right
* 📡 Dual ultrasonic sensors for pothole detection
* ⚠️ Intelligent safety system (blocks forward on large potholes)
* 💡 LED alert for dangerous pits
* 🖥️ Real-time data on OLED display
* 🧠 Non-blocking real-time processing

---

## 🛠️ Hardware Used

* ESP32 (38-pin)
* 2 × HC-SR04 Ultrasonic Sensors
* L298N Motor Driver
* 2 × TT DC Motors
* 0.96" I2C OLED Display (SSD1306)
* LED
* Power Supply (Battery)

---

## 🔌 Pin Configuration

### Motor Driver (L298N)

```
motor1pin1 → GPIO 27
motor1pin2 → GPIO 26
motor2pin1 → GPIO 25
motor2pin2 → GPIO 33
enableA    → GPIO 14
enableB    → GPIO 32
```

### Ultrasonic Sensors

```
Left Sensor:
TRIG → GPIO 5
ECHO → GPIO 18

Right Sensor:
TRIG → GPIO 17
ECHO → GPIO 16
```

### Other Components

```
OLED (I2C):
SDA → GPIO 21
SCL → GPIO 22

LED:
GPIO 2
```

---

## 🎮 Control System

The robot is controlled via **Bluetooth** using a mobile app.

**Recommended App:** RC Bluetooth Controller

### Controls Mapping

```
F → Forward
B → Backward
L → Left
R → Right
S → Stop
```

---

## 🧠 Working Principle

The robot performs **two tasks simultaneously**:

### 1. Movement Control

* Receives commands via Bluetooth
* Executes movement accordingly

### 2. Pothole Detection

* Continuously measures distance using two ultrasonic sensors
* Calculates average distance
* Classifies surface condition

---

## 🛣️ Pothole Detection Logic

| Condition   | Distance Range | Action                |
| ----------- | -------------- | --------------------- |
| Normal Road | > 3 cm        | All movements allowed |
| Small Pit   | 6 cm        | All movements allowed |
| Large Pit   | < 6 cm         | ❌ Forward blocked     |

---

## 🚨 Safety Feature

* If a **large pothole** is detected:

  * Robot stops forward movement
  * Allows backward, left, and right
  * LED turns ON
  * Warning displayed on OLED

---

## 🖥️ Output

* 📟 OLED Display:

  * Left distance
  * Right distance
  * Average distance
  * Pothole status

* 💻 Serial Monitor:

  * Live sensor data
  * Detected condition

---

## ⚙️ Software & Tools

* VS Code
* PlatformIO
* ESP32 Arduino Framework

### 📦 Required Libraries

```
Adafruit SSD1306
Adafruit GFX Library
BluetoothSerial (built-in)
```

---

## 🚀 Getting Started

1. Clone the repository:

```
git clone https://github.com/your-username/pothole-detection-robot.git
```

2. Open project in VS Code (PlatformIO)

3. Install required libraries

4. Upload code to ESP32

5. Connect Bluetooth:

   * Device name: `ESP32_ROBOT`

6. Control using mobile app

---

## 🔧 Future Improvements

* 📍 GPS integration for pothole mapping
* 📶 LoRa/Cloud data transmission
* 🤖 AI-based pothole detection (camera)
* 📊 Data logging for smart city analysis

---

## 📄 License

This project is open-source and free to use for educational purposes.

---

## 🙌 Author

**Vector Sine**

---

⭐ If you like this project, consider giving it a star!
