#pragma once
#include <easy2d/lib/map.hpp>
#include <easy2d/lib/string.hpp>

class SDL_Texture;
class SDL_Surface;

namespace easy2d
{

    class AssetsLoader
    {
    public:
        AssetsLoader() = default;
        ~AssetsLoader();

        SDL_Texture *loadTexture(string id, const char *path);
        SDL_Texture *getTexture(string id) { return _textures[id]; }

    private:
        map<string, SDL_Surface *> _surfaces{};
        map<string, SDL_Texture *> _textures{};
    };
} // -- easy2d
