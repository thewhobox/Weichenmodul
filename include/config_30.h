#include <Arduino.h>
#include "types.h"
#include "pins.h"

const byte addr = 0x30;

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
        .type = ElementType::Weiche
    },
    {
        .pin1 = PIN_D3,
        .pin2 = PIN_D4,
        .type = ElementType::Weiche
    },
};
