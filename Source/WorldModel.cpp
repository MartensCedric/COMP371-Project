#include "includes/WorldModel.hpp"
#include "../Source/includes/TreeModel.hpp"
#include "../Source/includes/Terrain.hpp"
#include "../Source/includes/CabinModel.hpp"
#include "../Source/includes/StonehengeModel.hpp"
#include <cstdlib>

#ifdef __unix__                    /* __unix__ is usually defined by compilers targeting Unix systems */

#define OS_Windows 0
#include "../ThirdParty/FastNoise.h"

#elif defined(_WIN32) || defined(WIN32)     /* _Win32 is usually defined by compilers targeting 32 or   64 bit Windows systems */

#define OS_Windows 1
#include "../FastNoise.h"
#endif


WaterModel* plane = nullptr;
AxesModel* axes = nullptr;
Terrain* terrain = nullptr;

void WorldModel::setAxesShader(int shaderProgram) { axes->setShader(shaderProgram); }
void WorldModel::setWaterShader(int shaderProgram) { plane->setShader(shaderProgram); }
void WorldModel::setTerrainShader(int shaderProgram) { terrain->setShader(shaderProgram); }

float WorldModel::getTerrainHeight(float x, float z) 
{

	int x_terrain = round(x);
	int z_terrain = round(z);

	return terrain->heightmap[x_terrain + terrain->SIZE/2][z_terrain + terrain->SIZE / 2];
}

void WorldModel::setModelShader(int shaderProgram) 
{ 
	for(auto it = models.begin(); it != models.end(); it++)
		(*it)->setShader(shaderProgram); 
}

void WorldModel::setSphereShader(int shaderProgram)
{
	for (auto it = spheres.begin(); it != spheres.end(); it++)
	{
		(*it)->setShader(shaderProgram);
	}
}

void WorldModel::generateForest()
{
	FastNoise fastNoise;
	fastNoise.SetSeed(this->parameters.seed);
	fastNoise.SetNoiseType(FastNoise::Simplex);
	int treeCount = 0;
	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			float noiseVal = fastNoise.GetNoise(i * parameters.forestSpread, j * parameters.forestSpread);
			float terrainHeight = terrain->heightmap[i][j];
			if (terrainHeight >= -0.175 && noiseVal > parameters.treeCap && rand() % parameters.forestDensity == 0 && treeCount < parameters.treeCap)
			{
				TreeModel* tree = new TreeModel();
				tree->translate(i - Terrain::SIZE / 2, terrainHeight, j - Terrain::SIZE / 2);
				tree->scale(0.5, 0.5, 0.5);
				models.push_back(tree);
				treeCount++; //not using model.size() because it would conflict with other models.
			}
		}
	}
}

void WorldModel::generateHouses()
{
	int cabinCount = 0;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			float terrainHeight = terrain->heightmap[i][j];
			if (terrainHeight >= -0.1 && rand() % 500 == 0  && cabinCount < parameters.cabinCap)
			{
				CabinModel* logcabin = new CabinModel();
				logcabin->translate(i - Terrain::SIZE / 2, terrainHeight+0.5f, j - Terrain::SIZE / 2);
				logcabin->scale(0.5, 0.5, 0.5);
				addChild(logcabin);
				models.push_back(logcabin);
				cabinCount++;
			}
		}
	}
}

void WorldModel::generateStonehenge()
{
	StonehengeModel* stonehenge = new StonehengeModel();
	models.push_back(stonehenge);
}


WorldModel::WorldModel() {

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	updateParameters();
};

void WorldModel::updateParameters()
{
	for (auto it = children.begin(); it != children.end(); it++)
		delete *it;

	this->children.clear();

	plane = new WaterModel();
	plane->translate(0, -2, 0);
	addChild(plane);

	axes = new AxesModel();
	axes->translate(0, 0.1, 0);
	addChild(axes);

	terrain = new Terrain();
	terrain->translate(-50, 0, -50);
	addChild(terrain);

	generateStonehenge();
	generateForest();
	generateHouses();

	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}
}