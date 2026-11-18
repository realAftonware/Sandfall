#pragma once
#include "../include/Variable.hpp"
#include <SDL3/SDL.h>
#include <array>

namespace Grid {
    struct CellData {
        Sandfall::Element element = Sandfall::Element::air;
        bool canMove = true;

        bool canGoDown = false;
        bool canGoLeftDown = false;
        bool canGoRightDown = false;
        bool canGoLeft = false;
        bool canGoRight = false;
    };
    inline std::array<CellData, Sandfall::canvaGridWidth * Sandfall::canvaGridHeight> cell = {};

    unsigned int calcCellIndex(const unsigned int x, const unsigned int y);
    CellData getCell(const unsigned int x, const unsigned int y);
    void setCell(const unsigned int x, const unsigned int y, const CellData cellData);
    void swapCell(const unsigned int ax, const unsigned int ay, const unsigned int bx, const unsigned int by);
    void setViablePath(const unsigned int x, const unsigned int y);
    void update();
}