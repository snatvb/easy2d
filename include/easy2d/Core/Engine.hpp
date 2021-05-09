#pragma once
#include <memory>
#include <easy2d/Debug/Log.hpp>
#include <easy2d/Core/AssetsLoader.hpp>
#include <easy2d/Core/System.hpp>
#include <easy2d/Core/World.hpp>
#include <easy2d/Core/UUID.hpp>
#include <easy2d/lib/map.hpp>

class SDL_Window;
class SDL_Renderer;

namespace easy2d
{
    class Engine;
    class World;
    class AssetsLoader;

    Engine &getEngine();

    class Engine
    {
    public:
        // no copy
        Engine(const Engine &) = delete;
        Engine(Engine &&) = delete;
        Engine &operator=(const Engine &) = delete;
        Engine &operator=(Engine &&) = delete;

        void initialize();

        Engine &addWorld(std::unique_ptr<World> world);
        Engine &skipIntro();
        Engine &setActiveWorld(const UUID &uuid);
        Engine &run();

        SDL_Window *window() { return _window; }
        SDL_Renderer *renderer() { return _renderer; }
        AssetsLoader &loader() { return _loader; }

    private:
        // needs dynamic for fps controll
        int _frameRate = 300;
        int _frameDelay = 1000 / 300;

        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;
        AssetsLoader _loader;

        bool _initialized = false;
        bool _needPlayIntro = true;

        World *_activeWorld;
        map<UUID, std::unique_ptr<World>> _worlds{};

        explicit Engine() = default;

        void _playIntro();

        friend Engine &getEngine();
    };

} // -- easy2d
