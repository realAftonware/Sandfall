#include "../include/Variable.hpp"

namespace Sandfall {
    float getDensity(Element element) {
        switch (element) {
            default:
            case Element::air:
                return 0.0;
            case Element::sand:
                return 1.44;
            case Element::water:
                return 1.0;
            case Element::stone:
                return 2.6;
        }
    }

    SDL_Color getColor(Element element) {
        switch (element) {
            default:
                return {0, 0, 0, 0};
            case Element::air:
                return {25, 25, 25, 255};
            case Element::sand:
                return {252, 198, 3, 255};
            case Element::water:
                return {3,   136, 252, 255};
            case Element::stone:
                return {128, 140, 150, 255};
        }
    }
    
    void Button::render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_FRect box = {positionX, positionY, width, height};
        SDL_RenderFillRect(renderer, &box);
    }

    bool Button::isInBound(const float touchX, const float touchY) {
        bool metX = touchX >= positionX && touchX < positionX + width;
        bool metY = touchY >= positionY && touchY < positionY + height;
        return (metX && metY);
    }
    
    void Button::check(const float touchX, const float touchY) {
        if (isInBound(touchX, touchY)) {
            isHeld = true;
            relativeX = touchX - positionX;
            relativeY = touchY - positionY;
        }
        else {
            isHeld = false;
            relativeX = relativeY = 0.0;
        }
    }
}