# Smart Sorter

The **Smart Sorter** is an intelligent dustbin system that automatically identifies, sorts, and manages waste using embedded vision and microcontroller logic.  
It combines the **ESP32-CAM** and **ESP32-WROOM32** to achieve autonomous object recognition, servo-based sorting, and real-time status display.

---

## Project Overview

The Smart Sorter uses **AI-powered image recognition** to detect the type of waste (e.g., plastic, paper, or metal) and then opens the corresponding bin lid automatically.  
It is designed to promote efficient waste management, reduce manual sorting, and demonstrate the integration of IoT and embedded systems.

---

## Hardware Components

| Component | Description | Role in System |
|------------|--------------|----------------|
| **ESP32-CAM** | Microcontroller with built-in camera module | Captures images of waste items and runs lightweight AI image classification (e.g., via Edge Impulse). Sends the identified category (plastic, metal, etc.) to the ESP32-WROOM32 through serial communication. |
| **ESP32-WROOM32** | Secondary microcontroller (main control unit) | Receives data from the ESP32-CAM and controls servo motors, LEDs, and the OLED display based on classification results. Handles lid opening and system logic. |
| **Battery Pack (4S Li-ion, 13.8V)** | Main power supply | Provides 13.8V to the system. |
| **Step-Down Converter (Buck Converter)** | Voltage regulator | Steps down 13.8V from the battery pack to 5V for the ESP32 boards, servos, OLED, and LEDs. Ensures stable operation and protects components from over-voltage. |
| **OLED Display (0.96" or 1.3")** | Visual feedback module | Displays real-time system status, such as connection info, detected waste type, and power level. Connected to the ESP32-WROOM32 via I²C (SDA, SCL). |
| **LED Indicators** | Visual status indicators | Provide quick visual feedback:<br>• **Green** – Ready / idle<br>• **Blue** – Object detected<br>• **Red** – Error or low power<br>• **Yellow** – Sorting in progress |
| **Servo Motors** | Mechanical actuators | Open and close the corresponding bin lids based on detected waste type. Controlled by the ESP32-WROOM32. |
| **Wires, Connectors & Frame** | Assembly materials | Provide structure and electrical connections between components. |

---

## Power System

- **Battery Pack:** 4 × 3.45V Li-ion cells = **13.8V total**
- **Step-Down Converter:** Converts 13.8V → **5V regulated**
- **5V Rail:** Powers both ESP32 boards, OLED display, and LEDs
- **3.3V Logic:** Internally handled by ESP32 regulators

 *Always double-check wiring polarity and voltage output before connecting components.*

 ## System Architecture
ESP32-CAM
├── Captures image
├── Classifies waste type
└── Sends result → ESP32-WROOM32 (via TX/RX)

ESP32-WROOM32
├── Receives data
├── Controls servos
├── Updates OLED display
└── Activates LEDs

## Features

-  Automatic waste detection and sorting  
-  Dual-microcontroller communication (ESP32-CAM → ESP32-WROOM32)  
-  OLED visual interface  
-  LED color status indicators  
-  Power-efficient design with step-down voltage regulation  
-  Modular — can be scaled to multiple bins or categories

### 1. ESP32-CAM Code
- Captures image using the onboard camera  
- Runs lightweight AI model (e.g., Edge Impulse)  
- Sends classification result via serial communication  

### 2. ESP32-WROOM32 Code
- Listens for data from the ESP32-CAM  
- Maps detected waste type → corresponding servo action  
- Updates OLED and LEDs in real time

## Wiring Summary

| Connection | ESP32-WROOM32 Pin | Peripheral |
|-------------|-------------------|-------------|
| OLED SDA | GPIO 21 | OLED display |
| OLED SCL | GPIO 22 | OLED display |
| LED 1 | GPIO 25 | Green LED |
| LED 2 | GPIO 26 | Blue LED |
| LED 3 | GPIO 27 | Red LED |
| Servo 1 | GPIO 2 or 3 | Lid mechanism |
| GND | Common Ground | All components |

*(Adjust pins based on your setup.)*

## Example Workflow

1. Waste item is placed near the Smart Sorter  
2. **ESP32-CAM** captures the image  
3. It identifies the object type using AI classification  
4. **ESP32-CAM** sends the result to **ESP32-WROOM32**  
5. **ESP32-WROOM32**:
   - Opens the correct bin lid (servo control)  
   - Updates OLED display  
   - Activates corresponding LED color

## Libraries Used

- `ESP32Servo.h` – Servo motor control  
- `Wire.h` – I²C communication  
- `Adafruit_GFX.h` and `Adafruit_SSD1306.h` – OLED display  
- `Edge Impulse SDK` (optional) – AI inference on ESP32-CAM  
- `HardwareSerial.h` – Serial communication between ESP32 boards

## Future Improvements

- Add **ultrasonic sensor** for motion detection (auto-wake)  
- Add **Wi-Fi logging** to send sorting statistics to a cloud dashboard  
- Implement **battery level monitoring** via analog read  
- Expand to **multi-bin system** with more servo outputs
- Add a switch for easy on off convinience
