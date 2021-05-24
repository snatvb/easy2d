#pragma once

#include <easy2d/lib/vec2d.hpp>

namespace easy2d
{
    struct SpriteAnimation
    {
        enum Direction : int8_t
        {
            FORWARD = 1,
            BACKWARD = -1,
        };
        enum Repeat : int8_t
        {
            NO_REPEAT,
            BACKFORTH,
            LOOP,
        };

        vec2di offset = {0, 0};
        vec2di frameCount;
        float frameTime;
        int currentFrame;
        float speed = 1.0f;
        Direction direction = FORWARD;
        Repeat repeat = LOOP;
        float cooldown = 0;
        bool play = true;

        SpriteAnimation(vec2di frameCount, float frameTime)
            : frameCount(frameCount), frameTime(frameTime) {}
    };

} // -- easy2d