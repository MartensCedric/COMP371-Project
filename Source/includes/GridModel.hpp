#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>

class GridModel : public SimpleModel {
    public:
        SimpleModel axes;
        GridModel();
        GridModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT));
        void draw();
        void setShader(int shaderProgram);
};