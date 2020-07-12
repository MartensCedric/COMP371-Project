#include "includes/GridModel.hpp"
#include <iostream>

GridModel::GridModel() {
    glm::vec3 color = glm::vec3(0.52f, 0.58f, 0.18f);
    
    glm::vec3 verticesGridUnit[] = {
		glm::vec3(-25.0f, 0, 0), color,
        glm::vec3(25.0f, 0, 0), color,

        glm::vec3(0, 0, -25.0f), color,
        glm::vec3(0, 0, 25.0f), color,
    };

    *this = GridModel(verticesGridUnit, sizeof(verticesGridUnit) / sizeof(verticesGridUnit[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");

        for (int i = 0; i < 100; i++) 
        {
			// draw rectangles in the x direction
			//glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 0, 1.0f));
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -25.0f + i));
			glm::mat4 worldMatrix = translationMatrix * objRBT;
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 0, 2);

			// draw rectangles in the z direction
			//glm::mat4 scalingMatrix1 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0, 50.0f));   //scale
			glm::mat4 translationMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f + i, 0, 0));   //translate
			//glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.5f, glm::vec3(0, 1, 0));
			glm::mat4 worldMatrix1 = translationMatrix1 * objRBT; //combine
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix1[0][0]); //send worldMatrix1 data to that memory location
			glDrawArrays(GL_LINES, 2, 2);
		}	
	});

	setupAttribPointer();
}

GridModel::GridModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) 
{}