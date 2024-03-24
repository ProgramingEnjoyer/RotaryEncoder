Overview

This Arduino sketch is designed to interface a rotary encoder with Bluetooth communication. The primary function is to read the encoder's rotation and button press, filter the rotation signal through a moving average, and send the data over Bluetooth. This project could be used as a basis for remote control applications, volume controls, or as an input device for a variety of projects.

Features

Reads rotation from a rotary encoder.
Debounces the encoder's button press.
Implements a moving average filter to smooth out the encoder's rotation readings.
Sends encoder data (rotation count and button press) over Bluetooth using a JSON format.
Serial output for monitoring and debugging purposes.

Requirements

Hardware:
1x Arduino Uno (or compatible) board
1x Generic Bluetooth module (e.g., HC-05, HC-06)
1x Rotary encoder with a push button
Jumper wires

Circuit Connections

Rotary Encoder to Arduino:
CLK pin to digital pin 4.
DT pin to digital pin 6.
SW pin to digital pin 5.
+(VCC) to 5V.
GND to ground.

HC-05 Bluetooth Module to Arduino:
TXD to digital pin 10 (RX).
RXD to digital pin 11 (TX).
VCC to 5V.
GND to ground.

Usage

Rotate the encoder to increase or decrease the value. The rotation is filtered through a moving average to smooth out jitter.
Press the encoder's button to reset the value to 0.
The encoder data is sent over Bluetooth at a set interval in milliseconds (interval variable), formatted as a JSON object containing the timestamp (time) and the current encoder value (value).

