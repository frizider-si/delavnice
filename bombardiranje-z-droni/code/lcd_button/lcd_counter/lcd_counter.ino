#include "LiquidCrystal.h"
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
const int buttonPin = 7;
int counter;
boolean counting = false;
long startTime;

void setup() {
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Cas v sekundah");
}
 
void loop() {
  float time;
  int buttonState;
  
  if (counting) {
    time = float(millis() - startTime) / 1000.0;
    lcd.setCursor(0, 1);
    lcd.print(time, 1);
  }
  
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    startTime = millis();
    while (buttonState == HIGH) {
      buttonState = digitalRead(buttonPin);
    }
    if (!counting) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cas v sekundah");
    }
    counting = !counting;
  }
}


