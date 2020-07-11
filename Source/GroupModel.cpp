#include "includes/GroupModel.hpp"

GroupModel::GroupModel() {}

void GroupModel::setupAttribPointer() {}

void GroupModel::setShader(int shaderProgram)
{
	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->shaderId = shaderProgram;
	}
};

void GroupModel::draw()
{
	for (std::vector<Model*>::iterator it = children.begin(); it != children.end(); it++)
	{
		(*it)->draw();
	}
}

GroupModel::~GroupModel() {}