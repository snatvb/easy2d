#include <SDL_image.h>
#include <easy2d/Core/Engine.hpp>
#include <easy2d/Debug/Log.hpp>
#include <easy2d/Components/Transform.hpp>
#include <easy2d/Components/Hierarchy.hpp>
#include <easy2d/Renderer/RenderSystem.hpp>
#include <easy2d/Renderer/SpriteComponent.hpp>
#include <easy2d/lib/assert.hpp>

namespace easy2d
{
    void RenderSystem::execute()
    {
        auto view = world->registry.view<const SpriteComponent, const Transform>();
        auto &engine = getEngine();
        auto &renderer = engine.renderer();
        for (auto [entity, sprite, transform] : view.each())
        {
            auto *texture = engine.loader().getTexture(sprite.assetId);
            ASSERT(texture != nullptr, "Error get texture: " << sprite.assetId);
            SDL_Rect src = {sprite.offset.x, sprite.offset.y, sprite.size.x, sprite.size.y};
            SDL_Rect dst = {
                static_cast<int>(transform.position.x + transform.local.position.x),
                static_cast<int>(transform.position.y + transform.local.position.y),
                static_cast<int>(sprite.size.x * (transform.scale.x * transform.local.scale.x)),
                static_cast<int>(sprite.size.y * (transform.scale.y * transform.local.scale.y))};

            SDL_RenderCopyEx(&renderer, texture, &src, &dst, transform.rotation + transform.local.rotation, NULL, SDL_FLIP_NONE);
        }
    }
} // -- easy2d
