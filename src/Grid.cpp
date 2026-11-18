#include "../include/Grid.hpp"

namespace Grid {
    unsigned int calcCellIndex(const unsigned int x, const unsigned int y) {
        unsigned int tmp = x + (y * Sandfall::canvaGridWidth);
        return tmp;
    }
    
    CellData getCell(const unsigned int x, const unsigned int y) {
        return cell.at(calcCellIndex(x, y));
    }
    
    void setCell(const unsigned int x, const unsigned int y, const CellData cellData) {
        cell.at(calcCellIndex(x, y)) = cellData;
    }

    void swapCell(const unsigned int ax, const unsigned int ay, const unsigned int bx, const unsigned int by) {
        CellData swapPlace = getCell(ax, ay);
        setCell(ax, ay, getCell(bx, by));
        setCell(bx, by, swapPlace);
    }

    void setViablePath(const unsigned int x, const unsigned int y) {
        switch (getCell(x, y).element) {
            default:
            case Sandfall::Element::air:
            case Sandfall::Element::stone:
                cell.at(calcCellIndex(x, y)).canGoDown = false;
                cell.at(calcCellIndex(x, y)).canGoLeftDown = false;
                cell.at(calcCellIndex(x, y)).canGoRightDown = false;
                cell.at(calcCellIndex(x, y)).canGoLeft = false;
                cell.at(calcCellIndex(x, y)).canGoRight = false;
                break;
            case Sandfall::Element::sand:
                if (y > 0) {
                    cell.at(calcCellIndex(x, y)).canGoDown = (Sandfall::getDensity(getCell(x, y+1).element) < Sandfall::getDensity(Sandfall::Element::sand));
                    if (x > 0) cell.at(calcCellIndex(x, y)).canGoLeftDown = (Sandfall::getDensity(getCell(x-1, y+1).element) < Sandfall::getDensity(Sandfall::Element::sand));
                    if (x < Sandfall::canvaGridWidth - 1)cell.at(calcCellIndex(x, y)).canGoRightDown = (Sandfall::getDensity(getCell(x+1, y+1).element) < Sandfall::getDensity(Sandfall::Element::sand));
                }
                break;
            case Sandfall::Element::water:
                if (y > 0) {
                    cell.at(calcCellIndex(x, y)).canGoDown = (Sandfall::getDensity(getCell(x, y+1).element) < Sandfall::getDensity(Sandfall::Element::sand));
                    if (x > 0) cell.at(calcCellIndex(x, y)).canGoLeftDown = (Sandfall::getDensity(getCell(x-1, y+1).element) < Sandfall::getDensity(Sandfall::Element::sand));
                    if (x < Sandfall::canvaGridWidth - 1) cell.at(calcCellIndex(x, y)).canGoRightDown = (Sandfall::getDensity(getCell(x+1, y+1).element) < Sandfall::getDensity(Sandfall::Element::sand));
                }
                break;
        }
    }

    void update() {
        for (int y = Sandfall::canvaGridHeight - 1; y > 0; y--) {
            for (int x = Sandfall::canvaGridWidth - 1; x > 0; x--) {
                setViablePath(x, y);
                CellData currentCell = getCell(x, y);
                switch (currentCell.element) {
                    default:
                    case Sandfall::Element::air:
                    case Sandfall::Element::stone:
                        continue;
                    case Sandfall::Element::sand:
                        if (currentCell.canGoDown) swapCell(x, y, x, y+1);
                        else if (currentCell.canGoLeftDown) swapCell(x, y, x-1, y+1);
                        else if (currentCell.canGoRightDown) swapCell(x, y, x+1, y+1);
                        break;
                    case Sandfall::Element::water:
                        break;
                }
            }
        }
    }
}