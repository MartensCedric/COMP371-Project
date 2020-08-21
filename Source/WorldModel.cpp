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
#include <time.h>
#endif

CloudModel::CloudModel() {
	setupAttribPointer();
	srand(time(0));
	SimpleModel* cloudCenter = new UnitCubeModel();
	double cloudCenterX = rand() % (36 - 15 + 1) + 15;
	double cloudCenterZ = rand() % (42 - 18 + 1) + 18;

	cloudCenter->scale(cloudCenterX, 5, cloudCenterZ);
	cloudCenter->translate(0, 70, 0);

	SimpleModel* cloudBottom = new UnitCubeModel();
	double cloudBottomX = rand() % (12 - 5 + 1) + 5;
	double cloudBottomZ = rand() %  (16 - 8 + 1) + 8;

	cloudBottom->scale(cloudBottomX, 3, cloudBottomZ);
	cloudBottom->translate(0,55, 0);
	addChild(cloudBottom);
	addChild(cloudCenter);

};

WaterModel* plane = nullptr;
GridModel* grid = nullptr;
AxesModel* axes = nullptr;
Terrain* terrain = nullptr;

void WorldModel::setGridShader(int shaderProgram) { grid->setShader(shaderProgram); }
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

void WorldModel::setCloudsShader(int shaderProgram)
{
	for (auto it = clouds.begin(); it != clouds.end(); it++)
	{
		(*it)->setShader(shaderProgram);
	}
}

void WorldModel::generateForest()
{
	FastNoise fastNoise;
	fastNoise.SetSeed(0xdeadbeef);
	fastNoise.SetNoiseType(FastNoise::Simplex);
	int treeCount = 0;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			float noiseVal = fastNoise.GetNoise(i, j);
			float terrainHeight = terrain->heightmap[i][j];
			if (terrainHeight >= -0.175 && noiseVal > 0.75 && rand() % 24 == 0 && treeCount < 35)
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

void WorldModel::generateClouds(GLuint TextureID)
{
	for (int i = 0; i < 8; i++)
	{
		srand(i*9+3);
		double randomX = rand() % 201 + (-100);
		double randomY = rand() % 9 + (-4);
		double randomZ = rand() % 201 + (-100);
		CloudModel* cloud = new CloudModel();
		cloud->translate(randomX, 0, randomZ);
		cloud->setTexture(TextureID);
		clouds.push_back(cloud);
	}
}





void WorldModel::generateHouses()
{
	int cabinCount = 0;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			float terrainHeight = terrain->heightmap[i][j];
			if (terrainHeight >= -0.1 && rand() % 500 == 0  && cabinCount < 5)
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
	addChild(stonehenge);
	models.push_back(stonehenge);
}


WorldModel::WorldModel() {
	// Load textures
	GLuint boxTextureID = loadTexture("../Assets/Textures/box.png");
	GLuint grassTextureID = loadTexture("../Assets/Textures/grass.jpg");
	GLuint goldTextureID = loadTexture("../Assets/Textures/gold.jpg");
	GLuint cloudTextureID = loadTexture("../Assets/Textures/cloud.jpg");

	
	GLuint trunkTextureID = loadTexture("../Assets/Textures/bark.jpg");
	GLuint leavesTextureID = loadTexture("../Assets/Textures/leaves.jpg");
	GLuint rockTextureID = loadTexture("../Assets/Textures/rock.jpg");
	GLuint snowTextureID = loadTexture("../Assets/Textures/snow.jpg");


	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	grid = new GridModel();
	// addChild(grid);
	
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
	generateClouds(cloudTextureID);
	
	generateHouses();

	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}

	for (auto it = clouds.begin(); it != clouds.end(); it++)
	{
		addChild(*it);
	}
};