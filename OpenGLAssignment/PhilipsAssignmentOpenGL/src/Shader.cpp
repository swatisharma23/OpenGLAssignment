#include "Shader.h"
#include <fstream>
#include <sstream>


GLuint Shader::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    // Create the shaders
    GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertShaderString = readShaderFromFile(vertex_file_path);
    std::string fragShaderString = readShaderFromFile(fragment_file_path);

    const char* vertShaderSource = vertShaderString.c_str();
    const char* fragShaderSource = fragShaderString.c_str();

    //compile shader
    glShaderSource(vertShaderId, 1, &vertShaderSource, NULL);
    glCompileShader(vertShaderId);

    glShaderSource(fragShaderId, 1, &fragShaderSource, NULL);
    glCompileShader(fragShaderId);

    return createProgram(vertShaderId, fragShaderId);

}

std::string Shader::readShaderFromFile(const char* shaderFilePath)
{
    
    std::string shaderSource;
    std::ifstream fileStream(shaderFilePath, std::ios::in);

    if (fileStream.is_open()) {
        std::stringstream sstr;
        sstr << fileStream.rdbuf();
        shaderSource = sstr.str();
        fileStream.close();
    }
    return shaderSource;
}

GLuint Shader::createProgram(GLuint vertShader, GLuint fragShader)
{    
    //create program 
    GLuint programID = glCreateProgram();
    //attach shader
    glAttachShader(programID, vertShader);
    glAttachShader(programID, fragShader);
    //link program 
    glLinkProgram(programID);

    return programID;
}

