#pragma once
#include <easy2d/lib/vec2d.hpp>

namespace easy2d
{
    struct Transform
    {
        vec2df position;
        vec2df scale = {1.0f, 1.0f};
        float rotation = 0.0f;
        bool isStatic = false;

        Transform() = default;
        Transform(vec2df position) : position(position) {}
    };
} // -- easy2d