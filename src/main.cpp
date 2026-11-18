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
        {0, 0, 0, 255},
        Sandfall::canvaPixelWidth,
        Sandfall::canvaPixelHeight,
        Sandfall::canvaPositionX,
        Sandfall::canvaPositionY,
        false,
        0.0,
        0.0
    };
    
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            SDL_ConvertEventToRenderCoordinates(renderer, &event);
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                canva.onHeld(event.button.x, event.button.y);
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                canva.onRelease(event.button.x, event.button.y);
            }
            if (canva.isHeld && canva.isInBound(event.button.x, event.button.y)) {
                std::cout << "(PollEvent)" << canva.relativeX << "    " << canva.relativeY << "\n";
                Grid::setCell(canva.relativeX, canva.relativeY, {Sandfall::Element::sand});
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Start drawing here

        canva.render(renderer);

        for (int y = 0; y < Sandfall::canvaGridHeight; y++) {
            for (int x = 0; x < Sandfall::canvaGridWidth; x++) {
                SDL_Color cellColor = Sandfall::getColor(Grid::getCell(x, y).element);
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