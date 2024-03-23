#include <SoftwareSerial.h>

SoftwareSerial myBluetooth(10, 11); // RX, TX

// Define rotary encoder pins
const int clkPin = 4;
const int dtPin = 6;
const int swPin = 5;

int currentStateCLK;
int previousStateCLK;

int rawEncoderValue = 0;

int encoderValue = 0; // Filtered value
unsigned long lastEncoderTime = 0; // Time of the last encoder change
int buttonState; // Current state of the button
int lastButtonState = HIGH; // Previous state of the button

// Moving average filter variables
const int numReadings = 10;
int readings[numReadings]; // the readings from the analog input
int readIndex = 0; // the index of the current reading
long total = 0; 
int average = 0; 

void setup() {
  Serial.begin(9600);
  myBluetooth.begin(9600);

  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP); // Set the button as input with internal pull-up resistor

  // Initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  previousStateCLK = digitalRead(clkPin);
}

void loop() {
  currentStateCLK = digitalRead(clkPin);
  buttonState = digitalRead(swPin); // Read the button state

  // Check if button state has changed to LOW (button pressed)
  if (buttonState == LOW && lastButtonState == HIGH) {
    rawEncoderValue = 0; 
    encoderValue = 0; 
    // Debounce delay to avoid accidental quick presses
    delay(50); 
  }

  if (currentStateCLK != previousStateCLK) {
    unsigned long currentMillis = millis(); // Get the current time

    if (digitalRead(dtPin) != currentStateCLK) {
      rawEncoderValue++; 
    } else {
      rawEncoderValue--; 
    }

    // Update the moving average filter
    total = total - readings[readIndex];
    readings[readIndex] = rawEncoderValue;
    total = total + readings[readIndex];
    readIndex = readIndex + 1;

    if (readIndex >= numReadings) {
      readIndex = 0; // ...wrap around to the beginning:
    }

    // Calculate the average:
    encoderValue = total / numReadings;

    // Send serialized data over Bluetooth
    myBluetooth.print("{ \"time\": ");
    myBluetooth.print(currentMillis);
    myBluetooth.print(", \"value\": ");
    myBluetooth.print(encoderValue);
    myBluetooth.println(" }");

    // Also print to Serial Monitor
    Serial.print("{ \"time\": ");
    Serial.print(currentMillis);
    Serial.print(", \"value\": ");
    Serial.print(encoderValue);
    Serial.println(" }");

    lastEncoderTime = currentMillis; // Update the last encoder time
  }

  previousStateCLK = currentStateCLK;
  lastButtonState = buttonState; // Update the last button state
  delay(1); // A short delay to reduce noise
}
