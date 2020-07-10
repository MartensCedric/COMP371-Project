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
#include "includes/UnitCubeModel.hpp"
#include "includes/GroupModel.hpp"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL#include "../Source/includes/Shader.hpp"

#include "../Source/includes/Shader.hpp"
#include "../Source/includes/SimpleModel.hpp"
#include "../Source/includes/Camera.hpp"
#include "../Source/includes/GridModel.hpp"
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

	//----------Models----------
	std::vector<Model*> models;
	
	// Draw an E
	// Empty parent
	SimpleModel e;
	e.setupAttribPointer();


	UnitCubeModel eLeft;
	eLeft.scale(0.5, 2.5, 0.5);
	eLeft.translate(0, 0, 0);

	UnitCubeModel eTop;
	eTop.scale(1.5, 0.5, 0.5);
	eTop.translate(1, 3, 0);

	UnitCubeModel eMiddle;
	eMiddle.scale(1.5, 0.5, 0.5);
	eMiddle.translate(1, 0, 0);

	
	UnitCubeModel eBottom;
	eBottom.scale(1.5, 0.5, 0.5);
	eBottom.translate(1, -3, 0);

	e.addChild(&eLeft);
	e.addChild(&eTop);
	e.addChild(&eMiddle);
	e.addChild(&eBottom);

	e.setShader(shaderProgram);
	
	models.push_back(&e);
	
    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window)) {
        // Each frame, reset color of each pixel to glClearColor and reset the depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		// Draw the 100x100 square grid and axes on the ground
		grid.draw();
		
		for (std::vector<Model*>::iterator it = models.begin(); it != models.end(); it++)
		{
			(*it)->setShader(shaderProgram);
			(*it)->draw();
		}

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
			
		//Switch to lines rendering mode
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) 
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//Switch to triangle rendering mode
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) 
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Switch to points rendering mode
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) 
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

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

		// Set initial view matrix again (because this is running in the "main while loop", it will update every frame)
		camera.reset();
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}