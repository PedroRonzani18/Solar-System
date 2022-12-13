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
-   Z: aumenta a iluminação ambiente 
-   X: diminui a iluminação ambiente 
-   C: aumenta a iluminação difusa
-   V: diminui a iluminação difusa
-   B: aumenta a iluminação especular 
-   N: diminui a iluminação especular 
-   L: desliga/liga a luz emitida pelos planetas Terra, Marte, Saturno
-   K: desliga/liga a luz emitida pelo Sol

### Movimentação
-   W: move-se para FRENTE de onde a câmera aponta
-   S: move-se para TRÁS de onde a câmera aponta
-   A: move-se para ESQUERDA de onde a câmera aponta
-   D: move-se para DIREITA de onde a câmera aponta
