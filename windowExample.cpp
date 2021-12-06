#include "window.h"
#include "OGLRender.h"

int main () {

    Window window ( "window", 0, 0, 800, 600 );
    OGLRender render;

    while ( !window.isQuit () ) {

        window.clearWindow ();

        window.swapBuffers ();
    }

    return 0;
}
