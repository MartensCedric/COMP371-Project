#include "includes/WorldModel.hpp"
#include "../Source/includes/Terrain.hpp"

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

	//modelsBottom.push_back(bottomDiv);
	//modelsTop.push_back(topDiv);
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



PlaneModel* plane = nullptr;
GridModel* grid = nullptr;
AxesModel* axes = nullptr;
Terrain* terrain = nullptr;

void WorldModel::setGridShader(int shaderProgram) { grid->setShader(shaderProgram); }
void WorldModel::setAxesShader(int shaderProgram) { axes->setShader(shaderProgram); }
void WorldModel::setPlaneShader(int shaderProgram) { plane->setShader(shaderProgram); }
void WorldModel::setTerrainShader(int shaderProgram) { terrain->setShader(shaderProgram); }

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

WorldModel::WorldModel() {
	// Load textures
	GLuint boxTextureID = loadTexture("../Assets/Textures/box.png");
	GLuint grassTextureID = loadTexture("../Assets/Textures/grass.jpg");
	GLuint goldTextureID = loadTexture("../Assets/Textures/gold.jpg");
	GLuint trunkTextureID = loadTexture("../Assets/Textures/bark.jpg");
	GLuint leavesTextureID = loadTexture("../Assets/Textures/leaves.jpg");
	GLuint snowTextureID = loadTexture("../Assets/Textures/snow.jpg");
	
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	grid = new GridModel();
//	addChild(grid);
	
	plane = new PlaneModel();
	//plane->setTexture(grassTextureID);
	plane->translate(0, 0.1, 0);
	//texturedElement.push_back(plane);
	//addChild(plane);

	axes = new AxesModel();
	axes->translate(0, 0.1, 0);
	addChild(axes);

	terrain = new Terrain();
	//terrain->setTexture(grassTextureID);
	texturedElement.push_back(terrain);
	terrain->translate(-50, 0, -50);
	addChild(terrain);




	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}
};