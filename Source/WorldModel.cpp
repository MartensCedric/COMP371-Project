#include "includes/WorldModel.hpp"

EModel::EModel() {
	setupAttribPointer();

	UnitCubeModel* left = new UnitCubeModel();
	left->scale(1, 5, 1);

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
	addChild(bottom);
};

FiveModel::FiveModel() {
	setupAttribPointer();

	UnitCubeModel* left = new UnitCubeModel();
	left->scale(1, 2.5, 1);
	left->translate(0, 1.25, 0);

	UnitCubeModel* right = new UnitCubeModel();
	right->scale(1, 2.5, 1);
	right->translate(2, -1.25, 0);

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
	addChild(right);
	addChild(top);
	addChild(middle);
	addChild(bottom);
};

IModel::IModel() {
	setupAttribPointer();
	
	UnitCubeModel* top = new UnitCubeModel();
	top->scale(2, 1, 1);
	top->translate(0, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(1, 5, 1);
	middle->translate(0, 0, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(2, 1, 1);
	bottom->translate(0, -3, 0);

	addChild(top);
	addChild(middle);
	addChild(bottom);
};

ThreeModel::ThreeModel() {
	setupAttribPointer();

	UnitCubeModel* right = new UnitCubeModel();
	right->scale(1, 5, 1);
	right->translate(2, 0, 0);

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 1, 1);
	top->translate(1, 3, 0);

	UnitCubeModel* middle = new UnitCubeModel();
	middle->scale(3, 1, 1);
	middle->translate(1, 0, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(3, 1, 1);
	bottom->translate(1, -3, 0);

	addChild(right);
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
	middle->scale(1, 5, 1);
	middle->translate(0, 0, 0);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(1, 1, 1);
	bottom->translate(0, -3, 0);

	addChild(top);
	addChild(middle);
	addChild(bottom);
};

DModel::DModel() {
	setupAttribPointer();

	UnitCubeModel* left = new UnitCubeModel();
	left->scale(1, 7.1, 1);

	UnitCubeModel* right = new UnitCubeModel();
	right->scale(1, 5.5, 1);
	right->translate(2.3, 0, 0);

	UnitCubeModel* top = new UnitCubeModel();
	top->scale(3, 1, 1);
	top->translate(1.2, 2.83, 0);
	top->rotate(0, 0, 1, -11);

	UnitCubeModel* bottom = new UnitCubeModel();
	bottom->scale(3, 1, 1);
	bottom->translate(1.2, -2.83, 0);
	bottom->rotate(0, 0, 1, 11);

	addChild(left);
	addChild(top);
	addChild(bottom);
	addChild(right);
};

EightModel::EightModel() {
	setupAttribPointer();

	UnitCubeModel* right = new UnitCubeModel();
	right->scale(1, 5, 1);
	right->translate(2, 0, 0);

	UnitCubeModel* left = new UnitCubeModel();
	left->scale(1, 5, 1);
	left->translate(0, 0, 0);

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
	addChild(right);
	addChild(top);
	addChild(middle);
	addChild(bottom);
};


PlaneModel* plane = nullptr;
GridModel* grid = nullptr;
AxesModel* axes = nullptr;

void WorldModel::setGridShader(int shaderProgram) { grid->setShader(shaderProgram); }
void WorldModel::setAxesShader(int shaderProgram) { axes->setShader(shaderProgram); }
void WorldModel::setPlaneShader(int shaderProgram) { plane->setShader(shaderProgram); }

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
	
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	plane = new PlaneModel();
	plane->setTexture(grassTextureID);
	plane->translate(0, 0.1, 0);
	texturedElement.push_back(plane);
	addChild(plane);

	grid = new GridModel();
	addChild(grid);
	
	axes = new AxesModel();
	axes->translate(0, 0.1, 0);
	addChild(axes);

	// Alpha numerical models
	// Splitting each model in two: 2/3 assigned to the bottom, the remainder 1/3 to the top
	SimpleModel* E5 = new SimpleModel();
	SimpleModel* E5top = new SimpleModel();
	SimpleModel* E5bottom = new SimpleModel();
	SimpleModel* I31 = new SimpleModel();
	SimpleModel* I32 = new SimpleModel();
	SimpleModel* T5 = new SimpleModel();
	SimpleModel* D8 = new SimpleModel();
	
	/* 
	 * ----------------------------------------------------
	 *                          T5
	 * ---------------------------------------------------- 
	 */

	/*SimpleModel* T5 = new SimpleModel();

	TModel* T = new TModel();
	T->setTexture(boxTextureID);
	texturedElement.push_back(T);
	T->translate(-2, 0, 0);
	T5->addChild(T);
	
	FiveModel* five_2 = new FiveModel();
	five_2->setTexture(goldTextureID);
	texturedElement.push_back(five_2);
	five_2->translate(1.5, 0, 0);
	T5->addChild(five_2);*/


	//Draw a T
	SimpleModel* T = new SimpleModel();
	SimpleModel* tTopDiv = new SimpleModel();
	SimpleModel* tBottomDiv = new SimpleModel();
	T->setTexture(boxTextureID);
	texturedElement.push_back(T);

	T->setupAttribPointer();
	T->translate(-2, 0, 0);

	UnitCubeModel* tTop = new UnitCubeModel();
	tTop->scale(4, 1, 1);
	tTop->translate(0, 3, 0);

	UnitCubeModel* tMiddle = new UnitCubeModel();
	tMiddle->scale(1, 3, 1);
	tMiddle->translate(0, 2, 0);

	UnitCubeModel* tBottom = new UnitCubeModel();
	tBottom->scale(1, 4, 1);
	tBottom->translate(0, -1.5, 0);

	tTopDiv->addChild(tTop);
	tTopDiv->addChild(tMiddle);
	tBottomDiv->addChild(tBottom);

	T->addChild(tTopDiv);
	T->addChild(tBottomDiv);

	modelsBottom.push_back(tBottomDiv);
	modelsTop.push_back(tTopDiv);

	T5->addChild(T);

	// Draw a 5
	SimpleModel* tFive = new SimpleModel();
	SimpleModel* tFiveTopDiv = new SimpleModel();
	SimpleModel* tFiveBottomDiv = new SimpleModel();
	tFive->setTexture(goldTextureID);
	texturedElement.push_back(tFive);

	tFive->setupAttribPointer();
	tFive->translate(2, 0, 0);

	UnitCubeModel* tFiveLeft = new UnitCubeModel();
	tFiveLeft->scale(1, 2.5, 1);
	tFiveLeft->translate(0, 1.75, 0);

	UnitCubeModel* tFiveRight = new UnitCubeModel();
	tFiveRight->scale(1, 2, 1);
	tFiveRight->translate(2, -1.5, 0);

	UnitCubeModel* tFiveTop = new UnitCubeModel();
	tFiveTop->scale(3, 1, 1);
	tFiveTop->translate(1, 3, 0);

	UnitCubeModel* tFiveMiddle = new UnitCubeModel();
	tFiveMiddle->scale(3, 1, 1);
	tFiveMiddle->translate(1, 0, 0);

	UnitCubeModel* tFiveBottom = new UnitCubeModel();
	tFiveBottom->scale(3, 1, 1);
	tFiveBottom->translate(1, -3, 0);

	tFiveTopDiv->addChild(tFiveLeft);
	tFiveTopDiv->addChild(tFiveTop);
	tFiveBottomDiv->addChild(tFiveMiddle);
	tFiveBottomDiv->addChild(tFiveRight);
	tFiveBottomDiv->addChild(tFiveBottom);

	tFive->addChild(tFiveTopDiv);
	tFive->addChild(tFiveBottomDiv);

	T5->addChild(tFive);

	T5->translate(-25, 3.5, -25);

	modelsBottom.push_back(tFiveBottomDiv);
	modelsTop.push_back(tFiveTopDiv);
	models.push_back(T5);

	SphereModel* sphere_4 = new SphereModel(6.0f, 36, 18);
	sphere_4->translate(0, 4, 0);
	spheres.push_back(sphere_4);
	T5->addChild(sphere_4);

	T5->translate(-18, 3.5, -18);

	/* 
	 * ----------------------------------------------------
	 *                          I3
	 * ---------------------------------------------------- 
	 */

	/*SimpleModel* I3 = new SimpleModel();

	IModel* I = new IModel();
	I->setTexture(boxTextureID);
	texturedElement.push_back(I);
	I->translate(-2, 0, 0);
	I3->addChild(I);

	ThreeModel* three = new ThreeModel();
	three->setTexture(goldTextureID);
	texturedElement.push_back(three);
	three->translate(2, 0, 0);
	I3->addChild(three);*/

	//Draw an I
	SimpleModel* I = new SimpleModel();
	SimpleModel* iTopDiv = new SimpleModel();
	SimpleModel* iBottomDiv = new SimpleModel();
	I->setTexture(boxTextureID);
	texturedElement.push_back(I);

	iTopDiv->setupAttribPointer();
	iBottomDiv->setupAttribPointer();
	I->setupAttribPointer();

	I->translate(-2, 0, 0);

	UnitCubeModel* iTop = new UnitCubeModel();
	iTop->scale(2, 1, 1);
	iTop->translate(0, 3, 0);

	UnitCubeModel* iMiddleTop = new UnitCubeModel();
	UnitCubeModel* iMiddleBottom = new UnitCubeModel();
	iMiddleTop->scale(1, 2, 1);
	iMiddleTop->translate(0, 2, 0);
	iMiddleBottom->scale(1, 4, 1);
	iMiddleBottom->translate(0, -1, 0);

	UnitCubeModel* iBottom = new UnitCubeModel();
	iBottom->scale(2, 1, 1);
	iBottom->translate(0, -3, 0);

	iTopDiv->addChild(iTop);
	iTopDiv->addChild(iMiddleTop);

	iBottomDiv->addChild(iMiddleBottom);
	iBottomDiv->addChild(iBottom);

	I->addChild(iTopDiv);
	I->addChild(iBottomDiv);

	I31->addChild(I);

	modelsTop.push_back(iTopDiv);
	modelsBottom.push_back(iBottomDiv);

	//Draw a 3
	SimpleModel* three = new SimpleModel();
	SimpleModel* threeTopDiv = new SimpleModel();
	SimpleModel* threeBottomDiv = new SimpleModel();
	three->setTexture(goldTextureID);
	texturedElement.push_back(three);

	UnitCubeModel* threeRightTop = new UnitCubeModel();
	threeRightTop->scale(1, 3, 1);
	threeRightTop->translate(2, 2, 0);

	UnitCubeModel* threeRightBottom = new UnitCubeModel();
	threeRightBottom->scale(1, 3, 1);
	threeRightBottom->translate(2, -2, 0);

	UnitCubeModel* threeTop = new UnitCubeModel();
	threeTop->scale(3, 1, 1);
	threeTop->translate(1, 3, 0);

	UnitCubeModel* threeMiddle = new UnitCubeModel();
	threeMiddle->scale(3, 1, 1);
	threeMiddle->translate(1, 0, 0);

	UnitCubeModel* threeBottom = new UnitCubeModel();
	threeBottom->scale(3, 1, 1);
	threeBottom->translate(1, -3, 0);

	threeTopDiv->addChild(threeTop);
	threeTopDiv->addChild(threeRightTop);
	threeBottomDiv->addChild(threeRightBottom);
	threeBottomDiv->addChild(threeMiddle);
	threeBottomDiv->addChild(threeBottom);

	three->addChild(threeBottomDiv);
	three->addChild(threeTopDiv);

	I31->addChild(three);

	modelsBottom.push_back(threeBottomDiv);
	modelsTop.push_back(threeTopDiv);

	I31->translate(25, 3.5, -25);

	SphereModel* sphere_1 = new SphereModel(6.0f, 36, 18);
	sphere_1->translate(0, 4, 0);
	spheres.push_back(sphere_1);
	I31->addChild(sphere_1);

	I31->translate(18, 3.5, -18);
	models.push_back(I31);

	/* 
	 * ----------------------------------------------------
	 *                          E5
	 * ---------------------------------------------------- 
	 */

	/*SimpleModel* E5 = new SimpleModel();

	EModel* E = new EModel();
	E->setTexture(boxTextureID);
	texturedElement.push_back(E);
	E->translate(-3.5, 0, 0);
	E5->addChild(E);

	FiveModel* five = new FiveModel();
	five->setTexture(goldTextureID);
	texturedElement.push_back(five);
	five->translate(1.5, 0, 0);
	E5->addChild(five);*/

	// Draw an E
	// split top/bot divisions
	SimpleModel* E = new SimpleModel();
	SimpleModel* eTopDiv = new SimpleModel();
	SimpleModel* eBottomDiv = new SimpleModel();
	E->setTexture(boxTextureID);
	texturedElement.push_back(E);

	UnitCubeModel* eLeftTop = new UnitCubeModel();
	eLeftTop->scale(1, 3, 1);
	eLeftTop->translate(0, 2, 0);

	UnitCubeModel* eLeftBottom = new UnitCubeModel();
	eLeftBottom->scale(1, 3, 1);
	eLeftBottom->translate(0, -2, 0);

	UnitCubeModel* eTop = new UnitCubeModel();
	eTop->scale(3, 1, 1);
	eTop->translate(1, 3, 0);

	UnitCubeModel* eMiddle = new UnitCubeModel();
	eMiddle->scale(3, 1, 1);
	eMiddle->translate(1, 0, 0);

	UnitCubeModel* eBottom = new UnitCubeModel();
	eBottom->scale(3, 1, 1);
	eBottom->translate(1, -3, 0);

	eTopDiv->addChild(eLeftTop);
	eTopDiv->addChild(eTop);
	eBottomDiv->addChild(eLeftBottom);
	eBottomDiv->addChild(eMiddle);
	eBottomDiv->addChild(eBottom);

	E->addChild(eTopDiv);
	E->addChild(eBottomDiv);

	eTopDiv->translate(-3.5, 0, 0);
	eBottomDiv->translate(-3.5, 0, 0);

	E5->addChild(E);

	modelsTop.push_back(eTopDiv);
	modelsBottom.push_back(eBottomDiv);

	// Draw a 5
	///*
	SimpleModel* five = new SimpleModel();
	SimpleModel* fiveTopDiv = new SimpleModel();
	SimpleModel* fiveBottomDiv = new SimpleModel();
	five->setTexture(goldTextureID);
	texturedElement.push_back(five);

	UnitCubeModel* fiveLeft = new UnitCubeModel();
	fiveLeft->scale(1, 2.5, 1);
	fiveLeft->translate(0, 1.25, 0);

	UnitCubeModel* fiveRight = new UnitCubeModel();
	fiveRight->scale(1, 2.5, 1);
	fiveRight->translate(2, -1.25, 0);

	UnitCubeModel* fiveTop = new UnitCubeModel();
	fiveTop->scale(3, 1, 1);
	fiveTop->translate(1, 3, 0);

	UnitCubeModel* fiveMiddle = new UnitCubeModel();
	fiveMiddle->scale(3, 1, 1);
	fiveMiddle->translate(1, 0, 0);

	UnitCubeModel* fiveBottom = new UnitCubeModel();
	fiveBottom->scale(3, 1, 1);
	fiveBottom->translate(1, -3, 0);

	fiveTopDiv->addChild(fiveLeft);
	fiveBottomDiv->addChild(fiveRight);
	fiveTopDiv->addChild(fiveTop);
	fiveBottomDiv->addChild(fiveMiddle);
	fiveBottomDiv->addChild(fiveBottom);

	fiveTopDiv->translate(1.5, 0, 0);
	fiveBottomDiv->translate(1.5, 0, 0);

	five->addChild(fiveTopDiv);
	five->addChild(fiveBottomDiv);
	E5->addChild(five);

	modelsTop.push_back(fiveTopDiv);
	modelsBottom.push_back(fiveBottomDiv);

	SphereModel* sphere = new SphereModel(6.0f, 36, 18);
	sphere->translate(0, 4, 0);
	spheres.push_back(sphere);
	E5->addChild(sphere);

	E5->translate(0, 3.5, 0);
	models.push_back(E5);

	/* 
	 * ----------------------------------------------------
	 *                          I3-2
	 * ---------------------------------------------------- 
	 */

	/*SimpleModel* I3_2 = new SimpleModel();

	IModel* I_2 = new IModel();
	I_2->setTexture(boxTextureID);
	texturedElement.push_back(I_2);
	I_2->translate(-2, 0, 0);
	I3_2->addChild(I_2);

	ThreeModel* three_2 = new ThreeModel();
	three_2->setTexture(goldTextureID);
	texturedElement.push_back(three_2);
	three_2->translate(2, 0, 0);
	I3_2->addChild(three_2);*/

	//Draw an I
	SimpleModel* I2 = new SimpleModel();
	SimpleModel* iTopDiv2 = new SimpleModel();
	SimpleModel* iBottomDiv2 = new SimpleModel();
	I2->setTexture(boxTextureID);
	texturedElement.push_back(I2);

	I2->translate(-2, 0, 0);

	UnitCubeModel* iTop2 = new UnitCubeModel();
	iTop2->scale(2, 1, 1);
	iTop2->translate(0, 3, 0);

	UnitCubeModel* iMiddleTop2 = new UnitCubeModel();
	UnitCubeModel* iMiddleBottom2 = new UnitCubeModel();

	iMiddleTop2->scale(1, 4, 1);
	iMiddleTop2->translate(0, 1, 0);
	iMiddleBottom2->scale(1, 2, 1);
	iMiddleBottom2->translate(0, -2, 0);

	UnitCubeModel* iBottom2 = new UnitCubeModel();
	iBottom2->scale(2, 1, 1);
	iBottom2->translate(0, -3, 0);

	// this is backwards because of the final 180 rotate at the end
	iTopDiv2->addChild(iMiddleBottom2);
	iTopDiv2->addChild(iBottom2);
	iBottomDiv2->addChild(iTop2);
	iBottomDiv2->addChild(iMiddleTop2);

	I2->addChild(iTopDiv2);
	I2->addChild(iBottomDiv2);

	modelsBottom.push_back(iBottomDiv2);
	modelsTop.push_back(iTopDiv2);

	I32->addChild(I2);

	//Draw a 3
	SimpleModel* three2 = new SimpleModel();
	SimpleModel* threeTopDiv2 = new SimpleModel();
	SimpleModel* threeBottomDiv2 = new SimpleModel();
	three2->setTexture(goldTextureID);
	texturedElement.push_back(three2);

	UnitCubeModel* threeRightTop2 = new UnitCubeModel();
	threeRightTop2->scale(1, 3, 1);
	threeRightTop2->translate(2, 2, 0);

	UnitCubeModel* threeRightBottom2 = new UnitCubeModel();
	threeRightBottom2->scale(1, 3, 1);
	threeRightBottom2->translate(2, -2, 0);

	UnitCubeModel* threeTop2 = new UnitCubeModel();
	threeTop2->scale(3, 1, 1);
	threeTop2->translate(1, 3, 0);

	UnitCubeModel* threeMiddle2 = new UnitCubeModel();
	threeMiddle2->scale(3, 1, 1);
	threeMiddle2->translate(1, 0, 0);

	UnitCubeModel* threeBottom2 = new UnitCubeModel();
	threeBottom2->scale(3, 1, 1);
	threeBottom2->translate(1, -3, 0);

	// this is backwards because of the final 180 rotate at the end
	threeTopDiv2->addChild(threeRightBottom2);
	threeTopDiv2->addChild(threeMiddle2);
	threeTopDiv2->addChild(threeBottom2);
	threeBottomDiv2->addChild(threeTop2);
	threeBottomDiv2->addChild(threeRightTop2);

	three2->addChild(threeTopDiv2);
	three2->addChild(threeBottomDiv2);

	three2->translate(2, 0, 0);

	I32->addChild(three2);
	I32->translate(25, 3.5, 25);
	I32->rotate(0, 0, 1, 180.0f);

	modelsBottom.push_back(threeBottomDiv2);
	modelsTop.push_back(threeTopDiv2);

	SphereModel* sphere_2 = new SphereModel(6.0f, 36, 18);
	sphere_2->translate(0, 4, 0);
	spheres.push_back(sphere_2);
	I32->addChild(sphere_2);

	I32->translate(18, 3.5, 18);
	models.push_back(I32);

	/* 
	 * ----------------------------------------------------
	 *                          D8
	 * ---------------------------------------------------- 
	 */

	/*SimpleModel* D8 = new SimpleModel();

	DModel* D = new DModel();
	D->setTexture(boxTextureID);
	texturedElement.push_back(D);
	D->translate(-3.5, 0, 0);
	D8->addChild(D);

	EightModel* eight = new EightModel();
	eight->setTexture(goldTextureID);
	texturedElement.push_back(eight);
	eight->translate(1.5, 0, 0);
	D8->addChild(eight);*/

	//Draw a D
	SimpleModel* D = new SimpleModel();
	SimpleModel* dTopDiv = new SimpleModel();
	SimpleModel* dBottomDiv = new SimpleModel();
	D->setTexture(boxTextureID);
	texturedElement.push_back(D);

	UnitCubeModel* dLeftTop = new UnitCubeModel();
	UnitCubeModel* dLeftBottom = new UnitCubeModel();

	dLeftBottom->scale(1, 3.55, 1);
	dLeftBottom->translate(0, -1.5, 0);
	dLeftTop->scale(1, 3.55, 1);
	dLeftTop->translate(0, 1.5, 0);

	UnitCubeModel* dRightTop = new UnitCubeModel();
	UnitCubeModel* dRightBottom = new UnitCubeModel();

	dRightTop->scale(1, 2.75, 1);
	dRightTop->translate(2.3, 1.25, 0);

	dRightBottom->scale(1, 2.75, 1);
	dRightBottom->translate(2.3, -1.25, 0);

	UnitCubeModel* dTop = new UnitCubeModel();
	dTop->scale(3, 1, 1);
	dTop->translate(1.2, 2.83, 0);
	dTop->rotate(0, 0, 1, -11);


	UnitCubeModel* dBottom = new UnitCubeModel();
	dBottom->scale(3, 1, 1);
	dBottom->translate(1.2, -2.83, 0);
	dBottom->rotate(0, 0, 1, 11);

	dTopDiv->addChild(dLeftTop);
	dTopDiv->addChild(dTop);
	dTopDiv->addChild(dRightTop);
	dBottomDiv->addChild(dBottom);
	dBottomDiv->addChild(dRightBottom);
	dBottomDiv->addChild(dLeftBottom);

	D->addChild(dBottomDiv);
	D->addChild(dTopDiv);

	modelsTop.push_back(dTopDiv);
	modelsBottom.push_back(dBottomDiv);

	D->translate(-3.5, 0, 0);
	D8->addChild(D);

	// Draw a 8
	SimpleModel* eight = new SimpleModel();
	SimpleModel* eightTopDiv = new SimpleModel();
	SimpleModel* eightBottomDiv = new SimpleModel();
	eight->setTexture(goldTextureID);
	texturedElement.push_back(eight);

	UnitCubeModel* eightRightTop = new UnitCubeModel();
	UnitCubeModel* eightRightBottom = new UnitCubeModel();

	eightRightTop->scale(1, 2.5, 1);
	eightRightTop->translate(2, 1.5, 0);
	eightRightBottom->scale(1, 2.5, 1);
	eightRightBottom->translate(2, -1.5, 0);

	UnitCubeModel* eightLeftTop = new UnitCubeModel();
	UnitCubeModel* eightLeftBottom = new UnitCubeModel();
	eightLeftTop->scale(1, 2.5, 1);
	eightLeftTop->translate(0, 1.5, 0);
	eightLeftBottom->scale(1, 2.5, 1);
	eightLeftBottom->translate(0, -1.5, 0);

	UnitCubeModel* eightTop = new UnitCubeModel();
	eightTop->scale(3, 1, 1);
	eightTop->translate(1, 3, 0);

	UnitCubeModel* eightMiddle = new UnitCubeModel();
	eightMiddle->scale(3, 1, 1);
	eightMiddle->translate(1, 0, 0);

	UnitCubeModel* eightBottom = new UnitCubeModel();
	eightBottom->scale(3, 1, 1);
	eightBottom->translate(1, -3, 0);

	eightTopDiv->addChild(eightTop);
	eightTopDiv->addChild(eightRightTop);
	eightTopDiv->addChild(eightLeftTop);
	eightBottomDiv->addChild(eightMiddle);
	eightBottomDiv->addChild(eightBottom);
	eightBottomDiv->addChild(eightRightBottom);
	eightBottomDiv->addChild(eightLeftBottom);

	eight->addChild(eightTopDiv);
	eight->addChild(eightBottomDiv);
	eight->translate(1.5, 0, 0);

	D8->addChild(eight);
	D8->translate(-25, 3.5, 25);
	D8->rotate(0, 1, 0, 175);

	modelsBottom.push_back(eightBottomDiv);
	modelsTop.push_back(eightTopDiv);

	SphereModel* sphere_3 = new SphereModel(6.0f, 36, 18);
	sphere_3->translate(0, 4, 0);
	spheres.push_back(sphere_3);	
	D8->addChild(sphere_3);

	D8->translate(-18, 3.5, 18);
	models.push_back(D8);


	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}
};


