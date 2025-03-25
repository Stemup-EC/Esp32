#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

// WiFi Credentials
#define WIFI_SSID "abcd"
#define WIFI_PASSWORD "123456789"

// Firebase Credentials
#define DATABASE_URL "https://esp32-7b9a0-default-rtdb.firebaseio.com/"  // Use your own firebase URL and SECRET 
#define DATABASE_SECRET "fusvmBhqpIy4tvPY2yLqjxjSAdTNCnuKmZIbNFa5"

// Firebase Objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// DHT11 Configuration
#define DHT_PIN 4  // GPIO pin connected to DHT11
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);

    // Start DHT sensor
    dht.begin();

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
    float temperature = dht.readTemperature();  // Read temperature in Celsius
    float humidity = dht.readHumidity();       // Read humidity percentage

    // Check if readings are valid
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C | Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    // Push temperature data to Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "/DHT11/temperature", temperature)) {
        Serial.println("Temperature sent to Firebase");
    } else {
        Serial.print("Firebase Error: ");
        Serial.println(fbdo.errorReason());
    }

    // Push humidity data to Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "/DHT11/humidity", humidity)) {
        Serial.println("Humidity sent to Firebase");
    } else {
        Serial.print("Firebase Error: ");
        Serial.println(fbdo.errorReason());
    }

    delay(5000);  // Send data every 5 seconds
}
