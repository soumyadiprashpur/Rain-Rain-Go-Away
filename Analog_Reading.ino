#include <Servo.h>

// Define LED pins using analog inputs
const int led1 = A0; // LED 1 connected to analog pin A0
const int led2 = A1; // LED 2 connected to analog pin A1
const int led3 = A2; // LED 3 connected to analog pin A2
const int led4 = A3; // LED 4 connected to analog pin A3

// Define servo control pin
const int servoPin = 9; // Servo signal pin

// Create servo object for angle control
Servo myServo;

// Define predefined angles for different LED intensities
const int angle1 = 30;   // Low-intensity LED angle
const int angle2 = 60;   // Medium-low intensity LED angle
const int angle3 = 120;  // Medium-high intensity LED angle
const int angle4 = 150;  // High-intensity LED angle

// Initialize pins and communication
void initializePins() {
  // Attach servo to specific pin
  myServo.attach(servoPin);

  // Set initial servo position to 0 degrees
  myServo.write(0);

  // Start serial communication for debugging
  Serial.begin(9600);
}

// Calculate average analog reading to reduce noise
int getAverageAnalogRead(int pin) {
  long sum = 0;
  // Take 10 readings with small delay between
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
    delay(10); // Small delay to stabilize readings
  }
  // Return average of 10 readings
  return sum / 10;
}

// Determine servo angle based on LED intensity
int getGlowingLedAngle() {
  // Debug: Print analog readings of specific LEDs
  Serial.print("LED4: ");
  Serial.println(getAverageAnalogRead(led4));

  Serial.print("LED3: ");
  Serial.println(getAverageAnalogRead(led3));

  // Check LEDs in priority order (LED4 -> LED1)
  if (getAverageAnalogRead(led4) >= 200) {
    return angle4; // Highest intensity LED
  } else if (getAverageAnalogRead(led3) >= 200) {
    return angle3; // High intensity LED
  } else if (getAverageAnalogRead(led2) >= 200) {
    return angle2; // Medium intensity LED
  } else if (getAverageAnalogRead(led1) >= 200) {
    return angle1; // Low intensity LED
  } else {
    return 0; // No LED glowing, default position
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
  // Get target angle based on LED intensity
  int targetAngle = getGlowingLedAngle();

  // Move servo to calculated angle
  moveServoToAngle(targetAngle);
}
