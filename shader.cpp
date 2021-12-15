#include <string>
#include <iostream>
#include <fstream>
#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.h"

static std::string LoadShader ( const std::string& filename );
static void CheckShaderError ( GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage );
static GLuint CreateShader ( const std::string& text, GLenum shaderType );

Shader::Shader ( const std::string& filename ) {
    
    m_program = glCreateProgram ();
    m_shaders [0] = CreateShader ( LoadShader ( filename + ".vs" ), GL_VERTEX_SHADER );
    m_shaders [1] = CreateShader ( LoadShader ( filename + ".fs" ), GL_FRAGMENT_SHADER );
    
    for ( unsigned int i = 0; i < NUM_SHADERS; i++ ) {
        glAttachShader ( m_program, m_shaders [i] );
    }
    
    glBindAttribLocation ( m_program, 0, "position" );
    
    glLinkProgram ( m_program );
    CheckShaderError ( m_program, GL_LINK_STATUS, true, "Error: Program linking failed:" );
    
    glValidateProgram ( m_program );
    CheckShaderError ( m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid:" );
}

Shader::Shader ( const std::string vertexShaderSource, const std::string fragmentShaderSource ) {
    
    m_program = glCreateProgram ();
    m_shaders [0] = CreateShader ( vertexShaderSource, GL_VERTEX_SHADER );
    m_shaders [1] = CreateShader ( fragmentShaderSource, GL_FRAGMENT_SHADER );
    
    for ( unsigned int i = 0; i < NUM_SHADERS; i++ ) {
        glAttachShader ( m_program, m_shaders [i] );
    }
    
    glBindAttribLocation ( m_program, 0, "position" );
    glBindAttribLocation ( m_program, 1, "texCoord" );
    
    glLinkProgram ( m_program );
    CheckShaderError ( m_program, GL_LINK_STATUS, true, "Error: Program linking failed:" );
    
    glValidateProgram ( m_program );
    CheckShaderError ( m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid:" );
}


void Shader::Bind () {
    glUseProgram ( m_program );
}


void Shader::SetUniform ( std::string name, double value ) {
    
    GLuint u_location = glGetUniformLocation ( this -> m_program, name.c_str () );
    glUniform1f ( u_location, value );
}

void Shader::SetUniform ( std::string name, glm::vec2 value ) {
    
    GLuint u_location = glGetUniformLocation ( this -> m_program, name.c_str () );
    glUniform2f ( u_location, value.x, value.y );
}

void Shader::SetUniform ( std::string name, glm::vec3 value ) {
    
    GLuint u_location = glGetUniformLocation ( this -> m_program, name.c_str () );
    glUniform3f ( u_location, value.x, value.y, value.z );
}

void Shader::SetUniform ( std::string name, glm::vec4 value ) {
    
    GLuint u_location = glGetUniformLocation ( this -> m_program, name.c_str () );
    glUniform4f ( u_location, value.x, value.y, value.z, value.t );
}


static GLuint CreateShader ( const std::string& text, GLenum shaderType ) {
    
    GLuint shader = glCreateShader ( shaderType );
    
    if ( shader == 0 ) {
        std::cerr << "Error: Shader creation failed" << std::endl;
    }
    
    const GLchar* shaderSourceStrings [1];
    int shaderSourceLengths = text.length ();
    
    shaderSourceStrings [0] = text.c_str ();
    
    glShaderSource ( shader, 1, shaderSourceStrings, &shaderSourceLengths );
    glCompileShader ( shader );
    
    CheckShaderError ( shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed:" );
    
    return shader;
}

static std::string LoadShader ( const std::string& filename ) {
    
    std::ifstream file;
    file.open ( (filename).c_str() );
    
    std::string output;
    std::string line;
    
    if ( file.is_open () ) {
        while ( file.good () ) {
            getline ( file, line );
            output.append ( line + "\n" );
        }
    } else {
        std::cerr << "Unable to load shader: " << filename << std::endl;
    }
    
    return output;
}

static void CheckShaderError ( GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage ) {
    
    GLint success = 0;
    GLchar error [1024] = { 0 };
    
    if ( isProgram ) {
        glGetProgramiv ( shader, flag, &success );
    } else {
        glGetShaderiv ( shader, flag, &success );
    }
    
    if ( success == GL_FALSE ) {
        if ( isProgram ) {
            glGetProgramInfoLog ( shader, sizeof ( error ), NULL, error );
        } else {
            glGetShaderInfoLog ( shader, sizeof ( error ), NULL, error );
        }
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::GetProgram ()
{
    return this->m_program;
}

Shader::~Shader () {
    
    for ( unsigned int i = 0; i < NUM_SHADERS; i++) {
        
        glDetachShader ( m_program, m_shaders [i] );
        glDeleteShader ( m_shaders [i] );
    }
    
    glDeleteProgram ( m_program );
}
