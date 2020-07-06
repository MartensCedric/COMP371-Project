//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 20/06/2019.
//
// Inspired by the following tutorials:
// - https://learnopengl.com/Getting-started/Hello-Window
// - https://learnopengl.com/Getting-started/Hello-Triangle

#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <glm/gtc/matrix_transform.hpp> // needed for transformation of matrices
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "includes/shader.hpp"
#include "model8.cpp"
#include "modelE.cpp"
#include "model5.cpp"
#include "axes.cpp"
#include "grid.cpp"

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

    // greyish background color
    glClearColor(0.2f, 0.29f, 0.29f, 1.0f);

    // Compile and link shaders here ...
    int shaderProgram = compileAndLinkShaders();

	glUseProgram(shaderProgram);
	
	//----------Camera setup----------

	// Camera parameters for view transform
	glm::vec3 cameraPosition(0.0f, 5.0f, 15.0f); // Where camera is positioned in 3d world
	glm::vec3 cameraLookAt(0.0f, 0.0f, -1.0f); // What position is the camera looking at in 3d world
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); // which direction is the top of the camera

	// Set projection matrix for the shader (in this case we use perspective projection)
	glm::mat4 projectionMatrix = glm::perspective(70.0f,            // field of view in degrees
												  1024.0f / 768.0f,  // aspect ratio
												  0.01f, 100.0f);   // near and far (near > 0)
	GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    
	// Set the initial view matrix     					
	glm::mat4 viewMatrix = lookAt(cameraPosition,  // eye
								  cameraLookAt ,  // center
								  cameraUp); // up
	GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

	GLfloat cameraSpeed = 0.1f; //Set camera speed

    // Define and upload geometry to the GPU here ...
    int vao = createCubeGrid();
	int axesVAO = createAxesVAO();
	int model8VAO = create8VAO();
	int modelEVAO = createEVAO();
	int model5VAO = create5VAO();

	glEnable(GL_CULL_FACE); //With this enabled (surfaces with vertices in counter clockwise direction will render)
							//Therefore the back of a surface will not render (more efficient)

	glEnable(GL_DEPTH_TEST); //With this enabled, object behind other objects will not be rendered

    // Entering Main Loop (this loop runs every frame)
    while(!glfwWindowShouldClose(window)) {
        // Each frame, reset color of each pixel to glClearColor and reset the depth
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		glUseProgram(shaderProgram); //Use shader program from compileAndLinkShaders()
		glBindVertexArray(vao); //the type of data we are using and the vbo

		drawGrid();

		glBindVertexArray(axesVAO);
		glm::mat4 identity = glm::mat4(1.0f);
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, 6);
		glLineWidth(1);

		//glBindVertexArray(model8VAO);
		//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		//glDrawArrays(GL_TRIANGLES, 0, 120);

		//glBindVertexArray(modelEVAO);
		//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		//glDrawArrays(GL_TRIANGLES, 0, 120);

		glBindVertexArray(model5VAO);
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &identity[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 120);

        // End frame
        glfwSwapBuffers(window);

        // Detect inputs
        glfwPollEvents();

		//Handle Inputs
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Terminate program
            glfwSetWindowShouldClose(window, true);
		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //move forward
			cameraPosition += cameraSpeed * cameraLookAt;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //move back
			cameraPosition -= cameraSpeed * cameraLookAt;

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //move left
			cameraPosition -= glm::normalize(glm::cross(cameraLookAt, cameraUp)) * cameraSpeed;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //move right
			cameraPosition += glm::normalize(glm::cross(cameraLookAt, cameraUp)) * cameraSpeed;

		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) //Switch to lines rendering mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) //Switch to triangle rendering mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) //Switch to points rendering mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

		// Set initial view matrix again (because this is running in the "main while loop", it will update every frame)
		glm::mat4 viewMatrix = lookAt(cameraPosition, cameraLookAt+cameraPosition,  cameraUp); 
		GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}