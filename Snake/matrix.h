#ifndef _MATRIX_H_
#define _MATRIX_H_

using namespace std;
#include <iostream>
#include <string.h>
#include "Point.h"
#include "Snake.h"
#include "mission.h"
#include "RowFly.h"
#include "ColFly.h"
#include "num_eater.h"


class TheSnakesGame;
class bullet;

class matrix {
	enum { ROWS = 24, COLS = 80,UPDATE=1, NOT_UPDATE=0};
	enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
	char vec_board[ROWS][COLS + 1];
	Snake s_temp[2];
	Colfly c_temp[2] = { { 55, 15, DOWN, "first" } ,{ 45, 22, UP, "second" } };
	Rowfly r_temp[2] = { { 30, 22, RIGHT, "first" } ,{ 50, 15, LEFT, "second" } };
	num_eater eater;
	Snake *p_to_s1;
	Snake *p_to_s2;
	bool MYBORD = NOT_UPDATE;
	int currMission;
	mission *digit;//the class with the misiion and the digits array 
public:
	matrix(){}
	~matrix() {}
	void setmission(mission* __digit) {
		digit = __digit;
	}
	bool is_board_update()
	{
		return(MYBORD);
	}
	void setUpdate() {
		MYBORD = UPDATE;
	}
	void update_snake_location_len(Snake&copy);
	void printmatrixcell();
	void copyBoardToBoard_inMatrix(char originalBoard[ROWS][COLS + 1]);
	void copySnake_parametrs(Snake org[2]);
	void update_score_to_mat(int s1, int s2);//this function update the score to the mat in the beginnig  of the level

	char getcol_row(int i, int j);

	void printToMatrix(int x, int y, char* str);
	void set_rowColFly(int i, int j, char name);
	void setcol_row(int i, int j, int c);
	

	void Setmatrix(const char board[ROWS][COLS + 1]);

	void print_matrix();
	void update_bullet_inMat(Snake& s);
	bool  which_snack_to_update(Snake& s);

	void UpdateNumInBoard2( int NumToUpdate, int x, int y);
	int CountDigit(int num);

};
#endif