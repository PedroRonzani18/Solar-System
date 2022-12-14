// Biblioteca propria
#include "../Header/Material.h"

Material::Material(float* ambient, float* difuse, float* espec, float shine)
{
    for(int i=0; i<4; i++)
    {
        this->matAmbient[i] = ambient[i];
        this->matDifuse[i] = difuse[i];
        this->matEspec[i] = espec[i];
    }

    this->matShininess = shine;
}