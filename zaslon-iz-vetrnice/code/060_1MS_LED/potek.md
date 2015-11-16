#Vklop LED za 1ms

Najprej v funkciji setup() s pomočjo for() zanke nastavimo pine s stevilkami 3,4,5,6,7,8 in 9 kot izhod.

    for(i = 0; i < NUM_LEDS; i++)
        pinMode(ledPins[i], OUTPUT);
  
Kadar se zgodi prekinitev, se v funkciji isr() v spremenljivko executeAt shrani trenutni čas. 

        void isr(){
            action = TURN_ON;
            executeAt = millis();
        }
        
V funkciji loop() se nato izvede prvi pogojni stavek(Pogoj je izpolnjen. Spremenljivka action ima vrednost TURN_ON, ki se v spremenljivko shrani takrat, ko gre magnet mimo magnetnega senzorja), ki vklopi LED in čas v spremenljivki executeAt poveča za 1ms. Kadar preteče čas 1ms, se izvede drugi pogojni stavek, ki LED izklopi(V prvemu pogojnemu stavku pridobi spremenljivka action vrednost TURN_OFF).

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
