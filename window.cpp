#include "window.h"

#include <iostream>

Window::Window ( std::string windowHeaderText, int posX, int posY, int width, int height ) {

    if ( SDL_Init ( SDL_INIT_EVERYTHING ) != 0 ) {

        std::cout << "SDL_Init error:\n" << SDL_GetError () << std::endl;
    }

    window = SDL_CreateWindow ( windowHeaderText.c_str (), posX, posY, width, height, SDL_WINDOW_OPENGL );


    SDL_SetWindowOpacity( window, 0.1 );
    SDL_SetWindowBordered ( window, SDL_FALSE );

    glContext = SDL_GL_CreateContext ( window );

    //glClearColor ( 0, 0, 0, 1 );
    glClear ( GL_COLOR_BUFFER_BIT );

    SDL_GL_SwapWindow ( window );

    SDL_Delay ( 5000 );

    SDL_GL_DeleteContext ( glContext );
}
