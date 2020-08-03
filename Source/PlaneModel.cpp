#include "includes/PlaneModel.hpp"

PlaneModel::PlaneModel() {
	glm::vec4 color = glm::vec4(0, 96.0/255, 25.0/255, 0.5);
    glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.f);
    
	//This plane appears slightly above other grid
	//When uv values are larger than one it gets tiled (in this case tiled 8 times in x direction and 8 times in z direction)
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(-50.5, 0, 50), color, normal, glm::vec2(0, 2)),
		Vertex(glm::vec3(50, 0, 50), color, normal, glm::vec2(2, 2)),
		Vertex(glm::vec3(50, 0, -50), color, normal, glm::vec2(2, 0)),

		Vertex(glm::vec3(50, 0, -50), color, normal, glm::vec2(2, 0)),
		Vertex(glm::vec3(-50, 0, -50), color, normal, glm::vec2(0, 0)),
		Vertex(glm::vec3(-50, 0, 50), color, normal, glm::vec2(0, 2))
	};

	*this = PlaneModel(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
		glDrawArrays(GL_TRIANGLES, 0, 6);
	});
	
	setShader(Shader::light);
	setupAttribPointer();
}

PlaneModel::PlaneModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) {}