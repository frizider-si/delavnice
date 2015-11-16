# Prekinitve

Doslej smo na izhode le pisali. Naučimo se brati z njih.

Vzeli bomo senzor za magnet in ga pripeli na pin 2. Ko mu bomo približali magnet, naj se prižgejo diode.

Kako se to počne, najbrž že slutimo: če je pin lahko `OUTPUT`, je najbrž lahko tudi `INPUT` in če imamo `digitalWrite`, najbrž obstaja tudi `digitalRead`. Kdor razmišlja tako, razmišlja prav. Vendar bomo uporabili drug, preprostejši trik. Napisali bomo funkcijo `switchOn`, ki bo prižgala diodo. Potem bomo Arduinu preprosto naročili, naj pokliče našo funkcijo takrat, ko se na pinu 2 kaj zgodi.

## Pisanje funkcij

Najprej napišimo novo funkcijo `switchOn`, ki prižge, recimo, vse diode na pinih od 3 do 9. Diode povežemo tako, kot je prikazano na spodnji shemi.

![alt tag](https://github.com/frizider-si/zaslon-iz-vetrnice/blob/master/pictures/MagnetLed.png)

Funkcije pravzaprav že znamo definirati. Že od samega začetka smo pisali funkciji `setup` in `loop`. Njuni imeni sta bili vnaprej določeni, Arduino hoče imeti funkciji s točno takima imenoma. Nihče pa nam ne brani pisati lastnih funkcij v poljubnimi imeni. V resnici gre čisto enako kot pri `setup` in `loop`.

Maloprej smo napisali takšenle `setup`, ki je z zamikom ene sekunde prižgal vse diode, takole

    void setup() {
    	int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
            digitalWrite(i, HIGH);
            delay(1000);
        }
    }

Funkcija `switchOn`, ki brez zamika prižge vse, je videti na dva lasa podobno.

    void switchOn() {
        int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
            digitalWrite(i, HIGH);
        }
    }

Spremenili smo ime in izpustili `delay`, to je vse.

Če bi zdaj hoteli ob začetku programa prižgati vse diode, bi lahko napisali

    void setup() {
        switchOn();
    }

    void loop() {
    }

    void switchOn() {
        int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
            digitalWrite(i, HIGH);
        }
    }

Estetika veli (in res se bo izkazalo za uporabnejše), da način delovanja pinov (`OUTPUT` ali `INPUT`) nastavljamo v `setup`u. Pa storimo tako.

    void setup() {
        int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        switchOn();
    }

    void loop() {
    }

    void switchOn() {
        int i;
        for(i = 3; i < 10; i++) {
            digitalWrite(i, HIGH);
        }
    }

Zdaj se `switchOn` ukvarja le še s prižiganjem pinov.

## Funkcije z argumenti

Funkcije, ki smo jih klicali, so imele pogosto tudi kakšne argumente. Tako ima, recimo `digitalWrite` dva, `delay` pa enega. Naučimo se pisati še te. Napisali bomo funkcijo, `setAllPins`, ki nastavi vse pine od tretjega do devetega na vrednost, ki jo podamo kot argument.

    void setAllPins(byte state) {
        int i;
        for(i = 3; i < 10; i++) {
            digitalWrite(i, state);
        }
    }

Med oklepaja za `setAllPins` smo napisali `byte state`. To pomeni, da pričakujemo, da bo funkcija dobila argument tipa `byte`. Tistemu, kar bo dobila kot argument (to bo seveda `LOW` ali `HIGH`), bomo znotraj funkcije rekli `state`. Ko torej kasneje pišemo `digitalWrite(i, state);`, to v bistvu pomeni, naj pin `i` postavi na tisto, kar je ta, ki je poklical funkcijo, dal funkciji kot argument.

Funkcijo `setAllPins` lahko kličemo kot vse druge funkcije. Lahko jo kličemo tudi iz svojih funkcij.

    void setup() {
        int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        switchOn();
    }
    
    void loop(){
    }

    void setAllPins(byte state) {
        int i;
        for(i = 3; i < 10; i++) {
            digitalWrite(i, state);
        }
    }

    void switchOn() {
        setAllPins(HIGH);
    }

    void switchOff() {
        setAllPins(LOW);
    }


## Prekinitve

Zdaj nam ostane, da naročimo Arduinu, naj pokliče tole funkcijo, ko bo senzor, obešen na pin 2, zavohal magnet.

Uporabili bomo nekaj, čemur se reče *prekinitev*. To zna Arduino, to znajo vsi sodobni procesorji: ko se zgodi določena reč, lahko pusti vse, kar dela, in začne "obravnavati prekinitev". Tokrat najprej povejmo, kaj nam je narediti; razlagajmo potem. Poklicati moramo funkcijo `attachInterrupt`.

    attachInterrupt(0, magnet, RISING);

Prekinitve so oštevilčene, pri čemer Arduinu številka prekinitve žal ni enaka številki pina, na katerega se prekinitev nanaša. Kadar bomo obesili kaj na pin 2, bo to *sprožilo* prekinitev številka 0.

