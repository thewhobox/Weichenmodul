#include <Arduino.h>
#include <Wire.h>
#include "pins.h"
#include "types.h"

#include "config_32.h"

int timedelay = 100;

const int led1 = PIN_D14;
const int led2 = PIN_D13;
const uint8_t pins[] = {
    PIN_D15, PIN_D16,   //Weiche 1
    PIN_D5, PIN_D6,     //weiche 2
    PIN_D7, PIN_D8,     //weiche 3
    PIN_D3, PIN_D4      //Weiche 4
};

void DataReceive(int numBytes) {}
void DataRequest() {}

void setup()
{
    int delayT = (addr - 0x30) * timedelay * 10;
    delay(delayT);

    Wire.begin(addr);
    Wire.onReceive(DataReceive);
    Wire.onRequest(DataRequest);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);

    int counter = sizeof(Elements) / sizeof(Elements[0]);
    for (int i = 0; i < counter; i++)
    {
        switch(Elements[i])
        {
            case ElementType::Weiche:
            {
                pinMode(pins[i*2], OUTPUT);
                pinMode(pins[i*2+1], OUTPUT);
                digitalWrite(pins[i*2], HIGH);
                digitalWrite(pins[i*2+1], LOW);
                delay(timedelay);
                digitalWrite(pins[i*2], LOW);
                break;
            }

            case ElementType::Signal:
            {
                pinMode(pins[i*2], OUTPUT);
                pinMode(pins[i*2+1], OUTPUT);
                digitalWrite(pins[i*2], HIGH);
                digitalWrite(pins[i*2+1], LOW);
                break;
            }

            case ElementType::Block:
            {
                break;
            }

            case ElementType::Trenner:
            {
                pinMode(pins[i*2], OUTPUT);
                digitalWrite(pins[i*2], LOW);
                break;
            }
        }
    }

    digitalWrite(led2, HIGH);
    delay(500);
    digitalWrite(led1, HIGH);
    delay(200);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
}

void loop()
{
    if (Wire.available())
    {
        digitalWrite(led2, HIGH);
        int data = Wire.read();
        int index = data >> 1;
        int state = data & 0x01;

        ElementType ele = Elements[index];

        switch (ele)
        {
            case ElementType::Weiche:
            {
                digitalWrite(led1, HIGH);
                int pin = state ? pins[index*2+1] : pins[index*2];
                digitalWrite(pin, HIGH);
                delay(timedelay);
                digitalWrite(pin, LOW);
                digitalWrite(led1, LOW);
                break;
            }

            case ElementType::Signal:
            {
                if(state)
                {
                    digitalWrite(pins[index*2], LOW);
                    digitalWrite(pins[index*2+1], HIGH);
                } else {
                    digitalWrite(pins[index*2+1], LOW);
                    digitalWrite(pins[index*2], HIGH);
                }
                digitalWrite(led1, HIGH);
                delay(timedelay);
                digitalWrite(led1, LOW);
                break;
            }

            case ElementType::Block:
            {
                break;
            }

            case ElementType::Trenner:
            {
                digitalWrite(pins[index*2], HIGH);
                delay(1000);
                digitalWrite(pins[index*2], HIGH);
                break;
            }
        }

        digitalWrite(led2, LOW);
    }
}