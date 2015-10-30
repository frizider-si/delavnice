# Trajnejši pomnilnik

## Izpisovanje

Arduino ni preveč nezgovoren. Računalniki imajo zaslone, na katere kaj izpišejo. Na Arduina pa obesimo LEDice in z njimi utripamo. Kaj pa, ko bi želeli kaj izpisati?

Arduino lahko komunicira z računalnikom prek USB-ja. Ima funkcijo za izpis s čudnim imenom `Serial.print`, kot argument pa ji damo bodisi število, bodisi kako besedilo, ki ga moramo v tem primeru zapreti v narekovaje.

Preden prvič v programu izpisujemo, moramo vzpostaviti povezavo tako, da pokličemo `Serial.begin(9600)`. (9600 je argument, ki pove hitrost povezave. To naj vas ne vznemirja; ves `Serial.begin(9600)` jemljite kot magične besede, ki jih je potrebno izreči pred prvim `print`om.)

    void setup() {
        Serial.begin(9600);
        Serial.print("Pozdravljen, svet!");
    }

    void loop() {
    }

XXXXX Kako to potem vidimo?

(Zakaj `Serial.`? Da bi bile reči preglednejše, se vse, kar je povezano s pisanjem na USB, začne s `Serial.`. Kakšno zvezo ima "serial" z USB? Takšno, da "S" iz USB pomeni Serial (U je universal in B je bus). "Serijsko" pomeni, da USB deluje tako, da po žici potuje bit za bitom in ne, recimo, osem bitov vzporedno.)

## Štoparica

Napišimo nekaj bolj zanimivega. Spet bomo vzeli senzor za magnet. Senzorju bomo vsake toliko časa približali magnet, Arduino pa bo izpisoval čas, ki je minil med prejšnjim in tem približanjem magneta.

    long previousSeen, lastSeen;

    void setup() {
        Serial.begin(9600);
        previousSeen = lastSeen = -1;
        attachInterrupt(0, magnet, RISING);
    }

    // Tole skoraj deluje, a ne povsem!
    void loop() {
        if (lastSeen != -1) {
            Serial.print(lastSeen - previousSeen);
            previousSeen = lastSeen;
            lastSeen = -1;
        }
    }

    void magnet() {
        lastSeen = millis();
    }

Najprej poglejmo, kaj naredi `magnet`. V začetku je `lastSeen` enak -1. Tak čas ne obstaja; -1 bomo uporabili, da zabeležimo, da magneta bodisi še nismo videli, bodisi smo trenutno videnje že obdelali. Funkcija `magnet`, ki jo pokliče prekinitev, postavi `lastSeen` na trenutni čas. To je tisto, na kar preži `loop`: če je `lastSeen` različen od -1 (spomnimo se: `!=` pomeni različnost), izpiše čas, ki je minil med `lastSeen` in `previousSeen`. Nato postavi `previousSeen` na `lastSeen` (za naslednjič), `lastSeen` pa na -1. S tem si zabeleži, da je trenutno videnje obdelano in zdaj čakamo, da funkcija `magnet` spet sporoči (s tem, ko zapiše nov čas), da smo videli magnet.

Tole bo skoraj delovalo, samo še na začetno vrednost `previousSeen` moramo biti pozorni. Ko se magnet pokaže prvič, še ne smemo (in ne moremo) izpisati ničesar. Kako vemo, da magnet vidimo prvič? Po tem, da je `previousSeen` enak -1. Oni `print` je potrebno zapreti v še en `if`.

    long previousSeen, lastSeen;

    void setup() {
        Serial.begin(9600);
        previousSeen = lastSeen = -1;
        attachInterrupt(0, magnet, RISING);
    }

    void loop() {
        if (lastSeen != -1) {
            if (previousSeen != -1) {
                Serial.print(lastSeen - previousSeen);
            }
            previousSeen = lastSeen;
            lastSeen = -1;
        }
    }

    void magnet() {
        lastSeen = millis();
    }

## Izpis hitrosti kroženja

(Popolnoma pravilen naslov bi govoril o kotni hitrosti ali pa celo frekvenci, vendar bi to spominjalo na fiziko in bi utegnilo koga preplašiti.)

Zdaj nas zanima tole: imamo vetrnico, ki se vrti z neznano hitrostjo. Radi bi jo izmerili. To bomo storili tako, da bo Arduino pritrjen na vetrnico. Senzor za magnet bo nekje na robu, magnet pa tik ob vetrnici, tako da ga bo senzor opazil vsakič, ko bo šel mimo.

Kako bi to sprogramirali?

