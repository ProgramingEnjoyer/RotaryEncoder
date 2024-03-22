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

void setup() {
  Serial.begin(9600);
  myBluetooth.begin(9600);

  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);

  previousStateCLK = digitalRead(clkPin);
}

void loop() {
  currentStateCLK = digitalRead(clkPin);

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
  delay(1); // A short delay to reduce noise
}
