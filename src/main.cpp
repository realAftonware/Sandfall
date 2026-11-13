#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

int main() {
    std::cout << "[Sandfall] starting...\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL video services [" << SDL_GetError() << "]\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Sandfall", 720, 1600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    
    bool isRunning = false;
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Box test
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_FRect yellowBox = {50, 50, 400, 400};
        SDL_RenderFillRect(renderer, &yellowBox);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}