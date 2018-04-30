#ifndef _COLFLY_H_
#define _COLFLY_H_
#include <cstring>
#include "Point.h"

class TheSnakesGame;
class Snake;

class Colfly {
	enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
	int dir;//direction
	char sign;//the shap of the creature
	Point ColFly_body;// position of the creature
	char* name;
	TheSnakesGame* MyGame;
	Snake* pToSnake1;
public:
	Colfly(int x, int y, int _dir, char* _name) {
		ColFly_body.set(x, y);
		sign = '$';
		dir = _dir;
		name = strdup(_name);
	}
	void resetColfly(int x, int y, int _dir, char* _name) {
		ColFly_body.set(x, y);
		sign = '$';
		dir = _dir;
		name = strdup(_name);
	}
	void setGamePointer(TheSnakesGame* _theGame, Snake* _Snake1) {
		MyGame = _theGame;
		pToSnake1 = _Snake1;
	}
	void setDir() {
		dir = 10;
	}
	void moveColfly();
	void changeColflyDirection(int newDir) { dir = newDir; }
	void removeSnakeFromScreen(Point & p);
	void ChangeColflyPlace(Point ColFly_body, int &remove_snake);//move a Colfly
	int getColflyX() {
		return ColFly_body.getX();
	}
	int getColflyY() {
		return ColFly_body.getY();
	}
	void setColflyPlace(int x, int y) {
		ColFly_body.set(x, y);
	}
	void PrintMe() {
		gotoxy(ColFly_body.getX(), ColFly_body.getY());
		cout << '$';
	}
};



#endif