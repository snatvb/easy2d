#pragma once
#include <memory>
#include <entt/entt.hpp>
#include <easy2d/lib/vec.hpp>

namespace easy2d
{
    class BaseSystem;
    class Engine;

    class World
    {
    public:
        entt::registry registry;

        template <typename T, typename... TArgs>
        World &registerSystem(TArgs &&...args)
        {
            T *system = new T(std::forward<TArgs>(args)...);
            system->_world = this;
            auto ptr = std::unique_ptr<BaseSystem>(system);
            _systems.emplace_back(std::move(ptr));
            return *this;
        }

    private:
        vec<std::unique_ptr<BaseSystem>> _systems{};

        void update();

        friend class Engine;
    };
} // -- easy2d
