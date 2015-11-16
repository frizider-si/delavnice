#Prikaz sekundnega in minutnega kazalca

Najprej v funkciji setup() s pomočjo for() zanke nastavimo pine s stevilkami 3,4,5,6,7,8 in 9 kot izhod.

    for(i = 0; i < NUM_LEDS; i++)
        pinMode(ledPins[i], OUTPUT);
        
Kadar gre magnet mimo magnetnega senzorja, se v spremenljivko loopTime shrani čas trajanja zadnjega kroga.

    void isr(){
 
        unsigned long currentTime = micros();
  
        // Racunanje casa enega kroga
        loopTime = currentTime - prevTime;
        prevTime = currentTime;

    }
      
V funkciji loop() s pomočjo trenutnega časa in časa zadnjega kroga izrisujemo minutni in sekundni kazalec. Sekundni kazalec vsako sekundo pomaknemo naprej za 6 stopinj. Kadar sekundni kazalec doseže 60 sekund, minutni kazalec premaknemo naprej za 6 stopinj.

    void loop(){
  
      // Izrisujemo crti za minute in sekunde. Sekundna crta se premakne vsako sekundo, minutna pa vsako minuto.
      if(millis() - clockTime >= 1000){
        // Povecevanje sekund in minut. Kadar pridejo sekunde na 0, se povecajo minute za +1
        if((seconds = ((++seconds) % 60)) == 0 && (minutes = ((++minutes) % 60)) == 0);
        clockTime = millis();
      }
      // Pri izrisu se pomikamo za 6 stopinj(360 / 60 = 6)
      seconds == minutes ? showLeds(seconds * 6, 2, 0b01010101): showLeds(seconds * 6, 2, 0b01010101),showLeds(minutes * 6, 2, 0b01010101);
  
    }

    void showLeds(short angle, short angleWidth, uint8_t mask){
  
      unsigned long currentTime;
      // Kadar cas, preracunan v stopinje ustreza stopinjam "angle", vklopimo LED. LED so vklopljene toliko casa, dokler ne dosezejo kota "angle" + "angleWidth"
      currentTime = micros();
      if((currentTime - prevTime) * 360.0 / loopTime >= angle && (currentTime - prevTime) * 360.0 / loopTime <= angle + angleWidth)
        manageLeds(mask);
      if((micros() - prevTime) * 360.0 / loopTime > angle + angleWidth)
        manageLeds(0);
  
    }

#Celotna koda programa

    volatile unsigned long loopTime = 1;
    volatile unsigned long prevTime = 1;
    byte pins[] = {3,4,5,6,7,8,9};
    byte seconds, minutes;
    unsigned long clockTime;

    void setup(){
  
        byte i;
  
        // LED pine nastavimo kot izhod
        for(i = 0; i < sizeof(pins); i++)
            pinMode(pins[i],OUTPUT);
  
        // Omogocimo prekinitve na pinu 2
        attachInterrupt(0, interrupt, FALLING);
  
    }

    void loop(){
  
        // Izrisujemo crti za minute in sekunde. Sekundna crta se premakne vsako sekundo, minutna pa vsako minuto.
        if(millis() - clockTime >= 1000){
            // Povecevanje sekund in minut. Kadar pridejo sekunde na 0, se povecajo minute za +1
            if((seconds = ((++seconds) % 60)) == 0 && (minutes = ((++minutes) % 60)) == 0);
                clockTime = millis();
        }
        // Pri izrisu se pomikamo za 6 stopinj(360 / 60 = 6)
        seconds == minutes ? showLeds(seconds * 6, 2, 0b01010101): showLeds(seconds * 6, 2, 0b01010101),showLeds(minutes * 6, 2, 0b01010101);
  
    }

    void showLeds(short angle, short angleWidth, uint8_t mask){
  
        unsigned long currentTime;
        // Kadar cas, preracunan v stopinje ustreza stopinjam "angle", vklopimo LED. LED so vklopljene toliko casa, dokler ne dosezejo kota "angle" + "angleWidth"
        currentTime = micros();
        if((currentTime - prevTime) * 360.0 / loopTime >= angle && (currentTime - prevTime) * 360.0 / loopTime <= angle + angleWidth)
            manageLeds(mask);
        if((micros() - prevTime) * 360.0 / loopTime > angle + angleWidth)
            manageLeds(0);
  
    }

    void manageLeds(uint8_t mask){

        PORTB = (mask >> 5) & 0b00000011;
        PORTD = (mask << 3) & 0b11111000;
  
    }

    void interrupt(){
 
        unsigned long currentTime = micros();
  
        // Racunanje casa enega kroga
        loopTime = currentTime - prevTime;
        prevTime = currentTime;

    }
