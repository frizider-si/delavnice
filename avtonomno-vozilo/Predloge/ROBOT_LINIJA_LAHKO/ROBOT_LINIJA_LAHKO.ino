#include <QTRSensors.h>

// V setup fazi v tem primeru arduino 10 sekund kalibrira senzor (prizgana led dioda)
// V TEH DESETIH SEKUNDAH SENZOR IZPOSTAVITE CRNI IN BELI BARVI (najtemnejši in najsvetlejši vzorec)

// If you want to skip the calibration phase, you can get the raw sensor readings
// (pulse times from 0 to 2500 us) by calling qtrrc.read(sensorValues) instead of
// qtrrc.readLine(sensorValues).

// Glavna zanka programa prebere vrednosti in jih uporabi za približno zaznavo pozicije črte. 
// Vrednosti senzorjev so normirane na vrednosti od 0 do 1000.
// Zadnja vrednost (0,1000,2000,...) nam pove pod katerim senzorjem je bila črta nazadnje zaznana

#define NUM_SENSORS   3     // Stevilo uporabljenih senzorjev
#define TIMEOUT       2500  // Cakanje na senzorje (nepomembno v naši aplikaciji, pustimo privzeto)
#define EMITTER_PIN   QTR_NO_EMITTER_PIN     // Nekateri modeli senzorja imajo dodano led diodo

QTRSensorsRC qtrrc((unsigned char[]) {2,3,4}, // Stevilke pinov na katere so povezani senzorji
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

#define VISOKO 255
#define NIZKO 0

void naravnost(int trajanje){
  analogWrite(5,VISOKO);
  analogWrite(10,VISOKO);
  delay(trajanje);
  analogWrite(5,NIZKO);
  analogWrite(10,NIZKO);
}
void nazaj(int trajanje){
  analogWrite(6,VISOKO);
  analogWrite(11,VISOKO);
  delay(trajanje);
  analogWrite(6,NIZKO);
  analogWrite(11,NIZKO);
}
void desno(int trajanje){
  analogWrite(5,VISOKO);
  analogWrite(11,VISOKO);
  delay(trajanje);
  analogWrite(5,NIZKO);
  analogWrite(11,NIZKO);
}
void levo(int trajanje){
  analogWrite(6,VISOKO);
  analogWrite(10,VISOKO);
  delay(trajanje);
  analogWrite(6,NIZKO);
  analogWrite(10,NIZKO);
}

void setup()
{
  //nastavimo PIN-e motorjev
  pinMode(5,OUTPUT);  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);  pinMode(11,OUTPUT);
  digitalWrite(5,LOW);  digitalWrite(6,LOW);
  digitalWrite(10,LOW);  digitalWrite(11,LOW);

  Serial.begin(9600);
  Serial.print("Prizigam LED na PIN-u: ");
  Serial.println(LED_BUILTIN);
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);    // Arduino LED naznanja kalibracijo
  for (int i = 0; i < 400; i++)  // 400 vzorcev (25ms na klic * 400 = 10s)
  {
    qtrrc.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);     // Arduino LED ugasnemo -> konec kalibracije
    
  //Izpis kalibriranih vrednosti
  for (int i = 0; i < NUM_SENSORS; i++)
  { 
    Serial.print("Senzor: ");
    Serial.print(i);
    Serial.print(" Minimum uporabljen za kalibracijo: ");
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(" Maximum uporabljen za kalibracijo: ");
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.println(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

void loop()
{
  unsigned int crta = qtrrc.readLine(sensorValues)/1000;
  //crta pove pod katerim senzorjem se nahaja črta -> 0,1,2
  
  //Upravljajte robota!
  
}
