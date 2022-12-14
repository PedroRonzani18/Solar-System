#ifndef _SOL_H
#define _SOL_H

// OpenGL
#include <GL/freeglut.h>

// Biblioteca propria
#include "CelestialBody.h"

class Sol : public CelestialBody
{
    public:
        double d,m,e;

        Sol(){}
        // Constroi um Sol a partir de um script.txt
        Sol(const char* planetName);
};

#endif