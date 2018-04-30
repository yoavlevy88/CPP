#ifndef _THESNAKESGAME_H_
#define _THESNAKESGAME_H_
#include <vector>
#include "mission.h"
#include "io_utils.h"
#include "Snake.h"
#include "bullet.h"
#include "matrix.h"
#include "ColFly.h"
#include "RowFly.h"
#include "Creatures.h"
#include "num_eater.h"

enum { ROWS = 24, COLS = 80 };
enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 , BULLET=4};

class TheSnakesGame {
	enum { ESC = 27 };
	enum { FINISH = -1 };
	mission digit;//the class with the misiion and the digits array 
	Snake s[2] = { { 3, YELLOW, 10, 9, '@' },{ 3, GREEN, 70, 9, '#' } };
	Colfly c[2] = { { 55, 15, DOWN, "first" } ,{ 45, 22, UP, "second" } };
	Rowfly r[2] = { {30, 22, RIGHT, "first"} ,{50, 15, LEFT, "second"} };
	num_eater eat;
	char originalBoard[ROWS][COLS + 1];	// this is the original board that we got (we need COLS+1 because we handle it as null terminated char*)
	char board[ROWS][COLS + 1];	// this is the actual board we play on, i.e. changes on board are done here
	char temp[ROWS][COLS + 1];
	int statusOfTheGame=0;
	int vector_index=0;
	bool SHOW_REPLAY = false, FINISH_STAGE = false;
public:
	void resetCreatures() {
		r[0] = { 30, 22, RIGHT, "first" };
		r[1] = { 50, 15, LEFT, "second" };
		c[0] = { 55, 15, DOWN, "first" };
		c[1] = { 45, 22, UP, "second" };
	}
	void replayFunction();
	int get_vector_index() {
		return(vector_index);
	}
	void update_counter_vector() {
		vector_index++;
		if (vec.size() == vector_index)
			vec.resize(vector_index * 2);
	}
	void Restart_counter_vector() {
		vector_index = 0;
	}

	void updateVector(int vector_index);

	matrix a;
	vector<matrix> vec;
	
	~TheSnakesGame() {

	}
	void ShowTheFirstScreen();
	void setBoard(char  originalBoard[ROWS][COLS + 1], const char*  board_to_copy[ROWS]);
	void deleteCharFromBoard(int x, int y);
	int declareyouTheWinner(int win1 ,int win2);
	bool IsAnswerCorrect(int answer);
	void ShowMainMenu();
	void init();
	void run();
	void play();
	void ShowInstructions();
	void ShowSubMenu();
	void PrintBoard(const char board[ROWS][COLS + 1]);
	void PrintFirstBoard(const char board[ROWS][COLS + 1]);//print full board
	void initBoard();
	bool checkDotInTheBoard(Point P_Tocheck,int num );
	int checkNextMove(const Point& p);
	int CountDigit(int num);
	void UpdateNumInBoard(char board[ROWS][COLS + 1], int NumToUpdate, int x, int y);
	void DeleteNumFromScreen(int x, int y);
	int GetNumFromBoard(Point const next);
	void copyBoardToBoard(char originalBoard[ROWS][COLS + 1], char board[ROWS][COLS + 1]);
	void MainMenu();
	void subMenu(int *count, char choice);
	void someoneWonSound();
	void someoneLoseSound();
	void startScreenSound();
	Point getRowflyPos(int i) {
		Point p;
		p.set(r[i].getRowflyX(), r[i].getRowflyY());
		return (p);
	}
	void checkForRightAnswers(int count);
	Point getColflyPos(int i) {
		Point p;
		p.set(c[i].getColflyX(), c[i].getColflyY());
		return (p);
	}
	Point getEaterflyPos() {
		Point p;
		p.set(eat.getEaterflyX(), eat.getEaterflyY());
		return (p);
	}
	void setColflyPos(Point p, int i) {
		c[i].setColflyPlace(p.getX(), p.getY());
		c[i].setDir();
	}
};

#endif