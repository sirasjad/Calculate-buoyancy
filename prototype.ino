#include <Servo.h>

Servo servo1;
Servo servo2;
const int servoPin1 = 6;
const int servoPin2 = 7;
const int buttonPin = 2;

volatile int buttonState = 0;
volatile unsigned long lastInterrupt = 0;

void setup() {
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), setGitterPosition, RISING);
  Serial.begin(9600);
}

void loop() {
  //
}

void setGitterPosition(){
  if((millis() - lastInterrupt) > 2000){
    switch(buttonState){
      case 0:{
        Serial.println("Opening gate!");
        for(int pos = 0; pos < 180; pos++){
          servo1.write(pos);
          servo2.write(pos);
        }
      } break;
      case 1:{
        Serial.println("Closing gate!");
        for(int pos = 180; pos > 15; pos--) { 
          servo1.write(pos);
          servo2.write(pos);
        }
      } break;
    }
    buttonState = !buttonState;
    lastInterrupt = millis();
  }
}
