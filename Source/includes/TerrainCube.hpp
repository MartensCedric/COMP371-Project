#pragma once
#include "UnitCubeModel.hpp"
class TerrainCube :
	public UnitCubeModel
{
public:
	float height; // [-1, 1]
	TerrainCube();
	virtual void draw() override;
	virtual ~TerrainCube();
};