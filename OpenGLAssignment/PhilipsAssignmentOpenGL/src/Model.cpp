#include "Model.h"

GLuint Model::getVBO()
{
    return vertexBuffer;
}

GLuint Model::getEBO()
{
    return indexBuffer;
}

GLuint Model::getTBO()
{
    return texBuffer;
}

void Model::createBuffers()
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &texBuffer);
	glGenBuffers(1, &indexBuffer);

}

void Model::deleteBuffers()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteBuffers(1, &texBuffer);
}
