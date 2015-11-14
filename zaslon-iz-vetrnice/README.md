# Utripanje 

## Prvi program

Vsak program za Arduino mora vsebovati vsaj tole:

    void setup() {
    }
    
    void loop() {
    }

Zakaj se piše ravno tako, kot se piše (čemu `void` in čemu vsi ti oklepaji), bomo izvedeli kasneje, sproti. Za zdaj je potrebno vedeti, da znotraj zavitih oklepajev napišemo, kaj naj Arduino stori ob začetku programa (to je znotraj oklepajev pri `setup`) in kaj potem stalno počne (to je znotraj `loop`). Se pravi, tisto, kar je znotraj `loop`, bo Arduino delal znova in znova in znova in znova in za vedno, dokler programa tako ali drugače ne ustavimo.

Ta program očitno ne dela ničesar, torej ni prav uporaben. Spremenili ga bomo tako, da bo v začetku, ko se začne izvajati, prižgal LEDico, ki je pripeta na pin 13. Za to je potrebno storiti dvoje: Arduino povedati, da je pin 13 izhodni - pini so lahko namreč vhodni ali izhodni; na izhodne pripnemo diode, motorje, zvočnike, karkoli že, na vhodne pa razne tipke, senzorje in podobno šaro.

Da je pin 13 namenjen izhodu, povemo tako, da rečemo

    pinMode(13, OUTPUT);

Temu `pinMode` rečemo "funkcija". Arduino ima veliko funkcij (da ne govorimo o tem, da si lahko izmišljamo še svoje). Funkcije v programih niso kot funkcije v matematiki; funkcije v programih so bolj kot nekakšni "ukazi". Ukazi (funkcije) imajo lahko argumente; te zapišemo v oklepaje za ukazom. Z ukazom `pinMode` torej Arduino "povemo", kateri pin naj ima kakšno vlogo. Ukaz ima dva argumenta, prvi je številka pina, drugi je vloga. Vloga je lahko `OUTPUT` ali `INPUT`; tole hočemo `OUTPUT`, zato torej

    pinMode(13, OUTPUT);

Na konec vsakega ukaza moramo dati podpičje. Če ga pozabimo, se bo program, ki spravi naš program na Arduino, pritožil, da je z našim programom nekaj narobe. Enako se bo zgodilo, če pozabimo kakšen oklepaj, uporabimo ukaz, ki ne obstaja ali kaj podobnega. Tole bo v začetku malo najedalo - teh napak bo veliko in sporočilo njih ne bomo vedno razumeli. Ko se človek malo izuri, pa dela vedno manj takšnih napak, pa tudi sporočila o njih vedno boljše razume in jih zato vedno hitreje popravlja.

Nato na ta "output" nato nekaj zapišemo. Ukaz (funkcija) za to se imenuje digitalWrite. Tudi ta ima dva argumenta; prvi pove, na kateri pin pišemo, drugi pa, kaj pišemo. Kaj je lahko `LOW` ali `HIGH`. Če je `HIGH`, bo dioda svetila, če `LOW`, ne.

Vse skupaj je torej videti takole: 

    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
    }

    void loop() {
    }

V `setup`, torej v začetku izvajanja programa, se izvedeta ukaza, ki povesta, da je pin 13 namenjen izhodu in da naj se na ta izhod zapiše `HIGH`.

V `loop` ni ničesar. Arduino bo torej le prižgal diodo, potem pa ...nič več.

Opazujte, kako oblikujemo program: vse, kar je znotraj `setup` in `loop` smo umaknili za štiri presledke, da je očitno, da je to "znotraj". To bo postalo posebej pomembno kasneje, ko bodo naši programi daljši in bi bili brez zamikanja nepregledni.

## Prižgi in ugasni

Naslednji izziv je, očitno, LED po prižiganju še ugasniti.

    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        digitalWrite(13, LOW);
    }

    void loop() {
    }

