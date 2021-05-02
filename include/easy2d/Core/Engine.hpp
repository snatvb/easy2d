#pragma once

class SDL_Window;
class SDL_Renderer;

namespace easy2d
{
    class Engine;

    Engine &getEngine();

    class Engine
    {
    public:
        void initialize();
        void skipIntro();

    private:
        // needs dynamic for fps controll
        int _frameRate = 300;
        int _frameDelay = 1000 / 300;

        SDL_Window *_window = nullptr;
        SDL_Renderer *_renderer = nullptr;
        
        bool _initialized = false;
        bool _needPlayIntro = true;

        Engine() = default;

        void _playIntro();

        friend Engine &getEngine();
    };

} // -- easy2d
