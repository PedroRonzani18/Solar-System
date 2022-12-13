# Solar System

## Bibliotecas Necessárias para execução no Linux

* Freeglut: `sudo apt-get install freeglut3-dev`
* SOIL: `sudo apt-get install libsoil-dev`
* LDS: `sudo apt-get install -y libsdl2-mixer-dev`
* GLM: `sudo apt install libglm-dev`

## Compilar e Executar o projeto

-   Para compilar, abra o terminal na pasta do projeto e dê o comando `make compilar`
-   Para executar, abra o terminal na pasta do projeto e dê o comando `./main`
-   Para compilar e executar, abra o terminal na pasta do projeto e dê o comando `make executar`

## Teclas Necessárias

### Iluminação
-   Z/X: aumenta/diminui a iluminação ambiente do Sol
-   C/V: aumenta/diminui a iluminação difusa do Sol
-   B/N: aumenta/diminui a iluminação especular do Sol
-   L: liga/desliga a luz emitida pelos planetas Terra, Marte, Saturno
-   K: liga/desliga a luz emitida pelo Sol

### Movimentação
-   W: move-se para FRENTE de onde a câmera aponta
-   S: move-se para TRÁS de onde a câmera aponta
-   A: move-se para ESQUERDA de onde a câmera aponta
-   D: move-se para DIREITA de onde a câmera aponta
