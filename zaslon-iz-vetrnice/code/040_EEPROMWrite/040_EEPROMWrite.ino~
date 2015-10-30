#include <EEPROM.h>

#define EEPROM_WRITES 100
#define PIN_NUM 4

volatile boolean interruptFlag;
volatile unsigned long loopTime;
int RPM;
byte EEPROMIndex = 1;

void setup(){

  // Omogocimo prekinitve na pinu 2 in nastavimo LED pin kot izhod
  pinMode(PIN_NUM, OUTPUT);
  attachInterrupt(0, isr, FALLING);
  
}

void loop(){

  if(interruptFlag){
    if(EEPROMIndex >= EEPROM_WRITES * 2){ // Kadar zapisemo vse hitrosti v EEPROM, se vklopi LED
      digitalWrite(PIN_NUM, HIGH);
      for(;;);
    }
    // Kadar se zgodi prekinitev(magnet gre mimo senzorja), izracunamo vrtljaje/minuto 
    // in vrednost zapisemo v EEPROM
    RPM = 60 / (loopTime / 1000.0);
    EEPROM.write(EEPROMIndex, (RPM & 0xFF00) >> 8);
    EEPROM.write(EEPROMIndex - 1, RPM & 0x00FF);
    interruptFlag = false;
    EEPROMIndex+=2;
  }
  
}

void isr(){
  
  static unsigned long lastTime;
  unsigned long currentTime = millis();
  
  // V prekinitvi izracunamo, koliko casa je trajal en krog
  loopTime = currentTime - lastTime;
  lastTime = currentTime;
  interruptFlag = true;
  
}
