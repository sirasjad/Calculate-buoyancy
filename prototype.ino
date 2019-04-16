#include <Servo.h>

Servo esc;          // Creating a servo class withe name as ESC

Servo servo1;
Servo servo2;
const int servoPin1 = 6;
const int servoPin2 = 7;
const int buttonPin = 2;

volatile int buttonState = 0;
volatile unsigned long lastInterrupt = 0;

void setup() {
  esc.attach(8);      // Specify the ESC signal pin, Here as D8
  esc.writeMicroseconds(1000);  //initialize the signal to 1000
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), setGitterPosition, RISING);
}

void loop() {
  int val;      // Creating a variable val
  val = analogRead(A0);   // Read input from analog pin a0 and store in val
  val = map(val, 0, 1023, 1000, 2000);    // mapping the val to minimum and maximum input
  esc.writeMicroseconds(val);   // using val as the signal to ESC
  
}

void setGitterPosition(){
  if((millis() - lastInterrupt) > 500){
    switch(buttonState){
      case 0:{
        Serial.println("Opening gate!");
        for(int pos = 0; pos < 110; pos++){
          servo1.write(pos);
          servo2.write(pos);
        }
      } break;
      case 1:{
        Serial.println("Closing gate!");
        for(int pos = 110; pos > 30; pos--) { 
          servo1.write(pos);
          servo2.write(pos);
        }
      } break;
    }
    buttonState = !buttonState;
    lastInterrupt = millis();
  }
}
