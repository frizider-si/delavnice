#Prižiganje LED

Vsak Arduino program mora vsebovati vsaj naslednji blok kode:

    void setup() {
    }
    
    void loop() {
    }

Funkcija setup() se zažene takoj, ko se začne program izvajati. V njej ponavadi inicializiramo spremenljivke, vhodno-izhodne pine in različne naprave(senzorji, moduli). Ko se funkcija setup() izvede, se začne periodično izvajati funkcija loop(). V funkciji loop() ponavadi beremo in spreminjamo vrednost spremenljivk, ter pišemo in beremo podatke iz različnih naprav(senzorji, moduli) in vhodno-izhodnih pinov.

Če želimo prižgati LED diodo, moramo najprej v funkciji setup() nastaviti pin13(na pin13 je priklopljena zelena LED dioda, ki ima na Arduinotu oznako L) kot izhod(pin je lahko nastavljen tudi kot vhod. V tem primeru iz pina beremo podatke). To naredimo tako, da uporabimo funkcijo pinMode(). Nato s pomočjo funkcije digitalWrite() LED diodo vklopimo in izklopimo.

        setup(){
            pinMode(13, OUTPUT); // Pin 13 nastavimo kot izhod
            digitalWrite(13, HIGH); // Vklop LED
            delay(1000); // Počakamo 1000ms
            digitalWrite(13, LOW); // Izklop LED
        }
        
        void loop(){
        }

Iz zgornje kode je razvidno, da je blok funkcije loop() prazen. Vso kodo smo namreč zapisali v funkcijo setup(), kar pomeni, da se koda izvede samo enkrat(LED se vklopi in se čez eno sekundo izklopi. Funkcija delay() z argumentom 1000 ustavi program za 1000ms). Če bi želeli, da se LED dioda vklaplja in izklaplja v nedogled, bi morali kodo za vklop in izklop LED diode zapisati v funkcijo loop().

        void setup(){
            pinMode(13, OUTPUT); 
        }
        
        void loop(){
            digitalWrite(13, HIGH); 
            delay(1000); 
            digitalWrite(13, LOW); 
            delay(1000);
        }

Ker program med izvajanjem funkcije delay() ne počne nobenega koristnega dela, bomo namesto tega uporabili pogojni if stavek in funkcijo millis(), ki vrne število milisekund od začetka izvajanja programa.

        long naslednjiCas = 0, trenutniCas = 0;
        short stanjeLed = HIGH;

        void setup(){
            pinMode(13, OUTPUT);
        }
        
        void loop(){
            trenutniCas = millis();
            if(trenutniCas >= naslednjiCas){
                digitalWrite(13, stanjeLed);
                if(stanjeLed == HIGH)
                    stanjeLed = LOW;
                else
                  stanjeLed = HIGH;
                naslednjiCas = trenutniCas + 1000;
            }
        }

#LED vlak

Napisali bomo program, ki bo vklopil in izklopil sedem diod. Najprej bo vklopil prvo, nato drugo, tretjo, ..., sedmo LED diodo. Nato bo izklopil sedmo, šesto, ..., prvo. Ko bo prišel ponovno do prve LED diode, bo celoten postopek ponovil.

Pri tem programu potrebujemo sedem pinov(pin3 - pin9) na katere priklopimo LED diode. Vseh sedem pinov je potrebno nastaviti kot izhod. To storimo s pomočjo funkcije pinMode(), pri tem pa si pomagamo s pomočjo for() zanke.

        byte nextPin;
        long switchAt;
        byte direction;

        void setup() {
            int i;
            for(i = 3; i < 10; i++) {
                pinMode(i, OUTPUT);
            }
            digitalWrite(3, HIGH);
            nextPin = 3;
            direction = 1;
            switchAt = millis() + 1000;
        }

        void loop() {
            if (millis() >= switchAt) {
                digitalWrite(nextPin, LOW);
                if (nextPin == 3) { // obrni desno, če si na levi
                    direction = 1;
                }
                if (nextPin == 9) { // obrni levo, če si na desni
                    direction = -1;
                }
                nextPin += direction;
                digitalWrite(nextPin, HIGH);
                switchAt += 1000;
            }
        }

V funkciji loop() prižigamo in ugašamo LED diode. Spremenljivka nextPin nam pove, katero LED diodo trenutno prižigamo oziroma ugašamo. Spremenljivka direction pa nam pove, v kateri smeri prižigamo oziroma ugašamo LED diode.

#Vklop LED s pomočjo magnetnega senzorja

Pri tem programu bomo spoznali koncept prekinitev. Prekinitev je vezana na nek dogodek, ki je lahko zunanjega ali notranjega izvora. V našem primeru bo prekinitev zunanjega izvora, ker jo bo preko pina pin2 prožil magnetni senzor. Kadar bo senzor zaznal magnet, bo Arduinotu to sporočil tako, da bo pin2 postavil v visok logični nivo(3.3v ali 5v). V primeru, da Arduino zazna visoko logično stanje na pinu 2, se izvede funkcija isr(), ki vklopi LED.

        void setup(){
            // Na pinu 2 nastavimo interrupt
            attachInterrupt(0, isr, RISING);
            // Pin 13 nastavimo kot izhod
            pinMode(13, OUTPUT);
        }

        void loop(){
        }

        void isr() {
            digitalWrite(13, HIGH); // Vklopimo LED
        }

