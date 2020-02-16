#pragma once

#include "ofMain.h"

class Point
{
public:
	Point(float x, float y) {
		_pos.x = x;
		_pos.y = y;
	}
	glm::vec2 _pos;
};