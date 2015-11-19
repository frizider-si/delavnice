const int buttonPin = 7;
const int ledPin =  2;

int buttonState = 0;
int ledState = LOW;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if (ledState == LOW) {
      ledState = HIGH;
    }
    else {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
    while (buttonState == HIGH) {
      buttonState = digitalRead(buttonPin);
    }
  }
}
