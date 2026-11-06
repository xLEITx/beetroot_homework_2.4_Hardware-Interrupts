#include <Arduino.h>

constexpr uint8_t BUTTON_PIN = 16;
uint16_t buttonPresses = 0;
volatile bool isButtonPressed = false;
bool isButtonAlreadyPressed = false;

void IRAM_ATTR buttonIsr(){
  isButtonPressed = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonIsr, FALLING);
}

void loop() {
  if (isButtonPressed)
  {
    noInterrupts();
    isButtonPressed = false;
    interrupts();

    if (digitalRead(BUTTON_PIN) == LOW && !isButtonAlreadyPressed)
    {
      isButtonAlreadyPressed = true;
      buttonPresses++;
      Serial.print("Presses count:");
      Serial.println(buttonPresses);
    }
  }
  
  if (digitalRead(BUTTON_PIN) == HIGH)
  {
    isButtonAlreadyPressed = false;
  }
  
  
}
