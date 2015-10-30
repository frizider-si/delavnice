#include <EEPROM.h>

#define EEPROM_READS 100

int RPM;
short EEPROMIndex = 1;

void setup(){
  Serial.begin(9600);
  // Iz EEPROMA preberemo zapisane hitrosti in jih nato izpisemo
  while(EEPROMIndex < EEPROM_READS * 2){
    RPM = EEPROM.read(EEPROMIndex)  + 100 * EEPROM.read(EEPROMIndex - 1);
    Serial.print("RPM: ");
    Serial.println(RPM);
    EEPROMIndex +=2;
  }
  Serial.println("End!");
}

void loop() {}
