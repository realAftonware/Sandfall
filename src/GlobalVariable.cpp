#include "GlobalVariable.hpp"

SDL_Color Global::getColor(Element element) {
    switch (element) {
        default:
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

float Global::getDensity(Element element) {
    switch (element) {
        default:
        case Element::null:
        case Element::air:
            return 0.0;
        case Element::sand:
            return 2.5;
        case Element::water:
            return 0.75;
        case Element::stone:
            return 6.75;
    }
}