#ifndef LEVEL_H
#define LEVEL_H
#include "cell.h"
#include <vector>
#include "memory"
#include <ncurses.h>
#include <math.h>
#include <random>
#include <list>
#include <iostream>
#include <stack>

using namespace std;
class level{
public:
	level(int xmax, int ymax);
	~level();
	cell& operator()(int xpos, int ypos);
	void setwalls();
	int getX();
	int getY();
	void print();
	void printFromPlayer(actor * player);
	void makeOffice();
	void printDist();
	void printFromPlayerWithDist(actor * player);
	int calcDist(int myX, int myY, int dX, int dY);
	void drunkenWalk();
	void drunkenWalkRecurse(int dX, int dY, int steps);
	void recdivide();
	void recdivideauto(int x, int y, int w, int h);
	void DFSmaze();
	void DFSmazeRec(int dX, int dY, vector<vector<bool> > & vistited);
	void placePlayerRandom(actor * player);
	void insertActor(actor * myActor);
	void removeActor(actor * myActor);
	actor * matchActor(int dX, int dY);
private:
	int sizeX;
	int sizeY;
	vector<vector<cell*> > layout;
	list<actor*> occupants;
};

#endif