#include "LiquidCrystal.h"
// POWERTIP LCD PC1602 - H
// LiquidCrystal display with:
// rs lcd  pin 4 on arduino pin 12
// rw lcd pin 5 on arduino pin 11
// enable lcd  pin 6 arduino on pin 10
// d4,d5,d6,d7 lcd pins 11, 12, 13, 14 on arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
 
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Cas v sekundah");
}
 
void loop() {
  // set the cursor to column 8, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
}
 
// rs on pin 12
// rw on pin 11
// enable on pin 10