Za program ne moremo reči, da ne deluje. Pravzaprav moramo reči, da deluje in to celo zelo hitro. Tako hitro, da najbrž niti ne opazimo, da se je dioda prižgala. Če hočemo kaj videti, moramo med prižiganje in ugašanje dodati malo pavze. Temu služi ukaz, ki se, res presenetljivo!, imenuje `delay`. Argument je čas čakanja v milisekundah. Če hočemo, da program na tem mestu počaka eno sekundo, bomo napisali `delay(1000)`.

    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
    }

    void loop() {
    }

## Utripanje

Naslednji korak je jasen: dioda naj utripa. Za to bomo uporabili `loop`. V `setup` bomo le še povedali, naj pin 13 služi kot izhod, v `loop` pa bomo prižgali diodo, počakali sekundo, ugasnili diodo in počakali sekundo.

Ne zveni težko - in tudi ni.

    void setup() {
        pinMode(13, OUTPUT);
    }

    void loop() {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
    }

## Spremenljivke

Utripne dioda *točno* vsako sekundo? V resnici - ne. Vse, o čemer smo lahko prepričani, je, da med prižiganjem in ugašanjem čakamo eno sekundo. Vendar vsak ukaz zahteva nekaj časa. Tudi izvajanje ukaza `digitalWrite` zahteva nekaj malega (res malega) časa, in `delay` poleg tega, da čaka eno sekundo, traja nekaj malega dlje, saj mora Arduino najprej "prebrati" ukaz in "razmisliti", kaj hočemo od njega. S programom, kot smo ga napisali, je utripanje v resnici drobno malenkost počasnejše.

Komu mar za tisto mikrosekundo tu in tam? Problem je v tem, da se začnejo te napake kopičiti. Ko bomo programirali vetrnico, pa se bo le-ta vrtela hitro in že majhne napake se bodo hitro poznale. Potrebujemo boljši način merjenja časa.

Takole se bomo lotili: ko bomo prižgali diodo, si bomo zabeležili, kdaj jo moramo ugasniti. Nato bomo pridno gledali na uro in ko bomo opazili, da je čas za prižiganje že prišel (ali odšel mimo), jo bomo ugasnili in si zabeležili, kdaj jo bo potrebno spet prižgati.

Da realiziramo ta načrt, se moramo naučiti dvoje: kako izvedeti, koliko je ura in kako si karkoli zabeležiti. Začnimo s slednjim.

Stvari si zabeležimo tako, da jih "priredimo spremenljivkam". Rečemo lahko, recimo

    x = 42;

Tudi takšno prirejanje je neke sorte ukaz, zato mu sledi podpičje.

Na ta način v "spremenljivko" `x` zapišemo 42. Računalništvo ni matematika. Računalništvo je bolj zares, zato je spremenljivka res spremenljivka. Čeprav smo tule rekli `x = 42;`, nam nihče ne brani, da v naslednji vrstici ne rečemo `x = 43;`. Tale flanc, recimo, je povsem legalen:

    x = 42;
    x = 43;
    y = 5;
    x = y + 2;
    x = x * y;

Računalnik (v tem primeru Arduino) vdano sledi temu, kar smo napisali. Najprej si zapomni, da je `x` enak 42. Nato si zapomni, da je `x` po novem enak 43. Nato si zapomni, da je `y` enak 5. Nato si zapomni, da je `x` enak `y + 2`, torej 7. V naslednji vrstici si zapomni, da je `x` enak, hm, `x * y`. Zvezdica pomeni množenje. Od prej si je zapomnil, da je `x` enak 7, `y` je 5, torej bo `x` po novem enak 35. Ko je tega nesmiselnega flanca konec, računalnik torej ve, da je `x` enak 35 in `y` 7.

Takšnole reč lahko zapišemo bodisi v `setup` bodisi v `loop` bodisi kam drugam - kam, bomo videli kasneje.

