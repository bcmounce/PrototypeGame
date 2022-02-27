#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "cell.h"
#include "actor.h"
#include "level.h"
#include <random>
#include <cstdlib>

using namespace std;
int main(){
 int ch;
 initscr();
 noecho();
 curs_set(FALSE);

 srand(time(NULL));
 bool Gswitch = FALSE;
 actor * player = new actor('@', 1, 1);

 level mylevel(221,221);
 mylevel.setwalls();
 //mylevel.drunkenWalk();
 mylevel.DFSmaze();
 mylevel.insertActor(player);
 mylevel.placePlayerRandom(player);
 //mylevel(player->getX(), player->getY()).setOccupant(player);

 while(ch != 127) {
 
 clear();
 if(Gswitch){
 	mylevel.printFromPlayerWithDist(player);
 }
 else{
 	mylevel.printFromPlayer(player);
 	//mylevel.print();
 }
 mvprintw(0, 51, "x pos: %u \n", player->getX());
 mvprintw(1, 51, "y pos: %u \n", player->getY());
 mvprintw(2, 51, "%u \n", ch);
 ch = getch();
 
 if(ch == 115 && !( mylevel(player->getX() , player->getY()+1).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX(), player->getY()+1); //update player coord to the cell below current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 
 else if (ch == 119 && !( mylevel(player->getX() , player->getY()-1).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX(), player->getY()-1); //update player coord to the cell above current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 
 else if (ch == 100 && !( mylevel(player->getX()+1 , player->getY()).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX()+1, player->getY()); //update player coord to the cell right of current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 
 else if (ch == 97 && !( mylevel(player->getX()-1 , player->getY()).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX()-1, player->getY()); //update player coord to the cell left of current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 else if (ch == 99 && !( mylevel(player->getX()+1 , player->getY()+1).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX()+1, player->getY()+1); //update player coord to the cell right and down of current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 else if (ch == 122 && !( mylevel(player->getX()-1 , player->getY()+1).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX()-1, player->getY()+1); //update player coord to the cell left and down of current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 else if (ch == 113 && !( mylevel(player->getX()-1 , player->getY()-1).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX()-1, player->getY()-1); //update player coord to the cell left and up of current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 else if (ch == 101 && !( mylevel(player->getX()+1 , player->getY()-1).checkwall() ) ){
 	mylevel(player->getX(), player->getY()).free(); //free current cell
 	player->setPos(player->getX()+1, player->getY()-1); //update player coord to the cell right and down of current
 	mylevel(player->getX(), player->getY()).setOccupant(); //update new cell pointer
 }
 else if (ch == 109){
 	Gswitch = !Gswitch;
 }
 else if(ch == 114){
 	mylevel.drunkenWalk();
 	mylevel.placePlayerRandom(player);
 }
 else if(ch == 116){
 	mylevel.DFSmaze();
 	mylevel.placePlayerRandom(player);
 }
 // Clear the screen of all
 // previously-printed characters
 refresh();

 //usleep(DELAY); // Shorter delay between movements
 }

 endwin();

	return 0;
}