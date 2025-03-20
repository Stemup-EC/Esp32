#define LED_PIN 4  // Using GPIO 4 (D4)

void setup() {
  pinMode(LED_PIN, OUTPUT);  // Set GPIO 4 as an output
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // Turn LED ON
  delay(1000);                 // Wait 1 second
  digitalWrite(LED_PIN, LOW);  // Turn LED OFF
  delay(1000);                 // Wait 1 second
}
