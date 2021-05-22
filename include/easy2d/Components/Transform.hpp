#pragma once
#include <easy2d/lib/vec2d.hpp>

namespace easy2d
{
    struct TransformRaw
    {
        vec2df position;
        vec2df scale = {1.0f, 1.0f};
        float rotation = 0.0f;

        TransformRaw() = default;
        TransformRaw(vec2df position) : position(position) {}
    };

    struct Transform : public TransformRaw
    {
        TransformRaw local;

        Transform(vec2df position)
            : TransformRaw(position), local(TransformRaw({0, 0})) {}
    };
} // -- easy2d