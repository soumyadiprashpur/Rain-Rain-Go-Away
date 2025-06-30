#include <Servo.h>

// Define LED pins as digital inputs
const int led1 = 2; // LED 1 connected to digital pin 2
const int led2 = 3; // LED 2 connected to digital pin 3
const int led3 = 4; // LED 3 connected to digital pin 4
const int led4 = 5; // LED 4 connected to digital pin 5

// Define servo control pin
const int servoPin = 9; // Servo signal pin

// Create servo object for angle control
Servo myServo;

// Define predefined angles for different LED states
const int angle1 = 30;   // Low-intensity LED angle
const int angle2 = 60;   // Medium-low intensity LED angle
const int angle3 = 120;  // Medium-high intensity LED angle
const int angle4 = 150;  // High-intensity LED angle
const int defaultAngle = 0; // Default angle if no LED is active

// Initialize pins and communication
void initializePins() {
  // Set LED pins as input
  pinMode(led1, INPUT);
  pinMode(led2, INPUT);
  pinMode(led3, INPUT);
  pinMode(led4, INPUT);

  // Attach servo to specific pin
  myServo.attach(servoPin);

  // Set initial servo position
  myServo.write(defaultAngle);

  // Start serial communication for debugging
  Serial.begin(9600);
}

// Determine servo angle based on LED digital state
int getGlowingLedAngle() {
  // Check LEDs in priority order (LED4 -> LED1)
  if (digitalRead(led4) == HIGH) {
    Serial.println("LED4 is HIGH, setting angle to 150");
    return angle4;
  } else if (digitalRead(led3) == HIGH) {
    Serial.println("LED3 is HIGH, setting angle to 120");
    return angle3;
  } else if (digitalRead(led2) == HIGH) {
    Serial.println("LED2 is HIGH, setting angle to 60");
    return angle2;
  } else if (digitalRead(led1) == HIGH) {
    Serial.println("LED1 is HIGH, setting angle to 30");
    return angle1;
  } else {
    Serial.println("No LED is HIGH, setting angle to 0");
    return defaultAngle;
  }
}

// Move servo to specified angle
void moveServoToAngle(int angle) {
  // Debug: Print target angle
  Serial.print("Moving servo to angle: ");
  Serial.println(angle);

  // Write angle to servo
  myServo.write(angle);
  delay(50); // Stabilize servo movement
}

// Setup function runs once
void setup() {
  initializePins();
}

// Main loop runs continuously
void loop() {
  // Get target angle based on LED digital state
  int targetAngle = getGlowingLedAngle();

  // Move servo to calculated angle
  moveServoToAngle(targetAngle);
}
