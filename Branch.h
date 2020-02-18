#pragma once

#include "ofMain.h"
#include "Bud.h"
#include "QuadTree.h"

class Branch {
public:
	Branch() {}
protected:
	Branch parentBranch;
	Bud rootBud;
	Bud lastBud;
	QuadTree<Bud> qtree;
	ofRectangle fences;


private:

};
