#pragma once

enum ElementType
{
    Weiche,
    Signal,
    Block,
    Trenner
};

struct Element
{
    const int pin1;
    const int pin2;
    ElementType type;
};