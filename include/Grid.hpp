#pragma once
#include "GlobalVariable.hpp"
#include <SDL3/SDL.h>
#include <array>

class Grid {
    public:
        std::array<std::array<Global::CellType, Global::canvaSizeX>, Global::canvaSizeY> cell = {};

        SDL_Color getColor(const unsigned int x, const unsigned int y);
        void setElement(const unsigned int x, const unsigned int y, Global::Element targetElement);
};