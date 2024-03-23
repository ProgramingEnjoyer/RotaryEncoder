Overview
This Arduino sketch provides an example of interfacing with a rotary encoder and a button to capture user input and send the data over Bluetooth. It is designed to work with a generic Bluetooth module connected via the Arduino's serial interface. The encoder's rotation (clockwise and counter-clockwise) changes an integer value, which, along with the current time in milliseconds, is transmitted over Bluetooth and the Serial Monitor.

Requirements
Hardware:
1x Arduino Uno (or compatible) board
1x Generic Bluetooth module (e.g., HC-05, HC-06)
1x Rotary encoder with a push button
Jumper wires

Software:
Arduino IDE (for compiling and uploading the sketch to the board)
Hardware Setup
Bluetooth Module:
Connect the Bluetooth module's RX (Receiver) pin to Digital Pin 10 on the Arduino.
Connect the Bluetooth module's TX (Transmitter) pin to Digital Pin 11 on the Arduino.
Ensure the Bluetooth module is powered correctly, typically with 3.3V to VCC and GND to a ground pin on the Arduino.
Rotary Encoder:
Connect the CLK pin of the rotary encoder to Digital Pin 4 on the Arduino.
Connect the DT pin of the rotary encoder to Digital Pin 6 on the Arduino.
Connect the SW pin (button output) of the rotary encoder to Digital Pin 5 on the Arduino.
Ensure the rotary encoder is powered correctly, with VCC to 5V and GND to a ground pin on the Arduino.
