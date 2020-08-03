#include "includes/AxesModel.hpp"

/**
* This class spawns three orthonormal axes, red green and blue.
* Red : X
* Green : Y
* Blue : Z
*/
AxesModel::AxesModel() {
    glm::vec4 red = glm::vec4(1, 0, 0, 1);
    glm::vec4 green = glm::vec4(0, 1, 0, 1);
    glm::vec4 blue = glm::vec4(0, 0, 1, 1);
    glm::vec3 normal = glm::vec3(0, 0, 0);

	std::vector<Vertex> vertices = {
        Vertex(glm::vec3(0, 0, 0), red, normal, glm::vec2(0, 0)),
        Vertex(glm::vec3(5, 0, 0), red, normal, glm::vec2(0, 0)),

        Vertex(glm::vec3(0, 0, 0), green, normal, glm::vec2(0, 0)),
        Vertex(glm::vec3(0, 5, 0), green, normal, glm::vec2(0, 0)),

        Vertex(glm::vec3(0, 0, 0), blue, normal, glm::vec2(0, 0)),
        Vertex(glm::vec3(0, 0, 5), blue, normal, glm::vec2(0, 0))
    };

	*this = AxesModel(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, vertexCount);
		glLineWidth(1);
	});

    setShader(Shader::passthrough);
	setupAttribPointer();
}

AxesModel::AxesModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) {}