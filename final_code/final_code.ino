#include "BluetoothSerial.h"
#include <driver/ledc.h>

BluetoothSerial SerialBT;
const int soilMoisturePin = 26;
String result="";

//char prev_data="0";

#define TRIGGER_PIN 27  // GPIO pin for trigger
#define ECHO_PIN    12  // GPIO pin for echo

#define DHTPIN 33  // DHT11 data pin, change as needed

// Motor A
int motor1Pin1 = 21; 
int motor1Pin2 = 18; 
int enable1Pin = 32; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int duty = 200;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Set your ESP32's Bluetooth device name
  SerialBT.setPin("1234"); // Set a PIN for pairing (optional)
  //SerialBT.begin("ESP32");
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
    // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);

}

void loop() {

  if (SerialBT.available()) {
    char receivedData = SerialBT.read();
    // Handle the received data as needed
    Serial.println(receivedData);
//    if(receivedData==prev_data){
//     }else{
            if(receivedData=='F'){
         duty=0;
         digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
         ledcWrite(pwmChannel, duty);
         }else if(receivedData=='N'){
            duty=240;
         digitalWrite(motor1Pin1, HIGH);
          digitalWrite(motor1Pin2, LOW);
         ledcWrite(pwmChannel, duty);
         }else if(receivedData=='+'){
            if(duty<246){duty=duty+10;}
         digitalWrite(motor1Pin1, HIGH);
          digitalWrite(motor1Pin2, LOW);
         ledcWrite(pwmChannel, duty);     
         }else if(receivedData=='-'){
            if(duty>10){duty=duty-10;}
         digitalWrite(motor1Pin1, HIGH);
          digitalWrite(motor1Pin2, LOW);
         ledcWrite(pwmChannel, duty);      
          }
//          prev_data= receivedData;
//     }     
  }
  
  // Read the analog value from the soil moisture sensor
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Map the analog value to a moisture percentage (adjust the values based on your sensor)
  int moisturePercentage = map(soilMoistureValue, 0, 4095, 0, 100);
  delay(100); // Wait for 2 seconds before the next reading

  result=String(moisturePercentage)+":";

  /////////////////////////////////////////////////////////////

  result=result+"0:0:";

  //////////////////////////////////////////////////////////////

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

  // Print the distance to the serial monitor

  delay(100);  // Wait for 1 second before the next measurement

  result=result+String(distance)+":"; 
  // Send data over Bluetooth Classic
  delay(100);
  SerialBT.print(result);
}
