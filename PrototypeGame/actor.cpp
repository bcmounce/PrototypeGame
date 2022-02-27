#include "actor.h"

actor::actor(char sym, int x, int y){
	symbol = sym;
	xpos = x;
	ypos = y;
}

char actor::getSymbol(){
	return symbol;
}

int actor::getX(){
	return xpos;
}

int actor::getY(){
	return ypos;
}
void actor::setSymbol(char sym){
	symbol = sym;
}

void actor::setPos(int x, int y){
	xpos = x;
	ypos = y;
}