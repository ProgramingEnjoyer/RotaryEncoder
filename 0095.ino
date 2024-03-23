#include <SoftwareSerial.h>

SoftwareSerial myBluetooth(10, 11); // RX, TX

// Define rotary encoder pins
const int clkPin = 4;
const int dtPin = 6;
const int swPin = 5;

int currentStateCLK;
int previousStateCLK;
int encoderValue = 0; // We'll count the encoder steps in this variable
unsigned long lastEncoderTime = 0; // Time of the last encoder change
int buttonState; // Current state of the button
int lastButtonState = HIGH; // Previous state of the button

void setup() {
  Serial.begin(9600);
  myBluetooth.begin(9600);

  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP); // Set the button as input with internal pull-up resistor

  previousStateCLK = digitalRead(clkPin);
}

void loop() {
  currentStateCLK = digitalRead(clkPin);
  buttonState = digitalRead(swPin); // Read the button state

  // Check if button state has changed to LOW (button pressed)
  if (buttonState == LOW && lastButtonState == HIGH) {
    encoderValue = 0; // Reset encoder value
    // Debounce delay to avoid accidental quick presses
    delay(50); 
  }

  if (currentStateCLK != previousStateCLK) {
    unsigned long currentMillis = millis(); // Get the current time

    if (digitalRead(dtPin) != currentStateCLK) {
      encoderValue++; // Increment the encoder value
    } else {
      encoderValue--; // Decrement the encoder value
    }

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
