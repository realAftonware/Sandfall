#pragma once
#include <SDL3/SDL.h>

namespace Global {
    enum class Element : unsigned char {
        null,
        air,
        sand,
        water,
        stone
    };
    
    // Constant
    constexpr unsigned int hostScreenSizeX = 720;
    constexpr unsigned int hostScreenSizeY = 1600;
    constexpr unsigned int canvaSizeX = 60;
    constexpr unsigned int canvaSizeY = 60;
    constexpr unsigned int canvaPositionX = 0;
    constexpr unsigned int canvaPositionY = 200;
    constexpr unsigned int buttonSizeX = 300;
    constexpr unsigned int buttonSizeY = 300;
    constexpr unsigned int buttonPositionX = 210;
    constexpr unsigned int buttonPositionY = 1110;
    constexpr unsigned int elementCounts = 5;
    
    // Variable
    inline Element holdingElement = Element::sand;

    // Object
    struct CellType {
        Element element{Element::null};
        float density{0.0};
    };

    SDL_Color getColor(Element element);
    float getDensity(Element element);
}