Le za nekaj moramo prej poskrbeti: spremenljivke, kot so `x` in `y` je potrebno prej napovedati ali, bolj učeno, `deklarirati`. Povedati moramo predvsem, kakšnega *tipa* bodo. Tule sta `x` in `y` očitno števili. Lahko bi bili tudi kaj drugega; kaj, bomo še videli. Poleg tega so števila lahko različna. Za začetek so lahko cela ali necela. Necelim številom se iz nekega razloga, ki ni tako pomemben, reče `float`. Če bi torej hoteli, da sta `x` in `y` neceli števili, bi pred ves ta flanc napisali

    float x;
    float y;

Ali, z eno vrstico

    float x, y;

Ta vrstica v bistvu ničesar ne "naredi" - ne nastavlja vlog pinov, ne piše na pine, ne čaka... Ta vrstica samo *pove*, da bomo uporabljali imeni `x` in `y` ter na kakšne reči se bosta `x` in `y` nanašala. (V resnici Arduino tule sicer nekaj naredi: vrednosti obeh *spremenljivk* nastavi na 0. Vendar drugi programski jeziki tega ne počnejo nujno, zato se na to ne bomo zanašali, temveč se bomo delali, da tule `x` in `y` vsebujeta kr neki.)

V našem primeru `x` in `y` sicer ne dišita po necelih številih. Očitno sta cela. Celih števil pa je več sort. Recimo tri: `byte`, `int` in `long`. Razlikujejo se potem, kako velika smejo biti: spremenljivke vrste `byte` lahko vsebujejo števila od -128 do 127, `int` od -32768 do 32767, `long` pa od -2147483648 do 2147483647. Zakaj ta izbira? In zakaj prav takšna? `byte` zasede en bajt pomnilnika, `int` zasede dva in `long` zasede štiri. V en bajte je mogoče zapisati 255 različnih števil, v dva 65536 in v štiri 4294967296. Zakaj -128 in +127, ne pa -127 in +128 pa je tema za kdaj drugič.

Danes lahko brez skrbi uporabljamo `long`; pri daljših programih pa bo morda potrebno varčevati s pomnilnikom, zato bomo takrat uporabljali le tolikšna števila, kot bo potrebno.

Za vrstico

    float x, y;

ali, kot vemo zdaj

    long x, y;

smo rekli, da jo moramo napisati "pred onim flancem". V resnici ni povsem vseeno kam. Lahko jo napišemo znotraj `setup` ali `loop`. Recimo tako

    void setup() {
        long x;
        x = 42;
    }

    void loop() {
    }

Lahko pa jo *deklariramo* izven `setup`a.

    long x;

    void setup() {
        x = 42;
    }

    void loop() {
    }

Razlika je v tem, da je tisto, kar je deklarirano izven `setup` in `loop` vidno v obeh, kar je v eni od njiju, pa le v njej.

Pa še ena pomembna razlika: kar je definirano zunaj, "ohrani" svojo vrednost. Če spremenljivko deklariramo znotraj bloka, bo "živa" le dokler se izvajajo ukazi znotraj bloka. Ko se blok izvede naslednjič, se spremenljivka pojavi na novo, o njenih morebitnih prejšnjih vrednostih pa Arduino ne ve ničesar. Vmes kar "izgubi spomin".

Tako, kot smo zastavili zdaj, lahko naredimo, recimo, naslednje:

    long x;

    void setup() {
        x = 0;
    }

    void loop() {
        x = x + 1
    }

Ko se program zažene, postavimo x na 0. Nato ga vsakič, ko pokliče `loop`, povečamo za 1. Na ta način torej štejemo, kolikokrat se je poklical `loop`.

To deluje zato, ker smo `x` deklarirali izven blokov `setup` in `loop`, zato si Arduino zapomni njeno vrednost. Če bi napisali

    void setup() {
        long x;
        x = 0;
    }

    void loop() {
        x = x + 1
    }

