#ifndef OGLRENDER_H
#define OGLRENDER_H

#include <GLES3/gl3.h>
#include <vector>

struct Vertex {
    Vertex ( float x, float y ) {
        this -> x = x;
        this -> y = y;
    }
    float x, y;
};

class OGLRender {
public:

    void loadImage ( unsigned char* input, int width, int height );
    void drawImage ();

    void setPositionOfView ( double x, double y );
    void setZoom ( double zoom ); //0.1 - 2 (isn't in %)

private:

    unsigned char* data;
    GLuint texture;

    std::vector <Vertex> imageCoordinates;
    std::vector <Vertex> textureCoordinates;

    double positionX = 0;
    double positionY = 0;
    double zoom;
};

#endif
