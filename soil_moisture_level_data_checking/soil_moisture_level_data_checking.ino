// Analog soil moisture sensor pin
const int soilMoisturePin = 26;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Map the analog value to a moisture percentage (adjust the values based on your sensor)
  int moisturePercentage = map(soilMoistureValue, 0, 4095, 0, 100);

  // Print the moisture percentage
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  delay(1000); // Wait for 2 seconds before the next reading
}
