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
#endif

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

WaterModel* plane = nullptr;
Terrain* terrain = nullptr;

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
			if (terrainHeight >= -0.175 && noiseVal > parameters.treeCap && rand() % (int) parameters.forestDensity == 0 && treeCount < parameters.treeCap)
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

void WorldModel::generatePenguins()
{
	FastNoise fastNoise;
	fastNoise.SetSeed(0xbaedeadf);
	fastNoise.SetNoiseType(FastNoise::Simplex);
	int penguinCtr = 0;
	
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			float noiseVal = fastNoise.GetNoise(i * parameters.penguinSpread, j * parameters.penguinSpread); // skip blocks 
			float terrainHeight = terrain->heightmap[i][j];
			if (terrainHeight >= -0.1 && noiseVal > parameters.penguinFrequency && rand() % (int) parameters.penguinDensity == 0 && penguinCtr < parameters.penguinCap)
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
	/*for (auto it = children.begin(); it != children.end(); it++)
		delete *it;
	
	for (auto it = models.begin(); it != models.end(); it++)
		delete *it;*/

	this->models.clear();
	this->children.clear();
	this->penguinos.clear();

	delete plane;
	plane = new WaterModel();
	plane->translate(0, parameters.waterHeight, 0);
	addChild(plane);

	delete terrain;
	terrain = new Terrain(&parameters);
	terrain->translate(-50, 0, -50);
	addChild(terrain);

	generateStonehenge();
	generateHouses();
	generateForest();
	generatePenguins();

	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}
}
