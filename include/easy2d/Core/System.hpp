#pragma once
#include "easy2d/Core/World.hpp"

namespace easy2d
{
    class BaseSystem
    {
    public:
        World *world = nullptr;

        BaseSystem() = default;
        virtual ~BaseSystem() = default;
        virtual void initialize() {}
        virtual void execute() = 0;
    };

    template <typename Impl>
    class System : public BaseSystem
    {
    };
} // -- easy2d