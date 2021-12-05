#include "OGLRender.h"

void OGLRender::loadImage ( unsigned char* input, int width, int height ) {

    imageCoordinates = {
        Vertex ( 1-1/width, 1-1/height ), //верхний правый
        Vertex ( 1-1/width, -(1-1/height) ), //нижний правый
        Vertex ( -(1-1/width), -(1-1/height) ), //нижний левый
        Vertex ( -(1-1/width), 1-1/height ) //верхний левый
    };
    textureCoordinates = {
        Vertex ( 1, 1 ), //соответственно
        Vertex ( 1, 0 ),
        Vertex ( 0, 0 ),
        Vertex ( 0, 1 )
    };

    glGenTextures ( 1, &texture );
    glBindTexture ( GL_TEXTURE_2D, texture );

    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB8, GL_UNSIGNED_BYTE, data );

    glBindTexture ( GL_TEXTURE_2D, 0 );


    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (GLvoid*)0 ); //coordinates of vertex

    glVertexAttribPointer ( 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof ( GLfloat ),
                           (GLvoid*)(3*sizeof(GLfloat)) ); //2d texture coordinates
}

void OGLRender::drawImage () {
    //
}


void OGLRender::setPositionOfView ( double x, double y ) {

    positionX = x;
    positionY = y;
}

void OGLRender::setZoom ( double zoom ) {

    this -> zoom = zoom;
}
