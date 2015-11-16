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

LED povežemo tako, kot je prikazano na spodnji shemi.

![alt tag](../pictures/OneLed.png)

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
