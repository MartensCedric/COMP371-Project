#pragma once
#include "SimpleModel.hpp"
#include "UnitCubeModel.hpp"
#include <glm/glm.hpp>

/**
* A subclass for an easy implementation of a digital clock segment.
* It is simply a stretched unit cube.
*/
class DigitalClockSegment : public UnitCubeModel {
public:
	DigitalClockSegment();
};