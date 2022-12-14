#ifndef _MOON_H
#define _MOON_H

// Biblioteca propria
#include "CelestialBody.h"

class Moon : public CelestialBody
{
    public:
        Moon(){}

        // Construtor de uma Lua de acordo com parâmetros passados no script
        Moon(const char* planetName, double coreRadius, double angle);
};

#endif