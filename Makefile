CC = g++
FLAGS= -lglut -lGL -lGLU -lSOIL -lSDL2 -lSDL2_mixer
OUTPUT= main
compilar:
		$(CC) -g -std=c++14 -O2 -Wall *.cpp */*.cpp $(FLAGS) -o $(OUTPUT)
		
all:
		$(CC) -g *.cpp */*.cpp $(FLAGS) -o $(OUTPUT)

run: all
	./$(OUTPUT)

executar: compilar
	./$(OUTPUT)

limpar:
		rm *.o -f