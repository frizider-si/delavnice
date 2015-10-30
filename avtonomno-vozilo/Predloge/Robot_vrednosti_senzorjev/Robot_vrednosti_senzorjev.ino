#include <QTRSensors.h>

// Glavna zanka prebere nakalibrirane vrednosti (surove), in jih prikaže na serijskem monitorju
// Vračane vrednosti so od 0(maximalna reflektivnost) do 2500 (minimalna reflektivnost (ni odboja)

#define NUM_SENSORS   3     // Stevilo uporabljenih senzorjev
#define TIMEOUT       2500  // Cakanje na senzorje (nepomembno v naši aplikaciji, pustimo privzeto)
#define EMITTER_PIN   QTR_NO_EMITTER_PIN     // Nekateri modeli senzorja imajo dodano led diodo

QTRSensorsRC qtrrc((unsigned char[]) {2,3,4}, // Stevilke pinov na katere so povezani senzorji
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

#define VISOKO 0
#define NIZKO 0

void setup()
{
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  pinMode(5,OUTPUT);  pinMode(6,OUTPUT);  pinMode(10,OUTPUT);  pinMode(11,OUTPUT);
  delay(5000);
}

void naravnost(int a){
  analogWrite(5,VISOKO);
  analogWrite(10,VISOKO);
  delay(a);
  analogWrite(5,NIZKO);
  analogWrite(10,NIZKO);
}
void nazaj(int a){
  analogWrite(6,VISOKO);
  analogWrite(11,VISOKO);
  delay(a);
  analogWrite(6,NIZKO);
  analogWrite(11,NIZKO);
}
void desno(int a){
  analogWrite(5,VISOKO);
  analogWrite(11,VISOKO);
  delay(a);
  analogWrite(5,NIZKO);
  analogWrite(11,NIZKO);
}
void levo(int a){
  analogWrite(6,VISOKO);
  analogWrite(10,VISOKO);
  delay(a);
  analogWrite(6,NIZKO);
  analogWrite(10,NIZKO);
}

void loop()
{
  qtrrc.read(sensorValues); //prebere vrednosti
  int vrednost = 0;
  for(int i=0;i<NUM_SENSORS;i++){
    vrednost+=sensorValues[i];
  }
  vrednost = vrednost/NUM_SENSORS;
  Serial.println(vrednost);
  if(vrednost < 100){
    nazaj(450);
    desno(770);
  }
  else{
    naravnost(50);
  }
}


