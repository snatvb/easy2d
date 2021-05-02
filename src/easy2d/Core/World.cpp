#pragma once
#include <easy2d/Core/World.hpp>
#include <easy2d/Core/System.hpp>

namespace easy2d
{
    void World::update()
    {
        for (auto &system : _systems)
        {
            system->execute();
        }
    };
} // -- easy2d
