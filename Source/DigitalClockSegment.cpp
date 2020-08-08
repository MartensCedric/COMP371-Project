#include "includes/DigitalClockSegment.h"
#include "includes/UnitCubeModel.hpp"

/**
* A subclass for an easy implementation of a digital clock segment.
* It is simply a stretched unit cube with two child unit cubes that are the "pointy part" of the font.
*/
DigitalClockSegment::DigitalClockSegment() : UnitCubeModel::UnitCubeModel() {
	this->scale(1, 0.6, 0.25);

	UnitCubeModel* pointyLeft = new UnitCubeModel();
	pointyLeft->translate(-0.43, 0, 0);
	pointyLeft->scale(0.75, 0.75, 1);
	pointyLeft->rotate(0, 0, 1, 45);
	addChild(pointyLeft);

	UnitCubeModel* pointyRight = new UnitCubeModel();
	pointyRight->translate(0.43, 0, 0);
	pointyRight->scale(0.75, 0.75, 1);
	pointyRight->rotate(0, 0, 1, 45);
	addChild(pointyRight);
}
