#include "LiquidCrystal.h"
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
const int buttonPin = 7;
int clicks = 0;
int buttonState;

void setup() {
  pinMode(buttonPin, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Klikni na tipko");
}
 
void loop() {
  lcd.setCursor(0, 1);
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    clicks = clicks + 1;
    lcd.setCursor(0, 1);
    lcd.print(clicks);
    while (buttonState == HIGH) {
      buttonState = digitalRead(buttonPin);
    }
  }
}


