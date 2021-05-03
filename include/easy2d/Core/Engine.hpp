#pragma once
#include <memory>
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

    Engine &getEngine();

    class Engine
    {
    public:
        void initialize();

        Engine &addWorld(std::unique_ptr<World> world);
        Engine &skipIntro();
        Engine &setActiveWorld(const UUID &uuid);
        Engine &run();

    private:
        // needs dynamic for fps controll
        int _frameRate = 300;
        int _frameDelay = 1000 / 300;

        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;

        bool _initialized = false;
        bool _needPlayIntro = true;

        std::unique_ptr<World> _activeWorld;
        map<UUID, std::unique_ptr<World>> _worlds{};

        Engine() = default;

        void _playIntro();

        friend Engine &getEngine();
    };

} // -- easy2d
