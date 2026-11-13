#pragma once
#include "GlobalVariable.hpp"

enum class Element {
    air,
    sand,
    water,
    stone
};

struct CellType {
    Element element{Element::air};
    float temperature = Global::ambientTemperature;
};