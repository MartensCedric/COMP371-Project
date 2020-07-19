#include "includes/Camera.hpp"

GLuint projectionMatrixLocation;
float defaultFOV = 0.785f;
/**
* This class instantiates a camera. It has some utility functions that manipulates it.
*/
Camera::Camera() :
	speed(0.1f),
	position(0.0f, 5.0f, 15.0f),
	lookAtPos(0, 2, 0),
	up(0.0f, 1.0f, 0.0f)
{
    // With this enabled (surfaces with vertices in counter clockwise direction will render)
    // Therefore the back of a surface will not render (more efficient)
    glEnable(GL_CULL_FACE); 
    
    //With this enabled, object behind other objects will not be rendered
    glEnable(GL_DEPTH_TEST);

    // greyish background color
    glClearColor(0.2f, 0.29f, 0.29f, 1.0f);
}

void Camera::moveForward() {
    position += speed * lookAtPos;
}

void Camera::moveBack() {
    position -= speed * lookAtPos;
}

void Camera::moveLeft() {
    position -= glm::normalize(glm::cross(lookAtPos, up)) * speed;
}

void Camera::moveRight() {
    position += glm::normalize(glm::cross(lookAtPos, up)) * speed;
}

void Camera::setViewMatrix(int shader)
{
	glm::mat4 viewMatrix = lookAt(
		position, // eye
		lookAtPos, // center
		up // up
	);
	GLuint viewMatrixLocation = glGetUniformLocation(shader, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

}

void Camera::setProjectionMatrix(int shader)
{
	// Set projection matrix for the shader (in this case we use perspective projection)
	glm::mat4 projectionMatrix = glm::perspective(
		this->fov,            // field of view in degrees
		1024.0f / 768.0f, // aspect ratio
		0.01f, 100.0f     // near and far (near > 0)
	);
	projectionMatrixLocation = glGetUniformLocation(shader, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}


//Replaces the values of the projection matrix within the projectionMatrixLocation
void Camera::setFOV(float fov) {
	if (fov > 1.8f) {
		this->fov = 1.8f;
	}
	else if (fov < 0.4f) {
		this->fov = 0.4f;
	}
	else {
		this->fov = fov;
	}
}

float Camera::getFOV() {
	return this->fov;
}

