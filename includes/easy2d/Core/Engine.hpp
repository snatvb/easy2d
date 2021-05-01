#pragma once

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
    };

} // -- easy2d
