#include "Scene.h"
#include "Vertices.h"

void Scene::createVAO() {
	glGenVertexArrays(1, &floorVAO);
	glGenVertexArrays(1, &cubeVAO);
}

GLuint Scene::getFloorVAO() {
	return floorVAO;
}

GLuint Scene::getCubeVAO() {
	return cubeVAO;
}


void Scene::createFloorData()
{
	glBindVertexArray(floorVAO);

	floorProgramId = Shader::LoadShaders("src/shader/simpleShader.vertex", "src/shader/simpleShader.fragment");
	floor.createBuffers();

	glBindBuffer(GL_ARRAY_BUFFER, floor.getVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vertex_buffer_data), floor_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, floor.getTBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor_tex_buffer_data), floor_tex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, floor.getEBO());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floor_index_buffer_data) , floor_index_buffer_data, GL_STATIC_DRAW);
}

Model Scene::getFloor()
{
	return floor;
}

void Scene::drawFloor()
{
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, floor.getTBO());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, floor.getVBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

GLuint Scene::getFloorProgram()
{
	return floorProgramId;
}


void Scene::createCubeData() {
	glBindVertexArray(cubeVAO);

	cubeProgramId = Shader::LoadShaders("src/shader/simpleShader.vertex", "src/shader/simpleShader.fragment");
	cube.createBuffers();
	 
	glBindBuffer(GL_ARRAY_BUFFER, cube.getVBO());
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_texture_buffer_data), cube_vertex_texture_buffer_data, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, cube.getTBO());
	//glBufferData(GL_ARRAY_BUFFER, sizeof(cube_tex_buffer_data), cube_tex_buffer_data, GL_STATIC_DRAW);


		//commented for rubix
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.getEBO());
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index_buffer_data), cube_index_buffer_data, GL_STATIC_DRAW);

}

void Scene::drawCube() {
	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, cube.getFBO());
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//commented for rubix
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.getEBO());
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index_buffer_data), cube_index_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, cube.getVBO());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

	//commented for rubix
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	//glBindBuffer(GL_ARRAY_BUFFER, cube.getVBO());

	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

Model Scene::getCube() {
	return cube;
}

GLuint Scene::getCubeProgram() {
	return cubeProgramId;
}


void Scene::createRobotData(string const& path) {
	
	robotProgramId = Shader::LoadShaders("src/shader/complexShader.vertex", "src/shader/complexShader.fragment");

	robot.loadComplexModel(path);
}

ComplexModel Scene::getRobot() {
	return robot;
}

void Scene::drawRobot() {
	robot.Draw(robotProgramId);
}

GLuint Scene::getRobotProgram() {
	return robotProgramId;
}

void Scene::cleanUp() {

	// Cleanup VBO and shader
	floor.deleteBuffers();
	cube.deleteBuffers();
	robot.deleteBuffers();

	glDeleteProgram(floorProgramId);
	glDeleteProgram(cubeProgramId);
	glDeleteProgram(robotProgramId);

	glDeleteVertexArrays(1, &floorVAO);
	glDeleteVertexArrays(1, &cubeVAO);

}
