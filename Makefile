all:
	clang src/*.c  -lGL -lglfw -lGLEW -o Game && ./Game
