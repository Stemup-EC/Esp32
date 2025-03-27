#define RELAY_PIN 5  // GPIO pin connected to relay

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);  // Set relay pin as output
  digitalWrite(RELAY_PIN, HIGH); // Ensure relay is off at startup (for active-low relays)
}

void loop() {
  Serial.println("Relay ON");
  digitalWrite(RELAY_PIN, LOW); // Turn ON relay (if active-low)
  delay(3000);  // Keep ON for 3 seconds

  Serial.println("Relay OFF");
  digitalWrite(RELAY_PIN, HIGH); // Turn OFF relay
  delay(3000);  // Keep OFF for 3 seconds
}
