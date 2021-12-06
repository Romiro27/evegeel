 
all:
	g++ -g -std=c++17 main.cpp -lpng

test:
	g++ windowExample.cpp window.cpp OGLRender.cpp -std=c++17 -o a.out -lSDL2 -lGL
