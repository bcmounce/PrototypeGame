#ifndef ACTOR_H
#define ACTOR_H

class actor{
public:
	actor(char sym, int x, int y);
	char getSymbol();
	void setSymbol(char sym);
	void setPos(int x, int y);
	int getX();
	int getY();

private:
	char symbol;
	int xpos;
	int ypos;
};

#endif