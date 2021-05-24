#pragma once
#include <easy2d/Core/System.hpp>
#include <easy2d/lib/vec.hpp>

namespace easy2d
{
    struct SpriteToRender;
    class RenderSystem : public System<RenderSystem>
    {
    public:
        void execute() override;

    private:
        void _preareSprites(vec<SpriteToRender> layersToRender[]);
        void _updateAnimation();
    };
} // -- easy2d
