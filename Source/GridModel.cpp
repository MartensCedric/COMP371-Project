#include "includes/GridModel.hpp"
#include <iostream>

GridModel::GridModel() {
    glm::vec3 colorBg = glm::vec3(0.52f, 0.58f, 0.18f);
    // this color corresponds to diagonal line in the rectangle
    glm::vec3 colorDiag = glm::vec3(0.2f, 0.29f, 0.29f);

    glm::vec3 verticesGridCubes[] = {
        //left side
        glm::vec3(-0.5f,-0.5f,-0.5f), colorBg,
        glm::vec3(-0.5f,-0.5f, 0.5f), colorBg,
        glm::vec3(-0.5f, 0.5f, 0.5f), colorBg,

        glm::vec3(-0.5f,-0.5f,-0.5f), colorBg,
        glm::vec3(-0.5f, 0.5f, 0.5f), colorBg,
        glm::vec3(-0.5f, 0.5f,-0.5f), colorBg,

        // back side
        glm::vec3(0.5f, 0.5f,-0.5f),  colorBg,
        glm::vec3(-0.5f,-0.5f,-0.5f), colorBg,
        glm::vec3(-0.5f, 0.5f,-0.5f), colorBg,

        glm::vec3(0.5f, 0.5f,-0.5f),  colorBg,
        glm::vec3(0.5f,-0.5f,-0.5f),  colorBg,
        glm::vec3(-0.5f,-0.5f,-0.5f), colorBg,

        // bottom side
        glm::vec3(0.5f,-0.5f, 0.5f),  colorDiag,
        glm::vec3(-0.5f,-0.5f,-0.5f), colorDiag,
        glm::vec3(0.5f,-0.5f,-0.5f),  colorDiag,

        glm::vec3(0.5f,-0.5f, 0.5f),  colorBg,
        glm::vec3(-0.5f,-0.5f, 0.5f), colorBg,
        glm::vec3(-0.5f,-0.5f,-0.5f), colorBg,

        // front side
        glm::vec3(-0.5f, 0.5f, 0.5f), colorBg,
        glm::vec3(-0.5f,-0.5f, 0.5f), colorBg,
        glm::vec3(0.5f,-0.5f, 0.5f),  colorBg,

        glm::vec3(0.5f, 0.5f, 0.5f),  colorBg,
        glm::vec3(-0.5f, 0.5f, 0.5f), colorBg,
        glm::vec3(0.5f,-0.5f, 0.5f),  colorBg,

        // right side
        glm::vec3(0.5f, 0.5f, 0.5f),  colorBg,
        glm::vec3(0.5f,-0.5f,-0.5f),  colorBg,
        glm::vec3(0.5f, 0.5f,-0.5f),  colorBg,

        glm::vec3(0.5f,-0.5f,-0.5f),  colorBg,
        glm::vec3(0.5f, 0.5f, 0.5f),  colorBg,
        glm::vec3(0.5f,-0.5f, 0.5f),  colorBg,

        // top side
        glm::vec3(0.5f, 0.5f, 0.5f),  colorBg,
        glm::vec3(0.5f, 0.5f,-0.5f),  colorBg,
        glm::vec3(-0.5f, 0.5f,-0.5f), colorBg,

        glm::vec3(0.5f, 0.5f, 0.5f),  colorBg,
        glm::vec3(-0.5f, 0.5f,-0.5f), colorBg,
        glm::vec3(-0.5f, 0.5f, 0.5f), colorBg
    };

    *this = GridModel(verticesGridCubes, sizeof(verticesGridCubes) / sizeof(verticesGridCubes[0]), [](int vertexCount, int shaderProgram, glm::mat4 objRBT) {
		for (int i = 0; i < 100; i++) 
        {
			//draw rectangles in the x direction
			glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 0.5f));   //scale
			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0.0f, -25.0f + i * 0.5f));   //translate
			glm::mat4 worldMatrix = translationMatrix * scalingMatrix * objRBT; //combine
			GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix"); //find memory location of world matrix
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]); //send worldMatrix data to that memory location
			glDrawArrays(GL_LINES, 0, vertexCount); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)

			//draw rectangles in the z direction
			glm::mat4 scalingMatrix1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 50.0f));   //scale
			glm::mat4 translationMatrix1 = glm::translate(glm::mat4(1.0f), glm::vec3(-25.0f + i * 0.5f, 0.0f, -0.25f));   //translate
			glm::mat4 worldMatrix1 = translationMatrix1 * scalingMatrix1 * objRBT; //combine
			glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix1[0][0]); //send worldMatrix1 data to that memory location
			glDrawArrays(GL_LINES, 0, vertexCount); // 36 vertices, starting at index 0 (for some reason only "GL_LINE_LOOP" shows all lines)
		}	
	});
	setupAttribPointer();
}

GridModel::GridModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT)) 
: SimpleModel(vertexArray, vertexCount, drawFunc) 
{}