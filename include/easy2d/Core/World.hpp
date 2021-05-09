#pragma once
#include <memory>
#include <entt/entt.hpp>
#include <easy2d/Debug/Log.hpp>
#include <easy2d/lib/vec.hpp>
#include <easy2d/Core/UUID.hpp>

namespace easy2d
{
    class BaseSystem;
    class Engine;

    class World
    {
    public:
        entt::registry registry;

        World() : _id(UUID::generate()) {}

        const UUID &id() const { return _id; }

        template <typename T, typename... TArgs>
        World &registerSystem(TArgs &&...args)
        {
            T *system = new T(std::forward<TArgs>(args)...);
            system->world = this;
            auto ptr = std::unique_ptr<BaseSystem>(system);
            _systems.emplace_back(std::move(ptr));
            return *this;
        }

    private:
        const UUID _id;
        vec<std::unique_ptr<BaseSystem>> _systems{};

        void _initialize();
        void _update();

        friend class Engine;
    };
} // -- easy2d
