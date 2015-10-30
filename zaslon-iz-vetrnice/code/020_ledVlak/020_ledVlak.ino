#define DELAY 1000
#define NUM_OF_LEDS 7

byte currentPinNum = 0;
boolean desno = true;
unsigned long currentTime, previousTime = 0;
const byte ledPins[] = {3,4,5,6,7,8,9};

void setup(){

  byte i;
  
  // Nastavimo pine kot izhodne
  for(i = 0; i < sizeof(ledPins); i++)
    pinMode(ledPins[i], OUTPUT);
  
}

void loop(){
  currentTime = millis();
  if(currentTime - previousTime > DELAY){
    digitalWrite(ledPins[currentPinNum], LOW);
    if (desno && (currentPinNum == NUM_OF_LEDS - 1)) {
        desno = false;
    }
    if (!desno && (currentPinNum == 0)) {
      desno = true;
    }
    if (desno) {
      currentPinNum = currentPinNum + 1;
    }
    else {
      currentPinNum = currentPinNum - 1;
    }
    digitalWrite(ledPins[currentPinNum], HIGH);
    previousTime = currentTime;
  }
}
