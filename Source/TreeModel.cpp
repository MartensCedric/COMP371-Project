#include "includes/WorldModel.hpp"
#include "../Source/includes/Terrain.hpp"
#include "includes/TreeModel.hpp"
#include <cstdlib>
#include <ctime>


TreeTrunkModel::TreeTrunkModel() {
	setupAttribPointer();

	UnitCubeModel* mainTrunk = new UnitCubeModel();
	mainTrunk->scale(1, 5.5, 1);
	//mainTrunk->translate(0, -1, 0);
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
	addChild(base3);
};


TreeModel::TreeModel() {
	// Load textures
	GLuint trunkTextureID = loadTexture("../Assets/Textures/bark.jpg");
	GLuint leavesTextureID = loadTexture("../Assets/Textures/leaves.jpg");
	GLuint snowTextureID = loadTexture("../Assets/Textures/snow.jpg");

	//-------------Random changes to the tree-------------

	//choose random number between 1 and 4
	float randomNum1 = 1 + (rand() % 4);
	//possible values for horizontal change are: 4/7, 3/7, 2/7 , 1/7
	float horizontalChange = randomNum1 / 7;

	//Choose another random number between 0 and 3
	float randomNum2 = (rand() % 4);
	//possible values for vertical change are: 3/6, 2/6, 1/6, 0/6
	float verticalChange = randomNum2 / 6;

	//choose random number between 1 and 10
	float randomNum3 = (rand() % 9);
	//possible degrees of change in rotation are: 0, 10, 20, 30, 40, 50, 60, 70, 80, 90
	float rotationalChange = randomNum3 * 10;

	
	//// --------------------Super low poly tree (2 cubes)--------------------

	//SimpleModel* tree = new SimpleModel();

	//TreeTrunkModel* trunk = new TreeTrunkModel();
	//trunk->setTexture(trunkTextureID);
	//texturedElement.push_back(trunk);
	//trunk->translate(0, 1, 0);
	//tree->addChild(trunk);

	//CubeLeaves* layer1 = new CubeLeaves();
	//layer1->setTexture(leavesTextureID);
	//texturedElement.push_back(layer1);
	//layer1->scale(3, 5, 3);
	//layer1->translate(0, 3, 0);
	//layer1->rotate(0, 1, 0, 0);
	//tree->addChild(layer1);




	////--------------------Low Poly tree Model (8 cubes)--------------------

	//SimpleModel* tree = new SimpleModel();

	UnitCubeModel* trunk = new UnitCubeModel();
	trunk->scale(1, 5, 1);
	trunk->setTexture(trunkTextureID);
	addChild(trunk);

	UnitCubeModel* layer1 = new UnitCubeModel();
	layer1->setTexture(leavesTextureID);
	layer1->scale(5, 1, 5);
	layer1->rotate(0, 1, 0, 0);
	addChild(layer1);

	UnitCubeModel* layer2 = new UnitCubeModel();
	layer2->setTexture(leavesTextureID);
	layer2->scale(3, 1, 3);
	layer2->translate(0, 1, 0);
	layer2->rotate(0, 1, 0, 0);
	addChild(layer2);

	UnitCubeModel* layer3 = new UnitCubeModel();
	layer3->setTexture(leavesTextureID);
	layer3->scale(4, 1, 4);
	layer3->translate(0, 2, 0);
	layer3->rotate(0, 1, 0, 45);
	addChild(layer3);

	UnitCubeModel* layer4 = new UnitCubeModel();
	layer4->setTexture(leavesTextureID);
	layer4->scale(2.5, 1, 2.5);
	layer4->translate(0, 3, 0);
	layer4->rotate(0, 1, 0, 0);
	addChild(layer4);

	UnitCubeModel* layer5 = new UnitCubeModel();
	layer5->setTexture(leavesTextureID);
	layer5->scale(3, 1, 3);
	layer5->translate(0, 4, 0);
	layer5->rotate(0, 1, 0, 45);
	addChild(layer5);

	UnitCubeModel* layer6 = new UnitCubeModel();
	layer6->setTexture(leavesTextureID);
	layer6->scale(2, 1, 2);
	layer6->translate(0, 5, 0);
	layer6->rotate(0, 1, 0, 0);
	addChild(layer6);

	UnitCubeModel* layer7 = new UnitCubeModel();
	layer7->setTexture(leavesTextureID);
	layer7->scale(0.80, 0.80, 0.80);
	layer7->translate(0, 5.8, 0);
	layer7->rotate(0, 1, 0, 45);
	addChild(layer7);





	//--------------------Original Tree Model-------------------- (127 cubs with snow) (70 cubes without snow)
	/*SimpleModel* tree = new SimpleModel();

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

	//snow for the tree

	RoundLeaves* snowLayer1 = new RoundLeaves();
	snowLayer1->setTexture(snowTextureID);
	texturedElement.push_back(snowLayer1);
	snowLayer1->scale(1, 0.25, 1);
	snowLayer1->translate(0, 0.60, 0);
	tree->addChild(snowLayer1);

	RoundLeaves* snowLayer3 = new RoundLeaves();
	snowLayer3->setTexture(snowTextureID);
	texturedElement.push_back(snowLayer3);
	snowLayer3->scale(0.80, 0.25, 0.80);
	snowLayer3->translate(0, 2.4, 0);
	snowLayer3->rotate(0, 1, 0, 45);
	tree->addChild(snowLayer3);

	RoundLeaves* snowLayer5 = new RoundLeaves();
	snowLayer5->setTexture(snowTextureID);
	texturedElement.push_back(snowLayer5);
	snowLayer5->scale(0.70, 0.25, 0.70);
	snowLayer5->translate(0, 3.9, 0);
	snowLayer5->rotate(0, 1, 0, 0);
	tree->addChild(snowLayer5);

	RoundLeaves* snowLayer7 = new RoundLeaves();
	snowLayer7->setTexture(snowTextureID);
	texturedElement.push_back(snowLayer7);
	snowLayer7->scale(0.50, 0.25, 0.50);
	snowLayer7->translate(0, 5.1, 0);
	snowLayer7->rotate(0, 1, 0, 45);
	tree->addChild(snowLayer7);

	SquareLeaves* snowLayer8 = new SquareLeaves();
	snowLayer8->setTexture(snowTextureID);
	texturedElement.push_back(snowLayer8);
	snowLayer8->scale(0.5, 0.25, 0.5);
	snowLayer8->translate(0, 5.7, 0);
	snowLayer8->rotate(0, 1, 0, 45);
	tree->addChild(snowLayer8);

	CubeLeaves* snowLayer9 = new CubeLeaves();
	snowLayer9->setTexture(snowTextureID);
	texturedElement.push_back(snowLayer9);
	snowLayer9->scale(0.5, 0.23, 0.5);
	snowLayer9->translate(0, 6.15, 0);
	snowLayer9->rotate(0, 1, 0, 0);
	tree->addChild(snowLayer9);*/

	//Apply random scale to tree
	//scale(1 - horizontalChange, 1 - verticalChange, 1 - horizontalChange);
	//Apply random rotation to tree
	rotate(0, 1, 0, rotationalChange);
	translate(0, 1.5, 0);
};