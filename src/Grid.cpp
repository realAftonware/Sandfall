#include "../include/Grid.hpp"

namespace Grid {
    unsigned int calcCellIndex(const unsigned int x, const unsigned int y) {
        unsigned int tmp = x + (y * Sandfall::canvaGridHeight);
        std::cout << "(calcCellIndex)" << tmp << " = " << x << "    " << y << "\n";
        return tmp;
    }
    CellData getCell(const unsigned int x, const unsigned int y) {
        return cell.at(calcCellIndex(x, y));
    }
    void setCell(const unsigned int x, const unsigned int y, const CellData cellData) {
        cell.at(calcCellIndex(x, y)) = cellData;
    }
}