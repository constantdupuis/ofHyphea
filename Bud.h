#pragma once

#include "ofMain.h"
#include "Point.h"
#include "Branch.h"

class Bud : Point
{
public:
	
	Bud()
	{
	}

	Bud(glm::vec2 pos, float dir, Branch parent) : Point(pos)
	{
		_dir = dir;
		_parentBranch = parent;
	}
	
	Bud(float x, float y, float dir, Branch parent) : Point(x, y)
	{	
		_dir = dir;
		_parentBranch = parent;
	}

protected:
	
	float _dir = 0;
	Branch _parentBranch;
	float _radius = 5;

private:

};
