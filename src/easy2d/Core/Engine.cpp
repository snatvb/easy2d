#include "easy2d/Core/Engine.hpp"
#include <entt/entt.hpp>
#include <SDL_config_winrt.h>
#include <SDL_image.h>

SDL_Texture *logoTexture;

struct position
{
    float x;
    float y;
};

struct velocity
{
    float dx;
    float dy;
};

void update(entt::registry &registry)
{
    auto view = registry.view<const position, velocity>();

    // use a callback
    view.each([](const auto &pos, auto &vel) { /* ... */ });

    // use an extended callback
    view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    // use a range-for
    for (auto [entity, pos, vel] : view.each())
    {
        // ...
    }

    // use forward iterators and get only the components of interest
    for (auto entity : view)
    {
        auto &vel = view.get<velocity>(entity);
        // ...
    }
}

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
        _window = SDL_CreateWindow("easy2d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        SDL_Renderer *renderer = SDL_CreateRenderer(_window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        SDL_Surface *logoSurface = IMG_Load("easy2d/resources/logo.png");
        logoTexture = SDL_CreateTextureFromSurface(renderer, logoSurface);
        SDL_FreeSurface(logoSurface);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, logoTexture, NULL, NULL);
        SDL_RenderPresent(renderer);

        entt::registry registry;

        for (auto i = 0u; i < 10u; ++i)
        {
            const auto entity = registry.create();
            registry.emplace<position>(entity, i * 1.f, i * 1.f);
            if (i % 2 == 0)
            {
                registry.emplace<velocity>(entity, i * .1f, i * .1f);
            }
        }

        update(registry);

        SDL_Delay(3000);
    }
}