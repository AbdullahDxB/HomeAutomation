# IoT Smart Home Automation System

A comprehensive smart home solution designed to automate environmental controls and enhance security, featuring smartphone and voice assistant integration. This project was developed for the Inter-College Technical Fest and was successfully scaled to fully automate my personal dorm room.

<img width="1844" height="1145" alt="image" src="https://github.com/user-attachments/assets/000c5f05-e021-4cf5-9f07-e1c8af37c34c" />

---

## Key Features

* **Automated Environmental Control:** Reduces manual intervention by over **50%** using a network of temperature, humidity, and light sensors.
* **Real-Time WebPage:** A user-friendly web interface for modular, room-wise control and monitoring.
* **Voice Assistant Integration:** Seamlessly integrated with the **Google Home API** for hands-free, voice-activated commands via Google Assistant/Gemini.
* **RFID-Based Security:** Secure access control using **RFID technology** to enhance room security.

---

## Technologies Used

* **Hardware:** ESP8266, RFID Reader (RC522), IR Sensors, DHT11 (Temperature/Humidity), L298 Motor Driver, nRF Antenna module
* **Firmware:** C/C++ (Arduino IDE)
* **API:** Google Home API

---

## Installation & Usage

### 1. Hardware Setup
Connect the sensors, RFID reader, and other modules to the ESP8266 microcontroller. The Arduino Mega was used for the original project. A detailed circuit diagram is given for clarity.

### 2. Firmware
1.  Open the `.ino` file in the Arduino IDE.
2.  Install the required libraries from the Library Manager (e.g., `ESP8266WiFi`, `MFRC522`, `Adafruit Unified Sensor`).
3.  Update the Wi-Fi credentials (`ssid` and `password`) in the code.
4.  Upload the firmware to the ESP8266.

### 3. Control
* **WebServer:** Connect the companion Web server to the ESP8266's IP address on your local network.
* **Voice Control:** Link the system to your Google Home account using a service like IFTTT to forward commands to the ESP8266.

---

## Project Status

This project is **complete** and was successfully demonstrated at the Inter-College Technical Fest, where it was used by over **50 people**. It is currently implemented and running in my personal dorm room.
