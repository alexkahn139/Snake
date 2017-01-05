TARGET = Snake

all: main.o inputoutput.o game.o gui.o grid.o
	gcc main.o inputoutput.o game.o gui.o grid.o -lSDL -o $(TARGET) `sdl-config --libs` -lSDL_ttf
	make clean

main.o: main.c grid.h gui.h Snake.h game.h inputoutput.h
	gcc main.c -c -o main.o `sdl-config --cflags`

inputoutput.o: inputoutput.c inputoutput.h grid.h Snake.h
	gcc inputoutput.c -c -o inputoutput.o `sdl-config --cflags`

game.o: game.c game.h Snake.h gui.h inputoutput.h
	gcc game.c -c -o game.o `sdl-config --cflags`

Snake.o: Snake.c Snake.h grid.h game.h
	gcc Snake.c -c -o Snake.o `sdl-config --cflags`

gui.o: gui.c gui.h grid.h Snake.h inputoutput.h
	gcc gui.c -c -o gui.o `sdl-config --cflags`

grid.o: grid.c grid.h Snake.h
	gcc grid.c -c -o grid.o `sdl-config --cflags`

clean:
	$(RM) *.o
