//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hefllo-Triangle

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0
#include "includes/Camera.hpp"
#include "includes/WorldModel.hpp"
#include "includes/Skybox.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL#include "../Source/includes/Shader.hpp"

#include "../Source/includes/Camera.hpp"
#include "../Source/includes/WorldModel.hpp"
#include "../Source/includes/Skybox.hpp"

#endif

// Include GLEW - OpenGL Extension Wrangler
#include <GL/glew.h>    

// GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs
#include <GLFW/glfw3.h> 

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

WorldModel* world = nullptr;

double currentYPos;
double previousYPos = -1;
int randomX;
int randomY;
double currentVariation = 0;
bool leftMouseClick = false;
Camera* camera = nullptr;
int windowWidth = 1024;
int windowHeight = 768;

int maxOffset = 2;

bool showTexture = true;
bool showLight = true;
bool isLightToggled = false;
bool isTextureToggled = false;

bool hasBottomMovedForward = false;
bool hasBottomMovedBackward = false;
bool hasBottomMovedRight = false;
bool hasBottomMovedLeft = false;

bool hasTopMovedForward = false;
bool hasTopMovedBackward = false;
bool hasTopMovedRight = false;
bool hasTopMovedLeft = false;

bool hasMovedForward = false;
bool hasMovedBackward = false;
bool hasMovedRight = false;
bool hasMovedLeft = false;

bool hasTurnedRight = false;
bool hasTurnedLeft = false;

void window_size_callback(GLFWwindow* window, int width, int height) {
	float scale = std::min(((float)width)/windowWidth, ((float)height)/windowHeight);
	float scaledWidth = windowWidth*scale;
	float scaledHeight = windowHeight*scale;
	glViewport((width - scaledWidth)/2, (height - scaledHeight)/2, scaledWidth, scaledHeight);
}

bool models_sort(Model* model1, Model* model2) { 
	// Apply the Model matrix to the center of the model
	// To get its position in the World coordinates system 
	glm::vec4 new_model1_pos = model1->getModelMatrix() * glm::vec4(0, 0, 0, 1);
	glm::vec4 new_model2_pos = model2->getModelMatrix() * glm::vec4(0, 0, 0, 1);
	
	return (new_model1_pos.z < new_model2_pos.z);
}

// Callbacks for keys
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_ENTER) &&
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS &&
		!hasTurnedLeft
	) {
		hasTurnedLeft = true;
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, 5);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
		hasTurnedLeft = false;
	}

	// Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_ENTER) &&
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS &&
		!hasTurnedRight
	) {
		hasTurnedRight = true;
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, -5);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
		hasTurnedRight = false;
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, 5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, -5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, 5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, -5);
		}
	}

	// Rotate World Orientation UP
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		world->rotate(0, 1, 0, 5);

		// Sort the models according to their z position 
		// For correct blending 
		sort(world->models.begin(), world->models.end(), &models_sort);
		sort(world->children.begin(), world->children.end(), &models_sort);
	}

	// Rotate World Orientation Down
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
		glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		world->rotate(0, 1, 0, -5);

		// Sort the models according to their z position 
		// For correct blending 
		sort(world->models.begin(), world->models.end(), &models_sort);
		sort(world->children.begin(), world->children.end(), &models_sort);
	}

	if (glfwGetKey(window, GLFW_KEY_HOME)) {
		world->reset();
	}

	// Scale Up
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->scale(1.05, 1.05, 1.05);
		}
	}
	
	// Scale Down
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->scale(0.95, 0.95, 0.95);
		}
	}
	
	// Switch to lines rendering mode
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Switch to triangle rendering mode
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Switch to points rendering mode
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	// Toggle Light
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !isLightToggled) {
		isLightToggled = true;
		showLight = !showLight;
	}

	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE) {
		isLightToggled = false;
	}

	// Toggle Texture
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !isTextureToggled) {
		isTextureToggled = true;
		showTexture = !showTexture;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE) {
		isTextureToggled = false;
	}

	// ------------------------------------------------ BOTTOM HALF CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !hasBottomMovedForward)
		{
			hasBottomMovedForward = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];
				if(dZ > -1*maxOffset) {
					(*it)->translate(0, 0, -1);
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {
			hasBottomMovedForward = false;
			hasTopMovedForward = false;
			hasMovedForward = false;
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !hasBottomMovedBackward)
		{
			hasBottomMovedBackward = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];

				if(dZ < maxOffset) {
					(*it)->translate(0, 0, 1);
				}
 			}
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
			hasBottomMovedBackward = false;
			hasTopMovedBackward = false;
			hasMovedBackward = false;
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !hasBottomMovedLeft)
		{
			hasBottomMovedLeft = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX > -1*maxOffset) {
					(*it)->translate(-1, 0, 0);
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
			hasBottomMovedLeft = false;
			hasTopMovedLeft = false;
			hasMovedLeft = false;
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !hasBottomMovedRight)
		{
			hasBottomMovedRight = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX < maxOffset) {
					(*it)->translate(1, 0, 0);
				}
			}
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
			hasBottomMovedRight = false;
			hasTopMovedRight = false;
			hasMovedRight = false;
		}

		// ------------------------------------------------ TOP HALF CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !hasTopMovedForward)
		{
			hasTopMovedForward = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];
				if(dZ > -1*maxOffset) {
					(*it)->translate(0, 0, -1);
				}
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !hasTopMovedBackward)
		{
			hasTopMovedBackward = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];

				if(dZ < maxOffset) {
					(*it)->translate(0, 0, 1);
				}
 			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !hasTopMovedLeft)
		{
			hasTopMovedLeft = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX > -1*maxOffset) {
					(*it)->translate(-1, 0, 0);
				}
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !hasTopMovedRight)
		{
			hasTopMovedRight = true;
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX < maxOffset) {
					(*it)->translate(1, 0, 0);
				}
			}
		}

		// ------------------------------------------------ FULL CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !hasMovedForward)
		{
			hasMovedForward = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !hasMovedBackward)
		{
			hasMovedBackward = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !hasMovedLeft)
		{
			hasMovedLeft = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !hasMovedRight)
		{
			hasMovedRight = true;
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}
}

