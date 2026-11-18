#include "../include/Variable.hpp"

namespace Sandfall {
    ElementType getType(Element element) {
        switch (element) {
            default:
                return ElementType::stationary;
            case Element::air:
                return ElementType::gas;
            case Element::sand:
                return ElementType::powder;
            case Element::water:
                return ElementType::liquid;
            case Element::stone:
                return ElementType::stationary;
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

    void Button::onHeld(const float touchX, const float touchY) {
        bool metX = touchX > positionX && touchX <= positionX + width;
        bool metY = touchY > positionY && touchY <= positionY + height;
        if (metX && metY) {
            isHeld = true;
            relativeX = touchX - positionX;
            relativeY = touchY - positionY;
        }
    }

    void Button::onRelease(const float touchX, const float touchY) {
        bool metX = touchX > positionX && touchX <= positionX + width;
        bool metY = touchY > positionY && touchY <= positionY + height;
        if (!metX || !metY) {
            isHeld = false;
            relativeX = 0.0;
            relativeY = 0.0;
        }
    }

    bool Button::isInBound(const float touchX, const float touchY) {
        bool metX = touchX > positionX && touchX <= positionX + width;
        bool metY = touchY > positionY && touchY <= positionY + height;
        return (metX && metY);
    }
}