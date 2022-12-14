#ifndef _PARSER_H
#define _PARSER_H

// STL
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

// OpenGL
#include <GL/freeglut.h>

class Parser
{
    public:
        const char* texture; // caminho da textura
        const char* modelo; // caminho do modelo para arquivos .obj
        float size; // tamanho do modelo para quesitos de desenho

        // Variaiveis que armazenam informacoes especificas de cada classe filha da Object
        float dependsOnLight;
        float numberOfMooons;
        float coreRadius;
        float rotationRadius;
        float rotationMultiplier;
        float translationPeriod;
        float rotationPeriod;
        GLenum glLightConst;
        float matAmbient[4];
        float matDifuse[4];
        float matEspec[4];
        float matShininess;
        float alteravel,d,m,e;

        // Funcoes que leem arquivos script.txt e retornam um parser 
        // carregado com informacoes especificas para cada tipo de construtor
        static Parser parsePlanet(const char* fileName, int creationType);
        static Parser parseSun(const char* fileName);
        static Parser parseMoon(const char* fileName);
        static std::vector<std::pair<const char*,int>> parseSolarSystem(const char* fileName);
        static Parser parseModel(const char* fileName);
};

#endif