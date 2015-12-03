#include <IRremote.h>
#include <Wire.h>
#include <SHT2x.h>


// Commands used to control motors
#define FORWARD PORTC = (PORTC & ~0b0001111) | 0b00000101 
#define STOP_F PORTC = (PORTC & ~0b0001111) | 0b00000000 
#define BACKWARD PORTC = (PORTC & ~0b0001111) | 0b00001010 
#define DOWNWARD PORTB = (PORTB & ~0b0000011) | 0b00000010 
#define STOP_UD PORTB = (PORTB & ~0b0000011) | 0b00000000 
#define UPWARD PORTB = (PORTB & ~0b0000011) | 0b00000001 
#define LEFT_T PORTC = (PORTC & ~0b0001111) | 0b00001001
#define RIGHT_T PORTC = (PORTC & ~0b0001111) | 0b00000110

// IR recv pin
#define RECV_PIN 0

#define LED_BLINKING_SPEED 500
#define MOTOR_ON_TIME 300

// SENSOR_MODE indicates which sensor is currently being read
typedef enum {TEMPERATURE, PRESSURE, HUMIDITY} SENSOR_MODE;
// SENSOR_STAGE is used to distinguish between sensor reading stage and led blinking stage
typedef enum {READING, INDICATING} SENSOR_STAGE;
// Led modes
typedef enum {ON, OFF} LED_MODE;

// Other vars and objects
IRrecv irrecv(RECV_PIN);
byte leds[3] = {2, 3};
decode_results results;

void setup(){
  
  // Set the motor pins to ouput
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT); 
  pinMode(14, OUTPUT); 
  pinMode(15, OUTPUT);     
  pinMode(16, OUTPUT); 
  pinMode(17, OUTPUT);
  
  // Set pins for diodes to OUTPUT
  pinMode(leds[0], OUTPUT);
  pinMode(leds[1], OUTPUT);
  pinMode(4, OUTPUT);
  
  // Start the receiver
  irrecv.enableIRIn();
  
  // Init i2c
  Wire.begin();

}

void loop(){
  
  // Show temperature and humidity by means of a blinking LEDs
  showSensorMeasurements();
  
  // Turn on motors if any of the control buttons is pressed
  IRRemoteRunAction();
}

void showSensorMeasurements(){

  static SENSOR_MODE s_mode = TEMPERATURE;
  static SENSOR_STAGE stage = READING;
  static LED_MODE l_mode = ON;
  static unsigned long lastTime;
  static long readings;
  static byte digit;
  static byte ledIndex;
  
  if(millis() - lastTime >= LED_BLINKING_SPEED){
    lastTime = millis();
    if(stage == READING){
      if(s_mode == TEMPERATURE){
        readings = SHT2x.GetTemperature();
        // Change stage
        stage = INDICATING;
        digitalWrite(4, HIGH);
      }
      else if(s_mode == HUMIDITY){
        readings = SHT2x.GetHumidity();
        // Change stage
        stage = INDICATING;
        digitalWrite(4, LOW);
      }
      // First digit
      digit = readings % 10;
    }
    else if(stage == INDICATING){ 
      if(readings == 0){
        s_mode == HUMIDITY ? s_mode = TEMPERATURE : s_mode = HUMIDITY;
        stage = READING;
        ledIndex = 0;
      }
      else if(digit == 0){
        readings = readings / 10;
        digit = readings % 10;
        ledIndex++;
       }
      // Blink
      else if(digit > 0){
        if(l_mode == ON){
          digitalWrite(leds[ledIndex], HIGH);
          l_mode = OFF;
        }
        else if(l_mode == OFF){
          digitalWrite(leds[ledIndex], LOW);
          digit--;
          l_mode = ON;
        }
      }
    }
  }
}

void IRRemoteRunAction(){
  
  static unsigned long lastTime;
  
  if(irrecv.decode(&results)) {
    switch(results.value){
      case 0x112005A:
        FORWARD;
        break;
      case 0x11200DA:
        BACKWARD;
        break;
      case 0x11200BA:
        RIGHT_T;
        break;
      case 0x112003A:
        LEFT_T;
        break;
      case 0x1120009:
        UPWARD;
        break;
      case 0x112005E:
        DOWNWARD;
        break;
    }
    lastTime = millis();
    irrecv.resume(); // Receive the next value
  }
  
  // Check if time is elapsed
  if(millis() - lastTime >= MOTOR_ON_TIME){
    // Stop motors 
    STOP_F;
    STOP_UD; 
  }
  
}
