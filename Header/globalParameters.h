#ifndef _GLOBALPARAMETERS_H
#define _GLOBALPARAMETERS_H

// OpenGL
#include <GL/freeglut.h>

// SLD_mixer
#include <SDL2/SDL_mixer.h>

// STL
#include <vector>
#include <memory>

// Bibliotecas proprias
#include "Keyboard.h"
#include "Vertex.h"

extern float razaoAspecto; // razao aspecto da tela
extern std::shared_ptr<double> tempo; // tempo de execucao do programa
extern std::shared_ptr<Keyboard> keys; // indica se teclas estao pressionadas ou nao
extern std::vector<GLuint> texturesId; // vector com ID's das texturas
extern int buttons[]; // vetor auxiliar para auxilio nde pressionamento de botoes

#endif