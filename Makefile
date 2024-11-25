all: compile run

compile:
	g++ main.cpp -o GameOfLife.exe -I ./deps/include/ -L ./deps/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lshell32
run:
	.\GameOfLife.exe 