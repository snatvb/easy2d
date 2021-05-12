#pragma once
#include <easy2d/lib/string.hpp>
#include <easy2d/lib/vec2d.hpp>

namespace easy2d
{
    struct SpriteComponent
    {
        string assetId;
        vec2di offset;
        vec2di size;
    };

    struct ASDComponent
    {
        float x;
    };
} // -- easy2d
