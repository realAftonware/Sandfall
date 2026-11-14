#include "../include/Grid.hpp"

SDL_Color Grid::getColor(const unsigned int x, const unsigned int y) {
    if (x > Global::canvaSizeX - 1 || y > Global::canvaSizeY - 1) {
        return SDL_Color{0, 0, 0, 255};
    }

    switch (cell[y][x].element) {
        case Global::Element::null:
            return SDL_Color{0,   0,   0,   255};
        case Global::Element::air:
            return SDL_Color{25,  25,  25,  255};
        case Global::Element::sand:
            return SDL_Color{252, 198, 3,   255};
        case Global::Element::water:
            return SDL_Color{3,   136, 252, 255};
        case Global::Element::stone:
            return SDL_Color{128, 140, 150, 255};
    }
}