TARGET = Snake

all: main.o inputoutput.o game.o gui.o grid.o snake.o
	gcc main.o inputoutput.o game.o gui.o grid.o snake.o -lSDL -o $(TARGET) `sdl-config --libs` -lsDL_ttf
	make clean

main.o: main.c grid.h gui.h snake.h game.h inputoutput.h
	gcc main.c -c -o main.o `sdl-config --cflags`

inputoutput.o: inputoutput.c inputoutput.h grid.h snake.h
	gcc inputoutput.c -c -o inputoutput.o `sdl-config --cflags`

game.o: game.c game.h snake.h gui.h inputoutput.h
	gcc game.c -c -o game.o `sdl-config --cflags`

snake.o: snake.c snake.h grid.h game.h
	gcc snake.c -c -o snake.o `sdl-config --cflags`

gui.o: gui.c gui.h grid.h snake.h inputoutput.h
	gcc gui.c -c -o gui.o `sdl-config --cflags`

grid.o: grid.c grid.h snake.h
	gcc grid.c -c -o grid.o `sdl-config --cflags`

clean:
	$(RM) *.o
