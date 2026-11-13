#pragma once
#include "GlobalVariable.hpp"
#include "CellType.hpp"
#include <array>
#include <iostream>

class Grid {
    public:
        std::array<std::array<CellType, Global::canvaSizeX>, Global::canvaSizeY> cell = {};

        void dump();
};