#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GLES3/gl3.h>
#include <string>

class Window {
public:

    Window ( std::string windowHeaderText, int posX, int posY, int width, int height );

    void clearWindow ();
    void swapBuffers ();

    bool isQuit ();

    ~Window ();

private:

    SDL_Window* window;

    SDL_Event event;

    SDL_GLContext glContext;
};

#endif
