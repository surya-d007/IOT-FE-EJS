const int waterSensorPin = 5; // Digital pin connected to the water sensor
const int IR_SENSOR_PIN = 3;  // IR sensor output pin
const int motionSensorPin = 7; // Pin where the motion detection sensor (PIR sensor) is connected

int previousWaterSensorValue = -1; // Variable to store the previous water sensor value, initialize with a value that is different from expected values (0 and 1)
int previousIRValue = -1;          // Variable to store the previous IR sensor value, initialize with a value that is different from expected values (0 and 1)
int previousPirState = LOW;        // Previous state of the motion detection sensor
int cleanRoom1 = 0;
int cleanRoom2 = 0;
int cleanRoom3 = 0;
int pirState = LOW; // Current state of the motion detection sensor

void setup() {
  // Set pin modes for buttons, sensors, and PIR sensor
  pinMode(2, INPUT_PULLUP);        // Button for room 1
  pinMode(4, INPUT_PULLUP);        // Button for room 2
  pinMode(6, INPUT_PULLUP);        // Button for room 3
  pinMode(IR_SENSOR_PIN, INPUT);   // IR sensor
  pinMode(waterSensorPin, INPUT);  // Water sensor
  pinMode(motionSensorPin, INPUT); // Motion detection sensor

  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  // Read button states for each room
  int buttonState1 = digitalRead(2); // Button for room 1
  int buttonState2 = digitalRead(4); // Button for room 2
  int buttonState3 = digitalRead(6); // Button for room 2

  // Handle button presses for room 1
  if (buttonState1 == LOW && cleanRoom1 == 0) {
    cleanRoom1 = 1;
    printStatus(); // Call printStatus when button status changes
    delay(400);    // Debounce delay
  } else if (buttonState1 == LOW && cleanRoom1 == 1) {
    cleanRoom1 = 0;
    printStatus(); // Call printStatus when button status changes
    delay(400);    // Debounce delay
  }

  // Handle button presses for room 2
  if (buttonState2 == LOW && cleanRoom2 == 0) {
    cleanRoom2 = 1;
    printStatus(); // Call printStatus when button status changes
    delay(400);    // Debounce delay
  } else if (buttonState2 == LOW && cleanRoom2 == 1) {
    cleanRoom2 = 0;
    printStatus(); // Call printStatus when button status changes
    delay(400);    // Debounce delay
  }

    if (buttonState3 == LOW && cleanRoom3 == 0) {
    cleanRoom3 = 1;
    printStatus(); // Call printStatus when button status changes
    delay(400);    // Debounce delay
  } else if (buttonState3 == LOW && cleanRoom3 == 1) {
    cleanRoom3 = 0;
    printStatus(); // Call printStatus when button status changes
    delay(400);    // Debounce delay
  }

  // Check for water sensor value change
  int waterSensorValue = digitalRead(waterSensorPin); // Read the water sensor value
  int irValue = digitalRead(IR_SENSOR_PIN);           // Read the IR sensor value
  pirState = digitalRead(motionSensorPin);            // Read the state of the motion detection sensor

  if (waterSensorValue != previousWaterSensorValue || irValue != previousIRValue || pirState != previousPirState) {
    printStatus(); // Call printStatus when water sensor, IR sensor, or motion sensor value changes
    previousWaterSensorValue = waterSensorValue; // Update previous water sensor value
    previousIRValue = irValue;                   // Update previous IR sensor value
    previousPirState = pirState;                 // Update previous motion sensor state
  }

  delay(100); // Delay for stability
}

void printStatus() {
  //Serial.print("Room 1: ");
  Serial.print(cleanRoom1 == 0 ? "clean" : "unclean");
  Serial.print(" ");
  //Serial.print(" | Room 2: ");
  Serial.print(cleanRoom2 == 0 ? "clean" : "unclean");
  Serial.print(" ");
  //Serial.print("Room 3: ");
  Serial.print(cleanRoom3 == 0 ? "clean" : "unclean");
  Serial.print(" ");
  //Serial.print(" | Water Sensor: ");
  Serial.print(digitalRead(waterSensorPin) == HIGH ? 0 : 1); 
  //Serial.print(digitalRead(waterSensorPin) == HIGH ? "Dry" : "Wet");
  Serial.print(" ");
  //Serial.print(" | IR Sensor: ");
  Serial.print(digitalRead(IR_SENSOR_PIN) == HIGH ? 0 : 1);
  //Serial.print(digitalRead(IR_SENSOR_PIN) == HIGH ? "No Object detected" : "Object detected");
  Serial.print(" ");
  //Serial.print(" | Motion Detection: ");
  Serial.println(digitalRead(motionSensorPin) == HIGH ? 1 : 0);
  //Serial.println(digitalRead(motionSensorPin) == HIGH ? "Motion detected!" : "No motion detected.");
}
