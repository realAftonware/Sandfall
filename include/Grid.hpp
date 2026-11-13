#pragma once
#include "GlobalVariable.hpp"
#include <array>

class Grid {
    public:
        std::array<std::array<Global::CellType, Global::canvaSizeX>, Global::canvaSizeY> cell = {};
};