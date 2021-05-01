#include "easy2d/Core/Engine.hpp"
#include <SDL.h>

namespace easy2d
{
    Engine &getEngine()
    {
        static Engine *engine = new Engine();

        return *engine;
    }

    void Engine::initialize()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Window *window = SDL_CreateWindow("easy2d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(3000);
    }
}