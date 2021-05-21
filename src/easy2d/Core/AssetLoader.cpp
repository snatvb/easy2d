#include <SDL.h>
#include <SDL_image.h>
#include <easy2d/Core/AssetsLoader.hpp>
#include <easy2d/Core/Engine.hpp>
#include <easy2d/Debug/Log.hpp>

namespace easy2d
{

    AssetsLoader::~AssetsLoader()
    {
        for (auto &[_, surface] : _surfaces)
        {
            SDL_FreeSurface(surface);
            delete surface;
        }

        for (auto &[_, texture] : _textures)
        {
            delete texture;
        }
    };

    bool AssetsLoader::loadTexture(string id, const char *path)
    {
        DEBUG("Loading {}: {}", id, path);
        SDL_Surface *surface = IMG_Load(path);
        if (!surface)
        {
            WARN("Error loaded file {} {}", id, path);
            auto err = SDL_GetError();
            WARN(err);
            return false;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(&getEngine().renderer(), surface);
        if (!texture)
        {
            WARN("Error create texture {} {}", id, path);
            auto err = SDL_GetError();
            WARN(err);
            return false;
        }
        _surfaces.emplace(id, surface);
        _textures.emplace(id, texture);
        return texture != nullptr;
    }

} // -- easy2d
