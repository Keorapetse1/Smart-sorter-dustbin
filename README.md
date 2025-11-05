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

## These are images of the process

![IMG_20251022_114253](https://github.com/user-attachments/assets/87b6361d-f905-47df-a649-93120fee5d65)

![IMG_20251023_102959](https://github.com/user-attachments/assets/6804c9d4-d4b2-4e89-8edd-93db40602f6c)

![IMG_20251022_115455](https://github.com/user-attachments/assets/45aaebf0-a7d9-4a31-9d80-a3ed0c86a508)

![IMG_20251022_142513](https://github.com/user-attachments/assets/61d2a999-5d06-4577-871b-cb1c3d5e3468)

![IMG_20251023_094448](https://github.com/user-attachments/assets/1f3b4366-3099-4ab8-bdb9-614e2efa3c3c)

![IMG_20251023_101248](https://github.com/user-attachments/assets/07a05283-d800-4ac6-bc70-cfb1594d2458)

![IMG_20251023_135641](https://github.com/user-attachments/assets/0a835cc2-ed4a-4385-ace4-62712f5a1133)

![IMG_20251023_142044](https://github.com/user-attachments/assets/5f612ae1-4063-4a52-93ec-db7de500c21b)

![IMG_20251023_150648](https://github.com/user-attachments/assets/9cbf4551-5e77-4f55-9924-97fbf14e09e3)

![IMG_20251024_093118](https://github.com/user-attachments/assets/9c77d306-8b33-4a77-8913-587c866bf376)

![IMG_20251024_104923](https://github.com/user-attachments/assets/183b378b-d6dc-4734-b637-20afb4faf050)

![IMG_20251024_115001](https://github.com/user-attachments/assets/6baba4a3-b362-4e4f-9f2d-6fd0024496a5)

![IMG_20251030_155914](https://github.com/user-attachments/assets/7f7b28ec-a872-429c-8e75-6ef86c91ee83)

![IMG_20251030_163024](https://github.com/user-attachments/assets/9856cdd7-5386-4538-8474-758ca8972a52)

![IMG_20251030_163031](https://github.com/user-attachments/assets/acddb3c4-abb5-41a3-bfe3-9b768894f728)

![IMG_20251030_163039](https://github.com/user-attachments/assets/9459b04e-f1ef-4aa4-b13c-ce842dd4d5fd)

![IMG_20251030_155950](https://github.com/user-attachments/assets/6ce4085d-0120-4b86-a15e-287694244571)

![IMG_20251030_160002](https://github.com/user-attachments/assets/4dd50e68-f358-410c-96f3-5b622229da3b)