#Spust kovinske kroglice

Koda je enaka kodi za vklop LED s pomočjo magnetnega senzorja. Spremeniti moramo samo stevilko pina v funkciji pinMode() in digitalWrite().

#Čas enega slota

Navodila za vezavo LCD zaslona so dostopna na: http://www.protorabbit.nl/2012/01/28/lcd-pc1602-h/

        #include <LiquidCrystal.h>
        
        #define CONTRAST_PIN 9
        #define RS 13
        #define RW 12
        #define E 11
        #define D4 6
        #define D5 5
        #define D6 4
        #define D7 3
        #define TIME_PRESCALER 1000000.0
        
        volatile double casSlota;
        volatile byte magnetNum = 0;

        // Init display pins
        LiquidCrystal lcd(RS, RW, E, D4, D5, D6, D7);

        void setup(){
            // Na pinu 2 nastavimo interrupt
            attachInterrupt(0, isr, RISING);
            // Init lib to use two rows. Each row consists of 16 chars
            lcd.begin(16, 2);
            analogWrite(CONTRAST_PIN, 100);
        }

        void loop(){
  
            if(magnetNum == 2){
                lcd.print("Cas:");
                lcd.print(casSlota);
                lcd.print("s");
                for(;;);
            }
  
        }

        void isr() {
            static long prejsnjiCas;
            long trenutniCas;
 
            trenutniCas = micros();
            casSlota = (trenutniCas - prejsnjiCas) / TIME_PRESCALER;
            prejsnjiCas = trenutniCas;
            magnetNum++;
            
        }
        
# Izračun in izpis pospeška

Navodila za vezavo LCD zaslona so dostopna na: http://www.protorabbit.nl/2012/01/28/lcd-pc1602-h/

        #include <LiquidCrystal.h>
        
        #define CONTRAST_PIN 9
        #define RS 13
        #define RW 12
        #define E 11
        #define D4 6
        #define D5 5
        #define D6 4
        #define D7 3
        #define TIME_PRESCALER 1000000.0
        
        #define DOLZINA_SLOTA 0.2 // Dolzina slota
        #define T_SLOT_Z 0 // Zacetni cas je vedno 0
        
        #define POVPRECNA_HITROST_ZADNJEGA_SLOTA(T_SLOT_ZACETNA, T_SLOT_KONCNA) (DOLZINA_SLOTA / (T_SLOT_KONCNA - T_SLOT_ZACETNA)) // Povprecna hitrost v prejsnjem slotu
        #define POSPESEK_ZADNJEGA_SLOTA(V_SLOT_ZACETNA, V_SLOT_KONCNA, T_SLOT_ZACETNA, T_SLOT_KONCNA) ((V_SLOT_KONCNA - V_SLOT_ZACETNA) / (T_SLOT_KONCNA - T_SLOT_ZACETNA)) // Pospesek v prejsnjem slotu
        
        volatile double casSlota;
        volatile byte magnetNum;
        volatile boolean isrFlag;
        double t_slot_k, a_slot, v_povprecna_slot, v_slot_z, v_slot_k;

        // Init display pins
        LiquidCrystal lcd(RS, RW, E, D4, D5, D6, D7);

        void setup(){
            // Na pinu 2 nastavimo interrupt
            attachInterrupt(0, isr, RISING);
            // Init lib to use two rows. Each row consists of 16 chars
            lcd.begin(16, 2);
            analogWrite(CONTRAST_PIN, 100);
        }

        void loop(){
  
            if(isrFlag == true){
              if(magnetNum >= 2){
                t_slot_k = casSlota;
                v_slot_k = POVPRECNA_HITROST_ZADNJEGA_SLOTA(T_SLOT_Z, t_slot_k);
                if(magnetNum >= 3){    
                  a_slot = POSPESEK_ZADNJEGA_SLOTA(v_slot_z, v_slot_k, T_SLOT_Z, t_slot_k);
                  lcd.print("A:");
                  lcd.print(a_slot);
                  for(;;);
                }
                v_slot_z = v_slot_k;
              }
            isrFlag = false;
          }
        }

        void isr() {
            static long prejsnjiCas;
            long trenutniCas;
 
            trenutniCas = micros();
            casSlota = (trenutniCas - prejsnjiCas) / TIME_PRESCALER;
            prejsnjiCas = trenutniCas;
            magnetNum++;
            isrFlag = true;
            
        }

#Spust kroglice na tarčo

