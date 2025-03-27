#define RELAY_PIN 5    // GPIO pin connected to relay
#define BUTTON_PIN 4   // GPIO pin connected to push button

bool relayState = false;  // Stores relay state
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);  
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Internal pull-up enabled
  digitalWrite(RELAY_PIN, HIGH);  // Relay starts OFF (active-low)
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) { // Detect button press
    relayState = !relayState;  // Toggle relay state
    digitalWrite(RELAY_PIN, relayState ? LOW : HIGH); // Active-low relay
    Serial.print("Relay State: ");
    Serial.println(relayState ? "ON" : "OFF");
    delay(300); // Debounce delay
  }

  lastButtonState = buttonState;
}
