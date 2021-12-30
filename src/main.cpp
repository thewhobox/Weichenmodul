#include <Arduino.h>
#include <Wire.h>

const byte addr = 0x37;

int timedelay = 100;
const int led = 3;
const int w11 = 7;
const int w12 = 8;
const int w21 = 14;
const int w22 = 15;

void DataReceive(int numBytes) { }
void DataRequest() { }

void setup() {
  Wire.begin(addr);
  Wire.onReceive(DataReceive);
  Wire.onRequest(DataRequest);
  
  pinMode(led, OUTPUT);
  pinMode(w11, OUTPUT);
  pinMode(w12, OUTPUT);
  pinMode(w21, OUTPUT);
  pinMode(w22, OUTPUT);


  for(int i = 0; i < 5; i++) {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
    delay(500);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Wire.available()) {
    digitalWrite(led, HIGH);
    int data = Wire.read();
    int pin;
    
    switch(data) {
      case 0:
        pin = w11;
        break;
      case 1:
        pin = w12;
        break;
      case 2:
        pin = w21;
        break;
      case 3:
        pin = w22;
        break;
    }

    digitalWrite(pin, HIGH);
    delay(timedelay);
    digitalWrite(pin, LOW);
    digitalWrite(led, LOW);
  }
}