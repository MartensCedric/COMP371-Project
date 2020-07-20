#pragma once
#include "Model.hpp"
class NormalsModel :
	public Model
{
public:
	NormalsModel();
	NormalsModel(glm::vec3* vertices, int verticesCount, unsigned short* indices, int indicesCount, void(*drawFunc)(int indicesCount, int shaderProgram, glm::mat4 objRBT, Camera * camera));
	virtual void setupAttribPointer() override;
	virtual ~NormalsModel();
};

