#pragma once
#include "GlobalVariable.hpp"
#include <SDL3/SDL.h>
#include <array>

class Grid {
    public:
        std::array<std::array<Global::CellType, Global::canvaSizeX>, Global::canvaSizeY> cell = {
            Global::Element::air
        };

        SDL_Color getColor(const unsigned int x, const unsigned int y);
        void setElement(const unsigned int x, const unsigned int y, Global::Element targetElement);
        void swapElement(const unsigned int xA, const unsigned int yA, const unsigned int xB, const unsigned int yB);
        void update();
};