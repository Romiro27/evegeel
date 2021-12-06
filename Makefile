 
all:
	g++ -g -std=c++17 main.cpp window.cpp OGLRender.cpp -lpng -lSDL2 -lGL -o a.out -g

