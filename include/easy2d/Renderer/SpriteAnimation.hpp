#pragma once

namespace easy2d
{
    struct SpriteAnimation
    {
        int frameCount;
        float frameTime;
        int currentFrame;
        float restTime;
        float speed = 1.0f;

        SpriteAnimation(int frameCount, float frameTime)
            : frameCount(frameCount), frameTime(frameTime) {}
    };
} // -- easy2d