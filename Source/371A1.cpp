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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, 5);
		}
	}

	// Rotate model about left about Y
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 1, 0, -5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, 5);
		}
	}

	// Rotate model about left about X
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(1, 0, 0, -5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, 5);
		}
	}

	// Rotate model about left about Z
	if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->rotate(0, 0, 1, -5);
		}
	}

	// Rotate World Orientation Left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		world.rotate(0, 0, 1, -5);
	}

	// Rotate World Orientation Right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		world.rotate(0, 0, 1, 5);
	}

	// Rotate World Orientation UP
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		world.rotate(1, 0, 0, -5);
	}

	// Rotate World Orientation Down
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		world.rotate(1, 0, 0, 5);
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
    int shaderProgram = compileAndLinkShaders();
	glUseProgram(shaderProgram);

	//----------Camera setup----------
	Camera camera(shaderProgram);
	
    // Define and upload geometry to the GPU here ...
	GridModel grid;
	grid.setShader(shaderProgram);
	world.addChild(&grid);
	
	AxesModel axes;
	axes.setShader(shaderProgram);
	world.addChild(&axes);

	SimpleModel E5;

	// Draw an E
	SimpleModel E;
	E.setupAttribPointer();

	UnitCubeModel eLeft;
	eLeft.scale(1, 5, 1);
	eLeft.translate(0, 0, 0);

	UnitCubeModel eTop;
	eTop.scale(3, 1, 1);
	eTop.translate(1, 3, 0);

	UnitCubeModel eMiddle;
	eMiddle.scale(3, 1, 1);
	eMiddle.translate(1, 0, 0);
	
	UnitCubeModel eBottom;
	eBottom.scale(3, 1, 1);
	eBottom.translate(1, -3, 0);

	E.addChild(&eLeft);
	E.addChild(&eTop);
	E.addChild(&eMiddle);
	E.addChild(&eBottom);

	E.setShader(shaderProgram);

	E.translate(-3.5, 3.5, 0);
	E5.addChild(&E);

	// Draw a 5
	SimpleModel five;
	five.setupAttribPointer();

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

	five.addChild(&fiveLeft);
	five.addChild(&fiveRight);
	five.addChild(&fiveTop);
	five.addChild(&fiveMiddle);
	five.addChild(&fiveBottom);

	five.setShader(shaderProgram);
	five.translate(1.5, 3.5, 0);
	
	E5.addChild(&five);

	models.push_back(&E5);

	//----------Models----------
	for (auto it = models.begin(); it != models.end(); it++)
	{
		world.addChild(*it);
	}

	SimpleModel I3;

	//Draw an I
	SimpleModel I;
	I.setupAttribPointer();

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

	I.setShader(shaderProgram);
	I.translate(17, 3.5, -25);
	I3.addChild(&I);

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

	three.setShader(shaderProgram);
	three.translate(21, 3.5, -25);

	I3.addChild(&three);

	models.push_back(&I3);
	    
    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window)) {
        // Each frame, reset color of each pixel to glClearColor and reset the depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

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
		
		//move forward
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, 0, -1);
			}
		}

		//move back
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, 0, 1);
			}
		}

		//move left
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(-1, 0, 0);
			}
		}

		//move right
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(1, 0, 0);
			}
		}

		//move up
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, 1, 0);
			}

		//move down
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
			{
				(*it)->translate(0, -1, 0);
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

		//Temporary camera controls for modeling purposes
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) //move forward
			camera.moveForward();

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) //move back
			camera.moveBack();

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) //move left
			camera.moveLeft();

		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) //move right
			camera.moveRight();

		// Set initial view matrix again (because this is running in the "main while loop", it will update every frame)
		camera.reset();
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}