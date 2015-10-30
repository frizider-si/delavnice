#define LED_PIN 13
#define DELAY_MS 1000

unsigned long currentTime, previousTime;
byte ledStatus;

void setup(){
  // Nastavimo pin LED_PIN kot izhod
  pinMode(LED_PIN, OUTPUT);
}

void loop(){
  currentTime = millis();
  // Vsakih DELAY_MS vklopimo in izklopimo LED
  if(currentTime - previousTime > DELAY_MS){
    if (ledStatus == LOW) {
      ledStatus = HIGH;
    }
    else {
      ledStatus = LOW;
    }
    previousTime = currentTime;
    digitalWrite(LED_PIN, ledStatus);
  }
  
}
