#pragma once

#include "ofMain.h"
#include "Bud.h"
#include "QuadTree.h"

class Branch {
public:
	Branch() {}

	bool grow();
protected:
	shared_ptr<Branch> parentBranch;
	shared_ptr<Bud> rootBud;
	shared_ptr<Bud> lastBud;
	shared_ptr<QuadTree<Bud>> qtree;
	ofRectangle fences;

	std::vector<shared_ptr<Bud>> buds;
	std::vector<shared_ptr<Branch>> childBranches;

	float timeToLive = 100;
	float currentLife = 0;
	bool growing = true;

private:

};

bool Branch::grow()
{
}
