# Vlak

Napisali bomo program za sedem diod, ki bo delal tako, da bo najprej prižgana prva, nato druga, nato tretja, ... in tako do sedme, nato pa nazaj in spet najprej in nazaj. Lučka bo torej potovala levo in desno.

## Komentarji

Za ogrevanje povejmo neko obstranskost. Če del programa zapremo med nenavadne "oklepaje" `/*` in `*/` je to tako, kot da tega sploh ne bi napisali. Arduino ta del ignorira.

Prav tako bo ignoriral vse od dvojne poševnice do konca vrstice `//`.

Takim delom programa pravimo *komentarji*. Navadno bomo na ta način pisali opombe o tem, kaj dela določena vrstica (da ne pozabimo), ali pa si zapisali, kaj je potrebno še preveriti, dodati...

    void setup() {
    	/* Postavi pin 3 na OUTPUT.
    	   Na tem pinu bo namrec dioda, ki jo bomo kasneje
    	   prizgali. */
        pinMode(3, OUTPUT);
    }

    void loop() {
    	if (millis() >= switchAt) { // Pazi, tu mora biti >= ne ==
    		digitalWrite(13, HIGH); 
    	}
    }

Poleg tega lahko na ta način "zakomentiramo" del programa. Če želimo odstraniti neko vrstico, ne da bi jo zares pobrisali (ker jo bomo morda še potrebovali), na njen začetek dodamo dvojni poševnici. Če želimo zakomentirati več vrstic, jih zapremo med `/*` in `*/`.

## Zanke

Na Arduina pripnimo sedem diod in jih postavimo na pine od 3 do 9. (Opozorimo na nenavadno dejstvo, da lahko damo na pine od 3 do 9 sedem diod, čeprav je 9 - 3 enako 6. Zakaj?)

Zdaj bi jih radi prižgali eno za drugo, s sekundnim zamikom. Za začetek si privoščimo uporabljati `delay`, čeprav zdaj že poznamo njegove pomanjkljivosti. Kasneje bomo naredili tudi boljše.

    void setup() {
        pinMode(3, OUTPUT);
        digitalWrite(3, nextState);
        delay(1000);
        pinMode(4, OUTPUT);
        digitalWrite(4, nextState);
        delay(1000);
        pinMode(5, OUTPUT);
        digitalWrite(5, nextState);
        delay(1000);
        pinMode(6, OUTPUT);
        digitalWrite(6, nextState);
        delay(1000);
        pinMode(7, OUTPUT);
        digitalWrite(7, nextState);
        delay(1000);
        pinMode(8, OUTPUT);
        digitalWrite(8, nextState);
        delay(1000);
        pinMode(9, OUTPUT);
        digitalWrite(9, nextState);
    }

    void loop() {
    }

Kako reč deluje, je menda jasno. Vendar takim programom programerji - razen Italijanov, ki so nad to zlorabo besede ogorčeni - pravijo špageti.

Gre boljše.

    void setup() {
    	int i;

    	i = 3;
    	while (i < 10) {
            pinMode(i, OUTPUT);
            digitalWrite(i, HIGH);
            delay(1000);
            i = i + 1;
        }
    }

    void loop() {
    }

`while` je zelo podobna reč kot `if`. Razlika je v tem, da `if` izvede tisto, kar piše znotraj njega, *če* je pogoj resničen, `while` pa `dokler` je pogoj resničen. Tisto znotraj zanke se bo ponavljalo vse dokler bo `i` manjši od deset.

Vse skupaj je torej takšnole: postavimo `i` na 3. Dokler je `i` manjši od 10, povemo, da `i`-ti pin služi izhodu, na `i`-ti pin zapišemo HIGH. Nato počakamo sekundo in - povečamo `i` za 1 (tako, da ga nastavimo na `i + 1`).

Vse skupaj se bo očitno zavrtelo sedemkrat, potem pogoj `i < 10` ne bo več izpolnjen in ponavljanja bo konec.

Stvari, ki smo jo pravkar spoznali, rečemo *zanka*. Arduino ima tri vrste zank. Kar takoj spoznajmo še drugo; s tretjo se ne mudi, saj je manj uporabna.

## Zanka `for`

Še enkrat poglejmo zanko `while` - a samo njeno bistvo, brez tistih pinov in čakanja.

    	i = 3;
    	while (i < 10) {
    		// to, kar hočemo ponavljati
            i = i + 1;
        }

Če odmislimo še konkretne številke in ime spremenljivke, gre takole

        nastavitev;
        while (pogoj) {
        	// to, kar hočemo ponavljati
            korak;
        }

"Nastavitev" je v tem primeru `i = 3;`, pogoj je `i < 10`, korak pa `i = i + 1`. Ker je ta reč tako pogosta, obstaja zanjo tudi krajši zapis.

    for(zacetek; pogoj; korak) {
    	// to, kar hočemo ponavljati
    }

