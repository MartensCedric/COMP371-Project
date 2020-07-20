#pragma once
#include "NormalsModel.h"
#include <glm/glm.hpp>

class UnitCubeModel : public NormalsModel {
    public:
        UnitCubeModel();
        UnitCubeModel(struct Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
};

