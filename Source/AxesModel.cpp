#include "includes/AxesModel.hpp"
#include <iostream>

/**
* This class spawns three orthonormal axes, red green and blue.
* Red : X
* Green : Y
* Blue : Z
*/
AxesModel::AxesModel() {
    glm::vec3 red = glm::vec3(1.0f , 0.0f, 0.0f);
    glm::vec3 green = glm::vec3(0.0f , 1.0f, 0.0f);
    glm::vec3 blue = glm::vec3(0.0f , 0.0f, 1.0f);

    glm::vec3 verticesAxes[] = {
        glm::vec3(0.0f, 0.0f, 0.0f), red,
        glm::vec3(5.0f, 0.0f, 0.0f), red,

        glm::vec3(0.0f, 0.0f, 0.0f), green,
        glm::vec3(0.0f, 5.0f, 0.0f), green,

        glm::vec3(0.0f, 0.0f, 0.0f), blue,
        glm::vec3(0.0f, 0.0f, 5.0f), blue
    };

	*this = AxesModel(verticesAxes, sizeof(verticesAxes) / sizeof(verticesAxes[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, vertexCount);
		glLineWidth(1);
	});
	setupAttribPointer();
}

AxesModel::AxesModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) 
{}