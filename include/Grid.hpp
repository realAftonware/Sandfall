#pragma once
#include <array>

class Grid {
    static const unsigned int sizeX = 60;
    static const unsigned int sizeY = 60;
    
    public:
        std::array<std::array<unsigned int, sizeX>, sizeY> cell = {};
};