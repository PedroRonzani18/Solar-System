#include "../Header/Planet.h"
#include "../Header/drawings.h"
#include "../Header/globalParameters.h"

// Construtor de um palneta de acordo com parâmetros passados no script
Planet::Planet(const char* planetName, int creationType)
{
    Parser aux = Parser::parsePlanet(planetName,creationType);

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

    int numberOfMoons = aux.numberOfMooons;
    switch(numberOfMoons)
    {
        case 3:
            addMooon(std::make_shared<Moon>("Assets/scripts/lua.txt",this->coreRadius,240));
        case 2:
            addMooon(std::make_shared<Moon>("Assets/scripts/lua.txt",this->coreRadius,360/numberOfMoons));
        case 1:
            addMooon(std::make_shared<Moon>("Assets/scripts/lua.txt",this->coreRadius,0));
            break;
    }  

    int luz = aux.glLightConst;

    switch (creationType)
    {
        case 0:
            this->light = new Light(); 
            this->hasLight = 0;
            break;


        case 1:
            switch(luz)
            {
                case 1:
                    this->glLightConst = GL_LIGHT1;
                    break;
                case 2:
                    this->glLightConst = GL_LIGHT2;
                    break;
                case 3:
                    this->glLightConst = GL_LIGHT3;
                    break;
            }
            this->light = new Light(1, 1, 1, glLightConst);  
            this->hasLight = 1;
            break;
    }

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
