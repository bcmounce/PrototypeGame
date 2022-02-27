#include "level.h"

level::level(int xmax, int ymax){
	sizeX = xmax;
	sizeY = ymax;
	layout.resize(xmax);
	for(int i = 0; i < xmax; i++){
		layout[i].resize(ymax);
	}
	for(int i = 0; i < xmax; i++){
		for(int j = 0; j < ymax; j++){
			layout[i][j] = new cell();
		}
	}
}

level::~level(){
	for(int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			delete layout[i][j];
		}
	}
}

cell& level::operator()(int xpos, int ypos){
	return *layout[xpos][ypos];
}

void level::setwalls(){
	for(int i = 0; i < sizeY; i++){
		layout[0][i]->setwall();
		layout[sizeX-1][i]->setwall();
	}
	for(int i = 0; i < sizeX; i++){
		layout[i][0]->setwall();
		layout[i][sizeY-1]->setwall();
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
 			mvprintw(j,i, "%c", (*this)(i, j).print());
 		}
 	}
}

void level::printFromPlayer(actor * player){
	int screenStartX = 24 - player->getX(); //offset the center of the screen by the current
	int screenStartY = 12 - player->getY(); //player position to find where the start of the level is
	for(int i = 0; (i < sizeX) && ((screenStartX + i) < 51); i++){
 		for(int j = 0; (j < sizeY) && ((screenStartY + j) < 26); j++){
 			mvprintw(screenStartY + j, screenStartX + i, "%c", (*this)(i, j).print());
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
				(*this)(i+3,j+3).setwall();
				(*this)(i,j+1).setwall();
				(*this)(i,j+2).setwall();
				(*this)(i,j+3).setwall();
				(*this)(i,j+4).setwall();
				(*this)(i,j+5).setwall();
				(*this)(i,j+6).setwall();
				(*this)(i+1,j+6).setwall();
				(*this)(i+3,j+2).setwall();
				(*this)(i+3,j+4).setwall();
				(*this)(i+3,j+5).setwall();
				(*this)(i+3,j+6).setwall();
			}
		}
	}
	
}

void level::setPlayerDist(actor * player){
	for(int i = 1; i < (sizeX - 1); i++){
		for (int j = 1; j < (sizeY - 1); j++){
			double tempx, tempy, sum;
			tempx = player->getX() - i;
			tempy = player->getY() - j;
			sum = pow(tempx, 2) + pow(tempy, 2);
			sum = (int)sqrt(sum);
			(*this)(i,j).setDist(sum);
		}
	}
}

void level::printDist(){
	for (int i = 0; i < sizeX; i++){
		for(int j = 0; j < sizeY; j++){
			mvprintw(j,i, "%u", (*this)(i, j).getDist());
		}
	}
}