#include <GL/glew.h>
class Model
{
private:

	GLuint vertexBuffer;
	GLuint texBuffer;
	GLuint indexBuffer;

public:
	GLuint getVBO();
	GLuint getEBO();
	GLuint getTBO();

	void createBuffers();
	void deleteBuffers();
};
