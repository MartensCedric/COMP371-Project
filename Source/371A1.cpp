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
#include "includes/Shader.hpp"
#include "includes/SimpleModel.hpp"
#include "includes/Camera.hpp"
#include "includes/GridModel.hpp"
#include "includes/AxesModel.hpp"
#include "includes/UnitCubeModel.hpp"
#include "includes/GroupModel.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL#include "../Source/includes/Shader.hpp"

#include "../Source/includes/Shader.hpp"
#include "../Source/includes/SimpleModel.hpp"
#include "../Source/includes/Camera.hpp"
#include "../Source/includes/GridModel.hpp"
#include "../Source/includes/AxesModel.hpp"
#include "../Source/includes/UnitCubeModel.hpp"
#include "../Source/includes/GroupModel.hpp"

#endif

#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
// initializing OpenGL and binding inputs

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

SimpleModel world;
std::vector<Model*> models;
std::vector<Model*> modelsBottom;
std::vector<Model*> modelsTop;

double currentYPos;
double previousYPos = -1;
double currentVariation = 0;
bool leftMouseClick = false;
Camera* camera = nullptr;

// Callbacks for keys
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, 5);
		}
	}

	// Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, -5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, 5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, -5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, 5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) &&
		!glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) &&
		!glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) &&
		glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, -5);
		}
	}

	// Rotate World Orientation Left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		world.rotate(1, 0, 0, -5);
	}

	// Rotate World Orientation Right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		world.rotate(1, 0, 0, 5);
	}

	// Rotate World Orientation UP
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		world.rotate(0, 1, 0, 5);
	}

	// Rotate World Orientation Down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		world.rotate(0, 1, 0, -5);
	}

	if (glfwGetKey(window, GLFW_KEY_HOME)) {
		world.reset();
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
static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
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


int main(int argc, char*argv[])
{
    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // Create Window and rendering context using GLFW
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Comp371 - Assignment 1", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Compile and link shaders here ...
	int passthroughShader = compileAndLinkShaders("../Shaders/passthrough.vshader", "../Shaders/passthrough.fshader");
	int lightAffectedShader = compileAndLinkShaders("../Shaders/phong.vshader", "../Shaders/phong.fshader");
	glUseProgram(passthroughShader);

	//----------Camera setup----------
	camera = new Camera();
	
    // Define and upload geometry to the GPU here ...
	GridModel grid;
	grid.setShader(passthroughShader);
	world.addChild(&grid);
	
	AxesModel axes;
	axes.setShader(passthroughShader);
	world.addChild(&axes);

	// Alpha numerical models
	// Splitting each model in two: 2/3 assigned to the bottom, the remainder 1/3 to the top
	SimpleModel E5top, E5bottom, I31, I32, T5, D8;

	// Draw an E
	// split top/bot divisions
	SimpleModel eTopDiv, eBottomDiv;
	eTopDiv.setupAttribPointer();
	eBottomDiv.setupAttribPointer();

	UnitCubeModel eLeftTop;
	eLeftTop.scale(1, 3, 1);
	eLeftTop.translate(0, 2, 0);

	UnitCubeModel eLeftBottom;
	eLeftBottom.scale(1, 3, 1);
	eLeftBottom.translate(0, -2, 0);

	UnitCubeModel eTop;
	eTop.scale(3, 1, 1);
	eTop.translate(1, 3, 0);

	UnitCubeModel eMiddle;
	eMiddle.scale(3, 1, 1);
	eMiddle.translate(1, 0, 0);
	
	UnitCubeModel eBottom;
	eBottom.scale(3, 1, 1);
	eBottom.translate(1, -3, 0);

	eTopDiv.addChild(&eLeftTop);
	eTopDiv.addChild(&eTop);
	eBottomDiv.addChild(&eLeftBottom);
	eBottomDiv.addChild(&eMiddle);
	eBottomDiv.addChild(&eBottom);

	eTopDiv.translate(-3.5, 0, 0);
	eBottomDiv.translate(-3.5, 0, 0);

	modelsTop.push_back(&eTopDiv);
	modelsBottom.push_back(&eBottomDiv);

	// Draw a 5
	///*
	SimpleModel fiveTopDiv, fiveBottomDiv;
	fiveTopDiv.setupAttribPointer();
	fiveBottomDiv.setupAttribPointer();

	UnitCubeModel fiveLeft;
	fiveLeft.scale(1, 2.5, 1);
	fiveLeft.translate(0, 1.25, 0);

	UnitCubeModel fiveRight;
	fiveRight.scale(1, 2.5, 1);
	fiveRight.translate(2, -1.25, 0);

	UnitCubeModel fiveTop;
	fiveTop.scale(3, 1, 1);
	fiveTop.translate(1, 3, 0);

	UnitCubeModel fiveMiddle;
	fiveMiddle.scale(3, 1, 1);
	fiveMiddle.translate(1, 0, 0);
	
	UnitCubeModel fiveBottom;
	fiveBottom.scale(3, 1, 1);
	fiveBottom.translate(1, -3, 0);

	fiveTopDiv.addChild(&fiveLeft);
	fiveBottomDiv.addChild(&fiveRight);
	fiveTopDiv.addChild(&fiveTop);
	fiveBottomDiv.addChild(&fiveMiddle);
	fiveBottomDiv.addChild(&fiveBottom);

	fiveTopDiv.translate(1.5, 0, 0);
	fiveBottomDiv.translate(1.5, 0, 0);

	modelsTop.push_back(&fiveTopDiv);
	modelsBottom.push_back(&fiveBottomDiv);


	// First I3
	//Draw an I
	SimpleModel I;
	I.setupAttribPointer();
	I.translate(-2, 0, 0);

	UnitCubeModel iTop;
	iTop.scale(2, 1, 1);
	iTop.translate(0, 3, 0);

	UnitCubeModel iMiddle;
	iMiddle.scale(1, 5, 1);
	iMiddle.translate(0, 0, 0);

	UnitCubeModel iBottom;
	iBottom.scale(2, 1, 1);
	iBottom.translate(0, -3, 0);

	I.addChild(&iTop);
	I.addChild(&iMiddle);
	I.addChild(&iBottom);

	I31.addChild(&I);

	//Draw a 3
	SimpleModel three;
	three.setupAttribPointer();

	UnitCubeModel threeRight;
	threeRight.scale(1, 5, 1);
	threeRight.translate(2, 0, 0);

	UnitCubeModel threeTop;
	threeTop.scale(3, 1, 1);
	threeTop.translate(1, 3, 0);

	UnitCubeModel threeMiddle;
	threeMiddle.scale(3, 1, 1);
	threeMiddle.translate(1, 0, 0);

	UnitCubeModel threeBottom;
	threeBottom.scale(3, 1, 1);
	threeBottom.translate(1, -3, 0);

	three.addChild(&threeRight);
	three.addChild(&threeTop);
	three.addChild(&threeMiddle);
	three.addChild(&threeBottom);
	three.translate(2, 0, 0);

	I31.addChild(&three);
	I31.translate(25, 3.5, -25);

	models.push_back(&I31);

	//Second I3
	//Draw an I
	SimpleModel I2;
	I2.setupAttribPointer();
	I2.translate(-2, 0, 0);

	UnitCubeModel iTop2;
	iTop2.scale(2, 1, 1);
	iTop2.translate(0, 3, 0);

	UnitCubeModel iMiddle2;
	iMiddle2.scale(1, 5, 1);
	iMiddle2.translate(0, 0, 0);

	UnitCubeModel iBottom2;
	iBottom2.scale(2, 1, 1);
	iBottom2.translate(0, -3, 0);

	I2.addChild(&iTop2);
	I2.addChild(&iMiddle2);
	I2.addChild(&iBottom2);

	I32.addChild(&I2);

	//Draw a 3
	SimpleModel three2;
	three2.setupAttribPointer();

	UnitCubeModel threeRight2;
	threeRight2.scale(1, 5, 1);
	threeRight2.translate(2, 0, 0);

	UnitCubeModel threeTop2;
	threeTop2.scale(3, 1, 1);
	threeTop2.translate(1, 3, 0);

	UnitCubeModel threeMiddle2;
	threeMiddle2.scale(3, 1, 1);
	threeMiddle2.translate(1, 0, 0);

	UnitCubeModel threeBottom2;
	threeBottom2.scale(3, 1, 1);
	threeBottom2.translate(1, -3, 0);

	three2.addChild(&threeRight2);
	three2.addChild(&threeTop2);
	three2.addChild(&threeMiddle2);
	three2.addChild(&threeBottom2);

	three2.translate(2, 0, 0);

	I32.addChild(&three2);
	I32.translate(25, 3.5, 25);
	I32.rotate(0, 0, 1, 180.0f);

	models.push_back(&I32);

	//Draw a D
	SimpleModel D;
	D.setupAttribPointer();


	UnitCubeModel dLeft;
	dLeft.scale(1, 7.1, 1);

	UnitCubeModel dRight;
	dRight.scale(1, 5.5, 1);
	dRight.translate(2.3, 0, 0);

	UnitCubeModel dTop;
	dTop.scale(3, 1, 1);
	dTop.translate(1.2, 2.83, 0);
	dTop.rotate(0, 0, 1, -11);


	UnitCubeModel dBottom;
	dBottom.scale(3, 1, 1);
	dBottom.translate(1.2, -2.83, 0);
	dBottom.rotate(0, 0, 1, 11);

	D.addChild(&dLeft);
	D.addChild(&dTop);
	D.addChild(&dBottom);
	D.addChild(&dRight);


	D.translate(-3.5, 0, 0);
	D8.addChild(&D);

	// Draw a 8
	SimpleModel eight;
	eight.setupAttribPointer();

	UnitCubeModel eightRight;
	eightRight.scale(1, 5, 1);
	eightRight.translate(2, 0, 0);

	UnitCubeModel eightLeft;
	eightLeft.scale(1, 5, 1);
	eightLeft.translate(0, 0, 0);

	UnitCubeModel eightTop;
	eightTop.scale(3, 1, 1);
	eightTop.translate(1, 3, 0);

	UnitCubeModel eightMiddle;
	eightMiddle.scale(3, 1, 1);
	eightMiddle.translate(1, 0, 0);

	UnitCubeModel eightBottom;
	eightBottom.scale(3, 1, 1);
	eightBottom.translate(1, -3, 0);

	eight.addChild(&eightLeft);
	eight.addChild(&eightRight);
	eight.addChild(&eightTop);
	eight.addChild(&eightMiddle);
	eight.addChild(&eightBottom);

	eight.translate(1.5, 0, 0);

	D8.addChild(&eight);
	D8.translate(-25, 3.5, 25);
	D8.rotate(0, 1, 0, 175);
	models.push_back(&D8);

	//Draw a T
	SimpleModel T;
	T.setupAttribPointer();
	T.translate(-2, 0, 0);

	UnitCubeModel tTop;
	tTop.scale(4, 1, 1);
	tTop.translate(0, 3, 0);

	UnitCubeModel tMiddle;
	tMiddle.scale(1, 5, 1);
	tMiddle.translate(0, 0, 0);

	UnitCubeModel tBottom;
	tBottom.scale(1, 1, 1);
	tBottom.translate(0, -3, 0);

	T.addChild(&tTop);
	T.addChild(&tMiddle);
	T.addChild(&tBottom);

	T5.addChild(&T);
	
	// Draw a 5
	SimpleModel tFive;
	tFive.setupAttribPointer();
	tFive.translate(2, 0, 0);

	UnitCubeModel tFiveLeft;
	tFiveLeft.scale(1, 2.5, 1);
	tFiveLeft.translate(0, 1.25, 0);

	UnitCubeModel tFiveRight;
	tFiveRight.scale(1, 2.5, 1);
	tFiveRight.translate(2, -1.25, 0);

	UnitCubeModel tFiveTop;
	tFiveTop.scale(3, 1, 1);
	tFiveTop.translate(1, 3, 0);

	UnitCubeModel tFiveMiddle;
	tFiveMiddle.scale(3, 1, 1);
	tFiveMiddle.translate(1, 0, 0);

	UnitCubeModel tFiveBottom;
	tFiveBottom.scale(3, 1, 1);
	tFiveBottom.translate(1, -3, 0);

	tFive.addChild(&tFiveLeft);
	tFive.addChild(&tFiveRight);
	tFive.addChild(&tFiveTop);
	tFive.addChild(&tFiveMiddle);
	tFive.addChild(&tFiveBottom);

	T5.addChild(&tFive);
	T5.translate(-25, 3.5, -25);
	
	models.push_back(&T5);

	//----------Models----------
	for (auto it = models.begin(); it != models.end(); it++)
	{
		world.addChild(*it);
		(*it)->setShader(lightAffectedShader);
	}

	for (auto it = modelsBottom.begin(); it != modelsBottom.end(); it++)
	{
		world.addChild(*it);
		(*it)->setShader(lightAffectedShader);
	}
	 
	for (auto it = modelsTop.begin(); it != modelsTop.end(); it++)
	{
		world.addChild(*it);
		(*it)->setShader(lightAffectedShader);
	}

	world.setCamera(camera);

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
		world.draw();

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

		// ------------------------------------------------ BOTTOM HALF CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsBottom.begin(); it != modelsBottom.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsBottom.begin(); it != modelsBottom.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsBottom.begin(); it != modelsBottom.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsBottom.begin(); it != modelsBottom.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}

		// move up
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsBottom.begin(); it != modelsBottom.end(); it++)
			{
				(*it)->translate(0, 1, 0);
			}
		}

		// move down
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsBottom.begin(); it != modelsBottom.end(); it++)
			{
				(*it)->translate(0, -1, 0);
			}
		}

		// ------------------------------------------------ TOP HALF CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsTop.begin(); it != modelsTop.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsTop.begin(); it != modelsTop.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsTop.begin(); it != modelsTop.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsTop.begin(); it != modelsTop.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}

		// move up
		if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsTop.begin(); it != modelsTop.end(); it++)
			{
				(*it)->translate(0, 1, 0);
			}
		}

		// move down
		if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = modelsTop.begin(); it != modelsTop.end(); it++)
			{
				(*it)->translate(0, -1, 0);
			}
		}

		// ------------------------------------------------ FULL CONTROLS -------------------------------------------------

		// move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		// move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		// move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		// move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}

		// move up
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, 1, 0);
			}
		}

		// move down
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, -1, 0);
			}
		}
			
		// Scale Up
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->scale(1.05, 1.05, 1.05);
			}
		}
		
		// Scale Down
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->scale(0.95, 0.95, 0.95);
			}
		}
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}