#pragma once
#include <memory>
#include <easy2d/Core/System.hpp>
#include <easy2d/Core/World.hpp>
#include <easy2d/lib/vec.hpp>

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
        Engine &skipIntro();
        Engine &setWorld(std::unique_ptr<World> world);
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

        Engine() = default;

        void _playIntro();

        friend Engine &getEngine();
    };

} // -- easy2d