//The purpose of the cursorPositionCallback is to track the mouse position, determine the variation in Y position, and to set the camera's FOV based on this variation
static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) 
{
	currentYPos = yPos;

	if (previousYPos != -1) {
		currentVariation = currentYPos - previousYPos;
	}

	if (leftMouseClick == true) {
		camera->setFOV((camera->getFOV())- currentVariation/1000);
	}
}

//The purpose of the mouseButtonCallback method is to detect a left click and signal the initial y position of the cursor through the use of the cursor callback method
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		previousYPos = currentYPos;
		leftMouseClick = true;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		previousYPos = -1;
		leftMouseClick = false;
	}
}

void setWorldMatrix(int shaderProgram, glm::mat4 worldMatrix)
{
	glUseProgram(shaderProgram);
	GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}

int main(int argc, char*argv[])
{
    // Initialize GLFW and OpenGL version
    glfwInit();

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if defined(PLATFORM_OSX)	
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create Window and rendering context using GLFW
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Comp371 - Final Project", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

	new Shader();
	
	int skyboxCubeMap = loadSkybox();
	
	// Two Pass Shadow Map. Code adapted from learnopengl.com
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int shadowMapFBO;
	glGenFramebuffers(1, &shadowMapFBO);
	
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Attach it to framebuffer's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE); // We don't need color buffer
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//----------Camera setup----------
	camera = new Camera(windowWidth, windowHeight);
	world = new WorldModel();
	Skybox skybox;
	skybox.setShader(Shader::skybox);
	skybox.setCamera(camera);
	skybox.setTexture(skyboxCubeMap);
	world->setCamera(camera);

	// Variables for Tilt/Pan
	double xCursor, yCursor;
	double xPanStart = -1;
	double yTiltStart = -1;
	bool isPanning = false;
	bool isTilting = false;
	glm::vec3 panDirection = glm::vec3(1.0f);
	glm::vec3 tiltDirection = glm::vec3(1.0f);

    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window)) {

		int modelShader = Shader::passthrough;

		if (showLight && showTexture)
		{
			modelShader = Shader::textureLight;
		}
		else if (showLight)
		{
			modelShader = Shader::light;
		}
		else if (showTexture)
		{
			modelShader = Shader::texture;
		}

		glUseProgram(Shader::shadow);
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (std::vector<Model *>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->setShader(Shader::shadow);
			(*it)->draw();
		}
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
		// Each frame, reset color of each pixel to glClearColor and reset the depth-
		glViewport(0, 0, windowWidth, windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthMask(GL_FALSE);
		//skybox.draw();
		glDepthMask(GL_TRUE);

		glActiveTexture(GL_TEXTURE0);
		int shadowMapTexureLoc = glGetUniformLocation(Shader::textureLight, "shadow_map");
		glUniform1i(shadowMapTexureLoc, 0);

		int shadowMapLoc = glGetUniformLocation(Shader::light, "shadow_map");
		glUniform1i(shadowMapLoc, 0);

		glBindTexture(GL_TEXTURE_2D, depthMap);
		
		for (std::vector<Model *>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->setShader(modelShader);
		}

		for (auto it = world->spheres.begin(); it != world->spheres.end(); it++)
		{
			(*it)->setShader(showLight ? Shader::light : Shader::passthrough);
		}
	
		world->draw();

        // End frame
        glfwSwapBuffers(window);

		glfwGetCursorPos(window, &xCursor, &yCursor);
        // Detect inputs
        glfwPollEvents();

		//Handle Inputs

		//Terminate program
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			if (isPanning)
			{
				// If the mouse is paning (left/right) move the camera around the axis -Camera-up 
				double dx = xCursor - xPanStart;
				double angleDegrees = dx/10.f;
				glm::mat4 panRotation = glm::rotate(glm::mat4(1.0f), (float)glm::radians(angleDegrees), -camera->up);
				glm::vec3 newDirection(glm::normalize(panRotation * glm::vec4(panDirection, 1.0f)) * 70.0f);
				glm::vec3 newLookAt = newDirection + camera->position;
				camera->lookAtPos = newLookAt;
			}
			else {
				isPanning = true;
				xPanStart = xCursor;
				panDirection = glm::normalize(camera->lookAtPos - camera->position);
			}
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
		{
			if (isPanning)
			{
				isPanning = false;
				xPanStart = -1;
				panDirection = glm::vec3(1.0f);
			}
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
		{
			if (isTilting)
			{
				// If the mouse is tilting (up/down) move the camera around the axis LookAt-Direction X Camera-up 
				double dy = yTiltStart - yCursor;
				double angleDegrees = dy / 10.f;
				glm::mat4 tiltRotation = glm::rotate(glm::mat4(1.0f), (float)glm::radians(angleDegrees), glm::cross(tiltDirection, camera->up));

				glm::vec3 newDirection(glm::normalize(tiltRotation * glm::vec4(tiltDirection, 1.0f)) * 70.0f);
				glm::vec3 newLookAt = newDirection + camera->position;
				camera->lookAtPos = newLookAt;

			}
			else {
				isTilting = true;
				yTiltStart = yCursor;
				tiltDirection = camera->lookAtPos - camera->position;
			}
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
		{
			if (isTilting)
			{
				isTilting = false;
				yTiltStart = -1;
				tiltDirection = glm::vec3(1.0f);
			}
		}
		
		// Rotate model about left about Y
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
			!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
			!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
			!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->rotate(0, 1, 0, 5);
			}
		}

		// Rotate model about left about Y
		if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
			!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
			!glfwGetKey(window, GLFW_KEY_LEFT_ALT) &&
			!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->rotate(0, 1, 0, -5);
			}
		}

		// ------------------------------------------------ BOTTOM HALF CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];
				if(dZ > -1*maxOffset) {
					(*it)->translate(0, 0, -0.25);
				}
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];

				if(dZ < maxOffset) {
					(*it)->translate(0, 0, 0.25);
				}
 			}
		}

		// move left
		if (!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && 
			glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX > -1*maxOffset) {
					(*it)->translate(-0.25, 0, 0);
				}
			}
		}

		// move right
		if (!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && 
			glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = SimpleModel::modelsBottom.begin(); it != SimpleModel::modelsBottom.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX < maxOffset) {
					(*it)->translate(0.25, 0, 0);
				}
			}
		}

		// ------------------------------------------------ TOP HALF CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];
				if(dZ > -1*maxOffset) {
					(*it)->translate(0, 0, -0.25);
				}
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dZ = transMat[3][2];

				if(dZ < maxOffset) {
					(*it)->translate(0, 0, 0.25);
				}
 			}
		}

		// move left
		if (!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_LEFT_ALT) && 
			glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX > -1*maxOffset) {
					(*it)->translate(-0.25, 0, 0);
				}
			}
		}

		// move right
		if (!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_LEFT_ALT) && 
			glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dX = transMat[3][0];

				if(dX < maxOffset) {
					(*it)->translate(0.25, 0, 0);
				}
			}
		}

		// move up
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dY = transMat[3][1];

				if(dY < maxOffset) {
					(*it)->translate(0, 0.25, 0);
				}
			}
		}

		// move down
		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = SimpleModel::modelsTop.begin(); it != SimpleModel::modelsTop.end(); it++)
			{
				glm::mat4 transMat = (*it)->objTransMat;
				float dY = transMat[3][1];

				if(dY > 0) {
					(*it)->translate(0, -0.25, 0);
				}
			}
		}

		// ------------------------------------------------ FULL CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		// move left
		if (!glfwGetKey(window, GLFW_KEY_ENTER) &&
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && 
			glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		// move right
		if (!glfwGetKey(window, GLFW_KEY_ENTER) && 
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && 
			glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}

		//move up
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 1, 0);
			}
		}

		//move down
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, -1, 0);
			}
		}
			
		// Scale Up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->scale(1.05, 1.05, 1.05);
			}
		}
		
		// Scale Down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->scale(0.95, 0.95, 0.95);
			}
		}

		// Reposition models
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->reset();
				randomX = rand() % 51 + (-25);
				randomY = rand() % 51 + (-25);
 				(*it)->translate(randomX, 3.5, randomY);
			}
		}
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}