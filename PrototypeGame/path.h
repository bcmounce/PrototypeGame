#ifndef _PATH_H
#define _PATH_H

#include <stack>
#include <pair>
#include "floor.h"

class path{
public:
	path(floor * currFloor);
	~path();
	void setDest(int Dx, Dy);
	void makePath();
private:
	stack<cell> openPath;
	stack<cell> closedPath;
	floor* myFloor;
	pair<int,int> destination;
}