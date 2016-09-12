CC=g++
CFLAGS=-O

engine: engine.cpp
	$(CC) -o engine engine.cpp -lglut -lGL
