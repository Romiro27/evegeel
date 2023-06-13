#include "window.h"

#include <iostream>

SDL_HitTestResult callback (SDL_Window* win, const SDL_Point* area, void* data)
{
    return SDL_HITTEST_DRAGGABLE;
}

Window::Window ( std::string windowHeaderText, int posX, int posY, int width, int height ) {

    if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 ) {

        std::cout << "SDL_Init error:\n" << SDL_GetError () << std::endl;
    }

    window = SDL_CreateWindow ( windowHeaderText.c_str (), posX, posY, width, height, SDL_WINDOW_OPENGL );


    //SDL_SetWindowOpacity( window, 0.5 );
    SDL_SetWindowBordered( window, SDL_FALSE );
    SDL_SetWindowHitTest( window, callback, nullptr);

    glContext = SDL_GL_CreateContext ( window );
}


void Window::clearWindow () {

    glClear ( GL_COLOR_BUFFER_BIT );
}

void Window::swapBuffers () {

    SDL_GL_SwapWindow ( window );

    int x, y;
    SDL_GetWindowSize( window, &x, &y );
    glViewport(0, 0, x, y );
}


bool Window::isQuit () {

    SDL_PollEvent ( &event );
    return event.type == SDL_QUIT;
}


Window::~Window () {

    SDL_GL_DeleteContext ( glContext );
}
