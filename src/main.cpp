#include <Arduino.h>

constexpr uint8_t BUTTON_PIN = 16;
uint16_t buttonPresses = 0;
volatile bool isButtonPressed = false;
uint32_t lastInterruptTime = 0;

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
    uint32_t currentTime = millis();

    if (currentTime - lastInterruptTime > 50)
    {
      buttonPresses++;
      lastInterruptTime = currentTime;
      Serial.print("Presses count:");
      Serial.println(buttonPresses);
    }
    


  }
  
  
}
