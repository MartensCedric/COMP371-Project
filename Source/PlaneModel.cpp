#include "includes/PlaneModel.hpp"

PlaneModel::PlaneModel() {
    glm::vec4 color = glm::vec4(0, 0, 0, 0);
    
	//This plane appears slightly above other grid
	//When uv values are larger than one it gets tiled (in this case tiled 8 times in x direction and 8 times in z direction)
	std::vector<Vertex> vertices = {
		Vertex(glm::vec3(-25, 0.01, 25), color, glm::vec2(0, 2)),
		Vertex(glm::vec3(25, 0.01, 25), color, glm::vec2(2., 2)),
		Vertex(glm::vec3(25, 0.01, -25), color, glm::vec2(2, 0)),

		Vertex(glm::vec3(25, 0.01, -25), color, glm::vec2(2, 0)),
		Vertex(glm::vec3(-25, 0.01, -25), color, glm::vec2(0, 0)),
		Vertex(glm::vec3(-25, 0.01, 25), color, glm::vec2(0, 2))
	};

	SimpleModel* plane = new SimpleModel(&vertices[0], vertices.size(), [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {
		GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
		glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]); //send worldMatrix data to that memory location
		glDrawArrays(GL_TRIANGLES, 0, 6);
	});
	
	this->addChild(plane);

	setupAttribPointer();
}