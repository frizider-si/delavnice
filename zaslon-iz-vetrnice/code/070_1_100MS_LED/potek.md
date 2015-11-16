#Vklop LED za 1ms, 2ms, ..., 100ms

Najprej v funkciji setup() s pomočjo for() zanke nastavimo pine s stevilkami 3,4,5,6,7,8 in 9 kot izhod.

    for(i = 0; i < NUM_LEDS; i++)
        pinMode(ledPins[i], OUTPUT);
        
Ko gre magnet mimo magnetnega senzorja, se LED prižgejo za 1ms, v naslednjem krogu za 2ms, nato za 3ms,... V zadnjem krogu so LED prižgane 100ms. Nato se čas ponovno nastavi na 1ms in celoten postopek se ponovi.

    void loop(){
      // Ko se zgodi prekinitev, se LED prizgejo. Intervali so 1ms, 2ms, ..., 100ms
      if(interruptFlag){
        if(!ledOnFlag){
          showLeds(true);
          lastTime = millis();
          ledOnFlag = true;
        }
        if(millis() - lastTime > delay_ms){
          showLeds(false);
         delay_ms < 100 ? delay_ms++ : delay_ms = 1;
         ledOnFlag = false;
         interruptFlag = false;
        }
      }
    }
#Celotna koda programa

    volatile boolean interruptFlag, ledOnFlag;
    unsigned long lastTime;
    const byte ledPins[] = {3,4,5,6,7,8,9};
    short delay_ms = 1;

    void setup(){

        byte i;
        // Pine ledPins nastavimo kot izhod
        for(i = 0; i < sizeof(ledPins); i++)
            pinMode(ledPins[i], OUTPUT);
        // Vklop prekinitev na pinu 2
        attachInterrupt(0, isr, FALLING);
  
    }

    void loop(){
        // Ko se zgodi prekinitev, se LED prizgejo. Intervali so 1ms, 2ms, ..., 100ms
        if(interruptFlag){
            if(!ledOnFlag){
                showLeds(true);
                lastTime = millis();
                ledOnFlag = true;
            }
        }
        if(millis() - lastTime > delay_ms){
            showLeds(false);
            delay_ms < 100 ? delay_ms++ : delay_ms = 1;
            ledOnFlag = false;
            interruptFlag = false;
        }
    }

    void showLeds(boolean show){
  
        byte i;
        // Vklop, oziroma izklop LED
        for(i = 0; i < sizeof(ledPins); i++){
            show == true ? digitalWrite(ledPins[i], HIGH) : digitalWrite(ledPins[i], LOW);
        }
  
    }

    void isr(){
        interruptFlag = true;
    }
