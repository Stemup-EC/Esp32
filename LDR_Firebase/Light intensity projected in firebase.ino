#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// WiFi Credentials
#define WIFI_SSID "abcd"
#define WIFI_PASSWORD "123456789"

// Firebase Credentials
#define DATABASE_URL "https://esp32-7b9a0-default-rtdb.firebaseio.com/"  // use your own URL and SECRET
#define DATABASE_SECRET "fusvmBhqpIy4tvPY2yLqjxjSAdTNCnuKmZIbNFa5"

// Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// LDR pin
const int LDR_PIN = 34;  // Analog pin for LDR

void setup() {
    Serial.begin(115200);
    
    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    // Firebase setup
    config.database_url = DATABASE_URL;
    config.signer.tokens.legacy_token = DATABASE_SECRET;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void loop() {
    int rawValue = analogRead(LDR_PIN);  // Read raw ADC value (0-4095)
    int lightIntensity = map(rawValue, 0, 4095, 1, 500);  // Scale to 1-500

    Serial.print("Raw ADC: ");
    Serial.print(rawValue);
    Serial.print(" | Mapped Light Intensity: ");
    Serial.println(lightIntensity);

    // Push data to Firebase
    if (Firebase.RTDB.setInt(&fbdo, "/light_intensity", lightIntensity)) {
        Serial.println("Data sent to Firebase successfully");
    } else {
        Serial.print("Firebase Error: ");
        Serial.println(fbdo.errorReason());
    }

    delay(5000);
}
