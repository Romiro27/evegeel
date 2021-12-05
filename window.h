#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GLES3/gl3.h>
#include <string>

class Window {
public:

    Window ( std::string windowHeaderText, int posX, int posY, int width, int height );


private:

    SDL_Window* window;

    SDL_GLContext glContext;
};

#endif
