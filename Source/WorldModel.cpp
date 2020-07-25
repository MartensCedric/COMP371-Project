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
	
	/* 
	 * ----------------------------------------------------
	 *                          T5
	 * ---------------------------------------------------- 
	 */

	SimpleModel* T5 = new SimpleModel();

	TModel* T = new TModel();
	T->setTexture(boxTextureID);
	texturedElement.push_back(T);
	T->translate(-2, 0, 0);
	T5->addChild(T);
	
	FiveModel* five_2 = new FiveModel();
	five_2->setTexture(goldTextureID);
	texturedElement.push_back(five_2);
	five_2->translate(1.5, 0, 0);
	T5->addChild(five_2);

	SphereModel* sphere_4 = new SphereModel(6.0f, 36, 18);
	sphere_4->translate(0, 4, 0);
	spheres.push_back(sphere_4);
	T5->addChild(sphere_4);

	T5->translate(-18, 3.5, -18);
	models.push_back(T5);

	/* 
	 * ----------------------------------------------------
	 *                          I3
	 * ---------------------------------------------------- 
	 */

	SimpleModel* I3 = new SimpleModel();

	IModel* I = new IModel();
	I->setTexture(boxTextureID);
	texturedElement.push_back(I);
	I->translate(-2, 0, 0);
	I3->addChild(I);

	ThreeModel* three = new ThreeModel();
	three->setTexture(goldTextureID);
	texturedElement.push_back(three);
	three->translate(2, 0, 0);
	I3->addChild(three);

	SphereModel* sphere_1 = new SphereModel(6.0f, 36, 18);
	sphere_1->translate(0, 4, 0);
	spheres.push_back(sphere_1);
	I3->addChild(sphere_1);

	I3->translate(18, 3.5, -18);
	models.push_back(I3);

	/* 
	 * ----------------------------------------------------
	 *                          E5
	 * ---------------------------------------------------- 
	 */

	SimpleModel* E5 = new SimpleModel();

	EModel* E = new EModel();
	E->setTexture(boxTextureID);
	texturedElement.push_back(E);
	E->translate(-3.5, 0, 0);
	E5->addChild(E);

	FiveModel* five = new FiveModel();
	five->setTexture(goldTextureID);
	texturedElement.push_back(five);
	five->translate(1.5, 0, 0);
	E5->addChild(five);

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

	SimpleModel* I3_2 = new SimpleModel();

	IModel* I_2 = new IModel();
	I_2->setTexture(boxTextureID);
	texturedElement.push_back(I_2);
	I_2->translate(-2, 0, 0);
	I3_2->addChild(I_2);

	ThreeModel* three_2 = new ThreeModel();
	three_2->setTexture(goldTextureID);
	texturedElement.push_back(three_2);
	three_2->translate(2, 0, 0);
	I3_2->addChild(three_2);

	SphereModel* sphere_2 = new SphereModel(6.0f, 36, 18);
	sphere_2->translate(0, 4, 0);
	spheres.push_back(sphere_2);
	I3_2->addChild(sphere_2);

	I3_2->translate(18, 3.5, 18);
	models.push_back(I3_2);

	/* 
	 * ----------------------------------------------------
	 *                          D8
	 * ---------------------------------------------------- 
	 */

	SimpleModel* D8 = new SimpleModel();

	DModel* D = new DModel();
	D->setTexture(boxTextureID);
	texturedElement.push_back(D);
	D->translate(-3.5, 0, 0);
	D8->addChild(D);

	EightModel* eight = new EightModel();
	eight->setTexture(goldTextureID);
	texturedElement.push_back(eight);
	eight->translate(1.5, 0, 0);
	D8->addChild(eight);

	SphereModel* sphere_3 = new SphereModel(6.0f, 36, 18);
	sphere_3->translate(0, 4, 0);
	spheres.push_back(sphere_3);	
	D8->addChild(sphere_3);

	D8->translate(-18, 3.5, 18);
	models.push_back(D8);


	for (auto it = models.begin(); it != models.end(); it++)
		addChild(*it);
};


