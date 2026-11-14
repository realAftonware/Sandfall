#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include "Grid.hpp"
#include "GlobalVariable.hpp"

int main(int argc, char* argv[]) {
    Grid grid;
    float cellSizeInPixel = static_cast<float>(Global::hostScreenSizeX) / Global::canvaSizeX;
    unsigned int holdingElementInt = static_cast<unsigned int>(Global::holdingElement);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL video services [" << SDL_GetError() << "]\n";
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Sandfall", Global::hostScreenSizeX, Global::hostScreenSizeY, 0);
    if (window == NULL) {
        std::cerr << "Failed to create SDL3 window [" << SDL_GetError() << "]\n";
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        std::cerr << "Failed to create SDL3 renderer [" << SDL_GetError() << "]\n";
        SDL_Quit();
        return 1;
    }

    bool isRunning = true;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    bool xValid = event.button.x >= Global::canvaPositionX && event.button.x < Global::canvaPositionX + (Global::canvaSizeX * cellSizeInPixel);
                    bool yValid = event.button.y >= Global::canvaPositionY && event.button.y < Global::canvaPositionY + (Global::canvaSizeY * cellSizeInPixel);
                    if (xValid && yValid) {
                        unsigned int targetCellGridX = (event.button.x - Global::canvaPositionX) / cellSizeInPixel;
                        unsigned int targetCellGridY = (event.button.y - Global::canvaPositionY) / cellSizeInPixel;
                        grid.setElement(targetCellGridX, targetCellGridY, Global::holdingElement);
                    }
                }
                if (event.button.button == SDL_BUTTON_LEFT) {
                    bool xValid = event.button.x >= Global::buttonPositionX && event.button.x < Global::buttonPositionX + Global::buttonSizeX;
                    bool yValid = event.button.y >= Global::buttonPositionY && event.button.y < Global::buttonPositionY + Global::buttonSizeY;
                    if (xValid && yValid) {
                        if (holdingElementInt < 4) {
                            
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        /* Drawing here */
        // Canva
        for (int y = 0; y < Global::canvaSizeY; y++) {
            for (int x = 0; x < Global::canvaSizeX; x++) {
                SDL_Color cellColor = grid.getColor(x, y);
                SDL_SetRenderDrawColor(renderer, cellColor.r, cellColor.g, cellColor.b, cellColor.a);
                SDL_FRect cell = {x * cellSizeInPixel + Global::canvaPositionX, y * cellSizeInPixel + Global::canvaPositionY, cellSizeInPixel, cellSizeInPixel};
                SDL_RenderFillRect(renderer, &cell);
            }
        }

        // Element button
        SDL_Color buttonColor = Global::getColor(static_cast<Global::Element>(holdingElementInt));
        SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
        SDL_FRect button = {Global::buttonPositionX, Global::buttonPositionY, Global::buttonSizeX, Global::buttonSizeY};
        SDL_RenderFillRect(renderer, &button);
        /* Stop drawing here */
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}