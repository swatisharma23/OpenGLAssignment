#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace std;
extern GLFWwindow* window;
bool firstFrame = true;

void Camera::setProjectionAndCamera(vec3 position, vec3 up , float yaw, float pitch)
    {
        Pos = position;
        upVec = up;
        Yaw = yaw;
        Pitch = pitch;
        Front = vec3(0.0f, 0.0f, -1.0f); 
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Zoom = ZOOM;
        updateMatrices();
    }

mat4 Camera::getViewMatrix() {
    return lookAt(Pos, Pos + Front, Up);
}

mat4 Camera::getProjectionMatrix(float ratio) {
	return perspective(radians(Zoom), ratio, 0.1f, 100.0f);
}

//planning to update camera position from mouse or keyboard inputs
void Camera::updateMatrices() {
    // calculate the new Front vector
    vec3 front;
    //cout << "Yaw " << Yaw << " pitch " << Pitch << endl;
    front.x = cos(radians(Yaw)) * cos(radians(Pitch));
    front.y = sin(radians(Pitch));
    front.z = sin(radians(Yaw)) * cos(radians(Pitch));
    //cout << "Front " << front.x << " " << front.y << " " << front.z << endl;

    Front = normalize(front);

    //cout << "normalized Front " << Front.x << " " << Front.y << " " << front.z << endl;
    // also re-calculate the Right and Up vector
    Right = normalize(cross(Front, upVec)); 
    Up = normalize(cross(Right, Front));
   // cout << "normalized up " << Up.x << " " << Up.y << " " << Up.z << endl;

}

//sets the initial projections and view matrices.
//void Camera::setProjectionAndCamera(float fovy, vec3 eyePos, vec3 origin, vec3 upVec,float ratio) {
//	
//	// Projection matrix : fovy° Field of View, ratio, display range : 0.1 unit <-> 100 units
//	//projectionMatrix = glm::perspective(fovy, ratio, 0.1f, 100.0f);
//	//projectionMatrix = glm::frustum( -ratio , ratio, -1.0f, 1.0f , 1.0f , 100.0f);
//	
//	// Camera matrix
//	//viewMatrix = glm::lookAt(eyePos, origin, upVec);
//		
//}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Pos += Front * velocity;
    if (direction == BACKWARD)
        Pos -= Front * velocity;
    if (direction == LEFT)
        Pos -= Right * velocity;
    if (direction == RIGHT)
        Pos += Right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateMatrices();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}