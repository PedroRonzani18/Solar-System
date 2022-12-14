#ifndef _DRAWINGS_H
#define _DRAWINGS_H

// OpenGL
#include <GL/freeglut.h>

// SOIL
#include <SOIL/SOIL.h>

// STL
#include <memory>
#include <stdio.h>

// Bibliotecas proprias
#include "Planet.h"
#include "Moon.h"
#include "Sol.h"
#include "Camera.h"
#include "Model.h"

GLuint loadTexture(const char* arquivo);
void createTextures();

void drawSolidSphere(double radius, int stacks, int columns);
void drawCylinder(GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
void drawVertex(Model* model);


void drawPlanet(std::shared_ptr<Planet> planet);
void drawMoon(std::shared_ptr<Moon> moon);
void drawSun(std::shared_ptr<Sol> sun);
void drawCamera(std::shared_ptr<Camera> camera);
void drawModel(std::shared_ptr<Model> model, double planetCoreRadius);

#endif