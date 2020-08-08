#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>


class PlaneModel : public SimpleModel {
    public:
        PlaneModel();
		PlaneModel(Vertex* vertexArray, int vertexCount, void(*drawFunc)(int vertexCount, int shaderProgram, glm::mat4 objRBT, Camera* camera));
};