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
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8,HIGH);
  pinMode(12,INPUT);
}

bool premik;
void loop()
{
  qtrrc.read(sensorValues); //prebere vrednosti
    
  premik = false;
  premik = (HIGH ==digitalRead(12));
  if(premik){
    if(sensorValues[0]<100 || sensorValues[1]<100 || sensorValues[2]<100){
      //stop
      digitalWrite(5,LOW);
      digitalWrite(10,LOW);
      digitalWrite(6,LOW);
      digitalWrite(11,LOW);
      //avoid
      int i = random(250,1000);
      digitalWrite(6,HIGH);
      digitalWrite(11,HIGH);
      delay(i);
      digitalWrite(6,LOW);
      digitalWrite(11,LOW);
      //turn around
      i = random(1);
      int j = random(500,1500);
      if(i==0){
        digitalWrite(5,HIGH);
        digitalWrite(11,HIGH);
        delay(j);
        digitalWrite(5,LOW);
        digitalWrite(11,LOW);
      }else{
        digitalWrite(6,HIGH);
        digitalWrite(10,HIGH);
        delay(j);
        digitalWrite(6,LOW);
        digitalWrite(10,LOW);
      }
    }
    else{
      digitalWrite(5,HIGH);
      digitalWrite(10,HIGH);
    }
  }
  delay(50);
}


