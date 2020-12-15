#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
private:
	static std::string readShaderFromFile(const char* shaderFilePath);
	static GLuint createProgram(GLuint vertShader, GLuint fragShader);
public:
	static GLuint LoadShaders(const char* vertex_shader_path, const char* fragment_shader_path);
};