Kako - kako? Mar še nismo? Mar to ni točno program, ki smo ga pravkar napisali, le da ne hodi gora k Mohamedu temveč Mohamed h gori - namesto da bi približevali magnet senzorju, se senzor približuje magnetu.

Tule imamo slabo novico in dobro novico in slabo novico.

Slaba: priključiti Arduina na USB in zavrteti vetrnico ne zveni kot posebej dobra ideja.

Dobra: po tem, ko prenesemo program na Arduina, lahko USB izključimo in program bo tekel naprej (če ima Arduino svoje napajanje).

Slaba: `Serial.print` ne deluje brez USBja.

Vrteč se Arduino bo težko sproti izpisoval hitrosti. Nekako si jih bo moral zapomniti. Kasneje ga bomo priključili na USB in si bo zapisal, kar si je zapomnil, ko se je ringlšpilal.

Tule imamo dobro novico in slabo novico in dobro novico.

Dobra: Arduino ima kar nekaj pomnilnika, v katerega lahko zapisujemo številke, ki bodo ostale tam po koncu izvajanja programa. Z enim programom jih bomo zapisali vanj, z drugim prebrali.

Slaba: v ta pomnilnik lahko pišemo le bajte, torej številke med 0 in 255.

Dobra: se bomo že znašli. :)

Pomnilnik te vrste se imenuje EEPROM. Kaj to pomeni, ni pomembno. Lahko si ga predstavljate kot oštevilčene škatlice, v katere se funkcijo `EEPROM.write` shranimo številko, z `EEPROM.read` pa jo preberemo.

`EEPROM.write` ima dva argumenta: zaporedno številko škatlice in številko, ki jo želimo zapisati. Prva škatlica ima številko 0. Računalnikarji pač navadno štejejo od 0, ne od 1.

`EEPROM.read` ima en argument, namreč številko škatlice. Funkcija vrne, kar je napisano v dotični škatlici.

Torej: namesto, da bi s `Serial.print` *izpisovali* čase, jih z `EEPROM.write` shranjujmo. Sicer pa bo program približno enak.
    
    long previousSeen, lastSeen;

    void setup() {
        previousSeen = lastSeen = -1;
        attachInterrupt(0, magnet, RISING);
    }

    // Zmerno (a ne povsem) dobra ideja.
    void loop() {
        if (lastSeen != -1) {
            if (previousSeen != -1) {
                EEPROM.write(0, lastSeen - previousSeen);
            }
            previousSeen = lastSeen;
            lastSeen = -1;
        }
    }

    void magnet() {
        lastSeen = millis();
    }

Tale program ni čisto, kar želimo. Ker čase vedno znova in znova in znova zapisuje v škatlico 0, pri čemer vsak nov zapis povozi starega, bo po koncu programa (hm, ki se konča - kdaj?) v škatlici 0 le zadnji čas.

Popravimo ga tako, da najprej zapisujemo v škatlico 0, nato v 1, v 2... Potrebovali bomo spremenljivko, v kateri bo pisalo, katera škatlica je naslednja na vrsti.

    long previousSeen, lastSeen;
    long nextCell;

    void setup() {
        previousSeen = lastSeen = -1;
        nextCell = 0;
        attachInterrupt(0, magnet, RISING);
    }

    // Boljša, a še vedno ne povsem dobra ideja.
    void loop() {
        if (lastSeen != -1) {
            if (previousSeen != -1) {
                EEPROM.write(nextCell, lastSeen - previousSeen);
                nextCell++;
            }
            previousSeen = lastSeen;
            lastSeen = -1;
        }
    }

    void magnet() {
        lastSeen = millis();
    }

V `setup` smo nastavili `nextCell` na 0. V zanki zapišemo v škatlo `nextCell` in nato povečamo `nextCell`, da bomo prihodnjič pisali v naslednjo.

To bi bilo v redu, če bi bil Arduinov EEPROM neskončen. Vendar ni. Velikost je odvisna od modela; nekateri imajo 512 bajtov (škatlic), največji pa 4096.

Tule bomo naredili takole: prebrali bomo 100 obratov. Po stotih obratih bomo prižgali diodo, da se bo vedelo, da je nabiranje podatkov končano.

Kako bomo dobili število obratov? Preprosto: ko bi morali pisati v celico 100, ne pišemo, temveč prižgemo diodo.

    long previousSeen, lastSeen;
    long nextCell;

    void setup() {
        previousSeen = lastSeen = -1;
        nextCell = 0;
        pinMode(13, OUTPUT);
        attachInterrupt(0, magnet, RISING);
    }

    void loop() {
        if (nextCell == 100) {
            digitalWrite(13, HIGH);
        }
        else {
            if (lastSeen != -1) {
                if (previousSeen != -1) {
                    EEPROM.write(nextCell, lastSeen - previousSeen);
                    nextCell++;
                }
                previousSeen = lastSeen;
                lastSeen = -1;
            }
        }
    }

    void magnet() {
        lastSeen = millis();
    }

