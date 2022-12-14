// Bibliotecas proprias
#include "../Header/Camera.h"
#include "../Header/globalParameters.h"
#include "../Header/drawings.h"

#define radGr(radianos) (radianos * (180.0 / M_PI))
#define grRad(graus) ((graus * M_PI) / 180.0)

// Construtor padrão da Camera
Camera::Camera()
{
    midPoint.x = -13.72;
    midPoint.y = 19.44;
    midPoint.z = -20.96;
    
    directionVector.x = 0.02;
    directionVector.y = -0.63;
    directionVector.z = 0.78;

    moveSpeed.x = 0.1;
    moveSpeed.y = 0.1;
    moveSpeed.z = 0.1;

    sensibilidade = 0.007;

    fi = 3.82;
    theta = 4.68;
}

// Função que retorna o valor em radianos do angulo entre dois lados de valor 1, e lado oposto a
double cossinLaw(double a)
{
    double aux = (2-pow(a,2))/2;
    if(aux <=-1)
        return 0;
    if(aux >= 1)
        return 0; 
    return acos(aux);
}

// Função que calcula distância entre dois pontos
double distanceBetweenPoints(glm::vec3 a, glm::vec3 b)
{
    return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y,2) + pow(a.z - b.z,2));
}

// Função que altera os valores ddo ponto central e vetor direção de acrodo com a posição do mouse e pressionamento de teclas
void Camera::move()
{   
    // Variações na posicao do mouse em x e y
    float deltaX = (mouseCoords_x - previousPosition_x) * sensibilidade;
    float deltaY = (mouseCoords_y - previousPosition_y) * sensibilidade;

    // Valor do sinal do ângulo
    int signal_x = 0, signal_y = 0;

    if(deltaX > 0) signal_x = 1;
    else if(deltaX < 0) signal_x = -1;

    if(deltaY > 0) signal_y = 1;
    else if(deltaY< 0) signal_y = -1;

    // Armazena a posição anterior do mouse
    previousPosition_x = mouseCoords_x;
    previousPosition_y = mouseCoords_y;

    // Altera o valor dos ângulos fi e theta
    theta += signal_x * cossinLaw(deltaX);
    fi += signal_y * cossinLaw(deltaY);

    // Limita os valores maximo e minimo de fi para câmera funcionar normalmente
    if(fi < 1.60) fi = 1.60;
    if(fi > 4.7) fi = 4.7;

    // Altera os valores das componentes do vetor direção de acordo com coordenadas esféricas
    if(checkMouse) // Se o mouse não for movimentado, não ha necessidade de alterar vetor direção
    {
        directionVector.x = cos(theta)*cos(fi);
        directionVector.y = sin(fi);
        directionVector.z = sin(theta)*cos(fi);
    }

    // Altera os valores das componentes do ponto central de acordo com o pressionamento de teclas
    midPoint.x += moveSpeed.x * ((keys->w - keys->s) * directionVector.x + (keys->d - keys->a) * (-directionVector.z)); 
    midPoint.y += moveSpeed.y * ( keys->w - keys->s) * directionVector.y ; 
    midPoint.z += moveSpeed.z * ((keys->w - keys->s) * directionVector.z + (keys->d - keys->a) * (directionVector.x));                 
}

// Função que cuida de voltar a câmera para a posição anterior a essa
void Camera::backPosition()
{
    midPoint.x += moveSpeed.x * ((-keys->w + keys->s) * directionVector.x + (- keys->d + keys->a) * (-directionVector.z)); 
    midPoint.y += moveSpeed.y * ( -keys->w + keys->s) * directionVector.y ; 
    midPoint.z += moveSpeed.z * ((-keys->w + keys->s) * directionVector.z + (- keys->d + keys->a) * (directionVector.x));
}

// Posiiona a câmera no espaço baseado nos valores de midPont e directionVector
void Camera::setupCamera()
{
    gluLookAt(midPoint.x                    , midPoint.y                    , midPoint.z                    ,
              midPoint.x + directionVector.x, midPoint.y + directionVector.y, midPoint.z + directionVector.z,
              0, 1, 0);
}
