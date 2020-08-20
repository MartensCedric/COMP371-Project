#include "includes/WorldModel.hpp"
#include "../Source/includes/Terrain.hpp"
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
	cloudBottom->translate(0,65, 0);
	addChild(cloudBottom);
	addChild(cloudCenter);

};

EModel::EModel() {
	setupAttribPointer();

	SimpleModel* topDiv = new SimpleModel();
	SimpleModel* bottomDiv = new SimpleModel();
	
	UnitCubeModel* leftTop = new UnitCubeModel();
	leftTop->scale(1, 3, 1);
	leftTop->translate(0, 2, 0);

	UnitCubeModel* leftBottom = new UnitCubeModel();
	leftBottom->scale(1, 3, 1);
	leftBottom->translate(0, -2, 0);

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 1, 1);
	top->translate(1, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(3, 1, 1);
	middle->translate(1, 0, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(3, 1, 1);
	bottom->translate(1, -3, 0);

	topDiv->addChild(leftTop);
	topDiv->addChild(top);
	bottomDiv->addChild(leftBottom);
	bottomDiv->addChild(middle);
	bottomDiv->addChild(bottom);

	addChild(topDiv);
	addChild(bottomDiv);

	//SimpleModel::modelsTop.push_back(topDiv);
	//SimpleModel::modelsBottom.push_back(bottomDiv);
};

FiveModel::FiveModel() {
	setupAttribPointer();

	// Draw a 5
	SimpleModel* topDiv = new SimpleModel();
	SimpleModel* bottomDiv = new SimpleModel();
	
	UnitCubeModel* left = new UnitCubeModel();
	left->scale(1, 2.5, 1);
	left->translate(0, 1.75, 0);

	UnitCubeModel* right = new UnitCubeModel();
	right->scale(1, 2, 1);
	right->translate(2, -1.5, 0);

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 1, 1);
	top->translate(1, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(3, 1, 1);
	middle->translate(1, 0, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(3, 1, 1);
	bottom->translate(1, -3, 0);

	topDiv->addChild(left);
	topDiv->addChild(top);
	bottomDiv->addChild(middle);
	bottomDiv->addChild(right);
	bottomDiv->addChild(bottom);

	addChild(topDiv);
	addChild(bottomDiv);

	//modelsBottom.push_back(bottomDiv);
	//modelsTop.push_back(topDiv);
};

IModel::IModel() {
	setupAttribPointer();
	
	SimpleModel* topDiv = new SimpleModel();
	SimpleModel* bottomDiv = new SimpleModel();
	
	UnitCubeModel* top = new UnitCubeModel();
	top->scale(2, 1, 1);
	top->translate(0, 3, 0);

	UnitCubeModel* middleTop = new UnitCubeModel();
	middleTop->scale(1, 2, 1);
	middleTop->translate(0, 2, 0);

	UnitCubeModel* middleBottom = new UnitCubeModel();
	middleBottom->scale(1, 4, 1);
	middleBottom->translate(0, -1, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(2, 1, 1);
	bottom->translate(0, -3, 0);

	topDiv->addChild(top);
	topDiv->addChild(middleTop);

	bottomDiv->addChild(middleBottom);
	bottomDiv->addChild(bottom);

	addChild(topDiv);
	addChild(bottomDiv);

	//modelsTop.push_back(topDiv);
	//modelsBottom.push_back(bottomDiv);
};

ThreeModel::ThreeModel() {
	setupAttribPointer();

	SimpleModel* topDiv = new SimpleModel();
	SimpleModel* bottomDiv = new SimpleModel();
	
	UnitCubeModel* rightTop = new UnitCubeModel();
	rightTop->scale(1, 3, 1);
	rightTop->translate(2, 2, 0);

	UnitCubeModel* rightBottom = new UnitCubeModel();
	rightBottom->scale(1, 3, 1);
	rightBottom->translate(2, -2, 0);

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 1, 1);
	top->translate(1, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(3, 1, 1);
	middle->translate(1, 0, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(3, 1, 1);
	bottom->translate(1, -3, 0);

	topDiv->addChild(top);
	topDiv->addChild(rightTop);
	bottomDiv->addChild(rightBottom);
	bottomDiv->addChild(middle);
	bottomDiv->addChild(bottom);

	addChild(bottomDiv);
	addChild(topDiv);
};

TModel::TModel() {
	setupAttribPointer();
	
	SimpleModel* topDiv = new SimpleModel();
	SimpleModel* bottomDiv = new SimpleModel();
	
	UnitCubeModel* top = new UnitCubeModel();
	top->scale(4, 1, 1);
	top->translate(0, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(1, 3, 1);
	middle->translate(0, 2, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(1, 4, 1);
	bottom->translate(0, -1.5, 0);

	topDiv->addChild(top);
	topDiv->addChild(middle);

	bottomDiv->addChild(bottom);

	addChild(topDiv);
	addChild(bottomDiv);

	//modelsBottom.push_back(bottomDiv);
	//modelsTop.push_back(topDiv);
};

DModel::DModel() {
	setupAttribPointer();

	SimpleModel* topDiv = new SimpleModel();
	SimpleModel* bottomDiv = new SimpleModel();
	
	UnitCubeModel* leftTop = new UnitCubeModel();
	UnitCubeModel* leftBottom = new UnitCubeModel();

	leftBottom->scale(1, 3.55, 1);
	leftBottom->translate(0, -1.5, 0);
	leftTop->scale(1, 3.55, 1);
	leftTop->translate(0, 1.5, 0);

	UnitCubeModel* rightTop = new UnitCubeModel();
	UnitCubeModel* rightBottom = new UnitCubeModel();

	rightTop->scale(1, 2.75, 1);
	rightTop->translate(2.3, 1.25, 0);

	rightBottom->scale(1, 2.75, 1);
	rightBottom->translate(2.3, -1.25, 0);

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 1, 1);
	top->translate(1.2, 2.83, 0);
	top->rotate(0, 0, 1, -11);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(3, 1, 1);
	bottom->translate(1.2, -2.83, 0);
	bottom->rotate(0, 0, 1, 11);

	topDiv->addChild(leftTop);
	topDiv->addChild(top);
	topDiv->addChild(rightTop);
	bottomDiv->addChild(bottom);
	bottomDiv->addChild(rightBottom);
	bottomDiv->addChild(leftBottom);

	addChild(bottomDiv);
	addChild(topDiv);

	//modelsTop.push_back(topDiv);
	//modelsBottom.push_back(bottomDiv);
};

EightModel::EightModel() {
	setupAttribPointer();

	// Draw a 8
	SimpleModel* topDiv = new SimpleModel();
	SimpleModel* bottomDiv = new SimpleModel();
	
	UnitCubeModel* rightTop = new UnitCubeModel();
	UnitCubeModel* rightBottom = new UnitCubeModel();

	rightTop->scale(1, 2.5, 1);
	rightTop->translate(2, 1.5, 0);
	rightBottom->scale(1, 2.5, 1);
	rightBottom->translate(2, -1.5, 0);

	UnitCubeModel* leftTop = new UnitCubeModel();
	UnitCubeModel* leftBottom = new UnitCubeModel();
	leftTop->scale(1, 2.5, 1);
	leftTop->translate(0, 1.5, 0);
	leftBottom->scale(1, 2.5, 1);
	leftBottom->translate(0, -1.5, 0);

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 1, 1);
	top->translate(1, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(3, 1, 1);
	middle->translate(1, 0, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(3, 1, 1);
	bottom->translate(1, -3, 0);

	topDiv->addChild(top);
	topDiv->addChild(rightTop);
	topDiv->addChild(leftTop);
	bottomDiv->addChild(middle);
	bottomDiv->addChild(bottom);
	bottomDiv->addChild(rightBottom);
	bottomDiv->addChild(leftBottom);

	addChild(topDiv);
	addChild(bottomDiv);
	
	//modelsBottom.push_back(bottomDiv);
	//modelsTop.push_back(topDiv);
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


	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			float noiseVal = fastNoise.GetNoise(i , j );
			float terrainHeight = terrain->heightmap[i][j];
			if (noiseVal >= 0.8f && terrainHeight >= -0.1 && rand() % 3 == 0)
			{
				UnitCubeModel* cube = new UnitCubeModel();
				cube->translate(i - Terrain::SIZE / 2, terrainHeight + 0.5f, j - Terrain::SIZE / 2);
				cube->scale(0.2, 1, 0.2);
				addChild(cube);
				models.push_back(cube);
			}
		}
	}
}

void WorldModel::generateClouds(GLuint TextureID)
{
	for (int i = 0; i < 7; i++)
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

void WorldModel::addCloud(int elapsed_seconds, int modelShader)
{
	GLuint cloudTextureID = loadTexture("../Assets/Textures/cloud.jpg");
		srand(elapsed_seconds);
		double randomX = rand() % 201 + (-100);
		double randomY = rand() % 9 + (-4);
		CloudModel* cloud = new CloudModel();
		//cloud->setShader(modelShader);
		cloud->translate(randomX, 0, -100);
		cloud->setTexture(cloudTextureID);
		clouds.push_back(cloud);
		addChild(cloud);
}



WorldModel::WorldModel() {
	// Load textures
	GLuint boxTextureID = loadTexture("../Assets/Textures/box.png");
	GLuint grassTextureID = loadTexture("../Assets/Textures/grass.jpg");
	GLuint goldTextureID = loadTexture("../Assets/Textures/gold.jpg");
	GLuint cloudTextureID = loadTexture("../Assets/Textures/cloud.jpg");

	
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	grid = new GridModel();
//	addChild(grid);
	
	plane = new WaterModel();
	plane->translate(0, -2, 0);
	addChild(plane);

	axes = new AxesModel();
	axes->translate(0, 0.1, 0);
	addChild(axes);

	terrain = new Terrain();
	terrain->translate(-50, 0, -50);
	addChild(terrain);

	// Alpha numerical models
	// Splitting each model in two
	// strategy: 2/3 assigned to the bottom, the remainder 1/3 to the top
	
	/* 
	 * ----------------------------------------------------
	 *                          T5
	 * ---------------------------------------------------- 
	 */




	SimpleModel* T5 = new SimpleModel();
	
	TModel* T = new TModel();
	T->setTexture(boxTextureID);
	T->translate(-2, 0, 0);
	T5->addChild(T);
	
	FiveModel* five_2 = new FiveModel();
	five_2->setTexture(goldTextureID);
	five_2->translate(1.5, 0, 0);
	T5->addChild(five_2);

	SphereModel* sphere_4 = new SphereModel(6.0f, 36, 18);
	sphere_4->translate(0, 4, 0);
	spheres.push_back(sphere_4);
	T5->addChild(sphere_4);

	T5->translate(-18, 3.5, -18);
	//models.push_back(T5);

	/* 
	 * ----------------------------------------------------
	 *                          I3
	 * ---------------------------------------------------- 
	 */

	SimpleModel* I3 = new SimpleModel();
	
	IModel* I = new IModel();
	I->setTexture(boxTextureID);
	I->translate(-2, 0, 0);
	I3->addChild(I);

	ThreeModel* three = new ThreeModel();
	three->setTexture(goldTextureID);
	three->translate(2, 0, 0);
	I3->addChild(three);

	SphereModel* sphere_1 = new SphereModel(6.0f, 36, 18);
	sphere_1->translate(0, 4, 0);
	spheres.push_back(sphere_1);
	I3->addChild(sphere_1);

	I3->translate(18, 3.5, -18);
	//models.push_back(I3);

	/* 
	 * ----------------------------------------------------
	 *                          E5
	 * ---------------------------------------------------- 
	 */

	SimpleModel* E5 = new SimpleModel();
	
	EModel* E = new EModel();
	E->setTexture(boxTextureID);
	E->translate(-3.5, 0, 0);
	E5->addChild(E);

	FiveModel* five = new FiveModel();
	five->setTexture(goldTextureID);
	five->translate(1.5, 0, 0);
	E5->addChild(five);

	SphereModel* sphere = new SphereModel(6.0f, 36, 18);
	sphere->translate(0, 4, 0);
	spheres.push_back(sphere);
	E5->addChild(sphere);

	E5->translate(0, 3.5, 0);
	//models.push_back(E5);

	/* 
	 * ----------------------------------------------------
	 *                          I3-2
	 * ---------------------------------------------------- 
	 */

	SimpleModel* I3_2 = new SimpleModel();
	
	IModel* I_2 = new IModel();
	I_2->setTexture(boxTextureID);
	I_2->translate(-2, 0, 0);
	I3_2->addChild(I_2);

	ThreeModel* three_2 = new ThreeModel();
	three_2->setTexture(goldTextureID);
	three_2->translate(2, 0, 0);
	I3_2->addChild(three_2);

	SphereModel* sphere_2 = new SphereModel(6.0f, 36, 18);
	sphere_2->translate(0, 4, 0);
	spheres.push_back(sphere_2);
	I3_2->addChild(sphere_2);

	I3_2->translate(18, 3.5, 18);
	//models.push_back(I3_2);

	/* 
	 * ----------------------------------------------------
	 *                          D8
	 * ---------------------------------------------------- 
	 */

	SimpleModel* D8 = new SimpleModel();
	
	DModel* D = new DModel();
	D->setTexture(boxTextureID);
	D->translate(-3.5, 0, 0);
	D8->addChild(D);

	EightModel* eight = new EightModel();
	eight->setTexture(goldTextureID);
	eight->translate(1.5, 0, 0);
	D8->addChild(eight);

	SphereModel* sphere_3 = new SphereModel(6.0f, 36, 18);
	sphere_3->translate(0, 4, 0);
	spheres.push_back(sphere_3);	
	D8->addChild(sphere_3);

	D8->translate(-18, 3.5, 18);
	//models.push_back(D8);

	generateForest();
	generateClouds(cloudTextureID);
	

	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}

	for (auto it = clouds.begin(); it != clouds.end(); it++)
	{
		addChild(*it);
	}
	 
};