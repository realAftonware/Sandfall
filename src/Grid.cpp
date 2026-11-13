#include "Grid.hpp"

void Grid::dump() {
    for (int x = 0; x < Global::canvaSizeX; x++) {
        for (int y = 0; y < Global::canvaSizeY; y++) {
            std::cout << cell.at(x).at(y).element;
            if (x == Global::canvaSizeX - 1)
                std::cout << '\n';
        }
    }
}