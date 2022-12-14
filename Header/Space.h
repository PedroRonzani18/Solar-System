#ifndef _SPACE_H
#define _SPACE_H

// Bibliotecas proprias
#include "Planet.h"
#include "Sol.h"
#include "Light.h"
#include "MusicManager.h"
#include "Camera.h"
#include "Model.h"

// STL
#include <vector>
#include <memory>

// OpenGL
#include <glm/glm.hpp>
#include <memory>
#include <cmath>
#include <stdio.h>

// SOIL
#include <SOIL/SOIL.h>

// Classe que gerencia todos os Objetos presentes na tela
class Space
{
    private:
        std::shared_ptr<Sol> sol; // ponteiro do Sol
        std::shared_ptr<Planet> estrelas; // ponteiro das estrelas
        std::vector<std::shared_ptr<Planet>> planets; // vector de ponteiros de planetas
        std::shared_ptr<MusicManager> musicManager; // ponteiro do gerenciador de musicas
        std::shared_ptr<Camera> camera; // ponteiro da camera
        std::vector<std::shared_ptr<Model>> models; // vector de ponteiros de modelos .obj

        // Instancia planetas e modelos
        void initializePlanets();// Função que adiciona os shared_ptr<Planet> ao vecot de planetas de acodo com os construtores baseados nos scripts
        void initializeModels();

        // Função que gerencia a colisão entre camera e todos os planetas, incluindo o universo
        void cameraColision();

        // Desenha todos os objetos presenhtes na tela
        void drawModels();
        void drawSaturnRing(); // Função que desenha o anel de saturno
        void drawPlanets(); // Função que desenhda todos os planetas

    public:
        Space();    

        std::shared_ptr<Sol> getSol(){return this->sol;}
        std::shared_ptr<Planet> getEstrelas(){return this->estrelas;}
        std::shared_ptr<Planet> getPlanet(int i){return planets[i];}
        std::shared_ptr<MusicManager> getMusicManager(){return this->musicManager;}
        std::shared_ptr<Camera> getCamera(){return this->camera;}

        static double distanceBetweenPlanets(glm::vec3 a, glm::vec3 b);// Função que calcula a distância entre dois pontos

        void display();//  Função que gerencia desenhos na tela
        void atualizaPropriedadesLuz();// Função que atualiza as propriedades da luz alterando os valores de glLight de cada fonte de luz
        void onOffSun(); // Função que gerencia o (des)ligamento das fontes de luz dfe acordo com pressionamento de teclas
        void cameraMoving(); // Função que chama funções relacionadas à camera
};

#endif