Ali, z našimi `i`-ji in trojkami in desetkami:

    for(i = 3; i < 10; i = i + 1) {
    	// to, kar hočemo ponavljati
    }


## Spreminjanje spremenljivk

Programerji so praktični ljudje in si za stvari, ki jih počnejo pogosto, radi izmišljajo bližnjice. Ker tolikokrat pišejo `i = i + 1`, so si to skrajšali v `i++`. Zapis `i++` pomeni, preprosto, povečaj `i` za 1. Kaj pomeni `i--`, lahko uganemo.

Včasih `i`-ja ne povečamo za 1, temveč za, recimo, 3. To napišemo `i += 3` in preberemo *povečaj `i` za 3*. Seveda lahko pišemo tudi `i += 42` ali `i += x` ali `i += (x + 2) * 18 + y`. Slednje pač poveča `i` za `(x + 2) * 18 + y` - kakršenkoli že smisel bi to utegnilo imeti.

Prav tako imamo `-=`, ki zmanjša vrednost spremenljivke. Podobno `*=` pomnoži spremenljivko, `/=` pa jo deli. Tako `i *= 5` pomeni *popeteri `i`*, `i /= 2` pa razpolovi `i`.

Zdaj lahko zanko zapišemo še krajše.

    for(i = 3; i < 10; i++) {
    	// to, kar hočemo ponavljati
    }

## Prižiganje diod

Z zanko `for` bomo vse diode na pinih od tretjega do devetega prižgali takole jedrnato.

    void setup() {
    	int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
            digitalWrite(i, HIGH);
            delay(1000);
        }
    }

    void loop() {
    }

Le primerjajte to s špagetom, ki smo ga napisali sprva!

## Isto, a v `loop`

Rekli smo, da se bomo izogibali uporabe funkcije `delay`. Radi bi, tako kot pri utripanju, uporabljali `loop` in uro, torej `millis`.

Pri utripanju smo beležili, kdaj je čas za naslednjo spremembo in na kaj je potrebno spremeniti stanje pina. Kaj pa si moramo zabeležiti zdaj?

Spet bomo morali vedeti, kdaj je čas za naslednjo spremembo. Kakšna je spremememba, vemo: prižgati diodo. Vedeti pa moramo, katero, torej, kateri je naslednji pin, ki ga prižigamo. Bojni načrt je torej takšen: v `setup` bomo rekli, da je naslednja akcija *takoj*, prižgati pa je potrebno pin 3. Poleg tega bomo v `setup` ohranili nastavljanje pinov na `OUTPUT`, prižiganje (in `delay`) pa seveda odstranili. V `loop` bomo s pogojem preverjali, ali je že čas za akcijo. Če je, bomo postavili pin, ki je na vrsti, na `HIGH`, poleg tega pa zabeležili čas za naslednjo akcijo in da je naslednji na vrsti naslednji pin.

	byte nextPin;
	long switchAt;

    void setup() {
    	int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        nextPin = 3;
        switchAt = millis();
    }

    void loop() {
        if (millis() >= switchAt) {
            digitalWrite(nextPin, HIGH);
            nextPin++;
            switchAt += 1000;
        }
    }

To je še kar v redu, le nekaj smo prezrli: tole se ne bo nikoli nehalo. `nextPin` se ne bo ustavil pri 9, temveč bo šel naprej na 10, 11, 12... Ustavimo ga. Postavljanje pina na `HIGH` in vse ostalo naj se zgodi le, če je `nextPin` manjši od 10.

    void loop() {
        if (millis() >= switchAt) {
        	if (nextPin < 10) {
	            digitalWrite(nextPin, HIGH);
	            nextPin++;
	            switchAt += 1000;
	        }
        }
    }

Tole je odlična priložnost, da se naučimo sestavljati pogoje. Vrstice znotraj notranjega `if`a naj se zgodijo le, če sta resnična oba pogoja, torej če velja `millis() >= switchAt` **in** `nextPin < 10`. "In" označimo z `&&`. Program z združenim pogojem je tak:

    void loop() {
        if ((millis() >= switchAt) && (nextPin < 10)) {
	        digitalWrite(nextPin, HIGH);
	        nextPin++;
	        switchAt += 1000;
        }
    }

Ne spreglejte oklepajev. Vsak pogoj zase je zaprt v svoje oklepaje, oba skupaj pa tudi. Včasih bomo namesto **in** potrebovali **ali** - želeli bomo, da se nekaj zgodi, če drži to **ali** ono. **Ali** zapišemo z znakom `||`.

## Enosmerni vlak

Program, ki smo ga napisali, postopno priže vse diode. Spremenimo ga tako, da jih bo ugašal za sabo. Vsakič, ko prižge eno diodo, naj ugasne tisto pred njo. To menda ne bo težko.

	byte nextPin;
	long switchAt;

    void setup() {
    	int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        nextPin = 3;
        switchAt = millis();
    }

    void loop() {
        if ((millis() >= switchAt) && (nextPin < 10)) {
        	digitalWrite(nextPin - 1, LOW);
	        digitalWrite(nextPin, HIGH);
	        nextPin++;
	        switchAt += 1000;
        }
    }

