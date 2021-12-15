#include <iostream>

#include "OGLRender.h"


void OGLRender::loadImage ( unsigned char* input, int width, int height ) {

    data = input;

	imageWidth = width;
	imageHeight = height; /* 1-1/width */

    imageCoordinates = {
        Vertex ( 1, 1 ), //верхний правый
        Vertex ( 1, -1 ), //нижний правый
        Vertex ( -1, -1 ), //нижний левый
        Vertex ( -1, 1 ) //верхний левый
    };
    textureCoordinates = {
        Vertex ( 1, 1 ), //соответственно
        Vertex ( 1, 0 ),
        Vertex ( 0, 0 ),
        Vertex ( 0, 1 )
    };

    glGenTextures ( 1, &texture );
    glBindTexture ( GL_TEXTURE_2D, texture );

    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameterf ( GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf ( GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB8, GL_UNSIGNED_BYTE, data );

    glGenerateMipmap ( GL_TEXTURE_2D );

    glBindTexture ( GL_TEXTURE_2D, 0 );


    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                          (GLvoid*)0 ); //coordinates of vertex

    glVertexAttribPointer ( 1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof ( GLfloat ),
                           (GLvoid*)(2*sizeof(GLfloat)) ); //2d texture coordinates

    shader = new Shader ( "./shader" );

}

void OGLRender::drawImage () {

	int width = /*(1-1/imageWidth)*zoom + positionX*/ 1;
	int height = /*(1-1/imageHeight) * zoom + positionY*/ 1;

	imageCoordinates = {
		Vertex ( width, height ), //верхний правый
		Vertex ( width, -height ), //нижний правый
		Vertex ( -width, -height ), //нижний левый
		Vertex ( -width, height ) //верхний левый
	};


	GLfloat vertices [16];

	int j = 0;

	for ( int i = 0; i < 16; i += 4 ) {

		vertices [i] = imageCoordinates [j].x;
		vertices [i + 1] = imageCoordinates [j].y;
		vertices [i + 2] = textureCoordinates [j].x;
		vertices [i + 3] = textureCoordinates [j].y;

		j++;
	}

	glBindTexture ( GL_TEXTURE_2D, texture );


	glGenBuffers ( 1, &VBO );
	glBindBuffer ( GL_ARRAY_BUFFER, VBO );
	glBufferData ( GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW );

	glGenVertexArrays ( 1, &VAO );
	glBindVertexArray ( VAO );
	glEnableVertexAttribArray ( 0 );


	shader -> Bind ();

	glDrawArrays ( GL_TRIANGLES, 0, 3 );
	glBindVertexArray ( 0 );
}


void OGLRender::setPositionOfView ( double x, double y ) {

    positionX = x;
    positionY = y;
}

void OGLRender::setZoom ( double zoom ) {

    this -> zoom = zoom;
}

