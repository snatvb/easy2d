#pragma once
#include <easy2d/lib/string.hpp>
#include <easy2d/lib/vec2d.hpp>

namespace easy2d
{
    struct SpriteComponent
    {
        string assetId;
        vec2di size;
        vec2di offset;
    };
} // -- easy2d
