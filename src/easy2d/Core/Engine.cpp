#include <string>
#include <filesystem>
#include <SDL.h>
#include <SDL_image.h>
#include <entt/entt.hpp>
#include <easy2d/Core/Engine.hpp>
#include <easy2d/Debug/Log.hpp>
#include <easy2d/Core/World.hpp>
#include <easy2d/Core/System.hpp>
#include <easy2d/Core/AssetsLoader.hpp>

namespace fs = std::filesystem;

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
        INFO("Engine initialization...");
        DEBUG("Path of runner: " + fs::current_path().string());

        if (_initialized)
        {
            CRIT("Engine Easy2D already initialized!");
            return;
        }

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            CRIT("SDL initialize has error...");
            return;
        }
        DEBUG("SDL initialied");

        DEBUG("Creating window...");
        _window = SDL_CreateWindow("easy2d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
        if (!_window)
        {
            CRIT("Window creating has error...");
            return;
        }
        DEBUG("Window created.");

        DEBUG("Create renderer...");
        _renderer = SDL_CreateRenderer(_window, -1, 0);
        if (!_renderer)
        {
            CRIT("Renderer creating has error...");
            return;
        }
        DEBUG("Renderer created.");

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

        DEBUG("Active World initializing...");
        _activeWorld->_initialize();

        DEBUG("Initialization success.");
        DEBUG("Create game loop.");

        Uint32 frameStart = SDL_GetTicks();
        int frameTime = 0;
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);

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
            _activeWorld->_update();

            SDL_RenderPresent(_renderer);

            frameTime = SDL_GetTicks() - frameStart;

            if (_frameDelay > frameTime)
            {
                SDL_Delay(_frameDelay - frameTime);
            }
        }
    }

    // ----------------------------------------------------------------------------------------
    Engine &Engine::addWorld(std::unique_ptr<World> world)
    {
        _worlds.emplace(world->id(), std::move(world));
        return *this;
    }

    // ----------------------------------------------------------------------------------------
    Engine &Engine::skipIntro()
    {
        _needPlayIntro = false;
        return *this;
    }

    // ----------------------------------------------------------------------------------------
    Engine &Engine::setActiveWorld(const UUID &uuid)
    {
        DEBUG("Set World " + uuid.toString() + " as active.");
        if (_activeWorld != nullptr && _activeWorld->id() == uuid)
        {
            WARN("World " + uuid.toString() + " already is active");
            return *this;
        }

        if (_worlds.find(uuid) != _worlds.end())
        {
            _activeWorld = _worlds[uuid].get();
        }
        else
        {
            ERR("Can't find world " + uuid.toString() + " to install as active.");
        }

        return *this;
    };

    // ----------------------------------------------------------------------------------------
    void Engine::_playIntro()
    {

        if (!_needPlayIntro)
        {
            return;
        }

        const int fps = 60;

        _loader.loadTexture("logo", "easy2d/resources/logo.png");
        SDL_Texture *logoTexture = _loader.getTexture("logo");
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

        DEBUG("Intro ended.");
    }
}