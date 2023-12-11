#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Set your ESP32's Bluetooth device name
  SerialBT.setPin("1234"); // Set a PIN for pairing (optional)
  //SerialBT.begin("ESP32");
}

void loop() {
  if (SerialBT.available()) {
    char receivedData = SerialBT.read();
    // Handle the received data as needed
  }

  // Send data over Bluetooth Classic
  SerialBT.print("27.3 C");
  delay(1000);
  SerialBT.print("50.0 C");
  delay(1000);
}
