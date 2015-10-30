# pametna-hisa
(14.10. v Frižiderju)

## Učni list, obseg: 4h

### Uvod (0.5h)

Pametna hiša je popularno ime, ki označuje področje avtomatizacije hiše. In je tematika o kateri se da razpravljati na dolgo in široko, neodvisno od starosti. Prav tako se s tem pojmom srečujemo že od vsaj prvih barvnih hollywood-skih filmov. Imeti robota v hiši, čudežne gospodinjske naprave, luči ki se same prižigajo, hiša ki se pogovarja z nami. Še wc in vodna pipa sta skozi leta postala pametna. 

Za kaj pravzaprav gre? Imamo hišo in funkcionalno namenske prostore v hiši, npr. stopnišče, dnevna soba, kuhinja, spalnica, kopalnica, učna soba, knjižnica, pralnica, delavnica, rastlinjak, itn. Vsak prostor ima svoj namen uporabe, ki je lahko med sabo tudi komplementaren. Naprimer, v spalnico gremo več ali manj samo spat, med tem ko se večino časa gibljemo v dnevni sobi. V nekaterih prostorih imamo vodovodno napeljavo, spet drugje samo električno. Lahko imamo tudi ogrevana tla. V vseh prostorih pa zagotovo najdemo elektronske naprave, ki jih priključimo v 230V električno omrežje, čedalje več je takih, ki jih priključimo tudi v internetno omrežje.

Torej, imamo množico naprav z 230V/ETH prikopom! Bistvo avtomatizacije hiše je, da za izbrane naprave v vsakem trenutku vemo v kakšnem stanju so (vključene, izključene) - NADZOR STANJA, da lahko vplivamo na njihovo delovanje (napravo vklopimo/izklopimo) - KONTROLA STANJA, in da prejemamo obvestila o spremembah stanja, ki so lahko del rednega delovanja ali okvara - ALARMIRANJE.

### PRIPRAVILI BI KRATKO! PREZENTACIJO S SLIKAMI TIPIČNE UPORABE, lahko tudi kakšen video z youtube-a

Ker so pametni telefoni in tablice popularni do te mere, da vsaka hiša premore kakšnega/-o, bi za izvedbo Pametne hiše rabili spletni vmesnik, ki bi nam omogočal Nadzor, Kontrolo in Alarmiranje izbranih naprav v hiši. Spletni vmesnik naj bo kar se da enostaven za uporabo (1 stikalo za 1 napravo).

### Spletni vmesnik (2h)

Tako kot lahko recikliramo smeti, tako lahko recikliramo tudi projekte in kodo. Na spletnem portalu DIY projektov Instructables, smo našli primeren in enostaven način implementacije spletnega vmesnika. Uporabili bomo kodo projekta in jo prilagodili našim potrebam (spremenili 1 številko v for zanki). Želimo uporabiti že izdelano tiskano vezje, na katerem je polje 7 ledic: Prižigali in ugašali bomo ledice, kot primer vklopa/izklopa naprav. Namesto ledice lahko uporabimo tudi PIR senzor premika in zvočni detektor.

Projekt: http://www.instructables.com/id/Simple-and-intuitive-web-interface-for-your-Raspbe/

Učni pripomočki: Vsak udeleženec bo imel Raspberry Pi, na katerem bo nameščen spletni strežnik, razširitev za PHP in knjižnica Wiring Pi. Raspberry Pi-ji bodo povezani v lokalno mrežo frižiderja, z odprtim WiFi za povezavo preko telefona. Tiskana vezja z ledicami se enostavno priklopijo točno določeno glede na pinout GPIO Raspberry Pi.

Programiranje: delo v konzolnem oknu - izvajanje gpio ukazov knjižnice Wiring Pi.

KORAK 1:

Predstavitev DIY projekta na Instructables

KORAK 2:

Predstavitev TIV ledic

KORAK 3:

Povezava TIV ledic na Raspberry Pi po vezavni shemi

KORAK 4:

Uporaba knjižnice Wiring Pi v konzolnem oknu Raspberry Pi. Naslavljanje pinov. Primer prižiga ene ledice:
```
  gpio mode 21 out
  gpio write 21 1
```
KORAK 5:

Razložimo sestavo spletnega vmesnika, zato da si ga bo lahko kdorkoli doma znal prilagoditi po svoje.

KORAK 6:

Vsak se s svojim telefonom poveže na lokalni WiFi, odpre brskalnik in vtipka IP svojega Raspberry Pi. Prižiga svoje ledice.

### Uporabili bomo resne naprave (1.5h)

Ledice niso resne naprave. Za resne naprave rabimo več napetosti in toka. Kako bomo prižigali in ugašali (toaster?) resno 230V napravo? Uporabili bomo stikalno polje (rele array). Za konec bomo demonstrirali Elisov prototip pametne hiše. In razdelili zgibanke za Jesenske tečaje.

KORAK 1:

Predstavitev stikalnega polja, in zakaj GPIO Raspberry Pi ni dovolj.

KORAK 2:

Povezava stikalnega polja z Raspberry Pi po vezavni shemi. Na eno stikalo priključimo porabnika - luč.

KORAK 3:

Uporaba knjižnice Wiring Pi v konzolnem oknu Raspberry Pi. Primer prižiga luči, podobno kot prej:
```
  gpio mode 21 out
  gpio write 21 1
```

KORAK 4:

Isti spletni vmesnik uporabimo za prižiganje luči.



