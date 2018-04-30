#ifndef _ROWFLY_H_
#define _ROWFLY_H_
#include <cstring>
#include "Point.h"

class TheSnakesGame;
class Snake;

class Rowfly {
	enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, BULLET = 4};
	enum { DIGIT = 2, SNAKE = 0, NUTRAL = -1, DEFULT_SIZE = 3 };
	int dir;//direction
	char sign;//the shap of the creature
	Point RowFly_body;// position of the creature
	char* name;
	TheSnakesGame* MyGame;
	Snake* pToSnake1;
public:
	Rowfly(int x, int y, int _dir, char* _name){
		RowFly_body.set (x, y);
		sign = '!';
		dir = _dir;
		name = strdup(_name);
	}
	void resetRowfly(int x, int y, int _dir, char* _name) {
		RowFly_body.set(x, y);
		sign = '!';
		dir = _dir;
		name = strdup(_name);
	}
	~Rowfly() {};
	void moveRowfly();
	void changeRowflyDirection(int newDir) { dir = newDir; }
	void ChangeRowflyPlace(Point RowFly_body, int &remove_snake);//move a RowFly
	void setGamePointer(TheSnakesGame* _theGame, Snake* _Snake1) {
		MyGame = _theGame;
		pToSnake1 = _Snake1;
	}
	void removeSnakeFromScreen(Point & p);
	int getRowflyX() {
		return RowFly_body.getX();
	}
	int getRowflyY() {
		return RowFly_body.getY();
	}
	void setRowflyPlace(int x, int y) {
		RowFly_body.set(x, y);
	}
	void PrintMe() {
		gotoxy(RowFly_body.getX(), RowFly_body.getY());
		cout << '!';
	}
};



#endif