#pragma once
#include "../include/Variable.hpp"
#include <SDL3/SDL.h>
#include <array>

namespace Grid {
    struct CellData {
        Sandfall::Element element = Sandfall::Element::air;
    };
    inline std::array<CellData, Sandfall::canvaGridWidth * Sandfall::canvaGridHeight> cell = {};

    unsigned int calcCellIndex(const unsigned int x, const unsigned int y);
    CellData getCell(const unsigned int x, const unsigned int y);
    void setCell(const unsigned int x, const unsigned int y, const CellData cellData);
}