#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.003f;
const float ZOOM = 45.0f;

//class that handles point of view of shot
class Camera
{
private:

	vec3 Pos;
	vec3 Front;
	vec3 Up;
	vec3 Right;
	vec3 upVec;

	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	float fovy;
	void updateMatrices();

public:

	void setProjectionAndCamera(vec3 position, vec3 up, float yaw = YAW, float pitch = PITCH);
	//void setProjectionAndCamera(float fovy, vec3 eyePos, vec3 origin, vec3 upVec,float ratio);
	mat4 getViewMatrix();
	//mat4 getProjectionMatrix();
	mat4 getProjectionMatrix(float ratio);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

};

