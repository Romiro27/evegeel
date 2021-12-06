#include "window.h"

#include <iostream>

Window::Window ( std::string windowHeaderText, int posX, int posY, int width, int height ) {

    if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 ) {

        std::cout << "SDL_Init error:\n" << SDL_GetError () << std::endl;
    }

    window = SDL_CreateWindow ( windowHeaderText.c_str (), posX, posY, width, height, SDL_WINDOW_OPENGL );


    SDL_SetWindowOpacity( window, 0.1 );
    //SDL_SetWindowBordered ( window, SDL_FALSE );

    glContext = SDL_GL_CreateContext ( window );
}


void Window::clearWindow () {

    glClear ( GL_COLOR_BUFFER_BIT );
}

void Window::swapBuffers () {

    SDL_GL_SwapWindow ( window );
}


bool Window::isQuit () {

    SDL_PollEvent ( &event );
    return event.type == SDL_QUIT;
}


Window::~Window () {

    SDL_GL_DeleteContext ( glContext );
}
