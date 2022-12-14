#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>   
#include <GL/freeglut.h>

class Texture
{
    public:
        GLuint id;
        const char* path;

        Texture(){}
        Texture(const char* path);
};

#endif