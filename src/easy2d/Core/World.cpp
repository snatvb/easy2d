#include <easy2d/Core/World.hpp>
#include <easy2d/Core/System.hpp>

namespace easy2d
{
    void World::_update()
    {
        for (auto const &system : _systems)
        {
            system->execute();
        }
    };

    void World::_initialize()
    {
        for (auto &system : _systems)
        {
            system->initialize();
        }
    };
} // -- easy2d
