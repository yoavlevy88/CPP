#ifndef _NUM_EATER_H_
#define _NUM_EATER_H_
#include <cstring>
#include "Point.h"
#include <vector>
class TheSnakesGame;
class mission;
class Snake;

class num_eater {
	enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
	int dir;//direction
	char sign ;//the shap of the bullet
	Point body;// position of the bulet
	TheSnakesGame* MyGame;
	mission *my_mission;
	Snake* pToSnake1;
	int currNum;//Random number for  mission number 0
	int currMission;//The current mission index for missionTypes array
	vector<Point> vec_answers;
	bool ANSWER = FALSE;
	int rightLeftMoves=0, upDownMoves=0;
	int dirSides, dirUpDown;
public:
	num_eater() {
		body.set(10, 19);
		sign = '%';
		vec_answers.reserve(30);
	}
	void resetPlace() {
		body.set(10, 19);
	}
	int getEaterflyX() {
		return body.getX();
	}
	void Myclear() {
		vec_answers.clear();
		ANSWER = FALSE;
	}
	int getEaterflyY() {
		return body.getY();
	}

	void setEater(int i, int j) {
		body.set(i, j);
	}

	int getEaterX() {
		return (body.getX());
	}
	int getEaterY() {
		return (body.getY());
	}

	void setSidesMoves(int x) {
		rightLeftMoves = x;
	}
	void setUpDownMoves(int x) {
		upDownMoves = x;
	}

	void setSidesKind(int side) {
		dirSides = side;
	}
	void setUpDownKind(int side) {
		dirUpDown = side;
	}
	Point getBody() {
		return (body);
	}
	int getSidesMoves() {
		return(rightLeftMoves);
	}
	int getUpDownMoves() {
		return(upDownMoves);
	}

	int getSidesKind() {
		return(dirSides);
	}
	int getUpDownKind() {
		return(dirUpDown);
	}

	int whoIsTheShorter(int res1, int res2, int res3);

	void update_mission_number(int num) {
		currMission = num;
	}

	void checkWhereToGo();

	void setGame(TheSnakesGame* _theGame, mission *_my_mission, Snake* s) {
		MyGame = _theGame;
		my_mission = _my_mission;
		pToSnake1 = s;
	}

	void drawStartingPos() {
		gotoxy(10, 19);
		cout << sign;
	}

	void Insert_Num_pos_VecAnswers(Point p) {//inserts the numbers that appears on the board to Point array (save the places of the digit only ) 
		vec_answers.push_back(p);
		ANSWER = TRUE;
	}

	bool is_VecArr_Full()
	{
		return(ANSWER);
	}
	void moveEater();
	void PrintMe() {
		gotoxy(body.getX(), body.getY());
		cout << '%';
	}
};

#endif