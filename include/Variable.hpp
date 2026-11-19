#pragma once
#include <SDL3/SDL.h>
#include <functional>

namespace Sandfall {
    enum class Element {
        air,
        sand,
        water,
        stone,
        MAX
    };
    
    SDL_Color getColor(Element element);
    float getDensity(Element element);
    
    constexpr float screenWidth = 720.0;
    constexpr float screenHeight = 1600.0;
    constexpr float canvaPixelWidth = screenWidth;
    constexpr float canvaPixelHeight = screenWidth;
    constexpr unsigned int canvaGridWidth = 60;
    constexpr unsigned int canvaGridHeight = 60;
    constexpr float canvaPositionX = 0.0;
    constexpr float canvaPositionY = 200.0;
    constexpr float cellWidthInPixel = canvaPixelWidth / canvaGridWidth;
    constexpr float cellHeightInPixel = canvaPixelHeight / canvaGridHeight;

    inline Element currentHoldingElement = Element::sand;

    struct Button {
        SDL_Color fillColor{0, 0, 0, 0};
        float width = 0.0;
        float height = 0.0;
        float positionX = 0.0;
        float positionY = 0.0;
        
        bool isHeld = false;
        float relativeX = 0.0;
        float relativeY = 0.0;
        
        void render(SDL_Renderer* renderer);
        bool isInBound(const float touchX, const float touchY);
        void check(const float touchX, const float touchY);
        std::function<void(Button&)> lambda1 = [](Button&) {};
        std::function<void(Button&)> lambda2 = [](Button&) {};
        std::function<void(Button&)> lambda3 = [](Button&) {};
    };
}