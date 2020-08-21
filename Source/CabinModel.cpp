#include "includes/WorldModel.hpp"
#include "../Source/includes/Terrain.hpp"
#include "includes/CabinModel.hpp"
#include <cstdlib>
#include <ctime>

LogCabinBase::LogCabinBase() {
	setupAttribPointer();

	UnitCubeModel* cabin = new UnitCubeModel();
	cabin->scale(4, 4, 7);
	cabin->translate(0, 0, 0);

	addChild(cabin);
};

CabinModel::CabinModel() {
	// Load textures
	GLuint rockTextureID = loadTexture("../Assets/Textures/rock.jpg");
	GLuint trunkTextureID = loadTexture("../Assets/Textures/bark.jpg");
	//GLuint snowTextureID = loadTexture("../Assets/Textures/snow.jpg");
	GLuint logTextureID = loadTexture("../Assets/Textures/log.jpg");
	GLuint log2TextureID = loadTexture("../Assets/Textures/darklog.jpg");
	GLuint doorTextureID = loadTexture("../Assets/Textures/door.jpg");
	GLuint windowTextureID = loadTexture("../Assets/Textures/window.jpg");
	GLuint woodTextureID = loadTexture("../Assets/Textures/wood.jpg");


	//choose random house type

	//choose random number between 1 and 3
	int randomNum = (rand() % 3) + 1;

	//---------------Log cabin model 1----------------

	SimpleModel* logCabin = new SimpleModel();

	LogCabinBase* cabinbase = new LogCabinBase();
	cabinbase->setTexture(logTextureID);
	texturedElement.push_back(cabinbase);
	cabinbase->translate(0, 0, 0);
	logCabin->addChild(cabinbase);

	LogCabinBase* cabinFoundation = new LogCabinBase();
	cabinFoundation->setTexture(rockTextureID);
	texturedElement.push_back(cabinFoundation);
	cabinFoundation->translate(0, -4, 0);
	logCabin->addChild(cabinFoundation);

	LogCabinBase* cabinTopFloor = new LogCabinBase();
	cabinTopFloor->setTexture(logTextureID);
	texturedElement.push_back(cabinTopFloor);
	cabinTopFloor->scale(0.72, 0.72, 0.99);
	cabinTopFloor->translate(0, 1.95, 0);
	cabinTopFloor->rotate(0, 0, 1, 45);
	logCabin->addChild(cabinTopFloor);

	LogCabinBase* cabinLeftRoof = new LogCabinBase();
	cabinLeftRoof->setTexture(log2TextureID);
	texturedElement.push_back(cabinLeftRoof);
	cabinLeftRoof->scale(0.85, 0.0625, 1.15);
	cabinLeftRoof->translate(-1.3, 2.9, 0);
	cabinLeftRoof->rotate(0, 0, 1, 45);
	logCabin->addChild(cabinLeftRoof);

	LogCabinBase* cabinRightRoof = new LogCabinBase();
	cabinRightRoof->setTexture(log2TextureID);
	texturedElement.push_back(cabinRightRoof);
	cabinRightRoof->scale(0.90, 0.0625, 1.15);
	cabinRightRoof->translate(1.2, 3.0, 0);
	cabinRightRoof->rotate(0, 0, 1, -45);
	logCabin->addChild(cabinRightRoof);

	LogCabinBase* cabinDoor = new LogCabinBase();
	cabinDoor->setTexture(doorTextureID);
	texturedElement.push_back(cabinDoor);
	cabinDoor->scale(0.05, 0.75, 0.25);
	cabinDoor->translate(2, -0.5, 0.0);
	cabinDoor->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinDoor);

	LogCabinBase* cabinstep1 = new LogCabinBase();
	cabinstep1->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep1);
	cabinstep1->scale(0.10, 1, 0.25);
	cabinstep1->translate(2.25, -4, 0.0);
	cabinstep1->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep1);

	LogCabinBase* cabinstep2 = new LogCabinBase();
	cabinstep2->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep2);
	cabinstep2->scale(0.10, 0.90, 0.25);
	cabinstep2->translate(2.65, -4.2, 0.0);
	cabinstep2->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep2);

	LogCabinBase* cabinstep3 = new LogCabinBase();
	cabinstep3->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep3);
	cabinstep3->scale(0.10, 0.80, 0.25);
	cabinstep3->translate(3.05, -4.4, 0.0);
	cabinstep3->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep3);

	LogCabinBase* cabinstep4 = new LogCabinBase();
	cabinstep4->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep4);
	cabinstep4->scale(0.10, 0.70, 0.25);
	cabinstep4->translate(3.45, -4.6, 0.0);
	cabinstep4->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep4);

	LogCabinBase* cabinstep5 = new LogCabinBase();
	cabinstep5->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep5);
	cabinstep5->scale(0.10, 0.60, 0.25);
	cabinstep5->translate(3.85, -4.8, 0.0);
	cabinstep5->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep5);

	LogCabinBase* cabinstep6 = new LogCabinBase();
	cabinstep6->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep6);
	cabinstep6->scale(0.10, 0.50, 0.25);
	cabinstep6->translate(4.25, -5.0, 0.0);
	cabinstep6->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep6);

	LogCabinBase* cabinstep7 = new LogCabinBase();
	cabinstep7->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep7);
	cabinstep7->scale(0.10, 0.40, 0.25);
	cabinstep7->translate(4.65, -5.2, 0.0);
	cabinstep7->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep7);

	LogCabinBase* cabinstep8 = new LogCabinBase();
	cabinstep8->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep8);
	cabinstep8->scale(0.10, 0.30, 0.25);
	cabinstep8->translate(5.05, -5.4, 0.0);
	cabinstep8->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep8);

	LogCabinBase* cabinstep9 = new LogCabinBase();
	cabinstep9->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep9);
	cabinstep9->scale(0.10, 0.20, 0.25);
	cabinstep9->translate(5.45, -5.6, 0.0);
	cabinstep9->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep9);

	LogCabinBase* cabinstep10 = new LogCabinBase();
	cabinstep10->setTexture(trunkTextureID);
	texturedElement.push_back(cabinstep10);
	cabinstep10->scale(0.10, 0.10, 0.25);
	cabinstep10->translate(5.85, -5.8, 0.0);
	cabinstep10->rotate(1, 0, 0, 180);
	logCabin->addChild(cabinstep10);

	LogCabinBase* cabinWindow1 = new LogCabinBase();
	cabinWindow1->setTexture(windowTextureID);
	texturedElement.push_back(cabinWindow1);
	cabinWindow1->scale(1.05, 0.40, 0.20);
	cabinWindow1->translate(0, 0, 2.2);
	logCabin->addChild(cabinWindow1);

	LogCabinBase* cabinWindow2 = new LogCabinBase();
	cabinWindow2->setTexture(windowTextureID);
	texturedElement.push_back(cabinWindow2);
	cabinWindow2->scale(1.05, 0.40, 0.20);
	cabinWindow2->translate(0, 0, -2.2);
	logCabin->addChild(cabinWindow2);

	//Snow for log cabin 1

	//LogCabinBase* cabinLeftRoofSnow = new LogCabinBase();
	//cabinLeftRoofSnow->setTexture(snowTextureID);
	//texturedElement.push_back(cabinLeftRoofSnow);
	//cabinLeftRoofSnow->scale(0.92, 0.03125, 1.15);
	//cabinLeftRoofSnow->translate(-1.33, 3.13, 0);
	//cabinLeftRoofSnow->rotate(0, 0, 1, 45);
	//logCabin->addChild(cabinLeftRoofSnow);

	//LogCabinBase* cabinRightRoofSnow = new LogCabinBase();
	//cabinRightRoofSnow->setTexture(snowTextureID);
	//texturedElement.push_back(cabinRightRoofSnow);
	//cabinRightRoofSnow->scale(0.94, 0.03125, 1.15);
	//cabinRightRoofSnow->translate(1.28, 3.19, 0);
	//cabinRightRoofSnow->rotate(0, 0, 1, -45);
	//logCabin->addChild(cabinRightRoofSnow);

	//random rotation for log cabin 1
	logCabin->rotate(0, 1, 0, (rand() % 360) + 1);

	logCabin->translate(0, 2, 0);  //original (0, 3.5, 0)
	if (randomNum == 1)
	{
		models.push_back(logCabin);
	}


	//---------------Log cabin model 2---------------
	SimpleModel* logCabin2 = new SimpleModel();

	LogCabinBase* cabinFoundation2 = new LogCabinBase();
	cabinFoundation2->setTexture(rockTextureID);
	texturedElement.push_back(cabinFoundation2);
	cabinFoundation2->translate(0, -4, 0);
	logCabin2->addChild(cabinFoundation2);

	LogCabinBase* cabinbase2 = new LogCabinBase();
	cabinbase2->setTexture(log2TextureID);
	texturedElement.push_back(cabinbase2);
	cabinbase2->translate(0, 0, 0);
	logCabin2->addChild(cabinbase2);

	LogCabinBase* cabinDoor2 = new LogCabinBase();
	cabinDoor2->setTexture(doorTextureID);
	texturedElement.push_back(cabinDoor2);
	cabinDoor2->scale(0.05, 0.75, 0.25);
	cabinDoor2->translate(2, -0.5, 0.0);
	cabinDoor2->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabinDoor2);

	LogCabinBase* cabin2step1 = new LogCabinBase();
	cabin2step1->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step1);
	cabin2step1->scale(0.10, 1, 0.25);
	cabin2step1->translate(2.25, -4, 0.0);
	cabin2step1->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step1);

	LogCabinBase* cabin2step2 = new LogCabinBase();
	cabin2step2->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step2);
	cabin2step2->scale(0.10, 0.90, 0.25);
	cabin2step2->translate(2.65, -4.2, 0.0);
	cabin2step2->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step2);

	LogCabinBase* cabin2step3 = new LogCabinBase();
	cabin2step3->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step3);
	cabin2step3->scale(0.10, 0.80, 0.25);
	cabin2step3->translate(3.05, -4.4, 0.0);
	cabin2step3->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step3);

	LogCabinBase* cabin2step4 = new LogCabinBase();
	cabin2step4->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step4);
	cabin2step4->scale(0.10, 0.70, 0.25);
	cabin2step4->translate(3.45, -4.6, 0.0);
	cabin2step4->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step4);

	LogCabinBase* cabin2step5 = new LogCabinBase();
	cabin2step5->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step5);
	cabin2step5->scale(0.10, 0.60, 0.25);
	cabin2step5->translate(3.85, -4.8, 0.0);
	cabin2step5->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step5);

	LogCabinBase* cabin2step6 = new LogCabinBase();
	cabin2step6->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step6);
	cabin2step6->scale(0.10, 0.50, 0.25);
	cabin2step6->translate(4.25, -5.0, 0.0);
	cabin2step6->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step6);

	LogCabinBase* cabin2step7 = new LogCabinBase();
	cabin2step7->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step7);
	cabin2step7->scale(0.10, 0.40, 0.25);
	cabin2step7->translate(4.65, -5.2, 0.0);
	cabin2step7->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step7);

	LogCabinBase* cabin2step8 = new LogCabinBase();
	cabin2step8->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step8);
	cabin2step8->scale(0.10, 0.30, 0.25);
	cabin2step8->translate(5.05, -5.4, 0.0);
	cabin2step8->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step8);

	LogCabinBase* cabin2step9 = new LogCabinBase();
	cabin2step9->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step9);
	cabin2step9->scale(0.10, 0.20, 0.25);
	cabin2step9->translate(5.45, -5.6, 0.0);
	cabin2step9->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step9);

	LogCabinBase* cabin2step10 = new LogCabinBase();
	cabin2step10->setTexture(trunkTextureID);
	texturedElement.push_back(cabin2step10);
	cabin2step10->scale(0.10, 0.10, 0.25);
	cabin2step10->translate(5.85, -5.8, 0.0);
	cabin2step10->rotate(1, 0, 0, 180);
	logCabin2->addChild(cabin2step10);

	LogCabinBase* cabin2Window1 = new LogCabinBase();
	cabin2Window1->setTexture(windowTextureID);
	texturedElement.push_back(cabin2Window1);
	cabin2Window1->scale(1.05, 0.40, 0.20);
	cabin2Window1->translate(0, 0, 2.2);
	logCabin2->addChild(cabin2Window1);

	LogCabinBase* cabin2Window2 = new LogCabinBase();
	cabin2Window2->setTexture(windowTextureID);
	texturedElement.push_back(cabin2Window2);
	cabin2Window2->scale(1.05, 0.40, 0.20);
	cabin2Window2->translate(0, 0, -2.2);
	logCabin2->addChild(cabin2Window2);

	LogCabinBase* cabinroof2 = new LogCabinBase();
	cabinroof2->setTexture(log2TextureID);
	texturedElement.push_back(cabinroof2);
	cabinroof2->scale(1.2, 0.15, 1.2);
	cabinroof2->translate(0, 2, 0);
	logCabin2->addChild(cabinroof2);

	//Snow for log cabin 2

	//LogCabinBase* cabinroof2snow = new LogCabinBase();
	//cabinroof2snow->setTexture(snowTextureID);
	//texturedElement.push_back(cabinroof2snow);
	//cabinroof2snow->scale(1.2, 0.05, 1.2);
	//cabinroof2snow->translate(0, 2.4, 0);
	//logCabin2->addChild(cabinroof2snow);

	//random rotation for log cabin 2
	logCabin2->rotate(0, 1, 0, (rand() % 360) + 1);

	logCabin2->translate(0, 2, 0);  //original (0, 3.5, 0)
	if (randomNum == 2)
	{
		models.push_back(logCabin2);
	}





	//---------------Log cabin model 3---------------
	SimpleModel* logCabin3 = new SimpleModel();

	LogCabinBase* cabinFoundation3 = new LogCabinBase();
	cabinFoundation3->setTexture(rockTextureID);
	texturedElement.push_back(cabinFoundation3);
	cabinFoundation3->scale(1, 1, 0.6);
	cabinFoundation3->translate(0, -4, 0);
	logCabin3->addChild(cabinFoundation3);

	LogCabinBase* cabinbase3 = new LogCabinBase();
	cabinbase3->setTexture(woodTextureID);
	texturedElement.push_back(cabinbase3);
	cabinbase3->scale(1, 1, 0.6);
	cabinbase3->translate(0, 0, 0);
	logCabin3->addChild(cabinbase3);

	LogCabinBase* cabin3TopFloor = new LogCabinBase();
	cabin3TopFloor->setTexture(woodTextureID);
	texturedElement.push_back(cabin3TopFloor);
	cabin3TopFloor->scale(0.72, 0.72, 0.59);
	cabin3TopFloor->translate(0, 1.95, 0);
	cabin3TopFloor->rotate(0, 0, 1, 45);
	logCabin3->addChild(cabin3TopFloor);

	LogCabinBase* cabin3LeftRoof = new LogCabinBase();
	cabin3LeftRoof->setTexture(log2TextureID);
	texturedElement.push_back(cabin3LeftRoof);
	cabin3LeftRoof->scale(0.85, 0.0625, 0.7);
	cabin3LeftRoof->translate(-1.3, 2.9, 0);
	cabin3LeftRoof->rotate(0, 0, 1, 45);
	logCabin3->addChild(cabin3LeftRoof);

	LogCabinBase* cabin3RightRoof = new LogCabinBase();
	cabin3RightRoof->setTexture(log2TextureID);
	texturedElement.push_back(cabin3RightRoof);
	cabin3RightRoof->scale(0.90, 0.0625, 0.7);
	cabin3RightRoof->translate(1.2, 3.0, 0);
	cabin3RightRoof->rotate(0, 0, 1, -45);
	logCabin3->addChild(cabin3RightRoof);

	LogCabinBase* cabinDoor3 = new LogCabinBase();
	cabinDoor3->setTexture(doorTextureID);
	texturedElement.push_back(cabinDoor3);
	cabinDoor3->scale(0.05, 0.75, 0.25);
	cabinDoor3->translate(2, -0.5, 0.0);
	cabinDoor3->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabinDoor3);

	LogCabinBase* cabin3step1 = new LogCabinBase();
	cabin3step1->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step1);
	cabin3step1->scale(0.10, 1, 0.25);
	cabin3step1->translate(2.25, -4, 0.0);
	cabin3step1->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step1);

	LogCabinBase* cabin3step2 = new LogCabinBase();
	cabin3step2->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step2);
	cabin3step2->scale(0.10, 0.90, 0.25);
	cabin3step2->translate(2.65, -4.2, 0.0);
	cabin3step2->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step2);

	LogCabinBase* cabin3step3 = new LogCabinBase();
	cabin3step3->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step3);
	cabin3step3->scale(0.10, 0.80, 0.25);
	cabin3step3->translate(3.05, -4.4, 0.0);
	cabin3step3->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step3);

	LogCabinBase* cabin3step4 = new LogCabinBase();
	cabin3step4->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step4);
	cabin3step4->scale(0.10, 0.70, 0.25);
	cabin3step4->translate(3.45, -4.6, 0.0);
	cabin3step4->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step4);

	LogCabinBase* cabin3step5 = new LogCabinBase();
	cabin3step5->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step5);
	cabin3step5->scale(0.10, 0.60, 0.25);
	cabin3step5->translate(3.85, -4.8, 0.0);
	cabin3step5->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step5);

	LogCabinBase* cabin3step6 = new LogCabinBase();
	cabin3step6->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step6);
	cabin3step6->scale(0.10, 0.50, 0.25);
	cabin3step6->translate(4.25, -5.0, 0.0);
	cabin3step6->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step6);

	LogCabinBase* cabin3step7 = new LogCabinBase();
	cabin3step7->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step7);
	cabin3step7->scale(0.10, 0.40, 0.25);
	cabin3step7->translate(4.65, -5.2, 0.0);
	cabin3step7->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step7);

	LogCabinBase* cabin3step8 = new LogCabinBase();
	cabin3step8->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step8);
	cabin3step8->scale(0.10, 0.30, 0.25);
	cabin3step8->translate(5.05, -5.4, 0.0);
	cabin3step8->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step8);

	LogCabinBase* cabin3step9 = new LogCabinBase();
	cabin3step9->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step9);
	cabin3step9->scale(0.10, 0.20, 0.25);
	cabin3step9->translate(5.45, -5.6, 0.0);
	cabin3step9->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step9);

	LogCabinBase* cabin3step10 = new LogCabinBase();
	cabin3step10->setTexture(trunkTextureID);
	texturedElement.push_back(cabin3step10);
	cabin3step10->scale(0.10, 0.10, 0.25);
	cabin3step10->translate(5.85, -5.8, 0.0);
	cabin3step10->rotate(1, 0, 0, 180);
	logCabin3->addChild(cabin3step10);

	LogCabinBase* cabin3Window1 = new LogCabinBase();
	cabin3Window1->setTexture(windowTextureID);
	texturedElement.push_back(cabin3Window1);
	cabin3Window1->scale(0.40, 0.40, 0.65);
	cabin3Window1->translate(0, 0, 0);
	logCabin3->addChild(cabin3Window1);


	//Snow for log cabin 3

	//LogCabinBase* cabin3LeftRoofSnow = new LogCabinBase();
	//cabin3LeftRoofSnow->setTexture(snowTextureID);
	//texturedElement.push_back(cabin3LeftRoofSnow);
	//cabin3LeftRoofSnow->scale(0.92, 0.03125, 0.7);
	//cabin3LeftRoofSnow->translate(-1.33, 3.13, 0);
	//cabin3LeftRoofSnow->rotate(0, 0, 1, 45);
	//logCabin3->addChild(cabin3LeftRoofSnow);

	//LogCabinBase* cabin3RightRoofSnow = new LogCabinBase();
	//cabin3RightRoofSnow->setTexture(snowTextureID);
	//texturedElement.push_back(cabin3RightRoofSnow);
	//cabin3RightRoofSnow->scale(0.94, 0.03125, 0.7);
	//cabin3RightRoofSnow->translate(1.28, 3.19, 0);
	//cabin3RightRoofSnow->rotate(0, 0, 1, -45);
	//logCabin3->addChild(cabin3RightRoofSnow);

	//random rotation for log cabin 3
	logCabin3->rotate(0, 1, 0, (rand() % 360) + 1);

	logCabin3->translate(0, 2, 0);  //original (0, 3.5, 0)
	if (randomNum == 3)
	{
		models.push_back(logCabin3);
	}

	for (auto it = models.begin(); it != models.end(); it++)
	{
		addChild(*it);
	}
};

CabinModel::~CabinModel() {}