CC = g++
FLAGS= -lglut -lGL -lGLU -lSOIL -lSDL2 -lSDL2_mixer
OUTPUT= main
all:
	@ echo "Building target using GCC compile:"
	@$(CC) -g *.cpp */*.cpp $(FLAGS) -o $(OUTPUT)

run: all
	@ echo "Running $(OUTPUT):"
	@./$(OUTPUT)

clean:
	rm -f $(OUTPUT)