#pragma once
#include <easy2d/Core/System.hpp>

namespace easy2d
{
    class RenderSystem : public System<RenderSystem>
    {
    public:
        void execute() override;
    };
} // -- easy2d
