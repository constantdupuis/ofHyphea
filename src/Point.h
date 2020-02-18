#pragma once

#include "ofMain.h"

class Point
{
public:

	Point()
	{
		_pos.x = 0.0f;
		_pos.y = 0.0f;
	}

	Point(float x, float y) 
	{
		_pos.x = x;
		_pos.y = y;
	}

	Point(glm::vec2 pos)
	{
		_pos = pos;
	}
	
	glm::vec2& pos() { return _pos; }

protected:
	glm::vec2 _pos;
};