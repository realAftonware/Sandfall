#include "../include/Grid.hpp"

Grid::Grid() {
    for (int y = 0; y < Global::canvaSizeY; y++) {
        for (int x = 0; x < Global::canvaSizeX; x++) {
            cell.at(y).at(x).element = Global::Element::air;
        }
    }
}

SDL_Color Grid::getColor(const unsigned int x, const unsigned int y) {
    if (x > Global::canvaSizeX - 1 || y > Global::canvaSizeY - 1) {
        return SDL_Color{0, 0, 0, 255};
    }

    return Global::getColor(cell.at(y).at(x).element);
}

void Grid::setElement(const unsigned int x, const unsigned int y, Global::Element targetElement) {
    if (x > Global::canvaSizeX - 1 || y > Global::canvaSizeY - 1) {
        return;
    }

    cell.at(y).at(x).element = targetElement;
}

void Grid::swapElement(const unsigned int xA, const unsigned int yA, const unsigned int xB, const unsigned int yB) {
    Global::CellType tmp = cell.at(yA).at(xA);
    cell.at(yA).at(xA) = cell.at(yB).at(xB);
    cell.at(yB).at(xB) = tmp;
}

void Grid::update() {
    for (int y = Global::canvaSizeY - 1; y > -1; y--) {
        for (int x = Global::canvaSizeX - 1; x > -1; x--) {
            if (cell.at(y).at(x).alreadyMoved) {
                cell.at(y).at(x).alreadyMoved = false;
                continue;
            }
            switch (cell.at(y).at(x).element) {
                default:
                case Global::Element::null:
                case Global::Element::air:
                case Global::Element::stone:
                    continue;
                case Global::Element::sand:
                    if (y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(cell.at(y+1).at(x).element) < Global::getDensity(Global::Element::sand)) {
                            swapElement(x, y, x, y+1);
                            break;
                        }
                        if (x > 0) {
                            if (Global::getDensity(cell.at(y+1).at(x-1).element) < Global::getDensity(Global::Element::sand)) {
                                swapElement(x, y, x-1, y+1);
                                break;
                            }
                        }
                        if (x < Global::canvaSizeX - 1) {
                            if (Global::getDensity(cell.at(y+1).at(x+1).element) < Global::getDensity(Global::Element::sand)) {
                                swapElement(x, y, x+1, y+1);
                                break;
                            }
                        }
                    }
                    break;
                case Global::Element::water:
                    if (cell.at(y).at(x).isGoingRight && x == Global::canvaSizeX - 1) {
                        cell.at(y).at(x).isGoingRight = false;
                    }
                    if (!cell.at(y).at(x).isGoingRight && x == 0) {
                        cell.at(y).at(x).isGoingRight = true;
                    }
                    if (y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(cell.at(y+1).at(x).element) < Global::getDensity(Global::Element::water)) {
                            swapElement(x, y, x, y+1);
                            break;
                        }
                        if (x > 0) {
                            if (Global::getDensity(cell.at(y+1).at(x-1).element) < Global::getDensity(Global::Element::water)) {
                                swapElement(x, y, x-1, y+1);
                                break;
                            }
                        }
                        if (x < Global::canvaSizeX - 1) {
                            if (Global::getDensity(cell.at(y+1).at(x+1).element) < Global::getDensity(Global::Element::water)) {
                                swapElement(x, y, x+1, y+1);
                                break;
                            }
                        }
                    }
                    if (x > 0) {
                        if (Global::getDensity(cell.at(y).at(x-1).element) < Global::getDensity(Global::Element::water) && !cell.at(y).at(x).isGoingRight) {
                            cell.at(y).at(x).alreadyMoved = true;
                            swapElement(x, y, x-1, y);
                            break;
                        }
                        else if (!cell.at(y).at(x).isGoingRight) {
                            cell.at(y).at(x).isGoingRight = true;
                            break;
                        }
                    }
                    if (x < Global::canvaSizeX - 1) {
                        if (Global::getDensity(cell.at(y).at(x+1).element) < Global::getDensity(Global::Element::water) && cell.at(y).at(x).isGoingRight) {
                            cell.at(y).at(x).alreadyMoved = false;
                            swapElement(x, y, x+1, y);
                            break;
                        }
                        else if (cell.at(y).at(x).isGoingRight) {
                            cell.at(y).at(x).isGoingRight = false;
                            break;
                        }
                    }
                    break;
            }
        }
    }
}