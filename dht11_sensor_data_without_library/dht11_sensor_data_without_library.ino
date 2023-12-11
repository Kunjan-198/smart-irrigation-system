uint8_t data[5] = {0, 0, 0, 0, 0};

  // Send start signal
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, LOW);
  delay(18);
  digitalWrite(DHTPIN, HIGH);
  delayMicroseconds(30);
  pinMode(DHTPIN, INPUT);

  // Wait for the DHT11 to respond
  unsigned long startTime = micros();
  while (digitalRead(DHTPIN) == HIGH) {
    if (micros() - startTime > 50) {
      Serial.println("Timeout waiting for DHT response");
      return;
    }
  }

  // Read the data bits
  for (int i = 0; i < 40; i++) {
    startTime = micros();
    while (digitalRead(DHTPIN) == LOW) {
      if (micros() - startTime > 50) {
        Serial.println("Timeout waiting for bit start");
        return;
      }
    }

    startTime = micros();
    while (digitalRead(DHTPIN) == HIGH) {
      if (micros() - startTime > 80) {
        Serial.println("Timeout waiting for bit end");
        return;
      }
    }

    // Record the bit duration
    data[i / 8] <<= 1;
    if (micros() - startTime > 40) {
      data[i / 8] |= 1;
    }
  }

  // Verify checksum
  if (data[4] == (data[0] + data[1] + data[2] + data[3]) & 0xFF) {
    // Calculate humidity and temperature
    float humidity = data[0];
    float temperature = data[2];

    // Print the results
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("%  Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  } else {
    Serial.println("Checksum error");
  }

  delay(2000);  // Delay between readings
