#include "includes/WorldModel.hpp"
#include "../Source/includes/TreeModel.hpp"
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

	addChild(leftTop);
	addChild(top);
	addChild(leftBottom);
	addChild(middle);
	addChild(bottom);
};

ESnow::ESnow() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 0.25, 1);
	top->translate(1, 3.63, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(2, 0.25, 1);
	middle->translate(1.5, 0.63, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(2, 0.25, 1);
	bottom->translate(1.5, -2.37, 0);

	addChild(top);
	addChild(middle);
	addChild(bottom);
};

FiveModel::FiveModel() {
	setupAttribPointer();

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

	addChild(left);
	addChild(top);
	addChild(middle);
	addChild(right);
	addChild(bottom);
};

FiveSnow::FiveSnow() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 0.25, 1);
	top->translate(1, 3.63, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(2, 0.25, 1);
	middle->translate(1.5, 0.63, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(2, 0.25, 1);
	bottom->translate(0.5, -2.37, 0);

	addChild(top);
	addChild(middle);
	addChild(bottom);

};

IModel::IModel() {
	setupAttribPointer();

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

	addChild(top);
	addChild(middleTop);
	addChild(middleBottom);
	addChild(bottom);
};

ISnow::ISnow() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(2, 0.25, 1);
	top->translate(0, 3.63, 0);

	UnitCubeModel* bottomLeft = new UnitCubeModel();
	bottomLeft->scale(0.5, 0.25, 1);
	bottomLeft->translate(-0.75, -2.37, 0);

	UnitCubeModel* bottomRight = new UnitCubeModel();
	bottomRight->scale(0.5, 0.25, 1);
	bottomRight->translate(0.75, -2.37, 0);

	addChild(top);
	addChild(bottomLeft);
	addChild(bottomRight);
};

ThreeModel::ThreeModel() {
	setupAttribPointer();

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

	addChild(top);
	addChild(rightTop);
	addChild(rightBottom);
	addChild(middle);
	addChild(bottom);
};

ThreeSnow::ThreeSnow() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 0.25, 1);
	top->translate(1, 3.63, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(2, 0.25, 1);
	middle->translate(0.5, 0.63, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(2, 0.25, 1);
	bottom->translate(0.5, -2.37, 0);

	addChild(top);
	addChild(middle);
	addChild(bottom);
};

TModel::TModel() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(4, 1, 1);
	top->translate(0, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(1, 3, 1);
	middle->translate(0, 2, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(1, 4, 1);
	bottom->translate(0, -1.5, 0);

	addChild(top);
	addChild(middle);
	addChild(bottom);
};

TSnow::TSnow() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(4, 0.25, 1);
	top->translate(0, 3.63, 0);

	addChild(top);
};

DModel::DModel() {
	setupAttribPointer();

	UnitCubeModel* leftTop = new UnitCubeModel();
	leftTop->scale(1, 3.55, 1);
	leftTop->translate(0, 1.5, 0);

	UnitCubeModel* leftBottom = new UnitCubeModel();
	leftBottom->scale(1, 3.55, 1);
	leftBottom->translate(0, -1.5, 0);

	UnitCubeModel* rightTop = new UnitCubeModel();
	rightTop->scale(1, 2.75, 1);
	rightTop->translate(2.3, 1.25, 0);

	UnitCubeModel* rightBottom = new UnitCubeModel();
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

	addChild(leftTop);
	addChild(top);
	addChild(rightTop);
	addChild(bottom);
	addChild(rightBottom);
	addChild(leftBottom);
};

DSnow::DSnow() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 0.25, 1);
	top->translate(1.29, 3.45, 0);
	top->rotate(0, 0, 1, -11);

	UnitCubeModel* left = new UnitCubeModel();
	left->scale(0.25, 0.25, 1);
	left->translate(-0.38, 3.42, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(1.3, 0.25, 1);
	bottom->translate(1.15, -2.16, 0);
	bottom->rotate(0, 0, 1, 11);

	addChild(top);
	addChild(left);
	addChild(bottom);

};

EightModel::EightModel() {
	setupAttribPointer();

	UnitCubeModel* rightTop = new UnitCubeModel();
	rightTop->scale(1, 2.5, 1);
	rightTop->translate(2, 1.5, 0);

	UnitCubeModel* rightBottom = new UnitCubeModel();
	rightBottom->scale(1, 2.5, 1);
	rightBottom->translate(2, -1.5, 0);

	UnitCubeModel* leftTop = new UnitCubeModel();
	leftTop->scale(1, 2.5, 1);
	leftTop->translate(0, 1.5, 0);

	UnitCubeModel* leftBottom = new UnitCubeModel();
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

	addChild(top);
	addChild(rightTop);
	addChild(leftTop);
	addChild(middle);
	addChild(bottom);
	addChild(rightBottom);
	addChild(leftBottom);
};

