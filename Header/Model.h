#ifndef _MODEL_H
#define _MODEL_H

// STL
#include <vector>
#include <string>

// OpenGL
#include <GL/freeglut.h>

// Bibliotecas proprias
#include "Vertex.h"
#include "Texture.h"
#include "Object.h"
#include "Parser.h"

class Model : public Object
{
    private:
        // Lê um arquivo .obj e retorna um vector com as caracteristicas de cada vertice
        std::vector<Vertex> loadObject(const char* fileName);

    public:
        std::vector<Vertex> vertices;
        Texture texture;
        const char* modelo;
        float size;

        // Cria um modelo a partir de um script.txt
        Model(const char* fileName);
};

#endif