pa bi se program, ki prenese naš program na Arduino, pritožil, da znotraj `loop` ne ve, kaj je to `x`, saj je `x` deklariran le znotraj `setup`.

Mimogrede povejmo še nekaj: spremenljivko lahko istočasno deklariramo in ji damo vrednost. Namesto

    long x;
    x = 0;

tako pišemo kar

    long x = 0;

## Malo čiščenja pojmov

Da bo naša govorica bolj pravilna in uporabna, poslej ne bomo več govorili o ukazi, temveč o funkcijah. `digitalWrite` in `delay` sta torej *funkciji*, ki ju *pokličemo* z določenimi argumenti.

Prav tako ne bomo več govorili o "blokih". `setup` in `loop` sta v resnici *funkciji*, le da ne funkciji, ki ju pokličemo, temveč funkciji, ki ju le *definiramo*, kliče pa jih Arduino. Kmalu se bomo naučili definirati tudi druge funkcije; predvsem takšne, ki jih ne bo klical Arduino, temveč jih bomo klicali sami.

Spremenljivke so imele doslej imeni `x` in `y`. Ime spremenljivke je lahko poljubna kombinacija malih in velikih črk angleške abecede, števk, pa še podčrtaj je lahko zraven. Edina omejitev je, da se ime ne more začeti s števko. Arduino razlikuje med malimi in velikimi črkami: `benjamin`, `Benjamin`, `BENJAMIN` in `BenjAmin` so štiri različne spremenljivke.

Funkcije naredijo to ali ono reč - pišejo na izhode, čakajo... Poleg tega lahko funkcije tudi *vrnejo vrednost*. Preprost primer takšne funkcije je, recimo, `abs`, ki vrne absolutno vrednost števila, ki ga podamo kot argument. Če rečemo, recimo,

    long x, y;
    x = -5;
    y = abs(x)

bo `x` enak `-5`, `y` pa 5.

Podobno se vede, recimo, `sqrt`, ki izračuna in vrne koren števila.

    float x, y;
    x = 25;
    y = sqrt(x);

Funkcije imajo lahko tudi več argumentov, kot recimo `pow`, ki računa potence.

    float x;
    x = pow(3, 4);

## Čas

Spremenljivke smo spoznali, da bi si lahko vanje zapišemo, kdaj bo potrebno ugasniti ali prižgati LEDico. Le še to moramo izvedeti, kako izvedeti, koliko je ura. Temu služi funkcija `millis`. Pove nam, koliko milisekund je minilo odkar se je začel izvajati program. To, kdaj je začel meriti, pravzaprav niti ni tako pomembno; lahko si predstavljamo, da gre za čas v milisekundah od jutra ali od treh popoldan včeraj; to bo, kot bomo videli, vseeno.

Za začetek zastavimo nekoliko manj ambiciozen cilj: dioda ne bo utripala, temveč se bo v začetku izvajanja programa prižgala, nato pa čez eno sekundo ustavila. Funkcijo `millis()` bomo uporabili nekako takole:

    long switchOffAt;

    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        switchOffAt = millis() + 1000;
    }

    void loop() {
    }

To je popolnoma enako prvemu programu, le da si po tem, ko diodo prižgemo, zapomnimo, da jo je potrebno ugasniti ob trenutnem času + 1000 milisekund, se pravi, čez eno sekundo.

Ne spreglejte, da smo funkcijo *poklicali brez argumentov*. Brez, zato ker jih pač nima in noče. *Poklicali* pa zato, ker moramo kljub temu, da nima argumentov, napisati oklepaje, pa čeprav prazne. *millis* je le ime funkcije; oklepaji pa pomenijo, da jo hočemo poklicati, pa najsibo kaj v njih ali ne.

Manjka seveda še ugašanje. Potrebovali bomo nekaj takšnega: če je trenutni čas enak temu, ki smo ga shranili v `switchOffAt`, ugasni LEDico. Kako pa se pove to?