Emmm, približno. V prvem koraku, ko je `nextPin` enak 3, bomo z `digitalWrite(nextPin - 1, LOW)` ugasnili (boljše: poskušali ugasniti) diodo na pinu 2. Temu se lahko izognemo tako, da preprosto preverimo, ali je `nextPin` večji od 3. Če ni, pač ne ugašamo.

    void loop() {
        if ((millis() >= switchAt) && (nextPin < 10)) {
        	if (nextPin > 3) {
        	    digitalWrite(nextPin - 1, LOW)
        	}
	        digitalWrite(nextPin, HIGH);
	        nextPin++;
	        switchAt += 1000;
        }
    }

Lahko pa vse skupaj nekoliko presukamo. Naj bo `nextPin` tisti pin, ki ga je potrebno ugasniti. Prižigamo pa naslednjega.

	byte nextPin;
	long switchAt;

    void setup() {
    	int i;
        for(i = 3; i < 10; i++) {
            pinMode(i, OUTPUT);
        }
        digitalWrite(3, HIGH);
        nextPin = 3;
        switchAt = millis() + 1000;
    }

    void loop() {
        if ((millis() >= switchAt) && (nextPin < 9)) {
        	digitalWrite(nextPin, LOW);
	        digitalWrite(nextPin + 1, HIGH);
	        nextPin++;
	        switchAt += 1000;
        }
    }

Ne spreglejte dveh sprememb. V `setup` zdaj prižgemo pin 3, `switchAt` pa nastavimo na `millis() + 1000`. Tako bo `loop` čez eno sekundo *ugasnil* pin 3 in prižgal `nextPin + 1`, torej pin 4.

Druga sprememba je v pogoju: `nextPin < 10` smo spremenili v `nextPin < 9`. Tako nikoli ne bomo prižigali pina 10; res pa tudi nikoli ugasnili pina 9.

Naš prihodnji podvig je tako ali tako "vlak", zato se s tem problemčkom ne bomo ukvarjali. Naredili bomo drug popravek. Program, kot smo ga zapisali, najprej prižge `nextPin + 1` in nato poveča `nextPin`. Bolj praktično bi bilo najprej povečati `nextPin` in potem prižgati `nextPin`.

    void loop() {
        if ((millis() >= switchAt) && (nextPin < 9)) {
        	digitalWrite(nextPin, LOW);
	        nextPin++;
	        digitalWrite(nextPin, HIGH);
	        switchAt += 1000;
        }
    }

Zveni kot lepotna sprememba, a ni. Kmalu nam bo precej olajšala razmišljanje.

Pravzaprav (tole bo služilo kot namig, za kasneje), namesto `++` uporabimo `+=`.

    void loop() {
        if ((millis() >= switchAt) && (nextPin < 9)) {
        	digitalWrite(nextPin, LOW);
	        nextPin += 1;
	        digitalWrite(nextPin, HIGH);
	        switchAt += 1000;
        }
    }

## Tja in nazaj

Kaj bi morali spremeniti v programu, če bi hoteli, da bi šle luči od 9 do 3 namesto od 3 do 9? Spremeniti bi morali začetno vrednosti `nextPin`, spremeniti bi morali pogoj v `loop` iz `nextPin < 9` v `nextPin > 3`, poleg tega pa bi spremenili `nextPin += 1` v `nextPin -= 1`. Ali pa, hm, `nextPin += -1` - povečaj `nextPin` za -1.

Kaj pa, če bi hoteli levo in desno? Začetna vrednost `nextPin` je lahko še vedno 3. Tisti `nextPin < 9` oziroma `nextPin > 3` bo moral nekako ven. Kaj pa z `nextPin += 1` oziroma `nextPin += -1`? Včasih bo potrebno uporabiti enega, včasih drugega. Pa imejmo spremenljivko `direction`, ki bo imela vrednost `+1` ali `-1`. Kadar bo `+1` bomo šli v desno, kadar `-1`, v levo. Ko bomo prišli do desnega konca (`nextPin == 9`) bomo zavili v levo (`direction = -1`), kadar do levega (`nextPin == 3`), v desno (`direction = 1`).

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

Pa smo!

## Perfekcionisti

Če se kdo dolgočasi, naj se poglobi v tale program. Kako se obrača? In zakaj v začetku postavimo `direction = -1`?

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
        direction = -1; // delajmo se, da smo šli na levo!!!
        switchAt = millis() + 1000;
    }

    void loop() {
        if (millis() >= switchAt) {
        	digitalWrite(nextPin, LOW);
        	if ((nextPin == 3) || (nextPin == 9)) { // obrni, če si na robu
        		direction = -direction; // spremeni +1 v -1 in -1 v 1
        	}
	        nextPin += direction;
	        digitalWrite(nextPin, HIGH);
	        switchAt += 1000;
        }
    }
