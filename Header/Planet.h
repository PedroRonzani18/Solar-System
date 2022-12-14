#ifndef _PLANET_H
#define _PLANET_H

// STL
#include <vector>
#include <memory>

// OpenGL
#include <GL/freeglut.h>

// Bibliotecas proprias
#include "CelestialBody.h"
#include "Moon.h"
#include "Parser.h"

class Planet : public CelestialBody
{
    private:
        // Vector com as luas de cada planeta (pode ou nao ter luas)
        std::vector<std::shared_ptr<Moon>> moons;

    public:
        Planet(){}

        // Construtor d eum planeta a partir de um script.txt
        Planet(const char* planetName, int creationType);

        std::vector<std::shared_ptr<Moon>> getMoons(){return this->moons;}
        void addMooon(std::shared_ptr<Moon> moon){this->moons.push_back(moon);}
};

#endif