## Pogojni stavki

Približno takole

    long switchOffAt;
    
    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        switchOffAt = millis() + 1000;
    }
    
    void loop() {
        if (millis() == switchOffAt)
            digitalWrite(13, LOW);
    }

Novost tule je `if`. Čeprav mu sledijo oklepaji, to ni funkcija, ki bi jo poklicali. V (okroglih) oklepajih je pogoj, ki odloča, ali se bo tisto, kar sledi `if`-u zgodilo ali ne.

Pogoj navadno vsebuje kakšno primerjavo. V tem primeru preverjamo, ali je trenutni čas enak času, v katerem je potrebno diodo ugasniti. Ali sta dve stvari enaki, preverimo z dvojnim enačajem, `millis() == switchOffAt` in ne enojnim `millis() = switchOffAt`. Enojni enačaj je namenjen prirejanju, dvojni primerjanju.

Program sicer lahko poženete in bo včasih deloval, ni pa nujno. Arduino sicer res stalno kliče naš `loop`, vendar se lahko zgodi, da bo ravno zamudil točen čas, v katerem želimo ugasniti diodo. V izogib težavam bomo v pogoj napisali, da mora biti čas večji ali enak `switchOffAt`.

    long switchOffAt;
    
    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        switchOffAt = millis() + 1000;
    }
    
    void loop() {
        if (millis() >= switchOffAt)
            digitalWrite(13, LOW);
    }

`if`-u lahko sledi - in mu pogosto tudi bo sledilo - kaj daljšega kot le en klic. Recimo, da bi hoteli, ko preteče čas, ugasniti diodo, poleg tega pa postaviti `x` na 1 in `y` na 2.

    void loop() {
        if (millis() >= switchOffAt)
            digitalWrite(13, LOW);
            x = 1;
            y = 2;
    }

To ne deluje. Čeprav smo zgledno zamikali vrstice, je za Arduino to isto, kot če bi napisali

void loop() {
if (millis() >= switchOffAt)
digitalWrite(13, LOW);
x = 1;
y = 2;
}

If odloča le o ukazu (klicu funkcije, prirejanju...), ki mu sledi. Le o prvem, torej. Vrstici `x = 1;` in `y = 2;` nista znotraj `if`-a in se izvedeta v vsakem primeru. Če hočemo z `if`-om nadzorovati več vrstic, ju zapremo v "blok".

    void loop() {
        if (millis() >= switchOffAt) {
            digitalWrite(13, LOW);
            x = 1;
            y = 2;
        }
        z = 4;
    }

Zdaj se tudi prirejanji `x = 1;` in `y = 2;` izvedeta le, če je minilo dovolj časa, `z = 4;` pa vedno.

Dogovorimo se, da bomo oklepaje za `if`-om pisali tudi, kadar mu bo sledil le en ukaz. Ta navada vas bo obvarovala mnogih zoprnih napak.

    long switchOffAt;
    
    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        switchOffAt = millis() + 1000;
    }
    
    void loop() {
        if (millis() >= switchOffAt) {
            digitalWrite(13, LOW);
        }
    }

Če program pozorno pogledamo, opazimo, da bo po preteku ene sekunde stalno ugašal in ugašal diodo. Nič hudega, to se tako ali tako ne bo poznalo.

## Utripanje

Če hočemo, da bo dioda utripala, bomo morali takrat, ko jo ugasnemo, zapisati, kdaj jo bo potrebno spet prižgati. V zanki, `loop`, ne bomo prežali le na ugašanje, temveč tudi na prižiganje. In ko jo prižgemo bomo, tako kot že doslej, zapisali, kdaj jo je potrebno ugasniti.

    long switchOffAt, switchOnAt;
    
    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        switchOffAt = millis() + 1000;
        switchOnAt = millis() + 10000000;
    }
    
    void loop() {
        if (millis() >= switchOffAt) {
            digitalWrite(13, LOW);
            switchOnAt = millis() + 1000;
        }
        if (millis() >= switchOnAt) {
            digitalWrite(13, HIGH);
            switchOffAt = millis() + 1000;
        }
    }

