#pragma once

namespace easy2d
{
    class World;

    class BaseSystem
    {
    public:
        World *world = nullptr;

        BaseSystem() = default;
        virtual void initialize(){};
        virtual void execute() = 0;
    };

    template <typename Impl>
    class System : public BaseSystem
    {
    public:
        System() = default;
    };
} // -- easy2d