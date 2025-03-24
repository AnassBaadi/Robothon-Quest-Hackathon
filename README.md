# 🚀 ESP32 Autonomous & Teleguided Robot

This project features an **ESP32-based robot** capable of operating in two distinct modes:

- **Autonomous Mode:** Utilizes ultrasonic and IR sensors for obstacle detection and circle counting.
- **Teleguided Mode:** Allows manual control via Bluetooth using a custom APK.

---

## 📦 **Features**

- ✅ **Bluetooth Control:** Remote operation via a custom Android APK.
- ✅ **Autonomous Navigation:** Obstacle avoidance with ultrasonic sensors HC-SR04.
- ✅ **Circle Detection:** Uses 3 TCRT5000 IR sensors to detect and count circles, triggering LED indications.
- ✅ **LED Indications:** Different colors represent different states or circle counts.

---

## 🛠️ **Hardware Requirements**

- **ESP32** microcontroller
- **Ultrasonic Sensor** (HC-SR04 or equivalent)
- **IR Sensors** (3 units for left, middle, and right)
- **L298N** Motor Driver Module
- **DC Motors** (2 units)
- **LEDs** (Red, Green, and Blue)
- **Power Supply**

---

## 🏗️ **Wiring Overview**

| Component         | ESP32 Pin  |
|--------------------|-----------|
| Motor 1 IN1        | GPIO 12   |
| Motor 1 IN2        | GPIO 13   |
| Motor 1 Enable     | GPIO 26   |
| Motor 2 IN1        | GPIO 14   |
| Motor 2 IN2        | GPIO 27   |
| Motor 2 Enable     | GPIO 25   |
| Ultrasonic Trigger | GPIO 15   |
| Ultrasonic Echo    | GPIO 18   |
| IR Right Sensor    | GPIO 32   |
| IR Middle Sensor   | GPIO 33   |
| IR Left Sensor     | GPIO 34   |
| Red LED            | GPIO 5    |
| Green LED          | GPIO 21   |
| Blue LED           | GPIO 22   |

---

## 🔧 **Installation**

1. **Clone this repository:**
   ```bash
   git clone https://github.com/AnassBaadi/Robothon-Quest-Hackathon.git
   ```

2. **Open the project in Arduino IDE** (or compatible environment).
3. **Install required libraries** if not already installed:
   - `BluetoothSerial.h`
4. **Upload the code to ESP32**.

---

## 📱 **APK for Bluetooth Control**

Download the **[ESP32 Robot Controller APK](#)** to remotely control the robot via Bluetooth.

- **Controls:**
  - **F:** Forward
  - **B:** Backward
  - **L:** Turn Left
  - **R:** Turn Right
  - **S:** Stop

---

## 🏅 **Acknowledgments**

This project was developed as part of **Robothon Quest Hackathon**. Special thanks to my team **Hossam Rouddasse** and **Fatima Zahra Sarma** , organizers, CRRT club of ENSA Agadir, and Code 212 for the opportunity to innovate!
