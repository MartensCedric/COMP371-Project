#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>

class AxesModel : public SimpleModel {
    public:
        AxesModel();
        AxesModel(glm::vec3* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT));
};