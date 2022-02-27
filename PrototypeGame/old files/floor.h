#ifndef LEVEL_H
#define LEVEL_H
#include "cell.h"
#include <vector>
#include "memory"
#include <ncurses.h>
#include <math.h>

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
	void setPlayerDist(actor * player);
	void printDist();
private:
	int sizeX;
	int sizeY;
	vector<vector<cell*> > layout;
};

#endif