#include "mbed.h"
#include "DHT.h"

Serial uart(p28, p27);  // tx, rx

AnalogIn SND_PIN(A0);
DHT DHT_PIN(D4, DHT11);
DigitalIn PIR_PIN(p29, PullUp); 
DigitalOut LED_PIN1(p30);
PwmOut LED_PIN2(p25);

float volume = 0.0f;
float h = 0.0f;
float c = 0.0f;

int main() {
        
    //give the PIR sensor some time to calibrate
    wait(30.0f);  
    printf("Sensor active \n");
        
    while(1) {
        
        // PIR sensor         
        if (PIR_PIN){
            uart.printf("M: DETECTED; ");
            LED_PIN1=1;            
        }
        else{
            uart.printf("M: undetected; ");            
            LED_PIN1=0; 
        }
        
        // SOUND sensor
        volume = SND_PIN.read()*1000;
        LED_PIN2=SND_PIN.read()*10;   // Fade a led - values from 0.0 to 1.0
        uart.printf("L: %3.0f; ", volume);
                
        // TEMP & HUMIDITY sensor
        DHT_PIN.readData();
        c = DHT_PIN.ReadTemperature(CELCIUS);
        h = DHT_PIN.ReadHumidity();
        uart.printf("T (C): %4.2f; ", c);
        uart.printf("H: %4.2f;\n", h);
        
        wait(3.0f);                
    }   // end while
}
