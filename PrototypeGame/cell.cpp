#include "cell.h"

cell::cell(){
	myTile = floor;
}

void cell::setwall(){
	myTile = wall;
}

char cell::print(){
	switch (myTile){
		case wall :
			return '#';
			break;
		case floor :
			return '.';
			break;
		case empty :
			return ' ';
			break;
		case occupiedfloor :
			return '.';
			break;
	}
}

bool cell::checkwall(){
	return (myTile == wall);
}

bool cell::checkoccupied(){
	return myTile == occupiedfloor;
}

void cell::setOccupant(){
	myTile = occupiedfloor;
}

void cell::free(){
	myTile = floor;
}
void cell::setFloor(){
	myTile = floor;
}