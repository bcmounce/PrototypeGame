#include "level.h"

level::level(int xmax, int ymax){
	sizeX = xmax;
	sizeY = ymax;
	layout.resize(xmax); //sets up the first dimesnion of the array
	for(int i = 0; i < xmax; i++){
		layout[i].resize(ymax);	//sets up each interior array
	}
	for(int i = 0; i < xmax; i++){
		for(int j = 0; j < ymax; j++){
			layout[i][j] = new cell(); //initilizes each cell in the 2d vector
		}
	}
}

level::~level(){
	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			delete layout[i][j]; // delete the cell pointers in the array
		}
	}
}

cell& level::operator()(int xpos, int ypos){
	return *layout[xpos][ypos]; //returns the cell in the pos (i,j)
}

void level::setwalls(){
	for(int i = 0; i < sizeY; i++){
		layout[0][i]->setwall();		// sets the walls on the north and south sides
		layout[sizeX-1][i]->setwall();	//
	}
	for(int i = 0; i < sizeX; i++){
		layout[i][0]->setwall();		// sets the walls on the east and west sides
		layout[i][sizeY-1]->setwall();	//
	}
}

int level::getX(){
	return sizeX;
}

int level::getY(){
	return sizeY;
}

void level::print(){
	for(int i = 0; i < this->getX(); i++){
 		for(int j = 0; j < this->getY(); j++){
 			mvprintw(j,i, "%c", (*this)(i, j).print()); //prints the floor by iterating through each cell and printing the cell
 		}
 	}
 	for(list<actor*>::iterator it = occupants.begin(); it != occupants.end(); it++){
 		mvprintw( (*it)->getY(), (*it)->getX(), "%c", (*it)->getSymbol());
 	}
}

void level::printFromPlayer(actor * player){
	int screenStartX = 24 - player->getX(); //offset the center of the screen by the current
	int screenStartY = 12 - player->getY(); //player position to find where the start of the level is
	for(int i = 0; (i < sizeX) && ((screenStartX + i) < 51); i++){
 		for(int j = 0; (j < sizeY) && ((screenStartY + j) < 26); j++){
 			if((*this)(i,j).checkoccupied()){
 				mvprintw(screenStartY + j, screenStartX + i, "%c", (*this).matchActor(i,j)->getSymbol());
 			}
 			else{
 				mvprintw(screenStartY + j, screenStartX + i, "%c", (*this)(i, j).print());
 			}
 		}
 	}
}

void level::makeOffice(){
	//minimum dimensions needs to be 15x12
	if((sizeX > 5) && (sizeY > 6)){
		for (int i = 0; (i + 5) < sizeX; i+= 5){
			(*this)(i,4).setwall();		//populates north with offices
			(*this)(i+1,4).setwall();	//	******
			(*this)(i+2,4).setwall();	//	*....*
			(*this)(i+3,4).setwall();	//	*....*
			(*this)(i+5,4).setwall();	//	*....*
			(*this)(i+5,1).setwall();	//	****.*
			(*this)(i+5,2).setwall();	//
			(*this)(i+5,3).setwall();	//
		}
	}
	if((sizeX > 6) && (sizeY > 7)){
		for(int i = 6; (i + 5) < sizeY; i+=5){
			(*this)(1,i).setwall();
			(*this)(2,i).setwall();		//populates west wall with offices
			(*this)(3,i).setwall();		//******
			(*this)(4,i).setwall();		//*.....
			(*this)(4,i+2).setwall();	//*....*
			(*this)(4,i+3).setwall();	//*....*
			(*this)(4,i+4).setwall();	//******
			(*this)(4,i+5).setwall();
			(*this)(1,i+5).setwall();
			(*this)(2,i+5).setwall();
			(*this)(3,i+5).setwall();
		}
	}
	if((sizeX > 11) && (sizeY > 16)){
		for (int i = 7; (i + 5) < sizeX; i+= 3){
			for (int j = 7; (j + 3) < sizeY; j+= 8){
				(*this)(i,j).setwall();
				(*this)(i+1,j).setwall();
				(*this)(i+3,j).setwall();
				(*this)(i+3,j+1).setwall();
				(*this)(i+3,j+3).setwall();
				(*this)(i+1,j+3).setwall();
				(*this)(i+2,j+3).setwall();
				(*this)(i+3,j+3).setwall();		//**.*
				(*this)(i,j+1).setwall();		//*..*
				(*this)(i,j+2).setwall();		//*..*
				(*this)(i,j+3).setwall();		//****
				(*this)(i,j+4).setwall();		//*..*
				(*this)(i,j+5).setwall();		//*..*
				(*this)(i,j+6).setwall();		//**.*
				(*this)(i+1,j+6).setwall();
				(*this)(i+3,j+2).setwall();
				(*this)(i+3,j+4).setwall();
				(*this)(i+3,j+5).setwall();
				(*this)(i+3,j+6).setwall();
			}
		}
	}
	
}


void level::printFromPlayerWithDist(actor * player){
	int screenStartX = 24 - player->getX(); //offset the center of the screen by the current
	int screenStartY = 12 - player->getY(); //player position to find where the start of the level is
	for(int i = 0; (i < sizeX) && ((screenStartX + i) < 51); i++){
 		for(int j = 0; (j < sizeY) && ((screenStartY + j) < 26); j++){
 			mvprintw(screenStartY + j, screenStartX + i, "%u", this->calcDist(i,j,player->getX(), player->getY() ) );
 		}
 	}
}

int level::calcDist(int myX, int myY, int dX, int dY){ //uses the pythagorean identity to calculate the distance between two points
	double sum,xdist, ydist;
	xdist = myX - dX;
	ydist = myY - dY;
	sum = pow(xdist, 2) + pow(ydist, 2);
	sum = sqrt(sum);
	return (int)sum;
}

