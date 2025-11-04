#include <ESP32Servo.h>           
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ======================= OLED SETUP =======================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ======================= SERIAL SETUP =======================
#define RX_PIN 4   // Connected to ESP32-CAM TX
#define BAUDRATE 115200

// ======================= SERVO SETUP =======================
#define SERVO_WOOD_PIN     12
#define SERVO_PLASTIC_PIN  13
#define SERVO_PAPER_PIN    14

Servo servoWood;
Servo servoPlastic;
Servo servoPaper;

// ======================= LED SETUP =======================
#define LED_GREEN 25   // System OK
#define LED_BLUE  26   // Communication OK
#define LED_RED   27   // Error

// ======================= VARIABLES =======================
String incomingData = "";
unsigned long lastCommandTime = 0;
bool communicationOK = false;

// ======================= SETUP =======================
void setup() {
  Serial.begin(115200);
  Serial2.begin(BAUDRATE, SERIAL_8N1, RX_PIN, -1);  // RX-only communication

  // LEDs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_GREEN, HIGH);  // system initialized
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    digitalWrite(LED_RED, HIGH);
    while (true);  // Stop if OLED fails
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Dustbin Ready");
  display.display();

  // Servo setup
  servoWood.setPeriodHertz(50);
  servoWood.attach(SERVO_WOOD_PIN, 500, 2400);

  servoPlastic.setPeriodHertz(50);
  servoPlastic.attach(SERVO_PLASTIC_PIN, 500, 2400);

  servoPaper.setPeriodHertz(50);
  servoPaper.attach(SERVO_PAPER_PIN, 500, 2400);

  // Close all servos initially
  servoWood.write(0);
  servoPlastic.write(0);
  servoPaper.write(0);
}

// ======================= MAIN LOOP =======================
void loop() {
  // Check for data from ESP32-CAM
  if (Serial2.available()) {
    incomingData = Serial2.readStringUntil('\n');
    incomingData.trim();

    if (incomingData.length() > 0) {
      communicationOK = true;
      lastCommandTime = millis();

      digitalWrite(LED_BLUE, HIGH);  // Communication working
      digitalWrite(LED_RED, LOW);

      if (incomingData == "WOOD") {
        openBin("WOOD");
      } else if (incomingData == "PLASTIC") {
        openBin("PLASTIC");
      } else if (incomingData == "PAPER") {
        openBin("PAPER");
      }
    }
  }

  // Timeout: if no command received for 10s, consider comms failed
  if (millis() - lastCommandTime > 10000) {
    communicationOK = false;
    digitalWrite(LED_BLUE, LOW);
  }

  // Power/comm status LEDs
  if (communicationOK) {
    digitalWrite(LED_GREEN, HIGH);
  } else {
    digitalWrite(LED_GREEN, HIGH);  // System still OK
  }
}

// ======================= FUNCTIONS =======================
void openBin(String type) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Opening bin:");
  display.println(type);
  display.display();

  // Close all first
  servoWood.write(0);
  servoPlastic.write(0);
  servoPaper.write(0);

  // Choose which to open
  if (type == "WOOD") {
    servoWood.write(90);
  } else if (type == "PLASTIC") {
    servoPlastic.write(90);
  } else if (type == "PAPER") {
    servoPaper.write(90);
  }

  delay(5000);  // 5 seconds open time

  // Close again
  servoWood.write(0);
  servoPlastic.write(0);
  servoPaper.write(0);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Bin closed");
  display.display();
}
