#include "Header/drawings.h"
#include "Header/globalParameters.h"
#include "Header/Planet.h"
#include "Header/Space.h"
#include "Header/Light.h"
#include "Header/Camera.h"
#include "Header/MusicManager.h"
#include "Header/Keyboard.h"
#include "Header/Light.h"
#include "Header/Parser.h"

// Objeto responsável por gerenciar os acontecimentos da cena
Space* space;

// Inicializa aspectos importantes para funcionamento do programa
void initialize()
{
    // Instancia o space
    space = new Space();

    // Instancia o sinalizador de pressionamento de teclas
    keys = std::make_shared<Keyboard>();

    tempo = std::make_shared<double>(0);

    // Habilita a cor dos materiais
    glEnable(GL_COLOR_MATERIAL);

    // ??
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

// Callback da função de desenho
void display()
{
    // Chama função de desenho
    space->display();
}

void reshape(int width, int height)   
{
    // Atualiza o valor da variável de razão aspecto da tela
    razaoAspecto = (double) glutGet(GLUT_WINDOW_WIDTH) / (double) glutGet(GLUT_WINDOW_HEIGHT);

    // Configura a Viewport
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    // Carrega a matriz identidade
    glLoadIdentity();

    // Configura a caixa de visualização
    glFrustum(-razaoAspecto, razaoAspecto, -1, 1, 2, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Callback da função de pressionamento de teclas
void keyboard(unsigned char key, int x, int y)
{
    char formattedKey = (char) toupper(key);

        switch (formattedKey)
        {
            case 27 :     
                exit(0);
                break;

            case 'W':
                if(keys->w) keys->w = 0;
                else       keys->w = 1;
                break;

            case 'A':
                if(keys->a) keys->a = 0;
                else       keys->a = 1;
                break;

            case 'S':
                if(keys->s) keys->s = 0;
                else       keys->s = 1;
                break;

            case 'D':
                if(keys->d) keys->d = 0;
                else       keys->d = 1;
                break;

            case ' ':
                if(keys->space) keys->space = 0;
                else        keys->space = 1;
                break;

            case 'F':
                if(keys->f) keys->f = 0;
                else       keys->f = 1;
                break;

            case 'Z':
                if(keys->z) keys->z = 0;
                else       keys->z = 1;
                break;

            case 'X':
                if(keys->x) keys->x = 0;
                else       keys->x = 1;
                break;

            case 'C':
                if(keys->c) keys->c = 0;
                else       keys->c = 1;
                break;

            case 'V':
                if(keys->v) keys->v = 0;
                else       keys->v = 1;
                break;

            case 'B':
                if(keys->b) keys->b= 0;
                else       keys->b = 1;
                break;
                
            case 'N':
                if(keys->n) keys->n = 0;
                else       keys->n = 1;
                break;

            case 'L':
                if(keys->l) keys->l = 0;
                else       keys->l = 1;
                buttons[0] = 1;
                break;

            case 'K':
                if(keys->k) keys->k = 0;
                else       keys->k = 1;
                buttons[1] = 1;
                break;


        }
}

// Callback da timerFunc
void timer(int t)
{
    // Atualiza o valor do tempo de execução do programa
    *tempo = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

    // Movimenta a câmera
    space->cameraMoving();

    // Determina se as fontes de luz estão ligadas
    space->onOffSun();

    glutPostRedisplay();
    glutTimerFunc(t, timer, t);
}

// Callback da passiveMotionFunc
void posicionaCamera(int x, int y)
{
    // Determina as coordenadas da câmera
    space->getCamera()->setMouseCoords(x,y);
}

// Inicializa aspectos da glut
void glutInitialize(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1384,752);
    glutInitWindowPosition(325,125);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Lista 3");

    glutIgnoreKeyRepeat(1); 

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard);
    glutPassiveMotionFunc(posicionaCamera);
    glutTimerFunc(2, timer, 2);
}

int main(int argc, char **argv)
{
    glutInitialize(argc, argv);
    initialize();
    glutMainLoop();

    return 0;
}