void level::drunkenWalk(){
	for (int i = 1; i < this->getX() - 1; i++){
		for (int j = 1; j < this->getY() - 1; j++){
			layout[i][j]->setwall();
		}
	}
	drunkenWalkRecurse(sizeX/2, sizeY/2, sizeX*sizeY);
}

void level::drunkenWalkRecurse(int dX, int dY, int steps){
	if( steps == 0){
		return;
	}
	else{
		layout[dX][dY]->setFloor();
		
		int dir = (rand() % 4) + 1; //1 = north, 2 = south, 3 = west, 4 = east
		bool exit = false;
		while(!exit){
			if(dir == 1 && ((dY - 1) == 0) ){
				dir = (rand() % 4) + 1;
			}
			else if(dir == 2 && ((dY + 1) == (sizeY-1) ) ){
				dir = (rand() % 4) + 1;
			}
			else if(dir == 3 && ((dX - 1) == 0 ) ){
				dir = (rand() % 4) + 1;
			}
			else if(dir == 4 && ((dX + 1) == (sizeX-1) ) ){
				dir = (rand() % 4) + 1;
			}
			else{
				exit = true;
			} 
		}
		if(dir == 1){
			drunkenWalkRecurse(dX, dY-1, steps-1);
		}
		else if(dir == 2){
			drunkenWalkRecurse(dX, dY+1, steps-1);
		}
		else if(dir == 3){
			drunkenWalkRecurse(dX-1, dY, steps-1);
		}
		else{
			drunkenWalkRecurse(dX+1, dY, steps-1);
		}
	}

}

void level::DFSmaze(){
	for (int i = 1; i < sizeX - 1; i++){
		for (int j = 1; j < sizeY - 1; j++){
			layout[i][j]->setwall();
		}
	}
	int startX = 2 * (rand() % ((sizeX-1)/2)) + 1;
	int startY = 2 * (rand() % ((sizeY-1)/2)) + 1;
	
	vector<vector<bool> > visited;
	visited.resize(sizeX);
	for(int i = 0; i < sizeX; i++){
		visited[i].resize(sizeY);
		for(int j = 0; j < sizeY; j++){
			visited[i][j] = false;
		}
	}
	layout[startX][startY]->setFloor();
	DFSmazeRec(startX, startY, visited);
}

void level::DFSmazeRec(int dX, int dY, vector<vector<bool> > & visited){
	visited[dX][dY] = true;
	int directions[4] = {5,5,5,5};
	for(int i = 1; i < 5; i++){
		bool inserted = false;
		int pos;
		while(!inserted){
			pos = rand() % 4;
			if(directions[pos] == 5){
				directions[pos] = i;
				inserted = true;
			}
		}
	}
	for(int i = 0; i < 4; i++){
		switch(directions[i]){
			case 1:
				if(!(dX-2 <= 0)){
					if(visited[dX-2][dY] == false){
						layout[dX-1][dY]->setFloor();
						layout[dX-2][dY]->setFloor();
						DFSmazeRec(dX-2, dY, visited);
					}
				}
				break;
			case 2:
				if(!(dX+2 >= sizeX-1)){
					if(visited[dX+2][dY] == false){
						layout[dX+1][dY]->setFloor();
						layout[dX+2][dY]->setFloor();
						DFSmazeRec(dX+2, dY, visited);
					}
				}
				break;
			case 3:
				if(!(dY-2 <= 0)){
					if(visited[dX][dY-2] == false){
						layout[dX][dY-1]->setFloor();
						layout[dX][dY-2]->setFloor();
						DFSmazeRec(dX, dY-2, visited);
					}
				}
				break;
			case 4:
				if(!(dY+2 >= sizeY-1)){
					if(visited[dX][dY+2] == false){
						layout[dX][dY+1]->setFloor();
						layout[dX][dY+2]->setFloor();
						DFSmazeRec(dX, dY+2, visited);
					}
				}
				break;
		}
	}
	return;
}

void level::placePlayerRandom(actor * player){
	bool placed = false;
	int dX;
	int dY;
	while(!placed){
		dX = (rand() % (sizeX) - 1 ) + 1;
		dY = (rand() % (sizeY) - 1 ) + 1;
		if(!layout[dX][dY]->checkwall()){
			player->setPos(dX,dY);
			layout[dX][dY]->setOccupant();
			placed = true;
		}
	}
}

void level::recdivide(){
	recdivideauto(1,1,sizeX-1,sizeY-1);
}

void level::recdivideauto(int x, int y, int w, int h){
	if(w <= 1 || h <= 1){
		return;
	}
	if(w <= h){
		int horizon = rand() % h;
		int door = (rand() % w - 1) + 1;
		for(int i = 0; i < w; i++){
			if(i != door){
				layout[x+i][y + horizon]->setwall();
			}
		}
		recdivideauto(x, y, w, horizon);
		recdivideauto(x, y + horizon + 1, w, h - horizon);
	}
	else{
		int vertical = rand() % w;
		int door = (rand() % h - 1) + 1;
		for(int i = 0; i < h; i++){
			if(i != door){
				layout[x+vertical][y + i]->setwall();
			}
		}
		recdivideauto(x, y, vertical, h);
		recdivideauto(x+vertical, y, w - vertical, h);
	}
}

void level::insertActor(actor * myActor){
	occupants.push_back(myActor);
}

void level::removeActor(actor * myActor){
	occupants.remove(myActor);
}

actor * level::matchActor(int dX, int dY){
	for(list<actor*>::iterator it = occupants.begin(); it != occupants.end(); it++){
 		if( ((*it)->getX() == dX) && ((*it)->getY() == dY)){
 			return (*it);
 		}
 	}
 	return new actor('X', dX, dY);
}