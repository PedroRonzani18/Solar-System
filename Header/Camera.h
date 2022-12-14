#ifndef _CAMERA_H
#define _CAMERA_H

// OpenGL
#include <GL/freeglut.h>

// GLM
#include <glm/glm.hpp>

// STL
#include <cmath>

class Camera{
    private:
        glm::vec3 midPoint;
        glm::vec3 directionVector;
        glm::vec3 moveSpeed;
        float theta;
        float fi;
        glm::vec3 angle;
        int mouseCoords_x, mouseCoords_y;
        int previousPosition_x, previousPosition_y;
        double sensibilidade;
        bool checkMouse;
        GLuint border;

    public:
        Camera();

        glm::vec3 getMidPoint(){return this->midPoint;}
        void setMidPoint(glm::vec3 midPoint){this->midPoint = midPoint;}

        glm::vec3 getDirectionVector(){return this->directionVector;}

        void setAngle(glm::vec3 angle){this->angle = angle;}

        void setCheckMouse(bool checkMouse){this->checkMouse = checkMouse;}
        void setMouseCoords(int x, int y){
            mouseCoords_x = x; mouseCoords_y = y;
            setCheckMouse(true);
        }

        float getTheta(){return this->theta;}
        float getFi(){return this->fi;}

        void setBorder(GLuint border){this->border = border;}
        GLuint getBorder(){return this->border;}

        void move();
        void setupCamera();
        void backPosition();
};

#endif