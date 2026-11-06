#include <Arduino.h>

constexpr uint8_t BUTTON_PIN = 16;

uint16_t buttonCounter = 0;

uint32_t lastPollTime = 0;
uint32_t lastDebounceTime = 0;

bool lastButtonState = HIGH;
bool stableButtonState = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  uint32_t currentTime = millis();

  if (currentTime - lastPollTime >= 5) {

    lastPollTime = currentTime;

    bool currentButtonState = digitalRead(BUTTON_PIN);

    if (currentButtonState != lastButtonState) {

      lastButtonState = currentButtonState;
      lastDebounceTime = currentTime;
    }

    if ((currentTime - lastDebounceTime >= 50) &&
        (stableButtonState != currentButtonState)) {

      stableButtonState = currentButtonState;

      if (stableButtonState == LOW) {

        buttonCounter++;

        Serial.print("Button counter: ");
        Serial.println(buttonCounter);
      }
    }
  }
}


