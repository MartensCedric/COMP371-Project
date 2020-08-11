#include "includes/WaterModel.hpp"

WaterModel::WaterModel() {
	glm::vec4 color = glm::vec4(0.52, 0.58, 0.18, 0);
    glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.f);
    
	//This plane appears slightly above other grid
	//When uv values are larger than one it gets tiled (in this case tiled 8 times in x direction and 8 times in z direction)
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(-1, 0, -1), color, normal, glm::vec2(0, 0)),
		Vertex(glm::vec3(-1, 0, 1), color, normal, glm::vec2(0, 2)),
		Vertex(glm::vec3(1, 0, -1), color, normal, glm::vec2(2, 2)),
		Vertex(glm::vec3(1, 0, 1), color, normal, glm::vec2(2, 0)),
	};


	*this = WaterModel(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
		glDrawArrays(GL_POINTS, 0, 4);
	});

	setupAttribPointer();
}


WaterModel::WaterModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera))
	: SimpleModel(vertexArray, vertexCount, drawFunc)
{}