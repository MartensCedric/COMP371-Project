#include "includes/UnitCubeModel.hpp"

/**
* A subclass for an easy implementation of a 1x1x1 unit cube.
*/
UnitCubeModel::UnitCubeModel() {
    glm::vec4 color = glm::vec4(0.5, 0.5, 0.5, 1);
    
    std::vector<Vertex> vertices = {
        // Front face
        Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(1.0f, 1.0f)),

        Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), color, glm::vec3(0, 0, 1), glm::vec2(0.0f, 1.0f)), 

        // Back face
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(1.0f, 0.0f)),

        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(0, 0, -1), glm::vec2(1.0f, 1.0f)), 

        // Left face
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(1.0f, 0.0f)),

        Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(-1, 0, 0), glm::vec2(1.0f, 0.0f)),

        // Right face
        Vertex(glm::vec3(0.5f, -0.5f, -0.5f), color, glm::vec3(1, 0, 0), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(1, 0, 0), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(1, 0, 0), glm::vec2(0.0f, 1.0f)),

        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(1, 0, 0), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(1, 0, 0), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(1, 0, 0), glm::vec2(1.0f, 1.0f)), 

        // Top face
        Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(0, 1, 0), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), color, glm::vec3(0, 1, 0), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 1, 0), glm::vec2(1.0f, 1.0f)),

        Vertex(glm::vec3(0.5f, 0.5f, 0.5f), color, glm::vec3(0, 1, 0), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(0.5f, 0.5f, -0.5f), color, glm::vec3(0, 1, 0), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), color, glm::vec3(0, 1, 0), glm::vec2(0.0f, 0.0f)),

        // Bottom face
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(0, -1, 0), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(0, -1, 0), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), color, glm::vec3(0, -1, 0), glm::vec2(0.0f, 1.0f)),

        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), color, glm::vec3(0, -1, 0), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), color, glm::vec3(0, -1, 0), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, -0.5f), color, glm::vec3(0, -1, 0), glm::vec2(1.0f, 0.0f))
    };

    *this = UnitCubeModel(
        &vertices[0], 
        vertices.size(), 
        [](int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {

			glm::vec3 eyePosition = camera->position;
			GLuint eyePositionLocation = glGetUniformLocation(shaderProgram, "eyePosition");
			glUniform3fv(eyePositionLocation, 1, &eyePosition[0]);
			
            GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);


        
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
	}
    );
    setupAttribPointer();
}

UnitCubeModel::UnitCubeModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) 
{}
