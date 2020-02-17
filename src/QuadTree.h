#pragma once

#include "ofMain.h"
#include "Point.h"
#include <array>

template<class T>
class QuadTree {

public:
	QuadTree(ofRectangle boundary, int capacity)
	{
		_boundary = boundary;
		_capacity = capacity;
		_subdivided = false;
	}

	void setup(ofRectangle boundary, int capacity)
	{
		_boundary = boundary;
		_capacity = capacity;
	}

	bool insert(shared_ptr<T> point)
	{
		// check template param type
		static_assert(std::is_base_of<Point, T>::value, "T should be derived from Point");

		//cout << "\ninsert (" << point->_pos.x << "x" << point->_pos.y << ")\n";
		// if point is not in our boundary just leave
		if (!_boundary.inside(point->pos())) {
			//cout << " point is not in our boundary, return\n";
			return false;
		}

		//cout << " point is in our boundary, continue\n";

		// if over capacity wreate sub QuadTree
		if (_points.size() == _capacity)
		{
			//cout << " our capacity is exceded, delegate to sub quadtree\n";
			// subdivide if needed
			subdivide();

			// insert point in sub QuadTree
			if (_topLeft->insert(point))
			{
				return true;
			}
			else if (_topRight->insert(point))
			{
				return true;
			}
			else if (_bottomLeft->insert(point))
			{
				return true;
			}
			else if (_bottomRight->insert(point))
			{
				return true;
			}
			else
			{
				throw std::runtime_error("Should never get here!");
			}
		}
		//cout << " capacity is ok, add point to our vector \n";
		// add point to this QuadTree
		_points.push_back(point);

		return true;
	}
	bool isSubdivided() { return _subdivided; }
	int nbPoints() { _points.size(); }

	void forEach( std::function<void(QuadTree<T>&)> callback);

	ofRectangle const& boundary()
	{
		return _boundary;
	}

	std::vector<shared_ptr<T>>& points()
	{
		return _points;
	}

	
private:
	std::vector<shared_ptr<T>> _points;

	ofRectangle _boundary;
	int _capacity = 4;
	bool _subdivided = false;

	unique_ptr<QuadTree<T>> _topLeft;
	unique_ptr<QuadTree<T>> _topRight;
	unique_ptr<QuadTree<T>> _bottomLeft;
	unique_ptr<QuadTree<T>> _bottomRight;

	void subdivide();

	void innerForEach( QuadTree<T>& currentQtree, std::function<void(QuadTree<T>&)> callback);
	
};

template<class T>
void QuadTree<T>::forEach(std::function<void(QuadTree<T>&)> callback)
{
	innerForEach(*this, callback);
}


template<class T>
void QuadTree<T>::innerForEach(QuadTree<T>& currentQtree, std::function<void(QuadTree<T>&)> callback)
{
	callback(currentQtree);

	if (!currentQtree.isSubdivided()) return;

	innerForEach(*(currentQtree._topLeft.get()), callback);
	innerForEach(*(currentQtree._topRight.get()), callback);
	innerForEach(*(currentQtree._bottomLeft.get()), callback);
	innerForEach(*(currentQtree._bottomRight.get()), callback);
}

//template<class T>
//void QuadTree<T>::forEachBoundary(std::function<void(const ofRectangle&)> callback)
//{
//}
//
//template<class T>
//void QuadTree<T>::forEachPoint(std::function<void(const T&)> callback)
//{
//}

template<class T>
void QuadTree<T>::subdivide()
{
	//cout << "subdivide\n";
	if (!_subdivided)
	{
		//cout << " not yet subdivided, do it\n";
		_subdivided = true;

		float x = _boundary.x;
		float y = _boundary.y;
		float nw = _boundary.width / 2.0;
		float nh = _boundary.height / 2.0;

		_topLeft = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x, y, nw, nh), _capacity);
		_topRight = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x + nw, y, nw, nh), _capacity);
		_bottomLeft = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x, y + nh, nw, nh), _capacity);
		_bottomRight = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x + nw, y + nh, nw, nh), _capacity);
	}
}
