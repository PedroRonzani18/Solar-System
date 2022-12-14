#ifndef _MATERIAL_H
#define _MATERIAL_H

// STL
#include <vector>

class Material
{
    public:
        float matAmbient[4];
        float matDifuse[4];
        float matEspec[4];
        float matShininess;

        Material(){}

        // Construtor de um material com parâmetros específicos
        Material(float* ambient, float* difuse, float* espec, float shine);
};

#endif