Funkcija `loop` ima zdaj že tri `if`e, a ker smo jih dodajali postopno, jim najbrž lahko sledimo, ne? Dodatni, zunanji, najprej preveri, da ni `nextCell` morda že enak 100. Če je, prižgemo diodo. `nextCell` pustimo pri miru, tako da bomo, no ja, stalno prižigali in prižigali diodo. Nič hudega, ne bo je skurilo.

Če `nextCell` še ni 100, pa vse teče tako kot prej.


## Za počasnejše vetrnice

Tole deluje samo za vetrnice, ki se vrtijo dovolj hitro, da čas obrata ni daljši od 256 milisekund. Ker je 256 milisekund približno 250 milisekund, ena sekunda pa ima 1000 milisekund, to pomeni, da se mora vetrnica, da bi tole delovalo, obrniti vsaj štirikrat v sekundi. Če je počasnejša, bomo poskušali v EEPROM zapisati številko, manjšo od 256 in zapisalo se bo nekaj čudnega.

Obljubili smo si, da se bomo znašli. Kako bi v EEPROM zapisali številko 1945? Preprosto, uporabili bi dve zaporedni škatli. V eno bi zapisali 19 in v drugo 45. Kako iz 1945 dobiti 19 in 45? Ker računalniki pri deljenju dveh celih števil zanemarijo zaostanek, bomo 19 dobili tako, da bomo 1945 delili s 100. 45 pa je, ostanek po deljenju s 100. Če bi torej imeli nek `x` in ga hoteli zapisati v celici `i` in `i+1` bi napisali

    EEPROM.write(i, x / 100);
    EEPROM.write(i, x % 100);

Ker lahko v prvo celico zapišemo števila med 0 in 255, je največje število, ki ga lahko zapišemo s tem trikom, enako 25599. (Razmisli, kako bi lahko napisali večja števila. Namig: zakaj deliti ravno s 100? Čemu ne s kakim večjim številom?)

    long previousSeen, lastSeen;
    long nextCell;

    void setup() {
        previousSeen = lastSeen = -1;
        nextCell = 0;
        pinMode(13, OUTPUT);
        attachInterrupt(0, magnet, RISING);
    }

    void loop() {
        long time;

        if (nextCell == 200) {
            digitalWrite(13, HIGH);
        }
        else {
            if (lastSeen != -1) {
                if (previousSeen != -1) {
                    time = lastSeen - previousSeen;
                    EEPROM.write(nextCell, time / 100);
                    EEPROM.write(nextCell + 1, time % 100);
                    nextCell += 2;
                }
                previousSeen = lastSeen;
                lastSeen = -1;
            }
        }
    }

    void magnet() {
        lastSeen = millis();
    }

Zaradi praktičnosti smo uvedli še eno spremenljivko, `time`. Deklarirali smo jo znotraj funkcije `loop`, saj jo potrebujemo le tam. Vanjo izračunamo čas, in potem v eno celico zapišemo `time / 100` in v drugo `time % 100`. Popaziti moramo še na štetje: `nextCell++` smo zamenjali z `nextCell += 2`, saj v vsakem obratu porabimo dve celici. Prav tako v prvem pogoju v `loop` ne prežimo več na `nextCell == 100` temveč `nextCell == 200`.

To zdaj deluje tudi za vetrnice, ki se vrtijo tako počasi, da njihov obrat traja 25599 sekund, kar je malo več kot sedem ur. Če kdo naredi počasnejšo, pa naj razmisli, kako shranjevati še večja števila (ali pa, morda, kako narediti hitrejšo vetrnico).

## Branje in izpis zbranih podatkov

Tole pa zahteva nov program. Preprost bo, tokrat bo vse v `setup`u. Prebrati mora sto številk iz dvestotih celic in jih izpisati. Priložnost za ponavljanje zanke `for`.

    void setup() {
        long cell, time;

        Serial.begin(9600);

        for(cell = 0; cell < 200; cell += 2) {
            time = 100 * EEPROM.read(cell) + EEPROM.read(cell + 1);
            Serial.print(time);
        }
    }

    void loop() {
    }

Računanje časa gre ravno obratno kot prej: iz 19 in 45 bi dobili 1945 tako,da bi 19 pomnožili s 100 (dobimo 1900), čemur prištejemo 45.
