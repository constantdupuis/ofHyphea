#pragma once

#include "ofMain.h"

class Point
{
public:
	Point(float x, float y) {
		_pos.x = x;
		_pos.y = y;
	}

	static shared_ptr<Point> create(float x, float y)
	{
		return std::make_shared<Point>(x, y);
	}

	glm::vec2& const pos() { return _pos; }

private:
	glm::vec2 _pos;
};