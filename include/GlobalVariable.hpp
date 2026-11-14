#pragma once
#include <SDL3/SDL.h>

namespace Global {
    // Constant
    constexpr unsigned int hostScreenSizeX = 720;
    constexpr unsigned int hostScreenSizeY = 1600;
    constexpr unsigned int canvaSizeX = 60;
    constexpr unsigned int canvaSizeY = 60;
    
    // Variable
    inline float ambientTemperature = 18.0;

    // Object
    enum class Element : unsigned char {
        null,
        air,
        sand,
        water,
        stone
    };

    struct CellType {
        Element element{Element::air};
        float temperature = ambientTemperature;
    };
}