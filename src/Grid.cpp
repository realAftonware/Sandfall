#include "../include/Grid.hpp"

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
    Global::Element tmp = cell.at(yA).at(xA).element;
    cell.at(yA).at(xA).element = cell.at(yB).at(xB).element;
    cell.at(yB).at(xB).element = tmp;
}

void Grid::update() {
    for (int y = Global::canvaSizeY - 1; y > -1; y--) {
        for (int x = Global::canvaSizeX - 1; x > -1; x--) {
            switch (cell.at(y).at(x).element) {
                default:
                case Global::Element::null:
                case Global::Element::air:
                case Global::Element::stone:
                    continue;
                case Global::Element::sand:
                    if (y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(Global::Element::sand) > Global::getDensity(cell.at(y+1).at(x).element)) {
                            swapElement(x, y, x, y+1);
                        }
                    }
                    if (x > 0 && y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(Global::Element::sand) > Global::getDensity(cell.at(y-1).at(x-1).element)) {
                            swapElement(x, y, x-1, y+1);
                        }
                    }
                    if (x < Global::canvaSizeX - 1 && y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(Global::Element::sand) > Global::getDensity(cell.at(y+1).at(x+1).element)) {
                            swapElement(x, y, x+1, y+1);
                        }
                    }
                    break;
                case Global::Element::water:
                    if (y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(Global::Element::water) > Global::getDensity(cell.at(y+1).at(x).element)) {
                            swapElement(x, y, x, y+1);
                        }
                    }
                    if (x > 0 && y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(Global::Element::water) > Global::getDensity(cell.at(y-1).at(x-1).element)) {
                            swapElement(x, y, x-1, y+1);
                        }
                    }
                    if (x < Global::canvaSizeX - 1 && y < Global::canvaSizeY - 1) {
                        if (Global::getDensity(Global::Element::water) > Global::getDensity(cell.at(y+1).at(x+1).element)) {
                            swapElement(x, y, x+1, y+1);
                        }
                    }
                    if (x > 0) {
                        if (Global::getDensity(Global::Element::water) > Global::getDensity(cell.at(y).at(x-1).element)) {
                            swapElement(x, y, x-1, y);
                        }
                    }
                    if (x < Global::canvaSizeX - 1) {
                        if (Global::getDensity(Global::Element::water) > Global::getDensity(cell.at(y).at(x+1).element)) {
                            swapElement(x, y, x+1, y);
                        }
                    }
                    break;
            }
        }
    }
}