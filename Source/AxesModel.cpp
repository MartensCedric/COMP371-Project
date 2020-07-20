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

    vertices = {
        glm::vec3(0.0f, 0.0f, 0.0f), red,
        glm::vec3(5.0f, 0.0f, 0.0f), red,

        glm::vec3(0.0f, 0.0f, 0.0f), green,
        glm::vec3(0.0f, 5.0f, 0.0f), green,

        glm::vec3(0.0f, 0.0f, 0.0f), blue,
        glm::vec3(0.0f, 0.0f, 5.0f), blue
    };

    indices = {
        0, 1,
        2, 3,
        4, 5
    };

	*this = AxesModel(&vertices[0], vertices.size(), &indices[0], indices.size(), [](int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
		glLineWidth(3);
		glDrawElements(GL_LINES, indicesCount, GL_UNSIGNED_SHORT, 0);
		glLineWidth(1);
	});
	setupAttribPointer();
}

AxesModel::AxesModel(glm::vec3* vertices, int verticesCount, unsigned short* indices, int indicesCount, void(*drawFunc)(int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertices, verticesCount, indices, indicesCount, drawFunc) 
{}