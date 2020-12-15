#include <GL/glew.h>
#include "Model.h"
#include "Shader.h"
#include "ComplexModel.h"
/* This class is responisble for
* loading vertex buffer and vertex array objects
* load and render a wavefront obj model 
*/
class Scene
{
private: 

	Model floor;
	GLuint floorVAO;
	GLuint floorProgramId;

	Model cube;
	GLuint cubeVAO;
	GLuint cubeProgramId;

	ComplexModel robot;
	GLuint robotProgramId;

public:

	void createVAO();

	GLuint getFloorVAO();
	void createFloorData();
	Model getFloor();
	void drawFloor();
	GLuint getFloorProgram();

	void createCubeData();
	Model getCube();
	void drawCube();
	GLuint getCubeProgram();
	GLuint getCubeVAO();

	void createRobotData(string const& path);
	ComplexModel getRobot();
	void drawRobot();
	GLuint getRobotProgram();

	void cleanUp();
	
};

