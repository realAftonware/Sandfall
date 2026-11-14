#include "../include/Grid.hpp"

SDL_Color Grid::getColor(const unsigned int x, const unsigned int y) {
    if (x > Global::canvaSizeX - 1 || y > Global::canvaSizeY - 1) {
        return SDL_Color{0, 0, 0, 255};
    }

    return Global::getColor(cell[y][x].element);
}

void Grid::setElement(const unsigned int x, const unsigned int y, Global::Element targetElement) {
    if (x > Global::canvaSizeX - 1 || y > Global::canvaSizeY - 1) {
        return;
    }

    cell[y][x].element = targetElement;
}