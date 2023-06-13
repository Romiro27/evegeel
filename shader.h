#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>

class Shader {
public:
    Shader ( const std::string& filename );
    Shader ( const std::string vertexShaderSource, const std::string fragmentShaderSource );
    
    void Bind ();
    void SetUniform ( std::string name, double value );
    void SetUniform ( std::string name, glm::vec2 value );
    void SetUniform ( std::string name, glm::vec3 value );
    void SetUniform ( std::string name, glm::vec4 value );

    GLuint GetProgram ();
    
    ~Shader ();
    
private:
    
    static const unsigned int NUM_SHADERS = 2;
    GLuint m_program;
    GLuint m_shaders [NUM_SHADERS];
};

#endif
