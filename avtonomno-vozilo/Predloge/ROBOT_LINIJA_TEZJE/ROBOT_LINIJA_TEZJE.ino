#include <QTRSensors.h>

// Glavna zanka prebere nakalibrirane vrednosti (surove), in jih prikaže na serijskem monitorju
// Vračane vrednosti so od 0(maximalna reflektivnost) do 2500 (minimalna reflektivnost (ni odboja)

#define NUM_SENSORS   3     // Stevilo uporabljenih senzorjev
#define TIMEOUT       2500  // Cakanje na senzorje (nepomembno v naši aplikaciji, pustimo privzeto)
#define EMITTER_PIN   QTR_NO_EMITTER_PIN     // Nekateri modeli senzorja imajo dodano led diodo

QTRSensorsRC qtrrc((unsigned char[]) {2,3,4}, // Stevilke pinov na katere so povezani senzorji
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  pinMode(5,OUTPUT);  pinMode(6,OUTPUT);  
  pinMode(10,OUTPUT);  pinMode(11,OUTPUT);
  analogWrite(5,0);  analogWrite(6,0);
  analogWrite(10,0);  analogWrite(11,0);
}

void naravnost(int trajanje){
  //SPISITE FUNKCIJO
}
void nazaj(int trajanje){
  //SPISITE FUNKCIJO
}
void desno(int trajanje){
  //SPISITE FUNKCIJO
}
void levo(int trajajnje){
  //SPISITE FUNKCIJO
}

void loop()
{
  qtrrc.read(sensorValues); //prebere vrednosti
  //VODI ROBOTA
}


