#include <Arduino.h>
#include <Wire.h>
#include "pins.h"

const byte addr = 0x37;

int timedelay = 100;

enum ElementType
{
    Weiche,
    Signal,
    Block
}

struct Element
{
    const int pin1,
    const int pin2,
    const ElementType type
};

const Element Elements[] = {
    {
        .pin1 = PIN_D15,
        .pin2 = PIN_D16,
        .type = ElementType.Weiche
    },
    {
        .pin1 = PIN_D5,
        .pin2 = PIN_D6,
        .type = ElementType.Weiche
    },
    {
        .pin1 = PIN_D7,
        .pin2 = PIN_D8,
        .type = ElementType.Signal
    },
    {
        .pin1 = PIN_D3,
        .pin2 = PIN_D4,
        .type = ElementType.Signal
    },
};

const int led1 = PIN_D14;
const int led2 = PIN_D13;

void DataReceive(int numBytes) {}
void DataRequest() {}

void setup()
{
    Wire.begin(addr);
    Wire.onReceive(DataReceive);
    Wire.onRequest(DataRequest);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    
    int counter = size(Elements) / size(Elements[0]);
    for(int i = 0; i < counter; i++)
    {
        pinMode(Elements[i].pin1, OUTPUT);
        pinMode(Elements[i].pin2, OUTPUT);
    }


    for (int i = 0; i < 4; i++)
    {
        digitalWrite(led1, HIGH);
        delay(1000);
        digitalWrite(led1, LOW);
        delay(500);
    }

    digitalWrite(led2, HIGH);
    delay(1000);
    digitalWrite(led2, LOW);
    delay(500);
    
}

void loop()
{
    if (Wire.available())
    {
        digitalWrite(led1, HIGH);
        int data = Wire.read();
        int index = data >> 1;
        int state = data & 0x01;

        Element ele = Elements[index];

        switch(ele.type)
        {
            case ElementType.Weiche:
            {
                int pin = state ? ele.pin2 : ele.pin1;
                digitalWrite(pin, HIGH);
                delay(timedelay);
                digitalWrite(pin, LOW);
                break;
            }

            case ElementType.Signal:
            {
                digitalWrite(state ? ele.pin1 : ele.pin2, LOW);
                digitalWrite(state ? ele.pin2 : ele.pin1, HIGH);
                break;
            }
        }

        digitalWrite(led1, LOW);
    }
}