#pragma once
#include "SimpleModel.hpp"
#include <glm/glm.hpp>

class GridModel : public SimpleModel {
    public:
        GridModel();
		void setShader(int shaderProgram) override;
};