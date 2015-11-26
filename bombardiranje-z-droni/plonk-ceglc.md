# Plonk ceglc

Tole gledamo bolj v skrajni sili. Če si prišel do sem slučajno, pojdi raje na zadnjo odprto stran. Če pa je bila sila, najdi ustrezen program in ga skušaj razumeti.

## Štetje prehodov magneta in časa med prehodi

    #include "LiquidCrystal.h"
    LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 6);

    int count = 0;
    long last_time = millis();

    void magnet() {
      long time_passed;  
      
      count = count + 1;
      time_passed = millis() - last_time;
      last_time = millis();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(count);
      lcd.setCursor(0, 1);
      lcd.print(time_passed);
    }

    void setup() {
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("Frizider");
      attachInterrupt(digitalPinToInterrupt(2), magnet, RISING);
    }

    void loop() {
    }

## Merjenje hitrosti

    #include "LiquidCrystal.h"
    LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 6);

    int count = 0;
    long last_time = millis();

    void magnet() {
      long time_passed;
      float v;
      
      count = count + 1;
      time_passed = millis() - last_time;
      last_time = millis();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(count);
      lcd.setCursor(0, 1);
      v = 0.2 / time_passed * 1000;
      lcd.print(v);
    }

    void setup() {
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("Frizider");
      attachInterrupt(digitalPinToInterrupt(2), magnet, RISING);
    }

    void loop() {
    }

## Merjenje hitrosti z dronom

    #include "LiquidCrystal.h"
    LiquidCrystal lcd(13, 12, 11, 6, 5, 4, 3);

    int count = 0;
    long last_time = millis();

    void magnet() {
      long time_passed;
      float v;
      
      count = count + 1;
      time_passed = millis() - last_time;
      last_time = millis();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(count);
      lcd.setCursor(0, 1);
      v = 0.2 / time_passed * 1000;
      lcd.print(v);
    }

    void setup() {
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("Frizider");
      attachInterrupt(digitalPinToInterrupt(2), magnet, RISING);
    }

    void loop() {
    }

## Met na 10-em magnetu

    #include "LiquidCrystal.h"
    #include "Servo.h"

    LiquidCrystal lcd(13, 12, 11, 6, 5, 4, 3);
    int servoPin = 10;
    int servoStart = 115;  // start angle of the servo
    int servoEnd = 160;  // end position of the servo
    bool dropped = false;
    Servo myservo;

    int count = 0;

    void magnet() {
      count = count + 1;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(count);
    }

    void setup() {
      lcd.begin(16, 2);
      lcd.setCursor(0, 0);
      lcd.print("Frizider");
      attachInterrupt(digitalPinToInterrupt(2), magnet, RISING);
      myservo.attach(servoPin);
      myservo.write(servoStart);
      delay(500);
      myservo.detach();
    }

    void loop() {
      if (count == 10 and not dropped) {
        myservo.attach(servoPin);
        myservo.write(servoEnd); // drop ball
        delay(1000);
        myservo.write(servoStart); // put the servo in the start position
        delay(1000);
        myservo.detach(); // switch off the servo to spare batteries
        dropped = true;
      }
    }