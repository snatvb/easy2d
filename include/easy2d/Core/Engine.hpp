#pragma once

class SDL_Window;

namespace easy2d
{
    class Engine;

    Engine &getEngine();

    class Engine
    {
    public:
        void initialize();

    private:
        Engine() = default;
        friend Engine &getEngine();
        SDL_Window *_window;
    };

} // -- easy2d