EightSnow::EightSnow() {
	setupAttribPointer();

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 0.25, 1);
	top->translate(1, 3.63, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(1, 0.25, 1);
	middle->translate(1, 0.63, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(1, 0.25, 1);
	bottom->translate(1, -2.37, 0);

	addChild(top);
	addChild(middle);
	addChild(bottom);
};

Stoneplate::Stoneplate() {
	setupAttribPointer();

	UnitCubeModel* square = new UnitCubeModel();
	square->scale(21, 1, 21);
	square->translate(0, 0, 0);

	UnitCubeModel* top1 = new UnitCubeModel();
	top1->scale(19, 1, 1);
	top1->translate(0, 0, -11);

	UnitCubeModel* top2 = new UnitCubeModel();
	top2->scale(17, 1, 1);
	top2->translate(0, 0, -12);

	UnitCubeModel* top3 = new UnitCubeModel();
	top3->scale(13, 1, 1);
	top3->translate(0, 0, -13);

	UnitCubeModel* top4 = new UnitCubeModel();
	top4->scale(7, 1, 1);
	top4->translate(0, 0, -14);

	UnitCubeModel* bottom1 = new UnitCubeModel();
	bottom1->scale(19, 1, 1);
	bottom1->translate(0, 0, 11);

	UnitCubeModel* bottom2 = new UnitCubeModel();
	bottom2->scale(17, 1, 1);
	bottom2->translate(0, 0, 12);

	UnitCubeModel* bottom3 = new UnitCubeModel();
	bottom3->scale(13, 1, 1);
	bottom3->translate(0, 0, 13);

	UnitCubeModel* bottom4 = new UnitCubeModel();
	bottom4->scale(7, 1, 1);
	bottom4->translate(0, 0, 14);

	UnitCubeModel* left1 = new UnitCubeModel();
	left1->scale(1, 1, 19);
	left1->translate(-11, 0, 0);

	UnitCubeModel* left2 = new UnitCubeModel();
	left2->scale(1, 1, 17);
	left2->translate(-12, 0, 0);

	UnitCubeModel* left3 = new UnitCubeModel();
	left3->scale(1, 1, 13);
	left3->translate(-13, 0, 0);

	UnitCubeModel* left4 = new UnitCubeModel();
	left4->scale(1, 1, 7);
	left4->translate(-14, 0, 0);

	UnitCubeModel* right1 = new UnitCubeModel();
	right1->scale(1, 1, 19);
	right1->translate(11, 0, 0);

	UnitCubeModel* right2 = new UnitCubeModel();
	right2->scale(1, 1, 17);
	right2->translate(12, 0, 0);

	UnitCubeModel* right3 = new UnitCubeModel();
	right3->scale(1, 1, 13);
	right3->translate(13, 0, 0);

	UnitCubeModel* right4 = new UnitCubeModel();
	right4->scale(1, 1, 7);
	right4->translate(14, 0, 0);

	addChild(square);
	addChild(top1);
	addChild(top2);
	addChild(top3);
	addChild(top4);
	addChild(bottom1);
	addChild(bottom2);
	addChild(bottom3);
	addChild(bottom4);
	addChild(left1);
	addChild(left2);
	addChild(left3);
	addChild(left4);
	addChild(right1);
	addChild(right2);
	addChild(right3);
	addChild(right4);
}

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

	//Letters and Numbers
	SimpleModel* stoneHenge = new SimpleModel();

	//plate for stone henge

	Stoneplate* plate = new Stoneplate();
	plate->setTexture(rockTextureID);
	texturedElement.push_back(plate);
	plate->translate(0, -4, 0);
	plate->scale(0.65, 0.65, 0.65);
	stoneHenge->addChild(plate);

	Stoneplate* snowPlate = new Stoneplate();
	snowPlate->setTexture(snowTextureID);
	texturedElement.push_back(snowPlate);
	snowPlate->translate(0, -3.5, 0);
	snowPlate->scale(0.65, 0.25, 0.65);
	stoneHenge->addChild(snowPlate);

	//Column for stone henge

	Stoneplate* column = new Stoneplate();
	column->setTexture(rockTextureID);
	texturedElement.push_back(column);
	column->translate(0, -24, 0);
	column->scale(0.07, 40, 0.07);
	stoneHenge->addChild(column);
	
	//Letters and numbers

	EModel* E = new EModel();
	E->setTexture(rockTextureID);
	texturedElement.push_back(E);
	E->translate(-2, 0, 8);
	E->rotate(0, 1, 0, 162);
	stoneHenge->addChild(E);

	FiveModel* five = new FiveModel();
	five->setTexture(rockTextureID);
	texturedElement.push_back(five);
	five->translate(-6, 0, 6);
	five->rotate(0, 1, 0, 126);
	stoneHenge->addChild(five);

	TModel* T = new TModel();
	T->setTexture(rockTextureID);
	texturedElement.push_back(T);
	T->translate(-8, 0, 0);
	T->rotate(0, 1, 0, 90);
	stoneHenge->addChild(T);

	FiveModel* five_2 = new FiveModel();
	five_2->setTexture(rockTextureID);
	texturedElement.push_back(five_2);
	five_2->translate(-7, 0, -4);
	five_2->rotate(0, 1, 0, 54);
	stoneHenge->addChild(five_2);

	IModel* I = new IModel();
	I->setTexture(rockTextureID);
	texturedElement.push_back(I);
	I->translate(-2, 0, -8);
	I->rotate(0, 1, 0, 18);
	stoneHenge->addChild(I);

	ThreeModel* three = new ThreeModel();
	three->setTexture(rockTextureID);
	texturedElement.push_back(three);
	three->translate(2, 0, -8);
	three->rotate(0, 1, 0, -18);
	stoneHenge->addChild(three);

	DModel* D = new DModel();
	D->setTexture(rockTextureID);
	texturedElement.push_back(D);
	D->translate(6, 0, -5);
	D->rotate(0, 1, 0, -54);
	stoneHenge->addChild(D);

	EightModel* eight = new EightModel();
	eight->setTexture(rockTextureID);
	texturedElement.push_back(eight);
	eight->translate(8, 0, 0);
	eight->rotate(0, 1, 0, -90);
	stoneHenge->addChild(eight);

	IModel* I_2 = new IModel();
	I_2->setTexture(rockTextureID);
	texturedElement.push_back(I_2);
	I_2->translate(6, 0, 6);
	I_2->rotate(0, 1, 0, -126);
	stoneHenge->addChild(I_2);

	ThreeModel* three_2 = new ThreeModel();
	three_2->setTexture(rockTextureID);
	texturedElement.push_back(three_2);
	three_2->translate(3, 0, 8);
	three_2->rotate(0, 1, 0, -162);
	stoneHenge->addChild(three_2);

	//Snow for stonehenge

	ESnow* Esnow = new ESnow();
	Esnow->setTexture(snowTextureID);
	texturedElement.push_back(Esnow);
	Esnow->translate(-2, 0, 8);
	Esnow->rotate(0, 1, 0, 162);
	stoneHenge->addChild(Esnow);

	ThreeSnow* three_2snow = new ThreeSnow();
	three_2snow->setTexture(snowTextureID);
	texturedElement.push_back(three_2snow);
	three_2snow->translate(3, 0, 8);
	three_2snow->rotate(0, 1, 0, -162);
	stoneHenge->addChild(three_2snow);

	FiveSnow* fivesnow = new FiveSnow();
	fivesnow->setTexture(snowTextureID);
	texturedElement.push_back(fivesnow);
	fivesnow->translate(-6, 0, 6);
	fivesnow->rotate(0, 1, 0, 126);
	stoneHenge->addChild(fivesnow);

	TSnow* Tsnow = new TSnow();
	Tsnow->setTexture(snowTextureID);
	texturedElement.push_back(Tsnow);
	Tsnow->translate(-8, 0, 0);
	Tsnow->rotate(0, 1, 0, 90);
	stoneHenge->addChild(Tsnow);

	FiveSnow* five_2snow = new FiveSnow();
	five_2snow->setTexture(snowTextureID);
	texturedElement.push_back(five_2snow);
	five_2snow->translate(-7, 0, -4);
	five_2snow->rotate(0, 1, 0, 54);
	stoneHenge->addChild(five_2snow);

	ISnow* Isnow = new ISnow();
	Isnow->setTexture(snowTextureID);
	texturedElement.push_back(Isnow);
	Isnow->translate(-2, 0, -8);
	Isnow->rotate(0, 1, 0, 18);
	stoneHenge->addChild(Isnow);

	ThreeSnow* threesnow = new ThreeSnow();
	threesnow->setTexture(snowTextureID);
	texturedElement.push_back(threesnow);
	threesnow->translate(2, 0, -8);
	threesnow->rotate(0, 1, 0, -18);
	stoneHenge->addChild(threesnow);

	DSnow* Dsnow = new DSnow();
	Dsnow->setTexture(snowTextureID);
	texturedElement.push_back(Dsnow);
	Dsnow->translate(6, 0, -5);
	Dsnow->rotate(0, 1, 0, -54);
	stoneHenge->addChild(Dsnow);

	EightSnow* eightsnow = new EightSnow();
	eightsnow->setTexture(snowTextureID);
	texturedElement.push_back(eightsnow);
	eightsnow->translate(8, 0, 0);
	eightsnow->rotate(0, 1, 0, -90);
	stoneHenge->addChild(eightsnow);

	ISnow* I_2snow = new ISnow();
	I_2snow->setTexture(snowTextureID);
	texturedElement.push_back(I_2snow);
	I_2snow->translate(6, 0, 6);
	I_2snow->rotate(0, 1, 0, -126);
	stoneHenge->addChild(I_2snow);

	stoneHenge->translate(0, 13, 0);
	stoneHenge->scale(0.5, 0.5, 0.5);
	models.push_back(stoneHenge);

	generateForest();


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