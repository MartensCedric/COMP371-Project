#include "includes/GroupModel.hpp"


/**
* This class is to group some models together. Not used in PA1
*/
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