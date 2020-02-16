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
	}

	bool insert(shared_ptr<T> point);

	//shared_ptr<std::vector<shared_ptr<T>>> query();

	void forEach( std::function<void(const QuadTree<T>&)> cb);
	void forEachBoundary( std::function<void(const ofRectangle&)> cb);
	void forEachPoint( std::function<void(const T&)> cb);

	ofRectangle const& boundary();
	shared_ptr<std::vector<shared_ptr<T>>> const& points();

private:
	shared_ptr<std::vector<shared_ptr<T>>> _points = std::make_shared<std::vector<shared_ptr<T>>>();
	std::unique_ptr<ofRectangle> _boundary;
	int _capacity = 4;
	bool _subdivided = false;

	std::unique_ptr<QuadTree<T>> _topLeft;
	std::unique_ptr<QuadTree<T>> _topRight;
	std::unique_ptr<QuadTree<T>> _bottomLeft;
	std::unique_ptr<QuadTree<T>> _bottomRight;

	/**
	* Subdivide this QuadTree in four sub QuadTree if not already done.
	*/
	void subdivide();

	void innerForEach( QuadTree<T>* currentQtree, std::function<void(const QuadTree<T>&)> cb);
	
};