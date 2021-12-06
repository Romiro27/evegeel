#include <iostream>

#include "OGLRender.h"


OGLRender::OGLRender () {

    vertexShaderSource =
		"#version 300 es\n"
		"layout (location = 0) in vec2 position;\n"
		"layout (location = 1) in vec2 texCoord;\n"

		"out vec2 TexCoord;\n"

		"void main()\n"
		"{\n"
			"gl_Position = vec4(position, 0.0f, 1.0f);\n"
			"TexCoord = texCoord;\n"
		"}\n";

	fragmentShaderSource =
		"#version 300 es\n"
		"in vec2 TexCoord;\n"

		"out vec4 color;\n"

		"uniform sampler2D ourTexture;\n"

		"void main()\n"
		"{\n"
		"	color = texture(ourTexture, TexCoord);\n"
		"}\n";

}

void OGLRender::loadImage ( unsigned char* input, int width, int height ) {

	vertexShader = glCreateShader ( GL_VERTEX_SHADER );

        glShaderSource ( vertexShader, 1, &vertexShaderSource, 0 );        glCompileShader ( vertexShader );
        //*******************
        GLint success;
GLchar infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if(!success)
{
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
        //*********************

        fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER );
        glShaderSource ( fragmentShader, 1, &fragmentShaderSource, 0 );
        glCompileShader ( fragmentShader );
                                                                      
        shaderProgram = glCreateProgram ();
                                                                              glAttachShader ( shaderProgram, vertexShader );
        glAttachShader ( shaderProgram, fragmentShader );                     glLinkProgram ( shaderProgram );                                                                                                    
        glDeleteShader ( vertexShader );
        glDeleteShader ( fragmentShader );

        //*******************
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
}
        //*******************


	imageWidth = width;
	imageHeight = height;

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
                           (GLvoid*)(3*sizeof(GLfloat)) ); //2d texture coordinates
}

void OGLRender::drawImage () {
    
	vertexShader = glCreateShader ( GL_VERTEX_SHADER );

	glShaderSource ( vertexShader, 1, &vertexShaderSource, 0 );
	glCompileShader ( vertexShader );


	fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER );
	glShaderSource ( fragmentShader, 1, &fragmentShaderSource, 0 );
	glCompileShader ( fragmentShader );

	
	shaderProgram = glCreateProgram ();

	glAttachShader ( shaderProgram, vertexShader );
	glAttachShader ( shaderProgram, fragmentShader );
	glLinkProgram ( shaderProgram );


	glDeleteShader ( vertexShader );
	glDeleteShader ( fragmentShader );


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


	glUseProgram ( shaderProgram );
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

