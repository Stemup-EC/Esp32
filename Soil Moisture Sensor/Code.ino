#define SOIL_SENSOR_PIN 34  // Analog pin for Soil Sensor

void setup() {
  Serial.begin(115200);
}

void loop() {
  int soilValue = analogRead(SOIL_SENSOR_PIN); // Read analog value
  Serial.print("Soil Moisture Level: ");
  Serial.println(soilValue);
  
  delay(1000); // Read every second
}
