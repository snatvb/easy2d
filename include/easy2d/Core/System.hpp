#pragma once

namespace easy2d
{
    class World;

    class BaseSystem
    {
    public:
        BaseSystem() = default;
        virtual void initialize(){};
        virtual void execute() = 0;

    private:
        World *_world = nullptr;

        friend class World;
    };

    template <typename Impl>
    class System : public BaseSystem
    {
    public:
        System() = default;
    };
} // -- easy2d