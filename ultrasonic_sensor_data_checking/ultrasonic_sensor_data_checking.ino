#define TRIGGER_PIN 27  // GPIO pin for trigger
#define ECHO_PIN    12  // GPIO pin for echo

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Set your ESP32's Bluetooth device name
  SerialBT.setPin("1234"); // Set a PIN for pairing (optional)
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration, distance;

  // Trigger the sensor by sending a 10 microsecond pulse
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure the duration of the echo pulse
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters
  distance = (duration / 2) * 0.0343;
    delay(1000);
  // Print the distance to the serial monitor
  String my="1:2:3:";
  my=my+String(distance);
 
  SerialBT.print(my);
  
  delay(1000);  // Wait for 1 second before the next measurement
}
