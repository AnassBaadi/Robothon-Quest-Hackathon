// Include the BluetoothSerial library for Bluetooth communication
#include "BluetoothSerial.h"

// Create a BluetoothSerial object
BluetoothSerial SerialBT;
String SBT; // String to store incoming Bluetooth data

// Motor control pins
int motor1Pin1 = 12; // Motor 1 direction pin 1
int motor1Pin2 = 13; // Motor 1 direction pin 2
int enable1Pin = 26; // Motor 1 speed control pin

int motor2Pin1 = 14; // Motor 2 direction pin 1
int motor2Pin2 = 27; // Motor 2 direction pin 2
int enable2Pin = 25; // Motor 2 speed control pin

// Infrared (IR) sensor pins
const int IRR = 32; // Right IR sensor
const int IRM = 33; // Middle IR sensor
const int IRL = 34; // Left IR sensor

// LED pins
const int LEDr = 5;   // Red LED
const int LEDv = 21;  // Green LED
const int LEDb = 22;  // Blue LED

// Ultrasonic sensor pins
#define TRIG_PIN 15
#define ECHO_PIN 18

// Variables for ultrasonic sensor
float duration_us, distance_cm;
int circleCount = 0; // Counter for circle detections
bool obstacleDetected = false; // Flag for obstacle detection

// Function to move robot forward
void handleForward() {
  analogWrite(enable1Pin, 120);
  analogWrite(enable2Pin, 120);
  Serial.println("Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn robot left
void handleLeft() {
  Serial.println("Left");
  analogWrite(enable1Pin, 120);
  analogWrite(enable2Pin, 120);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// Function to stop the robot
void handleStop() {
  Serial.println("Stop");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Function to turn robot right
void handleRight() {
  Serial.println("Right");
  analogWrite(enable1Pin, 120);
  analogWrite(enable2Pin, 120);
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move robot backward briefly and then stop
void handleReverse() {
  Serial.println("Reverse");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(enable1Pin, 150);
  analogWrite(enable2Pin, 150);
  delay(500); // Move back briefly
  handleStop(); // Stop after reversing
  obstacleDetected = false; // Reset obstacle flag
}

// Function to handle LED indication based on circle count
void handleLEDs() {
    if (circleCount == 1) { digitalWrite(LEDr, HIGH); delay(3000); digitalWrite(LEDr, LOW); }
    if (circleCount == 2) { digitalWrite(LEDb, HIGH); delay(3000); digitalWrite(LEDb, LOW); }
    if (circleCount == 3) { digitalWrite(LEDv, HIGH); delay(3000); digitalWrite(LEDv, LOW); }
    if (circleCount == 4) {
        digitalWrite(LEDr, HIGH); digitalWrite(LEDb, HIGH); digitalWrite(LEDv, HIGH);
        delay(5000);
        digitalWrite(LEDr, LOW); digitalWrite(LEDb, LOW); digitalWrite(LEDv, LOW);
    }
}

// Function to check for obstacles using ultrasonic sensor
void checkObstacle() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = duration_us * 0.034 / 2; // Convert to cm

  if (distance_cm < 25) { // Obstacle within 25 cm
    Serial.println("Obstacle detected");
    obstacleDetected = true;
    handleReverse();
  }
  Serial.print("Distance : ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  delay(200);
}

// Function to check for circle detection using IR sensors
void checkCircle() {
    int irr = digitalRead(IRR);
    int irm = digitalRead(IRM);
    int irl = digitalRead(IRL);
    if (irr == 0 || irm == 0 || irl == 0) { // If any sensor is triggered
        Serial.println("Circle detected");
        circleCount++;
        handleLEDs();
    }
}

// Initial setup function
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car"); // Initialize Bluetooth with name

  // Set motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set LED pins
  pinMode(LEDr, OUTPUT);
  pinMode(LEDv, OUTPUT);
  pinMode(LEDb, OUTPUT);

  // Set IR sensor pins
  pinMode(IRR, INPUT);
  pinMode(IRM, INPUT);
  pinMode(IRL, INPUT);
}

// Main loop function
void loop() {
  if (!obstacleDetected) { // Proceed only if no obstacle
    if (Serial.available()) { // Read from Serial
      SerialBT.write(Serial.read());
    }
    if (SerialBT.available()) { // Read from Bluetooth
      char command = SerialBT.read();
      Serial.println(command);

      // Control motors based on command
      switch (command) {
        case 'F': handleForward(); break;
        case 'B': handleReverse(); break;
        case 'L': handleLeft(); break;
        case 'R': handleRight(); break;
        case 'S': handleStop(); break;
        default: handleStop(); break;
      }
    }
  }

  checkObstacle(); // Check for obstacles
  checkCircle();   // Check for circle detection
  delay(5);        // Small delay for loop stability
}
