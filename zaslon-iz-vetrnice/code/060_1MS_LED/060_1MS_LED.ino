#define DELAY_MS 1
#define NUM_LEDS 7

// Mogoce priloznost, da vidijo koncni avtomat?
#define WAIT 0
#define TURN_ON 1
#define TURN_OFF 2

byte action; // To je v bistvu stanje
long executeAt; // Tole je ravno obraten koncept od lastTime, a zelo primeren za avtomat, po mojem.
const byte ledPins[] = {3,4,5,6,7,8,9}; // Je const tule res potreben?

void setup(){
  byte i;
  // Nastavimo pine ledPins kot izhod
  for(i = 0; i < NUM_LEDS; i++)
    pinMode(ledPins[i], OUTPUT);
  // Vklopimo prekinitev na pinu 2
  attachInterrupt(0, isr, RISING);
  action = WAIT;
}

void loop(){
  if ((action == TURN_ON) && (millis() >= executeAt)) {
    setLeds(HIGH);
    action = TURN_OFF;
    executeAt = millis() + DELAY_MS;
  }
  if ((action == TURN_OFF) && (millis() >= executeAt)) {
    setLeds(LOW);
    action = WAIT;
  }
}

// Tule prvic vidijo funkcijo, ki jo pisejo sami.
// Poleg tega ima ta funkcija argumente.
// Mogoce tule raje najprej naredijo brez funkcije, potem pa tisti, ki jim gre dobro, naredijo se funkcijo.
void setLeds(byte state){
  byte i;
  // Nastavi LEDice na 'state'
  for(i = 0; i < NUM_LEDS; i++){
    digitalWrite(ledPins[i], state);
  }
}

void isr(){
  action = TURN_ON;
  executeAt = millis();
}
