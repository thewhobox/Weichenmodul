#include <Arduino.h>
#include <Wire.h>
#include "pins.h"

const byte addr = 0x30;

int timedelay = 10000;

enum ElementType
{
    Weiche,
    Signal,
    Block
};

struct Element
{
    const int pin1;
    const int pin2;
    ElementType type;
};

const Element Elements[] = {
    {
        .pin1 = PIN_D15,
        .pin2 = PIN_D16,
        .type = ElementType::Weiche
    },
    {
        .pin1 = PIN_D5,
        .pin2 = PIN_D6,
        .type = ElementType::Weiche
    },
    {
        .pin1 = PIN_D7,
        .pin2 = PIN_D8,
        .type = ElementType::Signal
    },
    {
        .pin1 = PIN_D3,
        .pin2 = PIN_D4,
        .type = ElementType::Signal
    },
};

const int led1 = PIN_D14;
const int led2 = PIN_D13;

void DataReceive(int numBytes) {}
void DataRequest() {}

void blink(int count)
{
    digitalWrite(led2, HIGH);
    delay(500);

    for (int i = 0; i < count; i++)
    {
        digitalWrite(led1, HIGH);
        delay(1000);
        digitalWrite(led1, LOW);
        delay(500);
    }
    digitalWrite(led2, LOW);
}

void setup()
{
    Wire.begin(addr);
    Wire.onReceive(DataReceive);
    Wire.onRequest(DataRequest);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    
    int counter = sizeof(Elements) / sizeof(Elements[0]);
    blink(counter);
    for(int i = 0; i < counter; i++)
    {
        pinMode(Elements[i].pin1, OUTPUT);
        pinMode(Elements[i].pin2, OUTPUT);
        digitalWrite(Elements[i].pin1, LOW);
        digitalWrite(Elements[i].pin2, LOW);
    }


    for (int i = 0; i < 2; i++)
    {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
        delay(1000);
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
        delay(500);
    }

    digitalWrite(led2, LOW);    
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
            case ElementType::Weiche:
            {
                blink(4);
                digitalWrite(led1, HIGH);
                int pin = state ? ele.pin2 : ele.pin1;
                digitalWrite(pin, HIGH);
                delay(timedelay);
                digitalWrite(pin, LOW);
                digitalWrite(led1, LOW);
                break;
            }

            case ElementType::Signal:
            {
                blink(8);
                digitalWrite(state ? ele.pin1 : ele.pin2, LOW);
                digitalWrite(state ? ele.pin2 : ele.pin1, HIGH);
                break;
            }
        }

        digitalWrite(led1, LOW);
    }
}