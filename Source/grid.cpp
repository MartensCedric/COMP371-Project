#define GLEW_STATIC 1   // This allows linking with Static Library on Windows, without DLL
#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler

#include <GLFW/glfw3.h> // GLFW provides a cross-platform interface for creating a graphical context,
                        // initializing OpenGL and binding inputs

#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language

#include "includes/shader.hpp"

int createCubeGrid()
{
    // Upload geometry to GPU and return the Vertex Buffer Object ID

	glm::vec3 vertexArray[] = {
		// Cube model
		
		// position, color

		//left side
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f), 
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f), 
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),

		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f), 
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),

		// back side
		glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),

		glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f), 
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f), 
		
		// bottom side
		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.2f, 0.29f, 0.29f),
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.2f, 0.29f, 0.29f), // this color corresponds to diagonal line in the rectangle
		glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.2f, 0.29f, 0.29f),

		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
		
		// front side
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f), 
		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),

		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		
		// right side
		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),

		glm::vec3(0.5f,-0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		
		// top side
		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(0.5f, 0.5f,-0.5f),  glm::vec3(0.52f , 0.58f, 0.18f), 
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),

		glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec3(0.52f , 0.58f, 0.18f),
		glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.52f , 0.58f, 0.18f)
	};

	// Create a vertex array
	GLuint vertexArrayObject;   // Create a VAO 
	glGenVertexArrays(1, &vertexArrayObject); // Create array in memory for our object, parameters:(# of arrays, memory location)
	glBindVertexArray(vertexArrayObject);  // Tell openGL to use this VAO until I decide to change it (openGL is state machine)

	// Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
	GLuint vertexBufferObject;  // Create a VBO (VBO's connect to a single VAO)
	glGenBuffers(1, &vertexBufferObject); 
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);  
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,                     // attribute 0 matches aPos in Vertex Shader
		3,                     // size
		GL_FLOAT,              // type
		GL_FALSE,              // normalized?
		2 * sizeof(glm::vec3), // stride - each vertex contain 2 vec3 (position, color)
		(void*)0               // array buffer offset (how far from the start it starts)
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,                       // attribute 1 matches aColor in Vertex Shader
		3,
		GL_FLOAT,
		GL_FALSE,
		2 * sizeof(glm::vec3),
		(void*)sizeof(glm::vec3) // color is offseted a vec3 (comes after position)
	);
	glEnableVertexAttribArray(1);

	return vertexArrayObject;
}

void drawGrid() {
    // Compile and link shaders here ...
    int shaderProgram = compileAndLinkShaders();

    // Draw the 100x100 square grid on the ground
    for (int i = 0; i < 100; i++)
    {
        //draw rectangles in the x direction
        glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 0.5f));   //scale
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0.0f, -25.0f + i * 0.5f));   //translate
        glm::mat4 worldMatrix = translationMatrix * scalingMatrix; //combine
        GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]); //send worldMatrix data to that memory location
        glDrawArrays(GL_LINES, 0, 36); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)

        //draw rectangles in the z direction
        glm::mat4 scalingMatrix1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 50.0f));   //scale
        glm::mat4 translationMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f + i * 0.5f, 0.0f, -0.25f));   //translate
        glm::mat4 worldMatrix1 = translationMatrix1 * scalingMatrix1; //combine
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix1[0][0]); //send worldMatrix1 data to that memory location
        glDrawArrays(GL_LINES, 0, 36); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)
    }
}