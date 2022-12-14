#include "../Header/Texture.h"
#include "../Header/drawings.h"

Texture::Texture(const char* path)
{
    this->id = loadTexture(path);
    this->path = path;
}
