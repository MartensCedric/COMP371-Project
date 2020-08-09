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

TreeTrunkModel::TreeTrunkModel() {
	setupAttribPointer();

	UnitCubeModel* mainTrunk = new UnitCubeModel();
	mainTrunk->scale(1, 5.5, 1);
	mainTrunk->translate(0, -1, 0);

	addChild(mainTrunk);
};

RoundLeaves::RoundLeaves() {
	setupAttribPointer();

	UnitCubeModel* base = new UnitCubeModel();
	base->scale(3, 1, 3);
	base->translate(0, 0, 0);

	UnitCubeModel* leftTop = new UnitCubeModel();
	leftTop->scale(1, 1, 1);
	leftTop->translate(-2, 0, -1);
	UnitCubeModel* leftMiddle = new UnitCubeModel();
	leftMiddle->scale(1, 1, 1);
	leftMiddle->translate(-2, 0, 0);
	UnitCubeModel* leftBottom = new UnitCubeModel();
	leftBottom->scale(1, 1, 1);
	leftBottom->translate(-2, 0, 1);

	UnitCubeModel* rightTop = new UnitCubeModel();
	rightTop->scale(1, 1, 1);
	rightTop->translate(2, 0, -1);
	UnitCubeModel* rightMiddle = new UnitCubeModel();
	rightMiddle->scale(1, 1, 1);
	rightMiddle->translate(2, 0, 0);
	UnitCubeModel* rightBottom = new UnitCubeModel();
	rightBottom->scale(1, 1, 1);
	rightBottom->translate(2, 0, 1);

	UnitCubeModel* topLeft = new UnitCubeModel();
	topLeft->scale(1, 1, 1);
	topLeft->translate(-1, 0, -2);
	UnitCubeModel* topMiddle = new UnitCubeModel();
	topMiddle->scale(1, 1, 1);
	topMiddle->translate(0, 0, -2);
	UnitCubeModel* topRight = new UnitCubeModel();
	topRight->scale(1, 1, 1);
	topRight->translate(1, 0, -2);

	UnitCubeModel* bottomLeft = new UnitCubeModel();
	bottomLeft->scale(1, 1, 1);
	bottomLeft->translate(-1, 0, 2);
	UnitCubeModel* bottomMiddle = new UnitCubeModel();
	bottomMiddle->scale(1, 1, 1);
	bottomMiddle->translate(0, 0, 2);
	UnitCubeModel* bottomRight = new UnitCubeModel();
	bottomRight->scale(1, 1, 1);
	bottomRight->translate(1, 0, 2);

	addChild(base);

	addChild(leftTop);
	addChild(leftMiddle);
	addChild(leftBottom);

	addChild(rightTop);
	addChild(rightMiddle);
	addChild(rightBottom);

	addChild(topLeft);
	addChild(topMiddle);
	addChild(topRight);

	addChild(bottomLeft);
	addChild(bottomMiddle);
	addChild(bottomRight);
};

SquareLeaves::SquareLeaves() {
	setupAttribPointer();

	UnitCubeModel* topleft = new UnitCubeModel();
	topleft->scale(1, 1, 1);
	topleft->translate(-0.5, 0, -0.5);

	UnitCubeModel* topright = new UnitCubeModel();
	topright->scale(1, 1, 1);
	topright->translate(0.5, 0, -0.5);

	UnitCubeModel* bottomleft = new UnitCubeModel();
	bottomleft->scale(1, 1, 1);
	bottomleft->translate(-0.5, 0, 0.5);

	UnitCubeModel* bottomright = new UnitCubeModel();
	bottomright->scale(1, 1, 1);
	bottomright->translate(0.5, 0, 0.5);

	addChild(topleft);
	addChild(topright);
	addChild(bottomleft);
	addChild(bottomright);
};

CubeLeaves::CubeLeaves() {
	setupAttribPointer();

	UnitCubeModel* base3 = new UnitCubeModel();
	base3->scale(1, 1, 1);
	base3->translate(0, 0, 0);

	addChild(base3);
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

	//Tree Model
	SimpleModel* tree = new SimpleModel();

	TreeTrunkModel* trunk = new TreeTrunkModel();
	trunk->setTexture(trunkTextureID);
	texturedElement.push_back(trunk);
	trunk->translate(0, 1, 0);
	tree->addChild(trunk);

	RoundLeaves* layer1 = new RoundLeaves();
	layer1->setTexture(leavesTextureID);
	texturedElement.push_back(layer1);
	layer1->translate(0, 0, 0);
	tree->addChild(layer1);

	SquareLeaves* layer2 = new SquareLeaves();
	layer2->setTexture(leavesTextureID);
	texturedElement.push_back(layer2);
	layer2->scale(1.5, 1, 1.5);
	layer2->translate(0, 1, 0);
	tree->addChild(layer2);

	RoundLeaves* layer3 = new RoundLeaves();
	layer3->setTexture(leavesTextureID);
	texturedElement.push_back(layer3);
	layer3->scale(0.80, 1, 0.80);
	layer3->translate(0, 1.8, 0);
	layer3->rotate(0, 1, 0, 45);
	tree->addChild(layer3);

	SquareLeaves* layer4 = new SquareLeaves();
	layer4->setTexture(leavesTextureID);
	texturedElement.push_back(layer4);
	layer4->scale(0.9, 1, 0.9);
	layer4->translate(0, 2.5, 0);
	layer4->rotate(0, 1, 0, 45);
	tree->addChild(layer4);

	RoundLeaves* layer5 = new RoundLeaves();
	layer5->setTexture(leavesTextureID);
	texturedElement.push_back(layer5);
	layer5->scale(0.70, 0.80, 0.70);
	layer5->translate(0, 3.4, 0);
	layer5->rotate(0, 1, 0, 0);
	tree->addChild(layer5);

	SquareLeaves* layer6 = new SquareLeaves();
	layer6->setTexture(leavesTextureID);
	texturedElement.push_back(layer6);
	layer6->scale(0.75, 1, 0.75);
	layer6->translate(0, 3.9, 0);
	layer6->rotate(0, 1, 0, 0);
	tree->addChild(layer6);

	RoundLeaves* layer7 = new RoundLeaves();
	layer7->setTexture(leavesTextureID);
	texturedElement.push_back(layer7);
	layer7->scale(0.50, 0.80, 0.50);
	layer7->translate(0, 4.6, 0);
	layer7->rotate(0, 1, 0, 45);
	tree->addChild(layer7);

	SquareLeaves* layer8 = new SquareLeaves();
	layer8->setTexture(leavesTextureID);
	texturedElement.push_back(layer8);
	layer8->scale(0.5, 1, 0.5);
	layer8->translate(0, 5.1, 0);
	layer8->rotate(0, 1, 0, 45);
	tree->addChild(layer8);

	CubeLeaves* layer9 = new CubeLeaves();
	layer9->setTexture(leavesTextureID);
	texturedElement.push_back(layer9);
	layer9->scale(0.5, 0.5, 0.5);
	layer9->translate(0, 5.8, 0);
	layer9->rotate(0, 1, 0, 0);
	tree->addChild(layer9);


	tree->translate(7, 10, 0);
	models.push_back(tree);



	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}
};