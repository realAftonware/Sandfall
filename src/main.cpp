#include "../include/Variable.hpp"
#include "../include/Grid.hpp"
#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "[ERROR] Failed to initialize SDL3 video service [" << SDL_GetError() << "]\n";
        SDL_Quit();
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Sandfall", Sandfall::screenWidth, Sandfall::screenHeight, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        std::cerr << "[ERROR] Failed to create Window [" << SDL_GetError() << "]\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        std::cerr << "[ERROR] Failed to create Renderer [" << SDL_GetError() << "]\n";
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderLogicalPresentation(renderer, Sandfall::screenWidth, Sandfall::screenHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    
    Sandfall::Button canva = {
        {25, 25, 25, 255},
        Sandfall::canvaPixelWidth,
        Sandfall::canvaPixelHeight,
        Sandfall::canvaPositionX,
        Sandfall::canvaPositionY,
        false,
        0.0,
        0.0,
        [&]() {
            if (canva.isHeld) {
                unsigned int gridX = static_cast<unsigned int>(canva.relativeX / Sandfall::cellWidthInPixel);
                unsigned int gridY = static_cast<unsigned int>(canva.relativeY / Sandfall::cellHeightInPixel);

                if (gridX < Sandfall::canvaGridWidth && gridY < Sandfall::canvaGridHeight) {
                    Grid::setCell(gridX, gridY, {Sandfall::currentHoldingElement});
                }
            }
        }
    };

    Sandfall::Button switchElement = {
        {252, 198, 3, 255},
        300,
        300,
        210,
        1110,
        false,
        0.0,
        0.0,
        [&](float x, float y) {
            if (canva.isHeld) {
                bool condX = x >= positionX && x <= positionX + width;
                bool condY = y >= positionY && y <= positionY + height;
                if (condX && condY) {
                    if (static_cast<int>(Sandfall::currentHoldingElement) < (static_cast<int>(Sandfall::Element::MAX) - 1)) {
                        Sandfall::currentHoldingElement = static_cast<Sandfall::Element>(static_cast<int>(Sandfall::currentHoldingElement) + 1);
                    }
                    else {
                        Sandfall::currentHoldingElement = Sandfall::Element::air;
                    }
                }
            }
        }
    };
    
    bool quit = false;
    while (!quit) {
        SDL_PumpEvents();
        SDL_Event event;
        while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST) > 0) {
            SDL_ConvertEventToRenderCoordinates(renderer, &event);
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                canva.check(event.button.x, event.button.y);
                canva.lambda1();
                switchElement.check(event.button.x, event.button.y);
                switchElement.lambda1(event.button.x, event.button.y);
            }
            else if (event.type == SDL_EVENT_MOUSE_MOTION && (event.motion.state & SDL_BUTTON_LMASK)) {
                canva.check(event.motion.x, event.motion.y);
                canva.lambda1();
            }
            else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
                canva.isHeld = false;
                canva.relativeX = 0.0f;
                canva.relativeY = 0.0f;
            }
        }

        Grid::update();
        switchElement.fillColor = Sandfall::getColor(Sandfall::currentHoldingElement);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Start drawing here

        canva.render(renderer);
        switchElement.render(renderer);

        for (int y = 0; y < Sandfall::canvaGridHeight; y++) {
            for (int x = 0; x < Sandfall::canvaGridWidth; x++) {
                Sandfall::Element cellElement = Grid::getCell(x, y).element;

                if (cellElement == Sandfall::Element::air) continue;
                
                SDL_Color cellColor = Sandfall::getColor(cellElement);
                SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
                SDL_FRect cell = {x * Sandfall::cellWidthInPixel + Sandfall::canvaPositionX, y * Sandfall::cellHeightInPixel + Sandfall::canvaPositionY, Sandfall::cellWidthInPixel, Sandfall::cellHeightInPixel};
                SDL_RenderFillRect(renderer, &cell);
            }
        }
        
        // Stop drawing here
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}