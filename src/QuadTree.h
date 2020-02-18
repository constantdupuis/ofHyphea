#pragma once

#include "ofMain.h"
#include "Point.h"
#include <array>

template<class T>
class QuadTree {

public:
	QuadTree(std::unique_ptr<ofRectangle> boundary, int capacity)
	{
		_boundary = std::move(boundary);
		_capacity = capacity;
		_subdivided = false;
	}

	ofRectangle const& boundary();
	shared_ptr<std::vector<shared_ptr<T>>> const points();

	bool insert(shared_ptr<T> point);
	bool isSubdivided() { return _subdivided; }

	shared_ptr<std::vector<shared_ptr<T>>> query(ofRectangle area);

	void forEach( std::function<void(QuadTree<T>&)> cb);

private:
	shared_ptr<std::vector<shared_ptr<T>>> _points = std::make_shared<std::vector<shared_ptr<T>>>();
	std::unique_ptr<ofRectangle> _boundary;
	int _capacity = 4;
	bool _subdivided = false;

	std::unique_ptr<QuadTree<T>> _topLeft;
	std::unique_ptr<QuadTree<T>> _topRight;
	std::unique_ptr<QuadTree<T>> _bottomLeft;
	std::unique_ptr<QuadTree<T>> _bottomRight;

	void subdivide();

	void innerForEach( QuadTree<T>* currentQtree, std::function<void(QuadTree<T>&)> callback);

	void innerQuery(ofRectangle area, shared_ptr<std::vector<shared_ptr<T>>> found);
	
};

template<class T>
bool QuadTree<T>::insert(shared_ptr<T> point)
{
	// check template param type
	static_assert(std::is_base_of<Point, T>::value, "T should be derived from Point");

	//cout << "\ninsert (" << point->_pos.x << "x" << point->_pos.y << ")\n";
	// if point is not in our boundary just leave
	if (!_boundary->inside(point->_pos)) {
		//cout << " point is not in our boundary, return\n";
		return false;
	}
	
	//cout << " point is in our boundary, continue\n";

	// if over capacity wreate sub QuadTree
	if (_points->size() == _capacity)
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
	_points->push_back(point);

	return true;
}

template<class T>
inline shared_ptr<std::vector<shared_ptr<T>>> QuadTree<T>::query(ofRectangle area)
{
	auto ret = make_shared<std::vector<shared_ptr<T>>>();
	
	innerQuery(area, ret);

	return ret;
}

template<class T>
void QuadTree<T>::forEach(std::function<void(QuadTree<T>&)> callback)
{
	innerForEach(this, callback);
}

template<class T>
void QuadTree<T>::innerForEach(QuadTree<T>* currentQtree, std::function<void(QuadTree<T>&)> callback)
{
	callback(*(currentQtree));

	if (!currentQtree->isSubdivided()) return;

	innerForEach(currentQtree->_topLeft.get(), callback);
	innerForEach(currentQtree->_topRight.get(), callback);
	innerForEach(currentQtree->_bottomLeft.get(), callback);
	innerForEach(currentQtree->_bottomRight.get(), callback);
}

template<class T>
inline void QuadTree<T>::innerQuery(ofRectangle area, shared_ptr<std::vector<shared_ptr<T>>> found)
{
	// if query area don't intersect this doundary, just return
	if (!_boundary->intersects(area)) return;

	// collect all points inside the query area
	for (auto p : *(_points))
	{
		if (area.inside(p->_pos))
		{
			found->push_back(p);
		}
	}

	if (_subdivided)
	{
		_topLeft->innerQuery( area, found);
		_topRight->innerQuery(area, found);
		_bottomLeft->innerQuery(area, found);
		_bottomRight->innerQuery(area, found);
	}
}


template<class T>
ofRectangle const& QuadTree<T>::boundary()
{
	return *_boundary;
}

template<class T>
shared_ptr<std::vector<shared_ptr<T>>> const QuadTree<T>::points()
{
	return _points;
}

template<class T>
void QuadTree<T>::subdivide()
{
	//cout << "subdivide\n";
	if (!_subdivided)
	{
		//cout << " not yet subdivided, do it\n";
		_subdivided = true;

		float x = _boundary->x;
		float y = _boundary->y;
		float nw = _boundary->width / 2.0;
		float nh = _boundary->height / 2.0;

		_topLeft = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x, y, nw, nh), _capacity);
		_topRight = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x + nw, y, nw, nh), _capacity);
		_bottomLeft = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x, y + nh, nw, nh), _capacity);
		_bottomRight = std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x + nw, y + nh, nw, nh), _capacity);
	}
}
