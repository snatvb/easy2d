#include <SDL_image.h>
#include <easy2d/Core/Engine.hpp>
#include <easy2d/Debug/Log.hpp>
#include <easy2d/Components/Transform.hpp>
#include <easy2d/Components/Hierarchy.hpp>
#include <easy2d/Renderer/RenderSystem.hpp>
#include <easy2d/Renderer/SpriteAnimation.hpp>
#include <easy2d/Renderer/SpriteComponent.hpp>
#include <easy2d/lib/assert.hpp>

namespace easy2d
{
    struct SpriteToRender
    {
        SDL_Texture *texture;
        SDL_Rect srcrect;
        SDL_Rect dstrect;
        double angle;
        SDL_Point *center;
        SDL_RendererFlip flip;
    };

    void RenderSystem::execute()
    {
        _updateAnimation();
        auto &engine = getEngine();
        auto &renderer = engine.renderer();
        const auto layersCount = engine.layersCount();
        vec<SpriteToRender> layersToRender[layersCount];
        _preareSprites(layersToRender);

        for (size_t i = 0; i < layersCount; i++)
        {
            for (auto &spriteToRender : layersToRender[i])
            {
                SDL_RenderCopyEx(
                    &renderer, spriteToRender.texture,
                    &spriteToRender.srcrect,
                    &spriteToRender.dstrect,
                    spriteToRender.angle,
                    spriteToRender.center, spriteToRender.flip);
            }
        }
    }

    void RenderSystem::_preareSprites(vec<SpriteToRender> layersToRender[])
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

            SpriteToRender spriteToRender{
                texture,
                src,
                dst,
                transform.rotation + transform.local.rotation,
                NULL,
                SDL_FLIP_NONE};

            layersToRender[sprite.layer].emplace_back(spriteToRender);
        }
    }

    void RenderSystem::_updateAnimation()
    {

        auto view = world->registry.view<SpriteComponent, SpriteAnimation>();
        auto &engine = getEngine();
        INFO(std::to_string(engine.deltaTime()));
        auto &renderer = engine.renderer();
        for (auto [entity, sprite, animation] : view.each())
        {
            if (!animation.play)
            {
                continue;
            }

            animation.cooldown -= engine.deltaTime();
            if (animation.cooldown > 0)
            {
                continue;
            }

            animation.cooldown = animation.frameTime;

            // TODO: Add handle types of animation
            animation.currentFrame += 1;
            if (animation.currentFrame > animation.frameCount.area() - 1)
            {
                animation.currentFrame = 0;
            }

            const int xFrame = animation.currentFrame % animation.frameCount.x;
            const int yFrame = animation.currentFrame / animation.frameCount.x;

            sprite.offset.set(xFrame * sprite.size.x, yFrame * sprite.size.y);
        }
    }
} // -- easy2d
