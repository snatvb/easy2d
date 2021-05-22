#pragma once
#include <entt/entt.hpp>

namespace easy2d
{
    struct Hierarchy
    {
        entt::entity parent;
        bool autoRemove = true;

        Hierarchy(entt::entity parent) : parent(parent) {}
    };
}
