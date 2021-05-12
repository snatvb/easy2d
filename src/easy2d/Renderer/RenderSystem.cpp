#include <SDL_image.h>
#include <easy2d/Core/Engine.hpp>
#include <easy2d/Debug/Log.hpp>
#include <easy2d/Renderer/RenderSystem.hpp>
#include <easy2d/Renderer/SpriteComponent.hpp>

namespace easy2d
{
    void RenderSystem::execute()
    {
        auto view = world->registry.view<const SpriteComponent>();
        auto &engine = getEngine();
        auto &renderer = engine.renderer();
        for (auto [entity, sprite] : view.each())
        {
            INFO("Render sprite {}", sprite.assetId);
            auto *texture = engine.loader().getTexture(sprite.assetId);
            if (texture != nullptr)
            {
                SDL_Rect src = {sprite.offset.x, sprite.offset.y, sprite.size.x, sprite.size.y};
                SDL_Rect dst = {0, 0, sprite.size.x, sprite.size.y};

                SDL_RenderCopy(&renderer, texture, &src, &dst);
            }
        }
        SDL_RenderPresent(&renderer);
    }
} // -- easy2d
