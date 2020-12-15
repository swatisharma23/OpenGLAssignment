#pragma once
//Load texture files
#include <GL/glew.h>
#include <string>
using namespace std;

class Texture
{
public:
	GLuint static loadAndCreateTexture(const char * fileName);
	GLuint static TextureFromFile(const char* path, const string& directory);

};

