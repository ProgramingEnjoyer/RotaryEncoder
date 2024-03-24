# Arduino Bluetooth Rotary Encoder

This Arduino sketch interfaces a rotary encoder with Bluetooth communication for applications such as remote controls, volume controls, or as an input device for various projects. It reads the encoder's rotation, debounces the button press, applies a moving average filter to smooth the rotation readings, and sends the data over Bluetooth in JSON format. Serial output is also available for monitoring and debugging.

## Features

- **Reads Rotation:** Captures rotation from a rotary encoder.
- **Debounces Button Press:** Ensures stable button press readings.
- **Moving Average Filter:** Smooths out the encoder's rotation readings.
- **Bluetooth Communication:** Sends encoder data (rotation count and button press) over Bluetooth using JSON format.
- **Serial Output:** For monitoring and debugging purposes.

## Requirements

### Hardware

- 1x Arduino Uno (or compatible) board
- 1x Generic Bluetooth module (e.g., HC-05, HC-06)
- 1x Rotary encoder with a push button
- Jumper wires

### Circuit Connections

#### Rotary Encoder to Arduino

- CLK pin to digital pin 4
- DT pin to digital pin 6
- SW pin to digital pin 5
- +(VCC) to 5V
- GND to ground

#### HC-05 Bluetooth Module to Arduino

- TXD to digital pin 10 (RX)
- RXD to digital pin 11 (TX)
- VCC to 5V
- GND to ground

## Usage

- **Rotation:** Rotate the encoder to increase or decrease the value. The rotation is filtered through a moving average to reduce jitter.
- **Button Press:** Press the encoder's button to reset the value to 0.
- **Bluetooth Communication:** The encoder data is sent over Bluetooth at a set interval (modifiable in the `interval` variable), formatted as a JSON object containing the `timestamp` (time) and the current encoder `value`.

## Example JSON Data Format

```json
{
  "time": "2024-03-24T12:34:56Z",
  "value": 10
}
