#define MQ2_PIN 34   // Analog pin for MQ-2 sensor
#define BUZZER_PIN 26 // Digital pin for Buzzer

int gasThreshold = 2000; // Threshold for triggering alarm

void setup() {
    Serial.begin(115200);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer initially
}

void loop() {
    int gasLevel = analogRead(MQ2_PIN); // Read MQ-2 sensor value
    Serial.print("Gas Level: ");
    Serial.println(gasLevel);

    if (gasLevel > gasThreshold) {
        Serial.println("⚠️ Gas Detected! Triggering Alarm...");
        digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
    } else {
        digitalWrite(BUZZER_PIN, LOW);  // Turn off buzzer
    }

    delay(2000); // Delay for stability
}
