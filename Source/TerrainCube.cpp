#include "../Source/includes/TerrainCube.hpp"



TerrainCube::TerrainCube()
{
}

void TerrainCube::draw()
{
	glUseProgram(shaderId);
	int heightLoc = glGetUniformLocation(shaderId, "height");
	glUniform1f(heightLoc, height);

	Model::draw();
}

TerrainCube::~TerrainCube()
{
}