Navodila za vezavo LCD zaslona so dostopna na: http://www.protorabbit.nl/2012/01/28/lcd-pc1602-h/

        #include <Servo.h>
        #include <LiquidCrystal.h>

        #define TIME_PRESCALER 1000000.0
        #define CONTRAST_PIN 9
        #define SERVO_PIN 10
        #define RS 13
        #define RW 12
        #define E 11
        #define D4 6
        #define D5 5
        #define D6 4
        #define D7 3
        #define SERVO_START 115 // Drzalni kot
        #define SERVO_RELEASE 160 // Kot spusta

        #define VISINA_PREDMET 1.21 // V metrih
        #define G 9.83 // Gravitacijski pospesek v m/s^2
        #define DOLZINA_PISTE 2.15 // Dolzina piste v metrih
        #define DOLZINA_SLOTA 0.2 // Dolzina slota
        #define T_SLOT_Z 0 // Zacetni cas je vedno 0

        #define CAS_PADANJA_KROGLICE (sqrt(2 * VISINA_PREDMET / G) + 0.11) // Cas padanja kroglice
        #define POT_PADANJA_KROGLICE_PRI_V(V) (V * CAS_PADANJA_KROGLICE) // Prepotovana pot kroglice v smeri X, pri trenutni hitrosti V
        #define OPRAVLJENA_POT_PRI_T(V_ZACETNA, A, T) (V_ZACETNA * T + 0.5 * A * pow(T, 2)) // Opravljena pot pri Zacetni hitrosti V_ZACETNA, pospesku A in casu T
        #define POVPRECNA_HITROST_ZADNJEGA_SLOTA(T_SLOT_ZACETNA, T_SLOT_KONCNA) (DOLZINA_SLOTA / (T_SLOT_KONCNA - T_SLOT_ZACETNA)) // Povprecna hitrost v prejsnjem slotu
        #define TRENUTNA_HITROST_V_T(V_ZACETNA, POSPESEK, CAS) (V_ZACETNA + POSPESEK * CAS) // Trenutna hitrost
        #define POSPESEK_ZADNJEGA_SLOTA(V_SLOT_ZACETNA, V_SLOT_KONCNA, T_SLOT_ZACETNA, T_SLOT_KONCNA) ((V_SLOT_KONCNA - V_SLOT_ZACETNA) / (T_SLOT_KONCNA - T_SLOT_ZACETNA)) // Pospesek v prejsnjem slotu

        volatile uint8_t magnetNum;
        volatile double casZadnjegaSlota;
        volatile long zadnjiCas;
        volatile boolean isrFlag;
        double t_slot_k, t_trenutno, a_slot, v_povprecna_slot, v_slot_z, v_slot_k, s_prepotovana;
        Servo myservo;

        LiquidCrystal lcd(RS, RW, E, D4, D5, D6, D7);

        void setup(){
  
            attachInterrupt(0, isr, FALLING);
            lcd.begin(16, 2);
            myservo.attach(SERVO_PIN);
            myservo.write(SERVO_START);
            delay(2000);
            myservo.detach();
            analogWrite(CONTRAST_PIN, 100);
  
        } 

        void loop(){
  
  
            t_trenutno = (micros() - zadnjiCas) / TIME_PRESCALER;

            if(isrFlag == true){
                if(magnetNum >= 2){
                t_slot_k = casZadnjegaSlota;
                v_slot_k = POVPRECNA_HITROST_ZADNJEGA_SLOTA(T_SLOT_Z, t_slot_k);
                if(magnetNum >= 3)      
                    a_slot = POSPESEK_ZADNJEGA_SLOTA(v_slot_z, v_slot_k, T_SLOT_Z, t_slot_k);
                v_slot_z = v_slot_k;
                s_prepotovana += DOLZINA_SLOTA;
                }
      
            isrFlag = false;
      
            }
    
            if(magnetNum >= 3 && s_prepotovana + OPRAVLJENA_POT_PRI_T(v_slot_z, a_slot, t_trenutno) >= DOLZINA_PISTE - POT_PADANJA_KROGLICE_PRI_V(TRENUTNA_HITROST_V_T(v_slot_z, a_slot, t_trenutno))){
    
                myservo.attach(SERVO_PIN);
                myservo.write(SERVO_RELEASE);
                lcd.print("S:");
                lcd.print(s_prepotovana + OPRAVLJENA_POT_PRI_T(v_slot_z, a_slot, t_trenutno));
                lcd.print(" M:");
                lcd.print(magnetNum);
                lcd.print("P:");
                lcd.print(POT_PADANJA_KROGLICE_PRI_V(TRENUTNA_HITROST_V_T(v_slot_z, a_slot, t_trenutno)));
                lcd.setCursor(0, 1);
                lcd.print(" V:");
                lcd.print(TRENUTNA_HITROST_V_T(v_slot_z, a_slot, t_trenutno));
                lcd.print(" A:");
                lcd.print(a_slot);
                for(;;);
    
            }

        }


        void isr(){
   
            unsigned long trenutniCas;
 
            trenutniCas = micros();
            casZadnjegaSlota = (trenutniCas - zadnjiCas) / TIME_PRESCALER;
            zadnjiCas = trenutniCas;
            magnetNum++;  
            isrFlag = true;

        }
