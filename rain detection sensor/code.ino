#define RAIN_SENSOR_PIN 34  // Analog pin for rain sensor
#define DIGITAL_RAIN_PIN 32 // Digital pin for rain sensor

void setup() {
  Serial.begin(115200);
  pinMode(DIGITAL_RAIN_PIN, INPUT); // Set digital pin as input
}

void loop() {
  int rainAnalog = analogRead(RAIN_SENSOR_PIN);  // Read analog value
  int rainDigital = digitalRead(DIGITAL_RAIN_PIN); // Read digital value

  Serial.print("Analog Rain Sensor Value: ");
  Serial.println(rainAnalog);

  if (rainAnalog < 500) {  
    Serial.println("🌧 Heavy Rain Detected!");
  } else if (rainAnalog >= 500 && rainAnalog < 800) {
    Serial.println("🌦 Light Rain or Humid Condition.");
  } else {
    Serial.println("☀ No Rain.");
  }

  Serial.print("Digital Sensor Output: ");
  Serial.println(rainDigital ? "☀ Dry" : "🌧 Wet");

  delay(1000); // Update every second
}
