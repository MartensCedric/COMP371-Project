#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>
#include "Shader.hpp"

class AxesModel : public SimpleModel {
    public:
        AxesModel();
        AxesModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
};