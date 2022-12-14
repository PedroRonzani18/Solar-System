// Bibliotecas proprias
#include "../Header/Space.h"
#include "../Header/drawings.h"
#include "../Header/globalParameters.h"
#include "../Header/Vertex.h"

// Conversores entre graus e radianos
#define radGr(radianos) (radianos * (180.0 / M_PI))
#define grRad(graus) ((graus * M_PI) / 180.0)

Space::Space()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    createTextures();

    musicManager = std::make_shared<MusicManager>();
    musicManager->configureMusic();

    initializePlanets();
    initializeModels();

    camera = std::make_shared<Camera>();
    camera->setBorder(loadTexture("Assets/imagens/cabine.png"));
}

void Space::initializeModels()
{
    this->models.push_back(std::make_shared<Model>("Assets/scripts/satelite.txt"));
}

void Space::initializePlanets() 
{              
    sol = std::make_shared<Sol>("Assets/scripts/sol.txt"); 
    estrelas = std::make_shared<Planet>("Assets/scripts/estrelas.txt", 0); 

    for(auto planet: Parser::parseSolarSystem("Assets/scripts/solarSystem.txt"))
        planets.push_back(std::make_shared<Planet>(planet.first,planet.second));
}

void Space::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    sol->getLight()->LightInfo();
    camera->setupCamera();
    atualizaPropriedadesLuz();

    drawPlanets();
    drawModels();
    drawSaturnRing();
    drawCamera(camera);

    glutSwapBuffers();
}

void Space::drawModels()
{
    for(std::shared_ptr<Model> model: models)
    {        
        glPushMatrix();
            glRotated(-90,1,0,0); // rotaciona para frente para dar mais visibilidade na rotação
            glRotatef(radGr(planets[0]->getAngle()),0,0,1); // rotaciona ao redor do planeta
            glTranslated(-planets[0]->getRotationRadius(),0, 0); // determina o raio da rotação (e indiretamente o centro de rotação)
            drawModel(model,planets[0]->getCoreRadius());
        glPopMatrix();
    }
}

void Space::drawPlanets()
{
    glPushMatrix();
        glRotated(-90,1,0,0); // rotaciona para frente para dar mais visibilidade na rotação
        drawPlanet(estrelas);
    glPopMatrix();

    glPushMatrix();
        glRotated(-90,1,0,0); // rotaciona para frente para dar mais visibilidade na rotação

        glPushMatrix();
            drawSun(sol);
        glPopMatrix();

        for(std::shared_ptr<Planet> planet : planets)
        {
            glPushMatrix();
                planet->setAngle(*tempo * planet->getTranslationAngularSpeed());
                planet->setMidPoint(-planet->getRotationRadius() * cos(planet->getAngle()),
                                    0,
                                     planet->getRotationRadius() * sin(planet->getAngle()));
                drawPlanet(planet);
            glPopMatrix();

            for(std::shared_ptr<Moon> moon: planet->getMoons())
            {
                glPushMatrix();
                    glRotatef(radGr(planet->getAngle()),0,0,1); // rotaciona ao redor do planeta
                    glTranslated(-planet->getRotationRadius(),0, 0); // determina o raio da rotação (e indiretamente o centro de rotação)
                    drawMoon(moon);
                glPopMatrix();
            }
        }
    glPopMatrix();
}

void Space::drawSaturnRing()
{
    std::shared_ptr<Planet> saturn = planets[2];
    glm::vec3 aux = saturn->getMidPoint();

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texturesId[1]);
            glTranslatef(aux.x,aux.y,aux.z);
            glRotated(-90,1,0,0); // rotaciona para frente para dar mais visibilidade na rotação
            drawCylinder(1.2 * saturn->getCoreRadius(), 1.2 * saturn->getCoreRadius(), 0.3, 400, 400);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

double Space::distanceBetweenPlanets(glm::vec3 a, glm::vec3 b)
{
    return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2) + pow(a.z - b.z,2));
}

void Space::cameraMoving()
{
    // Movimenta a câmera
    camera->move();

    cameraColision();

    // Chama a função que determina o volume da musica
    musicManager->marsMusic(distanceBetweenPlanets(camera->getMidPoint(),planets[1]->getMidPoint()));
}

void Space::cameraColision()
{
    if(distanceBetweenPlanets(sol->getMidPoint(),camera->getMidPoint()) <= 3 + sol->getCoreRadius())
        camera->backPosition();

    if(distanceBetweenPlanets(estrelas->getMidPoint(),camera->getMidPoint()) >= estrelas->getCoreRadius() - 10)
        camera->backPosition();

    for(std::shared_ptr<Planet> planet: planets)
    {
        if(distanceBetweenPlanets(planet->getMidPoint(),camera->getMidPoint()) < 3 + planet->getCoreRadius())
            camera->backPosition();

        for(std::shared_ptr<Moon> moon: planet->getMoons())
        {
            if(distanceBetweenPlanets(moon->getMidPoint(),camera->getMidPoint()) < 2 + moon->getCoreRadius())
                camera->backPosition();
        }
    }
}

void Space::atualizaPropriedadesLuz()
{
    sol->getLight()->atualizaPropriedadesLuz();
    for(std::shared_ptr<Planet> planet: planets)
        planet->getLight()->atualizaPropriedadesLuz();
}

void Space::onOffSun()
{
    // (Des)liga as fontes de luz da Terra, Marte, Saturno
    if(buttons[0] && keys->l)
    {
        buttons[0] = 0;

        if(sol->getLight()->lighGeralLigada) sol->getLight()->lighGeralLigada = 0;
        else                                 sol->getLight()->lighGeralLigada = 1;

        
        if(sol->getLight()->lighGeralLigada) 
        {
            glEnable(GL_LIGHT1);
            glEnable(GL_LIGHT2);
            glEnable(GL_LIGHT3);
        }
        else                                
        {
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
            glDisable(GL_LIGHT3);
        }   
    }

    // (Des)liga as fontes de luz da Terra, Marte, Saturno
    if(buttons[1] && keys->k)
    {       
        buttons[1] = 0;

        if(sol->getLight()->lightLigada) sol->getLight()->lightLigada = 0;
        else                                sol->getLight()->lightLigada = 1;

        if(sol->getLight()->lightLigada) glEnable(GL_LIGHT0);
        else                                glDisable(GL_LIGHT0);
    }
}