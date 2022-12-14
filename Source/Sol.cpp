#include "../Header/Sol.h"
#include "../Header/Parser.h"
#include "../Header/drawings.h"

// Construtor do Sol de acordo com parâmetros passados no script
Sol::Sol(const char* planetName)
{
    Parser aux = Parser::parseSun(planetName);

    this->d = aux.d;
    this->m = aux.m;
    this->e = aux.e;

    const char* arquivo = aux.texture;

    this->texture = loadTexture(arquivo);
    this->dependsOnLight = aux.dependsOnLight;
    this->coreRadius = aux.coreRadius/113.0;
    this->rotationRadius = 1.7 * aux.rotationRadius;
    this->translationPeriod = aux.translationPeriod;
    this->rotationPeriod = aux.rotationPeriod;
    this->midPoint.x = 0;
    this->midPoint.y = 0;
    this->midPoint.z = rotationRadius;

    double translationSpeed, angularSpeed;

    if(translationPeriod != 0) translationSpeed = 306.0 / this->translationPeriod;
    else                       translationSpeed = 0;

    if(rotationPeriod != 0) angularSpeed = 30.0/ this->rotationPeriod;
    else                    angularSpeed = 0;

    this->translationAngularSpeed = translationSpeed;
    this->rotationAngularSpeed = angularSpeed;

    this->light = new Light(1, d, m, e, GL_LIGHT0);  
    this->hasLight = 1;

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
