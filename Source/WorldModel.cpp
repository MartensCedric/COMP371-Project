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

WorldModel::WorldModel() {
	// Compile and link shaders here ...
	int passthroughShader = compileAndLinkShaders("../Shaders/passthrough.vshader", "../Shaders/passthrough.fshader");
	int lightAffectedShader = compileAndLinkShaders("../Shaders/phong.vshader", "../Shaders/phong.fshader");
	glUseProgram(passthroughShader);

	GridModel* grid = new GridModel();
	grid->setShader(passthroughShader);
	addChild(grid);
	
	AxesModel* axes = new AxesModel();
	axes->setShader(passthroughShader);
	addChild(axes);
	
	SphereModel* sphere = new SphereModel(15.0f, 36, 18);
	sphere->translate(0, 15, 0);
	models.push_back(sphere);

	/* 
	 * ----------------------------------------------------
	 *                          E5
	 * ---------------------------------------------------- 
	 */

	SimpleModel* E5 = new SimpleModel();

	EModel* E = new EModel();
	E->translate(-3.5, 0, 0);
	E5->addChild(E);

	FiveModel* five = new FiveModel();
	five->translate(1.5, 0, 0);
	E5->addChild(five);

	E5->translate(0, 3.5, 0);
	models.push_back(E5);

	/* 
	 * ----------------------------------------------------
	 *                          I3
	 * ---------------------------------------------------- 
	 */

	SimpleModel* I3 = new SimpleModel();

	IModel* I = new IModel();
	I->translate(-2, 0, 0);
	I3->addChild(I);

	ThreeModel* three = new ThreeModel();
	three->translate(2, 0, 0);

	I3->addChild(three);
	I3->translate(8, 3.5, -8);

	models.push_back(I3);

	/* 
	 * ----------------------------------------------------
	 *                          I3-2
	 * ---------------------------------------------------- 
	 */

	SimpleModel* I3_2 = new SimpleModel();

	IModel* I_2 = new IModel();
	I_2->translate(-2, 0, 0);
	I3_2->addChild(I_2);

	ThreeModel* three_2 = new ThreeModel();
	three_2->translate(2, 0, 0);
	I3_2->addChild(three_2);

	I3_2->translate(8, 3.5, 8);
	//I3_2->rotate(0, 0, 1, 180.0f);

	models.push_back(I3_2);

	/* 
	 * ----------------------------------------------------
	 *                          D8
	 * ---------------------------------------------------- 
	 */

	SimpleModel* D8 = new SimpleModel();

	DModel* D = new DModel();
	D->translate(-3.5, 0, 0);
	D8->addChild(D);

	EightModel* eight = new EightModel();
	eight->translate(1.5, 0, 0);
	D8->addChild(eight);

	D8->translate(-8, 3.5, 8);
	//D8->rotate(0, 1, 0, 175);
	models.push_back(D8);

	/* 
	 * ----------------------------------------------------
	 *                          T5
	 * ---------------------------------------------------- 
	 */

	SimpleModel* T5 = new SimpleModel();

	TModel* T = new TModel();
	T->translate(-2, 0, 0);
	T5->addChild(T);
	
	FiveModel* five_2 = new FiveModel();
	five_2->translate(1.5, 0, 0);
	T5->addChild(five_2);

	T5->translate(-8, 3.5, -8);
	models.push_back(T5);

	//----------Models----------
	for (auto it = models.begin(); it != models.end(); it++)
	{
		(*it)->setShader(lightAffectedShader);
		addChild(*it);
	}
};