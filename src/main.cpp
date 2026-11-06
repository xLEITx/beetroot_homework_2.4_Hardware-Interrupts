#include <Arduino.h>

constexpr uint8_t BUTTON_PIN = 16;
volatile uint16_t buttonPresses = 0;
volatile bool isButtonPressed = false;

void IRAM_ATTR buttonIsr(){
  buttonPresses++;
  isButtonPressed = true;
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonIsr, FALLING);
}

void loop() {
  if (isButtonPressed)
  {
    Serial.print("Number of presses:");
    Serial.println(buttonPresses);
    isButtonPressed = false;
  }
  
  
}
