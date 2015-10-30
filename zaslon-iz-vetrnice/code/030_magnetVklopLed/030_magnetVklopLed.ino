#define PIN_NUM 4

void setup(){
  // Na pinu 2 nastavimo interrupt
  attachInterrupt(0, isr, RISING);
  // Pin PIN_NUM nastavimo kot izhod
  pinMode(PIN_NUM, OUTPUT);
  
}

void loop(){
  
}

void isr() {
  digitalWrite(PIN_NUM, HIGH); 
}
