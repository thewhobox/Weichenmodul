#include <Arduino.h>
#include <Wire.h>
#include "pins.h"
#include "types.h"

#include "config_33.h"

int timedelay = 100;

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

    int counter = sizeof(Elements) / sizeof(Elements[0]);
    for (int i = 0; i < counter; i++)
    {
        switch(Elements[i].type)
        {
            case ElementType::Weiche:
            {
                pinMode(Elements[i].pin1, OUTPUT);
                pinMode(Elements[i].pin2, OUTPUT);
                digitalWrite(Elements[i].pin1, LOW);
                digitalWrite(Elements[i].pin2, LOW);
                break;
            }

            case ElementType::Signal:
            {
                pinMode(Elements[i].pin1, OUTPUT);
                pinMode(Elements[i].pin2, OUTPUT);
                digitalWrite(Elements[i].pin1, HIGH);
                digitalWrite(Elements[i].pin2, LOW);
                break;
            }

            case ElementType::Block:
            {
                break;
            }

            case ElementType::Trenner:
            {
                pinMode(Elements[i].pin1, OUTPUT);
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

        Element ele = Elements[index];

        switch (ele.type)
        {
            case ElementType::Weiche:
            {
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
                if(state)
                {
                    digitalWrite(ele.pin1, LOW);
                    digitalWrite(ele.pin2, HIGH);
                } else {
                    digitalWrite(ele.pin2, LOW);
                    digitalWrite(ele.pin1, HIGH);
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
                digitalWrite(ele.pin1, HIGH);
                delay(1000);
                digitalWrite(ele.pin1, HIGH);
                break;
            }
        }

        digitalWrite(led2, LOW);
    }
}