V začetku smo nastavili `switchOnAt` na neko ogromno vrednost, da ne bi slučajno česa sprožila.

Poženimo program - in vidimo, da ne deluje. Dioda se prižge in ugasne - ter ne prižge več.

Dobrodošli v svetu iskanja trdovratnih čudnih napak.

Tule se zgodi naslednje: dioda se prižge in zapomnimo si čas, ko jo je potrebno ugasniti. Ko mine sekunda (`millis() > switchOffAt`), se dioda ugasne in zabeležimo čas, ko jo bo potrebno spet prižgati, namreč eno sekundo od tega trenutka. Arduino nato spet pokliče `loop`. Ker je čas za ugašanje že napočil (`millis() > switchOffAt`), se dioda ugasne (a ni bila že ugasnjena?) in zapomnimo čas, ko jo je potrebno ugasniti, namreč eno sekundo od tega trenutka. Arduino nato spet pokliče `loop`. Ker je čas za ugašanje že napočil (`millis() > switchOffAt`), se dioda ugasne (a ni bila že ugasnjena?) in zapomnimo čas, ko jo je potrebno ugasniti, namreč eno sekundo od tega trenutka...

(Ugasnjena) Dioda se vedno znova ugaša, čas, ko jo bomo ponovno prižgali pa se znova in znova odmika za eno sekundo v prihodnost. Popravek je preprost.

    long switchOffAt, switchOnAt;
    
    void setup() {
        pinMode(13, OUTPUT);
        digitalWrite(13, HIGH);
        switchOffAt = millis() + 1000;
        switchOnAt = millis() + 10000000;
    }
    
    void loop() {
        if (millis() >= switchOffAt) {
            digitalWrite(13, LOW);
            switchOnAt = millis() + 1000;
            switchOffAt = millis() + 10000000;
        }
        if (millis() >= switchOnAt) {
            digitalWrite(13, HIGH);
            switchOffAt = millis() + 1000;
            switchOnAt = millis() + 10000000;
        }
    }

Z vrsticama 

            switchOnAt = millis() + 1000;
            switchOffAt = millis() + 10000000;

dosežemo, da se bo prižiganje zgodilo čez eno sekundo, ugašanje pa "enkrat kasneje". Namesto milijon bi lahko napisali tudi dva tisoč, pa bi bilo ravno tako dovolj. Da pomembno je le, da prižgemo, preden bomo ponovno ugašali.

Pri prižiganju se zgodba ponovi: ugašanje bo čez eno sekundo, prižiganje enkrat veliko kasneje.

Še eno zvitost si privoščimo. Poenostavimo `setup`. Iz njega lahko vržemo prižiganje, pač pa postavimo `switchOnAt = millis()`, tako da se bo dioda prižgala takoj ob prvem klicu `loop`.

    long switchOffAt, switchOnAt;
    
    void setup() {
        pinMode(13, OUTPUT);
        switchOffAt = millis() + 1000;
        switchOnAt = millis();
    }
    
    void loop() {
        if (millis() >= switchOffAt) {
            digitalWrite(13, LOW);
            switchOnAt = millis() + 1000;
            switchOffAt = millis() + 10000000;
        }
        if (millis() >= switchOnAt) {
            digitalWrite(13, HIGH);
            switchOffAt = millis() + 1000;
            switchOnAt = millis() + 10000000;
        }
    }

## Gnezdeni pogoji, stanja

