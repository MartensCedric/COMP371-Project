#include "includes/UnitCubeModel.hpp"

/**
* A subclass for an easy implementation of a 1x1x1 unit cube.
*/
UnitCubeModel::UnitCubeModel() {
    glm::vec3 color = glm::vec3(1, 0, 1);

    vertices = {
        // Front face
        glm::vec3(-0.5f, -0.5f, 0.5f), color,
        glm::vec3(0.5f, -0.5f, 0.5f), color,
        glm::vec3(0.5f, 0.5f, 0.5f), color,
        glm::vec3(-0.5f, 0.5f, 0.5f), color,

        // Back face
        glm::vec3(-0.5f, -0.5f, -0.5f), color,
        glm::vec3(0.5f, -0.5f, -0.5f), color,
        glm::vec3(0.5f, 0.5f, -0.5f), color,
        glm::vec3(-0.5f, 0.5f, -0.5f), color
    };
 
    indices = {
        // Front face
        0, 1, 2,
        0, 2, 3,

        // Back face
        4, 6, 5,
        4, 7, 6,

        // Left face
        4, 0, 7,
        0, 3, 7,

        // Right face
        5, 6, 1,
        1, 6, 2,

        // Top face
        7, 3, 2,
        2, 6, 7,

        // Bottom face
        4, 1, 0,
        1, 4, 5
    };
    
    *this = UnitCubeModel(
        &vertices[0],
        vertices.size(), 
        &indices[0], 
        indices.size(),
        [](int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera* camera) {

			glm::vec3 spotlightPosition(0.0f, 5.0f, 6.0f);
			GLuint spotlightPositionLocation = glGetUniformLocation(shaderProgram, "lightPosition");
			glUniform3fv(spotlightPositionLocation, 1, &spotlightPosition[0]);

			glm::vec3 ambientColor(1.0f, 0.843f, 0.0f);
			GLuint ambientColorLocation = glGetUniformLocation(shaderProgram, "ambientColor");
			glUniform3fv(ambientColorLocation, 1, &ambientColor[0]);

			glm::vec3 eyePosition = camera->position;
			GLuint eyePositionLocation = glGetUniformLocation(shaderProgram, "eyePosition");
			glUniform3fv(eyePositionLocation, 1, &eyePosition[0]);
            
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &objRBT[0][0]);
            glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, 0);
        }
    );
    setupAttribPointer();
}

UnitCubeModel::UnitCubeModel(glm::vec3* vertices, int verticesCount, unsigned short* indices, int indicesCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera)) 
: SimpleModel(vertices, verticesCount, indices, indicesCount, drawFunc) 
{}