S klicem funkcije `attachInterrupt` smo na prekinitev 0 (ki spremlja pin 2) "priključili" funkcijo `magnet`, ki jo moramo še napisati. Ko se bo kaj zgodilo na pinu 2, bo Arduino takoj, nemudoma, pustil vse, kar dela, in izvedel funkcijo `magnet`.

Funkcija `magnet` bo salamensko preprosta. Le vse diode bo prižgala.

    void magnet() {
        switchOn();
    }

Kaj pa se lahko zgodi na pinu 2? To, na kar prežimo, je povedal tretji argument, `RISING`: čakamo, da bo napetost na tem pinu narasla. Narasla bo, ko jo bo pač povečal senzor, priključen nanj. To pa bo storil, ko bo zagledal magnet.

Še enkrat povejmo: ko bo na pinu 2 narasla napetost (preskočila iz LOW na HIGH - le da je tokrat ni pišemo mi, temveč senzor), se bo sprožila prekinitev 0, na prekinitev 0 pa je priključena naša funkcija `magnet`.

Funkcijo `attachInterrupt` pokličemo seveda znotraj `setup`.

Sestavimo vse skupaj.

    void setup() {
        int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        attachInterrupt(0, magnet, RISING);
    }
    
    void loop(){
    }

    void magnet() {
        switchOn();
    }

    void setAllPins(byte state) {
        int i;
        for(i = 3; i < 10; i++) {
            digitalWrite(i, state);
        }
    }

    void switchOn() {
        setAllPins(HIGH);
    }

    void switchOff() {
        setAllPins(LOW);
    }


## Malo kasneje pa ugasni

Po telovadbi z vlakom bi morala biti tale vaja preprosta: diode naj bodo prižgane le sekundo po tem, ko vidijo magnet. Nato naj ugasnejo.

Prekinitev nam pomaga pri prižiganju, pri ugašanju nam pa ne bo. Naredili bomo, kot smo vajeni: zapomnili si bomo, kdaj je potrebno ugasniti diode in v `loop`u prežali na ta trenutek.

    long switchOffAt;

    void setup() {
        int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        switchOffAt = millis() + 1000000;
        attachInterrupt(0, magnet, RISING);
    }

    void magnet() {
        switchOn();
        switchOffAt = millis() + 1000;
    }

    void loop() {
        if (millis() > switchOffAt) {
            switchOff();
            switchOffAt = millis() + 1000000;
        }
    }

    void setAllPins(byte state) {
        int i;
        for(i = 3; i < 10; i++) {
            digitalWrite(i, state);
        }
    }

    void switchOn() {
        setAllPins(HIGH);
    }

    void switchOff() {
        setAllPins(LOW);
    }


## Krajše prekinitve

Prekinitve morajo biti čim krajše. Arduino v tem času res pusti vse, kar dela. Tudi če je ravno sredi funkcije, recimo, `loop`, še hujše, če smo ravnokar poklicali nek `digitalWrite(3, HIGH)` in je začel delati na tem, da bi nastavil pin 3 na `HIGH` ... prekinil bo nastavljanje pina (zato se pa reč imenuje prekinitev!) in se začel ukvarjati s funkcijo `magnet`.

Prekinitve morajo biti zaradi tega čim čim čim krajše. Tule pa znotraj funkcije `magnet` kličemo funkcijo `switchOn`, ki kliče `switchAllPins`, ki vsebuje zanko... V tem primeru sicer ne bo katastrofe, lepo pa ni.

Po vaji, ki smo jo imeli z utripanjem in vlakom, znamo precej skrajšati prekinitev. Vse, kar bomo naredili v funkciji `magnet` je tole:

    void magnet() {
        switchOnAt = millis();
    }

Se pravi, prižgi diode - takoj.

Zdaj mora `loop` to opaziti in jih prižgati. Poleg tega pa zapisati, da je potrebno diode čez eno sekundo ugasniti.

To je sicer vaja na isto temo, a jo naredimo, da bo naredila mojstra.

    long switchOnAt, switchOffAt; // Tule smo dodali še switchOnAt!

    void setup() {
        int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        switchOffAt = millis() + 1000000;
        switchOnAt = millis() + 1000000; // Prizgi ... dalec v prihodnosti
        attachInterrupt(0, magnet, RISING);
    }

    void magnet() {
        switchOnAt = millis(); // Samo zabeleži, da je potrebno prizgati
    }

    void loop() {
        if (millis() > switchOnAt) {
            switchOn();
            switchOffAt = switchOnAt + 1000;
            switchOnAt = millis() + 1000000;
        }
        if (millis() > switchOffAt) {
            switchOff();
            switchOffAt = millis() + 1000000;
        }
    }

    void setAllPins(byte state) {
        int i;
        for(i = 3; i < 10; i++) {
            digitalWrite(i, state);
        }
    }

    void switchOn() {
        setAllPins(HIGH);
    }

    void switchOff() {
        setAllPins(LOW);
    }

## Vetrnica se prvič zavrti

Recimo, da bi skrajšali čas, ko so diode prižgane, na eno milisekundo, prenesli program na Arduina, izključili USB in priključili motor. Vetrnica pa naj se vrti mimo magneta... Bi že dobili kaj zanimivega?

Kaj pa, če ta magnet - previdno, da nas vetrnica ne bo po prstih - premikamo okrog vetrnice?
