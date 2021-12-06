#include "OGLRender.h"


OGLRender::OGLRender () {

	vertexShaderSource =
		"#version 330 core"
		"in vec3 ourColor;"
		"in vec2 TexCoord;"

		"out vec4 color;"

		"uniform sampler2D ourTexture;"

		"void main()"
		"{"
		"	color = texture(ourTexture, TexCoord);"
		"}";

	fragmentShaderSource =
		"#version 330 core"
		"layout (location = 0) in vec3 position;"
		"layout (location = 1) in vec3 color;"
		"layout (location = 2) in vec2 texCoord;"

		"out vec3 ourColor;"
		"out vec2 TexCoord;"

		"void main()"
		"{"
			"gl_Position = vec4(position, 1.0f);"
		    	"ourColor = color;"
			"TexCoord = texCoord;"
		"}";
}

void OGLRender::loadImage ( unsigned char* input, int width, int height ) {

	vertexShader = glCreateShader ( GL_VERTEX_SHADER );

        glShaderSource ( vertexShader, 1, &vertexShaderSource, 0 );        glCompileShader ( vertexShader );


        fragmentShader = glCreateShader ( GL_FRAGMENT_SHADER );
        glShaderSource ( fragmentShader, 1, &fragmentShaderSource, 0 );
        glCompileShader ( fragmentShader );
                                                                      
        shaderProgram = glCreateProgram ();
                                                                              glAttachShader ( shaderProgram, vertexShader );
        glAttachShader ( shaderProgram, fragmentShader );                     glLinkProgram ( shaderProgram );                                                                                                    
        glDeleteShader ( vertexShader );
        glDeleteShader ( fragmentShader );


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

    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB8, GL_UNSIGNED_BYTE, data );

    glBindTexture ( GL_TEXTURE_2D, 0 );


    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          (GLvoid*)0 ); //coordinates of vertex

    glVertexAttribPointer ( 1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof ( GLfloat ),
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


	int width = (1-1/imageWidth)*zoom + positionX;
	int height = (1-1/imageHeight) * zoom + positionY;

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

