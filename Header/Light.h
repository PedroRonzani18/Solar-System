#ifndef _LIGHT_H
#define _LIGHT_H

// OpenGL
#include <GL/freeglut.h>

// Representa as fontes de luz
class Light
{
    public:
        // Construtor de luz nao alteravel. Usada em planetas que nao emitem luz
        Light(){this->alteravel = 0;}

        // Construtor de luz branca customizável
        Light(int alteravel, double d, double m, double e, GLenum glLightConst);

        // Construtor de luz não alterável por parâmetros, porém tem cor customizada
        Light(double r, double g, double b, GLenum glLightConst);

        double d,e,m,s;
        double r,g,b;

        int hasAtenuation;
        int lightLigada;
        int lighGeralLigada;
        int alteravel;

        // Propriedades das fontes de luz
        float lightAmb[4];    // ??
        float lightDif[4];  // intensidade da difusa do branco
        float lightSpec[4]; // intensidade da especular do branco
        float lightPos[4];  // posição ?? da luz
        float globAmb[4];

        // Propriedades do material da esfera
        float matAmbAndDif[4];   // cor ambiente e difusa: branca (ambiente = cor | )
        float matSpec[4];    // cor especular: branca

        GLenum glLightConst;

        void atualizaPropriedadesLuz();// Função que atualiza os valores dos parâmetros da luz 

        void LightInfo();// Função que escreve as informações das fontes de luz na tela
};



#endif