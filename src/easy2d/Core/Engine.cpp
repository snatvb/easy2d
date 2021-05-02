#include <string>
#include <filesystem>
#include <easy2d/Core/Engine.hpp>
#include <entt/entt.hpp>
#include <SDL_image.h>
#include <easy2d/Debug/Log.hpp>

namespace fs = std::filesystem;

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

    // ----------------------------------------------------------------------------------------
    void Engine::initialize()
    {
        log("Engine initialization...");
        log("Path of runner: " + fs::current_path().string());

        if (_initialized)
        {
            log("Engine Easy2D already initialized!");
            return;
        }

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            log("SDL initialize has error...");
            return;
        }
        log("SDL initialied");

        log("Creating window...");
        _window = SDL_CreateWindow("easy2d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!_window)
        {
            log("Window creating has error...");
            return;
        }
        log("Window created.");

        log("Create renderer...");
        _renderer = SDL_CreateRenderer(_window, -1, 0);
        if (!_renderer)
        {
            log("Renderer creating has error...");
            return;
        }
        log("Renderer created.");

        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        _playIntro();

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

        log("Initialization success.");
        log("Create game loop.");

        Uint32 frameStart = SDL_GetTicks();
        int frameTime;

        while (true)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    return;
                }
            }

            frameStart = SDL_GetTicks();

            SDL_RenderClear(_renderer);
            update(registry);
            SDL_RenderPresent(_renderer);

            frameTime = SDL_GetTicks() - frameStart;

            if (_frameDelay > frameTime)
            {
                SDL_Delay(_frameDelay - frameTime);
            }
        }
    }

    // ----------------------------------------------------------------------------------------
    void Engine::skipIntro()
    {
        _needPlayIntro = false;
    }

    // ----------------------------------------------------------------------------------------
    void Engine::_playIntro()
    {

        if (!_needPlayIntro)
        {
            return;
        }

        const int fps = 60;

        log("Create logo surface");
        SDL_Surface *logoSurface = IMG_Load("easy2d/resources/logo.png");
        log("Create texture from the surface");
        if (logoSurface)
        {
            log("Surface is ok");
        }
        else
        {
            log("Surface is incorrect");
            printf("IMG_Load: %s\n", IMG_GetError());
        }
        logoTexture = SDL_CreateTextureFromSurface(_renderer, logoSurface);
        SDL_FreeSurface(logoSurface);
        SDL_SetTextureBlendMode(logoTexture, SDL_BLENDMODE_BLEND);

        Uint32 frameStart;
        int frameTime = 0;
        Uint8 alpha = 255;

        while (true)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    return;
                }
            }

            frameStart = SDL_GetTicks();

            SDL_RenderClear(_renderer);

            int nextAlpha = alpha - 10 * frameTime;
            log(std::to_string(nextAlpha));
            alpha = nextAlpha < 0 ? 0 : nextAlpha;

            SDL_SetTextureAlphaMod(logoTexture, alpha);

            SDL_Rect offset = {0, 0, 400, 101};
            SDL_Rect dest = {800 / 2 - 400 / 2, 600 / 2 - 100 / 2, 400, 100};
            SDL_RenderCopy(_renderer, logoTexture, &offset, &dest);
            SDL_RenderPresent(_renderer);

            if (alpha == 0)
            {
                break;
            }

            frameTime = SDL_GetTicks() - frameStart;

            if (fps > frameTime)
            {
                SDL_Delay(fps - frameTime);
            }
        }

        log("Intro ended.");
    }
}