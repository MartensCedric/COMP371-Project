#include "includes/Camera.hpp"

GLuint projectionMatrixLocation;
float defaultFOV = 0.785f;

Camera::Camera(int shaderProgram) : 
    speed(0.1f), 
    position(0.0f, 5.0f, 15.0f),
    lookAtPos(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f),
    shaderProgram(shaderProgram)
{
    // With this enabled (surfaces with vertices in counter clockwise direction will render)
    // Therefore the back of a surface will not render (more efficient)
    glEnable(GL_CULL_FACE); 
    
    //With this enabled, object behind other objects will not be rendered
    glEnable(GL_DEPTH_TEST);

    // greyish background color
    glClearColor(0.2f, 0.29f, 0.29f, 1.0f);

    // Set projection matrix for the shader (in this case we use perspective projection)
    glm::mat4 projectionMatrix = glm::perspective(
        defaultFOV,            // field of view in degrees
        1024.0f / 768.0f, // aspect ratio
        0.01f, 100.0f     // near and far (near > 0)
    );
    projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Set the initial view matrix     					
    reset();
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

void Camera::reset() {
    // Set initial view matrix (because this is running in the "main while loop", it will update every frame)
    glm::mat4 viewMatrix = lookAt(
        position, // eye
        lookAtPos + position, // center
        up // up
    ); 
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);	
}

//Replaces the values of the projection matrix within the projectionMatrixLocation
void Camera::setFOV(float fov) {
	if (fov > 1.8f) {
		defaultFOV = 1.8f;
	}
	else if (fov < 0.4f) {
		defaultFOV = 0.4f;
	}
	else {
		defaultFOV = fov;
	}
	// Set projection matrix for the shader (in this case we use perspective projection)
	glm::mat4 projectionMatrix = glm::perspective(
		defaultFOV,            // field of view in degrees
		1024.0f / 768.0f, // aspect ratio
		0.01f, 100.0f     // near and far (near > 0)
	);
	projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

float Camera::getFOV() {
	return defaultFOV;
}

