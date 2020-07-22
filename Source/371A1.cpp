//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hello-Triangle

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0
#include "includes/Camera.hpp"
#include "includes/WorldModel.hpp"
#include "includes/PlaneModel.hpp"
#include "includes/LoadTexture.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL#include "../Source/includes/Shader.hpp"

#include "../Source/includes/Shader.hpp"
#include "../Source/includes/SimpleModel.hpp"
#include "../Source/includes/Camera.hpp"
#include "../Source/includes/WorldModel.hpp"
#include "../Source/includes/PlaneModel.hpp"
#include "../Source/includes/LoadTexture.hpp"

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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
GLuint loadTexture(const char *filename);

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

void window_size_callback(GLFWwindow* window, int width, int height) {
	float scale = std::min(((float)width)/windowWidth, ((float)height)/windowHeight);
	float scaledWidth = windowWidth*scale;
	float scaledHeight = windowHeight*scale;
	glViewport((width - scaledWidth)/2, (height - scaledHeight)/2, scaledWidth, scaledHeight);
}

// Callbacks for keys
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, 5);
		}
	}

	// Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, -5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, 5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, -5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, 5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, -5);
		}
	}

	// Rotate World Orientation Left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		world->rotate(1, 0, 0, -5);
	}

	// Rotate World Orientation Right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		world->rotate(1, 0, 0, 5);
	}

	// Rotate World Orientation UP
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		world->rotate(0, 1, 0, 5);
	}

	// Rotate World Orientation Down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		world->rotate(0, 1, 0, -5);
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
	
	//Switch to lines rendering mode
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Switch to triangle rendering mode
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Switch to points rendering mode
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
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
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Comp371 - Assignment 1", NULL, NULL);
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

	// Load textures
	GLuint boxTextureID = loadTexture("../Assets/Textures/box.png");
	GLuint grassTextureID = loadTexture("../Assets/Textures/grass.jpg");
	GLuint goldTextureID = loadTexture("../Assets/Textures/gold.jpg");



    // Compile and link shaders here ...
	int passthroughShader = compileAndLinkShaders("../Shaders/passthrough.vshader", "../Shaders/passthrough.fshader");
	int lightAffectedShader = compileAndLinkShaders("../Shaders/phong.vshader", "../Shaders/phong.fshader");
	int textureShader = compileAndLinkShaders("../Shaders/texture.vshader", "../Shaders/texture.fshader");
	//glUseProgram(textureShader);

	//----------Camera setup----------
	camera = new Camera(windowWidth, windowHeight);
	world = new WorldModel();
	world->setCamera(camera);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, boxTextureID);

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
        // Each frame, reset color of each pixel to glClearColor and reset the depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		glfwGetCursorPos(window, &xCursor, &yCursor);

		// Draw the 100x100 square grid and axes on the ground
		world->draw();

        // End frame
        glfwSwapBuffers(window);

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


		//move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		//move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		//move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		//move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}

		//move up
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, 1, 0);
			}

		//move down
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			for (std::vector<Model*>::iterator it = world->models.begin(); it != world->models.end(); it++)
			{
				(*it)->translate(0, -1, 0);
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

GLuint loadTexture(const char *filename)
{
	// Step1 Create and bind textures
	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	assert(textureId != 0);

	glBindTexture(GL_TEXTURE_2D, textureId);

	// Step2 Set filter parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// Step3 Load Textures with dimension data
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0); //function responsible for loading the image with appropriate dimensions 
	if (!data)
	{
		std::cerr << "Error::Texture could not load texture file:" << filename << std::endl;
		return 0;
	}

	// Step4 Upload the texture to the GPU
	GLenum format = 0;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
		0, format, GL_UNSIGNED_BYTE, data);

	//If you specify mipmap behaviour you have to pregenerate the mipmaps for your image
	glGenerateMipmap(GL_TEXTURE_2D);

	// Step5 Free resources
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureId;
}