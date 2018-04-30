#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <cstring>
#include "Point.h"
#include "bullet.h"

class TheSnakesGame;
enum { DIGIT = 2, SNAKE = 0, NUTRAL = -1, DEFULT_SIZE = 3, ROWFLY = 5, COLFLY = 6, NUMEATER = 7};
class Snake {
	int win;//if the snack ate a right answer win =1 if the answer is worng win=0  
	Point body[15];
	int direction ; 
	char arrowKeys[5];
	Color color;
	char sign;//the shap of the snack
	int SnakeLen;
	TheSnakesGame* theGame;
	bullet bullets_arr [5];
	int counter_bullet;//index for the bullet array
	int OptionalSize = 0;//count the bullet on the screen
	int injury;//if the snack won one more bullet injury==1
	Snake* P_toOtherSnake;
	bool disapear = FALSE;
	int FiveNumbersCount;//count the number of digit on the screen -we use it when the snack is remove from the board
	
public:
	void printMyarray(int type);
	//------------------function that copy snake to matrix snake
	void update_cell_in_snake_body_arr(int index, Point&p);
	void update_cell_in_bullets_arr(int index, Point&p);

	bullet *get_bullet_array(int i) {
		return(&bullets_arr[i]);
	}
	Point get_body_cell(int i) {
		return(body[i]);
	}
	Snake(){}
	Snake(const size_t len, Color _color, int x, int y, const char ch) {//ctor of snake

		color = _color;

		SnakeLen = len;
		body[0].set(x, y);
		sign = ch;
		win = NUTRAL;
		injury = NUTRAL + 1;
		counter_bullet = NUTRAL;
		OptionalSize = 0;
	}

	~Snake() {
	}

	void  deletebulletFromArr(Point& p);
	void replaceSnakeInRandomPlace();
	void removeSnakeFromScreen(Point & p);
	void removeDeletedCellFrom_Bullet_Array();
	bool checkforBullet(const Point& p);
	void moveBullet();
	void setbulletArray();
	void move();

	void setOptionalCountAndSize() {
		OptionalSize=0;
		counter_bullet = NUTRAL;
	}
	bool IsDisapear() {
		return disapear;
	}

	void IsNotDisapear() {
		disapear = FALSE;
	}
	char get_sign() {
		return(sign);
	}

	int get_counter_bullet() {
		return(counter_bullet);
	}
	void set_counter_bullet(int num) {
		counter_bullet = num;
	}

	void setPointerToOtherSnake(Snake* other) {
		P_toOtherSnake = other;
	}
	
	Point getSnakeHaed () {
		return(body[0]);
	}

	void SetFiveNumbersCountToZero() {
		FiveNumbersCount = 0;	
	}

	void SetFiveNumbersCount() {
		FiveNumbersCount++;
	}

	bool getFiveNumbersCount() {
		return (FiveNumbersCount == 5);
	}

	void deleteSnakeBodyFromScreen();

	void ResetSnake(int x, int y,int dir) {//ctor of snake
		SnakeLen = DEFULT_SIZE;
		body[0].set(x, y);
		win = NUTRAL;
		setDirection(dir);
	}

	void ResetPlaceForSnake(int x, int y, int dir) {//ctor of snake
		body[0].set(x, y);
		setDirection(dir);
	}

	void setHead(int x, int y) {
		body[0].set(x, y);
	}

	 int getWin() {
		return(win);
	}

	 int getLen() {
		 return(SnakeLen);
	 }

	void setIfSnackWon(int num) {
		win = num;
	}

	void setLen(int num) {
		SnakeLen = num;
	}

	void setLen() {
		body[SnakeLen] = body[SnakeLen - 1];
		SnakeLen++;
	}
	

	Snake*  getPtosnack() {
		return(P_toOtherSnake);

	}

	void setGame(TheSnakesGame* _theGame) {
		theGame = _theGame;

	}

	bool checkForSnakes(const Point& p);

	void setArrowKeys(const char* keys) {
		arrowKeys[0] = keys[0];
		arrowKeys[1] = keys[1];
		arrowKeys[2] = keys[2];
		arrowKeys[3] = keys[3];
		arrowKeys[4] = keys[4];
	}
	
	int getDirection(char key);

	void setDirection(int dir) {
			direction = dir;
	}
	bool checkforRowfly(const Point& p);//check if the posision of p is as one of the bullets on the board
	bool checkforColfly(const Point& p);//check if the posision of p is as one of the bullets on the board
	bool checkforEaterfly(const Point& p);//check if the posision of p is as one of the bullets on the board
};

#endif