#include "includes/AxesModel.hpp"

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

	std::vector<Vertex> vertices = {
        Vertex(glm::vec3(0.0f, 0.0f, 0.0f), red, glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(5.0f, 0.0f, 0.0f), red, glm::vec2(0.0f, 0.0f)),

        Vertex(glm::vec3(0.0f, 0.0f, 0.0f), green, glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.0f, 5.0f, 0.0f), green, glm::vec2(0.0f, 0.0f)),

        Vertex(glm::vec3(0.0f, 0.0f, 0.0f), blue, glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.0f, 0.0f, 5.0f), blue, glm::vec2(0.0f, 0.0f))
    };

	*this = AxesModel(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, vertexCount);
		glLineWidth(1);
	});
	setupAttribPointer();
}

AxesModel::AxesModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) {}