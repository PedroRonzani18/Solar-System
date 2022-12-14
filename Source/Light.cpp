// Bibliotecas proprias
#include "../Header/Light.h"
#include "../Header/globalParameters.h"

Light::Light(double r, double g, double b, GLenum glLightConst)
{
    this->alteravel = 0;

    this->glLightConst = glLightConst;
    this->r = r;
    this->g = g;
    this->b = b;
    
    lightLigada = 1;
    lighGeralLigada = 1;

    for(int i=0; i<3 ; i++)
    {
        lightAmb[i] = 0;
        lightSpec[i] = 0;
        lightPos[i] = 0;
        globAmb[i] = 0;
        matAmbAndDif[i] = 1;
        matSpec[i] = 1;
    }

    lightDif[0] = r;
    lightDif[1] = g;
    lightDif[2] = b;
    lightDif[3] = 1;

    lightAmb[3] = 1;
    lightSpec[3] = 1;
    lightPos[3] = 1;
    globAmb[3] = 1;
    matAmbAndDif[3] = 1;
    matSpec[3] = 1; 

    hasAtenuation = 1;

    glEnable(glLightConst);
}

Light::Light(int alteravel, double d, double m, double e, GLenum glLightConst)
{
    this->d = d;
    this->m = m;
    this->e = e;
    this->glLightConst = glLightConst;
    
    lightLigada = 1;
    lighGeralLigada = 1;

    for(int i=0; i<3 ; i++)
    {
        lightAmb[i] = 0;
        lightDif[i] = d;
        lightSpec[i] = e;
        lightPos[i] = 0;
        globAmb[i] = m;
        matAmbAndDif[i] = 1;
        matSpec[i] = 1;
    }

    lightAmb[3] = 1;
    lightDif[3] = 1;
    lightSpec[3] = 1;
    lightPos[3] = 1;
    globAmb[3] = 1;
    matAmbAndDif[3] = 1;
    matSpec[3] = 1;    

    this->alteravel = 1;
    hasAtenuation = 0;

    glEnable(glLightConst);
}

void Light::atualizaPropriedadesLuz()
{
    for(int i=0; i<4; i++)
        globAmb[i] = 0;

    if(alteravel)
    {
        if(0 < m) m += -keys->x * 0.05;
        if(m < 1) m +=  keys->z * 0.05;

        if(0 < d) d += -keys->v * 0.05;
        if(d < 1) d +=  keys->c * 0.05;

        if(0 < e) e += -keys->n * 0.05;
        if(e < 1) e +=  keys->b * 0.05;

        for(int i=0; i<3; i++) 
        {
            lightDif[i] = d;
            lightSpec[i] = e;
            lightAmb[i] = m;
        }
    }
    
    else
    {
        for(int i=0; i<3; i++)
        {
            lightSpec[i] = 0;
            lightAmb[i] = 0;
        }
        lightDif[0] = r;
        lightDif[1] = g;
        lightDif[2] = b; 
        lightDif[3] = 1;
    }

    // Atualiza as propriedades da fonte de luz glLightConst
    glLightfv(glLightConst, GL_AMBIENT, lightAmb); // rgb da luz ambiente
    glLightfv(glLightConst, GL_DIFFUSE, lightDif);
    glLightfv(glLightConst, GL_SPECULAR, lightSpec);    
    glLightfv(glLightConst, GL_POSITION, lightPos);

    if(hasAtenuation)
        glLightf(glLightConst, GL_QUADRATIC_ATTENUATION, 0.8);     

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Luz ambiente global
}

// Função que escreve um conjunto de caracteres
void writeOnScreen(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void Light::LightInfo()
{
    glDisable(GL_LIGHTING);

    char* dados = (char*)malloc(100 * sizeof(char));

    glRasterPos3f(-0.85 * razaoAspecto, 0.8, -2.0);
    sprintf(dados, "    FONTE DE LUZ DO SOL");
    writeOnScreen(GLUT_BITMAP_8_BY_13, dados);

    glRasterPos3f(-0.85 * razaoAspecto, 0.74, -2.0);
    sprintf(dados, "* Componente Ambiente (Z/X) : %0.2f", m);
    writeOnScreen(GLUT_BITMAP_8_BY_13, dados);

    glRasterPos3f(-0.85 * razaoAspecto, 0.68, -2.0);
    sprintf(dados, "* Componente Difusa (C/V) : %0.2f", d);
    writeOnScreen(GLUT_BITMAP_8_BY_13, dados);

    glRasterPos3f(-0.85 * razaoAspecto, 0.62, -2.0);
    sprintf(dados, "* Componente Especular (B/N) : %0.2f", e);
    writeOnScreen(GLUT_BITMAP_8_BY_13, dados);

    glRasterPos3f(-0.85 * razaoAspecto, 0.56, -2.0);
    sprintf(dados, "* Estado da Luz solar (K): %s", lightLigada ? "Ligada" : "Desligada");
    writeOnScreen(GLUT_BITMAP_8_BY_13, dados);

    glRasterPos3f(-0.85 * razaoAspecto, 0.44, -2.0);
    sprintf(dados, "    FONTE DE LUZ DOS PLANETAS");
    writeOnScreen(GLUT_BITMAP_8_BY_13, dados);

    glRasterPos3f(-0.85 * razaoAspecto, 0.38, -2.0);
    sprintf(dados, "* Luzes da Terra, Marte, Saturno (L) : %s", lighGeralLigada ? "Ligada" : "Desligada");
    writeOnScreen(GLUT_BITMAP_8_BY_13, dados);

    glEnable(GL_LIGHTING);

    free(dados);
}