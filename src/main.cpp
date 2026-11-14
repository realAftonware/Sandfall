#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "Grid.hpp"
#include "GlobalVariable.hpp"

int main() {
    std::cout << "[Sandfall] starting...\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL video services [" << SDL_GetError() << "]\n";
        return 1;
    }

    Grid grid;
    float cellSizeInPixel = static_cast<float>(Global::hostScreenSizeX) / Global::canvaSizeX;
    
    SDL_Window* window = SDL_CreateWindow("Sandfall", Global::hostScreenSizeX, Global::hostScreenSizeY, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Let continue from here
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Drawing here
        for (int y = 0; y < Global::canvaSizeY; y++) {
            for (int x = 0; x < Global::canvaSizeX; x++) {
                SDL_Color cellColor = grid.getColor(x, y);
                SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
                SDL_FRect cell = {x * cellSizeInPixel, y * cellSizeInPixel, cellSizeInPixel, cellSizeInPixel};
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