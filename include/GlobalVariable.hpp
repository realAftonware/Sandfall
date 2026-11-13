#pragma once

namespace Global {
    // Constant
    constexpr unsigned int canvaSizeX = 60;
    constexpr unsigned int canvaSizeY = 60;
    
    // Variable
    float ambientTemperature = 18.0;

    // Object
    enum class Element {
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