Poskusimo še nekaj bolj premetenega: namesto dveh spremenljivk, `switchOnAt` in `switchOffAt` imejmo le eno. No, le dve. :) Prva bo `switchAt`, ki bo povedala, kdaj je potrebno spremeniti stanje diode. Druga bo `nextState`, ki bo povedala, na kaj jo je potrebno spremeniti.

    long switchAt;
    byte nextState;
    
    void setup() {
        pinMode(13, OUTPUT);
        switchAt = millis();
        nextState = HIGH;
    }
    
    void loop() {
        if (millis() >= switchAt) {
            digitalWrite(13, nextState);
            
            switchAt = millis() + 1000;
            if (nextState == HIGH) {
                nextState = LOW;
            }
            else {
                nextState = HIGH;
            }
        }
    }

V `setup` zabeležimo, da želimo, da `loop` takoj spremeni stanje diode, pri čemer naj bo to, naslednje stanje, `nextState`, enako `HIGH`. Za `nextState` smo rekli, naj bo tipa `byte`. Tako, za vajo.

V `loop` preverimo, ali je že čas za akcijo. Če je, pač nastavimo pin 13 na `nextState`. Nato si zapomnimo, kdaj bo čas za naslednjo spremembo, `switchAt = millis()`. Nato zapišemo še, na kaj bo potrebno spremeniti stanje. Če je trenutno stanje `HIGH`, naj bo naslednje stanje `LOW` in obratno. Za "in obratno" uporabimo `else`: `else` lahko sledi `if`-u in pove, kaj naj se zgodi, če pogoj ni bil resničen.

Ne spreglejmo, da se vse tole, kar smo pisali v `loop` godi znotraj `if`-a. Da, znotraj `if`-a imamo še en `if`. Pogoj v notranjem `if` se seveda preverja in upošteva le, če je bil izpolnjen pogoj iz zunanjega.

## Picajzlanje

Bodimo še malenkost picajzlasti. Tudi ta dioda ne utripa nujno vsako sekundo. Problem je tule

            switchAt = millis() + 1000;

S tem povemo, da je čas za naslednjo spremembo 1000 milisekund po *trenutnem* času. Če hočemo utripanje na sekundo (z malenkostnimi zamiki v vsakem krogu, vendar ne takšnimi, da bi se nabirali), moramo reči, da je čas za novo spremembo *eno sekundo po tej spremembi*, torej

            switchAt = switchAt + 1000;

Zdaj bo utripanje toliko natančno, kot je natančna Arduinova ura. To pa je, za naše potrebe, čisto in povsem natančno.

## Zaključek

Marsikaj, kar smo naredili, bi se dalo napisati učinkoviteje. Zadnji program, recimo, bi bil v resnici lahko čisto kratek. Komur se raziskuje, naj raziskuje.

Predvsem pa bi se dal vse napisati tudi precej drugače, kot smo napisali. Naloge iz programiranja nikoli nimajo ene same pravilne rešitve. Še najboljših rešitev je navadno več in so stvar okusa. Tule smo pač naredili tako, kot smo; če je kdo drugače, pa je tudi prav.


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


# Prekinitve

Doslej smo na izhode le pisali. Naučimo se brati z njih.

Vzeli bomo senzor za magnet in ga pripeli na pin 2. Ko mu bomo približali magnet, naj se prižgejo diode.

Kako se to počne, najbrž že slutimo: če je pin lahko `OUTPUT`, je najbrž lahko tudi `INPUT` in če imamo `digitalWrite`, najbrž obstaja tudi `digitalRead`. Kdor razmišlja tako, razmišlja prav. Vendar bomo uporabili drug, preprostejši trik. Napisali bomo funkcijo `switchOn`, ki bo prižgala diodo. Potem bomo Arduinu preprosto naročili, naj pokliče našo funkcijo takrat, ko se na pinu 2 kaj zgodi.

## Pisanje funkcij

Najprej napišimo novo funkcijo `switchOn`, ki prižge, recimo, vse diode na pinih od 3 do 9.

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


# Nadaljevanje

Nadaljevanje delavnice si lahko preberete v posameznih lekcijah na githubu.