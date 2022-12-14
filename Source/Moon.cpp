// Bibliotecas proprias
#include "../Header/Moon.h"
#include "../Header/drawings.h"
#include "../Header/globalParameters.h"

Moon::Moon(const char* planetName, double coreRadius, double angle)
{
    Parser aux = Parser::parseMoon(planetName);

    this->angle = angle;
    this->texture = texturesId[0];
    this->coreRadius = aux.coreRadius;
    this->rotationRadius = aux.coreRadius + aux.rotationMultiplier * coreRadius;
    this->translationAngularSpeed = aux.translationPeriod;
    this->rotationAngularSpeed = aux.rotationPeriod;
    this->light = new Light();
    this->hasLight = 0;

    this->material = new Material();

    for(int i=0; i<4; i++)
    {
        this->material->matAmbient[i] = aux.matAmbient[i];
        this->material->matDifuse[i] = aux.matDifuse[i];
        this->material->matEspec[i] = aux.matEspec[i];
    }
    this->material->matShininess = aux.matShininess;  

    GLuint auxList = glGenLists(1);

    glNewList(auxList, GL_COMPILE);
        drawSolidSphere(this->coreRadius,200,200);
    glEndList();

    displayListId = auxList; 
}