#include "../include/Grid.hpp"

namespace Grid {
    unsigned int calcCellIndex(const unsigned int x, const unsigned int y) {
        unsigned int tmp = x + (y * Sandfall::canvaGridWidth);
        return tmp;
    }
    
    CellData& getCell(const unsigned int x, const unsigned int y) {
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

    void update() {
        for (int y = Sandfall::canvaGridHeight - 1; y >= 0; --y) {
            for (int x = Sandfall::canvaGridWidth - 1; x >= 0; --x) {
                CellData& currentCell = getCell(x, y);

                if (!currentCell.canMove) {
                    currentCell.canMove = true;
                    continue;
                }
                
                switch (currentCell.element) {
                    case Sandfall::Element::MAX:
                    case Sandfall::Element::air:
                    case Sandfall::Element::stone:
                        continue;
                    case Sandfall::Element::sand:
                        if (y < Sandfall::canvaGridHeight - 1) {
                            if (Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x, y+1).element)) {
                                currentCell.canMove = false;
                                swapCell(x, y, x, y+1);
                            }
                            else if (x > 0 && Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x-1, y+1).element)) {
                                currentCell.canMove = false;
                                swapCell(x, y, x-1, y+1);
                            }
                            else if (x < Sandfall::canvaGridWidth - 1 && Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x+1, y+1).element)) {
                                currentCell.canMove = false;
                                swapCell(x, y, x+1, y+1);
                            }
                        }
                        break;
                    case Sandfall::Element::water:
                        if (y < Sandfall::canvaGridHeight - 1) {
                            if (Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x, y+1).element)) {
                                currentCell.canMove = false;
                                swapCell(x, y, x, y+1);
                                break;
                            }
                            else if (x > 0 && Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x-1, y+1).element)) {
                                currentCell.canMove = false;
                                swapCell(x, y, x-1, y+1);
                                break;
                            }
                            else if (x < Sandfall::canvaGridWidth - 1 && Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x+1, y+1).element)) {
                                currentCell.canMove = false;
                                swapCell(x, y, x+1, y+1);
                                break;
                            }
                        }
                        if (x > 0 && Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x-1, y).element) && !currentCell.waterGoRight) {
                            currentCell.canMove = false;
                            swapCell(x, y, x-1, y);
                        }
                        else {
                            currentCell.waterGoRight = true;
                        }
                        break;
                        
                        if (x < Sandfall::canvaGridWidth - 1 && Sandfall::getDensity(currentCell.element) > Sandfall::getDensity(getCell(x+1, y).element) && currentCell.waterGoRight) {
                            currentCell.canMove = false;
                            swapCell(x, y, x+1, y);
                        }
                        else {
                            currentCell.waterGoRight = false;
                        }
                        break;
                }
            }
        }
    }
}