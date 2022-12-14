#ifndef _CELESTIALBODY_H
#define _CELESTIALBODY_H

// OpenGL
#include <GL/freeglut.h>

// Biublioteca propria
#include "Object.h"

class CelestialBody : public Object
{
    protected:
        double coreRadius; // raio do planeta

    public:
        CelestialBody(){}

        double getCoreRadius(){return this->coreRadius;}
        void setCoreRadius(double coreRadius){this->coreRadius = coreRadius;}
};

#endif