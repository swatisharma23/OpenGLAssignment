// PhilipsAssignmentOpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Camera.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "ComplexModel.h"

using namespace glm;
using namespace std;

GLFWwindow* window;
Camera camera;
Scene scene;

int windowWidth = 800;
int windowHeight = 600;
float lastX = windowWidth / 2.0f;
float lastY = windowHeight / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float robotangle = 0.0f;

void windowSizeChanged_callback(GLFWwindow* window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

int main()
{
    cout << "Hello 3D graphics World!\n";
	// Initialise GLFW
	if (!glfwInit())
	{
		cout << stderr << "Failed to initialize GLFW" << endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	window = glfwCreateWindow(windowWidth, windowHeight, "Philips Assignement", NULL, NULL);
	if (window == NULL) {
		cout << stderr << "Failed to open GLFW window." << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, windowSizeChanged_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();
	glfwSetCursorPos(window, windowWidth / 2.0f, windowHeight / 2.0f);

	glewExperimental = true; // core profile
	if (glewInit() != GLEW_OK) {
		cout << stderr << "Failed to initialize GLEW" << endl;
		glfwTerminate();
		return -1;
	}

	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);


	// Camera is at (3,0,0), in World Space
	// Head is up (set to 0,1,0 to look upside-down)
	camera.setProjectionAndCamera(vec3(3,0,0), vec3(0,1, 0));

	float ratio = float(windowWidth) / float(windowHeight);

	scene.createVAO();
	scene.createFloorData();
	scene.createCubeData();
	scene.createRobotData("./res/object/OrangeBot_OBJ/OrangeBOT.obj");

	//get shader handler
	GLuint floorMVPMatrixID;
	GLuint floorTextureID ;
	GLuint floorTexture;
	floorTexture = Texture::loadAndCreateTexture("./res/texture/floor.jpeg");

	GLuint cubeMVPMatrixID;
	GLuint cubeTextureID;
	GLuint cubeTexture;
	cubeTexture = Texture::loadAndCreateTexture("./res/texture/rubik.jpg");

	GLuint robotMVPMatrixID;

	mat4 projectionMatrix;
	mat4 viewMatrix;
	vec3 translateFloor = vec3(3.0f, 0.4f, -3.5f);
	vec3 translateCube[] = { vec3(2.9f, 0.3f, -4.1f),
							 vec3(2.3f,  -0.1f, -2.5f) 
							};
	vec3 translateRobot = vec3(3.7f, 0.35f, -3.6f);

	
	//render loop
		
	do {

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// Clear the screen.
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		projectionMatrix = camera.getProjectionMatrix(ratio);
		viewMatrix = camera.getViewMatrix();
		

		/////////////// draw floor/////////////////////
		// Use floor shader
		glUseProgram(scene.getFloorProgram());
		mat4 floorModel = glm::mat4(1.0f);
		floorModel = glm::translate(floorModel, translateFloor);
		mat4 floorMVP = projectionMatrix * viewMatrix * floorModel;
		glBindVertexArray(scene.getFloorVAO());
		floorMVPMatrixID = glGetUniformLocation(scene.getFloorProgram(), "MVP");
		floorTextureID = glGetUniformLocation(scene.getFloorProgram(), "sampler");
		glUniformMatrix4fv(floorMVPMatrixID, 1, GL_FALSE, &floorMVP[0][0]);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		glUniform1i(floorTextureID, 0);
		scene.drawFloor();
		///////////////////////////////////////////////////

		////////////draw cube/////////////////////////////

		for (unsigned int i = 0; i < 2; i++) {

			glUseProgram(scene.getCubeProgram());
			mat4 cubeModel = glm::mat4(1.0f);
			
			cubeModel = glm::translate(cubeModel, translateCube[i]);
			float angle = -60.0f + 120 * i;
			cubeModel = glm::rotate(cubeModel, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
			if (i == 1) {
				cubeModel = glm::scale(cubeModel, vec3(1.0f, 0.5f, 0.5f));
			}
			else {
				cubeModel = glm::scale(cubeModel, vec3(2.0f, 1.0f, 1.0f));
			}

			mat4 cubeMVP = projectionMatrix * viewMatrix * cubeModel;
			glBindVertexArray(scene.getCubeVAO());
			cubeMVPMatrixID = glGetUniformLocation(scene.getCubeProgram(), "MVP");
			cubeTextureID = glGetUniformLocation(scene.getCubeProgram(), "sampler");
			glUniformMatrix4fv(cubeMVPMatrixID, 1, GL_FALSE, &cubeMVP[0][0]);
			glBindTexture(GL_TEXTURE_2D, cubeTexture);
			glUniform1i(cubeTextureID, 0);
			scene.drawCube();
		}
		///////////////////////////////////////////////

		//////////////////draw Complex Model//////////////
		glUseProgram(scene.getRobotProgram());
		mat4 robotModel = glm::mat4(1.0f);

		//backpack settings
		/*complexModel = glm::translate(complexModel, vec3(3.7f, -0.2f, -2.9f));
		float angle = 100.0f;
		complexModel = glm::rotate(complexModel, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		complexModel = glm::scale(complexModel, vec3(0.2f));*/

		//robot settings
		robotModel = glm::translate(robotModel, translateRobot);

		if (robotangle > 360) {
			robotangle = 0;
		}
		robotangle += 3.14159f * 5.0f * deltaTime;
		
		robotModel = glm::rotate(robotModel, glm::radians(robotangle), glm::vec3(0.0f, 1.0f, 0.0f));
		robotModel = glm::scale(robotModel, vec3(0.2f));


		mat4 robotMVP = projectionMatrix * viewMatrix * robotModel;
		robotMVPMatrixID = glGetUniformLocation(scene.getRobotProgram(), "MVP");
		glUniformMatrix4fv(robotMVPMatrixID, 1, GL_FALSE, &robotMVP[0][0]);
		scene.drawRobot();

		/////////////////////////////////////////////////

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	scene.cleanUp();
	glDeleteTextures(1, &floorTextureID);
	glDeleteTextures(1, &cubeTextureID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

