#include "includes/WorldModel.hpp"
#include "includes/ConeModel.hpp"
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
	cloudCenter->translate(0, 23, 0);

	SimpleModel* cloudBottom = new UnitCubeModel();
	double cloudBottomX = rand() % (12 - 5 + 1) + 5;
	double cloudBottomZ = rand() %  (16 - 8 + 1) + 8;

	cloudBottom->scale(cloudBottomX, 3, cloudBottomZ);
	cloudBottom->translate(0,18, 0);
	addChild(cloudBottom);
	addChild(cloudCenter);

};

// NOTE: "left" and "right" are from the perspective of the viewer looking at a penguin directly facing them
PenguinModel::PenguinModel() {
	setupAttribPointer();

	// Load textures
	GLuint whiteFurTextureID = loadTexture("../Assets/Textures/penguin-white-fur.png");
	GLuint whiteScleraTextureID = loadTexture("../Assets/Textures/pearl-white.jpg");
	GLuint orangeTextureID = loadTexture("../Assets/Textures/penguin-orange.jpg");
	GLuint blackFurTextureID = loadTexture("../Assets/Textures/penguin-black-fur.jpg");
	GLuint blackPupilTextureID = loadTexture("../Assets/Textures/pitch-black.png");

	SimpleModel* leftFoot = new UnitCubeModel();
	SimpleModel* leftLeg = new UnitCubeModel();
	SimpleModel* rightFoot = new UnitCubeModel();
	SimpleModel* rightLeg = new UnitCubeModel();
	SimpleModel* back = new UnitCubeModel();
	SimpleModel* belly = new UnitCubeModel();
	SimpleModel* leftWing = new UnitCubeModel();
	SimpleModel* rightWing = new UnitCubeModel();
	SimpleModel* head = new UnitCubeModel();
	//@TODO: use Cedrics epic cone model instead of unit cube
	//this->beak = new ConeModel(glm::vec4(1, 1, 0, 1));
	SimpleModel* beak = new UnitCubeModel();
	SimpleModel* leftEyeSclera = new UnitCubeModel();
	SimpleModel* rightEyeSclera = new UnitCubeModel();
	SimpleModel* leftEyePupil = new UnitCubeModel();
	SimpleModel* rightEyePupil = new UnitCubeModel();

	back->scale(3, 3, 1);
	back->translate(0, 2, 0);
	back->setTexture(blackFurTextureID);
	belly->scale(3, 3, 0.75);
	belly->translate(0, 2, 0.9);
	belly->setTexture(whiteFurTextureID);

	leftLeg->scale(0.3, 1, 0.3);
	rightLeg->scale(0.3, 1, 0.3);
	leftLeg->translate(-0.65, 0.3, 0.4);
	rightLeg->translate(0.65, 0.3, 0.4);
	leftLeg->setTexture(orangeTextureID);
	rightLeg->setTexture(orangeTextureID);

	leftFoot->scale(0.9, 0.5, 1.2);
	rightFoot->scale(0.9, 0.5, 1.2);
	leftFoot->translate(-0.65, 0, 0.6);
	rightFoot->translate(0.65, 0, 0.6);
	leftFoot->setTexture(orangeTextureID);
	rightFoot->setTexture(orangeTextureID);
	
	leftWing->scale(0.5, 2, 1.2);
	leftWing->translate(-1.5, 2, 0.4);
	leftWing->setTexture(blackFurTextureID);
	rightWing->scale(0.5, 2, 1.2);
	rightWing->translate(1.5, 2, 0.4);
	rightWing->setTexture(blackFurTextureID);
	
	head->scale(1.5, 1.5, 1);
	head->translate(0, 4.25, 0.3); // z=0.5 will center it
	head->setTexture(blackFurTextureID);
	
	leftEyeSclera->scale(0.3, 0.3, 0.3);
	rightEyeSclera->scale(0.3, 0.3, 0.3);
	leftEyeSclera->translate(-0.5, 4.25, 0.7);
	rightEyeSclera->translate(0.5, 4.25, 0.7);
	leftEyeSclera->setTexture(whiteScleraTextureID);
	rightEyeSclera->setTexture(whiteScleraTextureID);
	leftEyePupil->scale(0.2, 0.2, 0.2);
	rightEyePupil->scale(0.2, 0.2, 0.2);
	leftEyePupil->translate(-0.5, 4.25, 0.8);
	rightEyePupil->translate(0.5, 4.25, 0.8);
	leftEyePupil->setTexture(blackPupilTextureID);
	rightEyePupil->setTexture(blackPupilTextureID);

	beak->scale(0.2, 0.2, 0.7);
	beak->translate(0, 4, 0.9);
	beak->setTexture(orangeTextureID);

	addChild(back);
	addChild(belly);
	addChild(leftFoot);
	addChild(rightFoot);
	addChild(leftLeg);
	addChild(leftWing);
	addChild(rightLeg);
	addChild(rightWing);
	addChild(head);
	addChild(leftEyeSclera);
	addChild(leftEyePupil);
	addChild(rightEyeSclera);
	addChild(rightEyePupil);
	addChild(beak);
}

/*
void PenguinModel::setBeakShader(int shaderID) {
	this->beak->setShader(shaderID);
}
*/

WaterModel* plane = nullptr;
GridModel* grid = nullptr;
AxesModel* axes = nullptr;
Terrain* terrain = nullptr;

void WorldModel::setGridShader(int shaderProgram) { grid->setShader(shaderProgram); }
void WorldModel::setAxesShader(int shaderProgram) { axes->setShader(shaderProgram); }
void WorldModel::setWaterShader(int shaderProgram) { plane->setShader(shaderProgram); }
void WorldModel::setTerrainShader(int shaderProgram) { terrain->setShader(shaderProgram); }
//void WorldModel::setPenguinBeaksShader(int shaderProgram)
/*{ 
	for (auto it = penguinos.begin(); it != penguinos.end(); it++)
	{
		(*it)->setBeakShader(shaderProgram);
	}
}*/

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
	const int MAX_TREES = 35;
	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			float noiseVal = fastNoise.GetNoise(i, j);
			float terrainHeight = terrain->heightmap[i][j];
			if (terrainHeight >= -0.175 && noiseVal > 0.75 && rand() % 24 == 0 && treeCount < MAX_TREES)
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

void WorldModel::generatePenguins()
{
	FastNoise fastNoise;
	fastNoise.SetSeed(0xbaedeadf);
	fastNoise.SetNoiseType(FastNoise::Simplex);
	int penguinCtr = 0;
	const int MAX_PENGUINS = 20;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			float noiseVal = fastNoise.GetNoise(i * 3, j * 3); // skip blocks 
			float terrainHeight = terrain->heightmap[i][j];
			if (terrainHeight >= -0.1 && noiseVal > 0.82 && rand() % 6 == 0 && penguinCtr < MAX_PENGUINS)
			{
				PenguinModel* penguino = new PenguinModel();
				penguino->translate(i - Terrain::SIZE / 2, terrainHeight + 0.5f, j - Terrain::SIZE / 2);
				penguino->rotate(0, 1, 0, rand() % 360);
				penguino->scale(0.4, 0.4, 0.4);
				addChild(penguino);
				models.push_back(penguino);
				penguinCtr++;
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
	generateClouds(cloudTextureID);
	generateHouses();
    generateForest();
	generatePenguins();

	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}

	for (auto it = clouds.begin(); it != clouds.end(); it++)
	{
		addChild(*it);
	}
};

