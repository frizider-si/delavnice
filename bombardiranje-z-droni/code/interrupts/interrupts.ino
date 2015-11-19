#include "LiquidCrystal.h"
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 6);

void magnet() {
  lcd.clear();
  lcd.print("Pingvin");
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Frizider");
  lcd.setCursor(0, 1);
  lcd.print("Bomba");
  attachInterrupt(digitalPinToInterrupt(2), magnet, RISING);
}

void loop() {
}
