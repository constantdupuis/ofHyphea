
#include "QuadTree.h"

template<class T>
bool QuadTree<T>::insert(shared_ptr<T> point)
{
	// check template param type
	static_assert(std::is_base_of<Point, T>::value, "T should be derived from Point");

	// if point is not in our boundary just leave
	if (!_boundary->inside(point->_pos)) return false;

	// if over capacity wreate sub QuadTree
	if (_points->size() > _capacity)
	{
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
	// add point to this QuadTree
	_points->push_back(point);

	return true;
}

template<class T>
void QuadTree<T>::forEach(std::function<void(const QuadTree<T>&)> cb)
{
	innerForEach(this, cb);
}

template<class T>
void QuadTree<T>::forEachBoundary(std::function<void(const ofRectangle&)> cb)
{
}

template<class T>
void QuadTree<T>::forEachPoint(std::function<void(const T&)> cb)
{
}

template<class T>
ofRectangle const& QuadTree<T>::boundary()
{
	return *_boundary;
}

template<class T>
shared_ptr<std::vector<shared_ptr<T>>> const& QuadTree<T>::points()
{
	return _points;
}

template<class T>
void QuadTree<T>::subdivide()
{
	if (!_subdivided)
	{
		_subdivided = true;
		
		float x		= _boundary->x;
		float y		= _boundary->y;
		float nw	= _boundary->width / 2.0;
		float nh	= _boundary->height / 2.0;

		_topLeft		= std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x, y, nw, nh), _capacity);
		_topRight		= std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x+nw, y, nw, nh), _capacity);
		_bottomLeft		= std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x, y+nh, nw, nh), _capacity);
		_bottomRight	= std::make_unique<QuadTree<T>>(make_unique<ofRectangle>(x+nw, y+nh, nw, nh), _capacity);
	}
}

template<class T>
void QuadTree<T>::innerForEach(QuadTree<T>* currentQtree, std::function<void(const QuadTree<T>&)> cb)
{
	cb(*(this));

	if (!_subdivided) return;

	innerForEach(_topLeft.get(), cb);
	innerForEach(_topRight.get(), cb);
	innerForEach(_bottomLeft.get(), cb);
	innerForEach(_bottomRight.get(), cb);
}

