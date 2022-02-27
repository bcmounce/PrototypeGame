#ifndef CELL_H
#define CELL_H
#include <string>
#include "actor.h"
using namespace std;

class cell{
public:
	enum tile {empty, floor, wall, occupiedfloor};
	cell();
	cell(bool data);
	void setwall();
	char print();
	void setOccupant();
	bool checkwall();
	bool checkoccupied();
	void free();
	void setFloor();
private:
	tile myTile;
};
#endif 

