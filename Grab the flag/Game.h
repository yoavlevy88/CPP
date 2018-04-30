#ifndef _GAME_H_
#define _GAME_H_
#define _CRT_SECURE_NO_WARNINGS

#include "AlgorithmRegistration.h"
#include <iostream>
#include <fstream>
#include <io.h>
#include <string>
#include <Windows.h>
#include "AbstractPlayer.h"
#include "Board.h"
#include "screens.h"
#include "MyBoard.h"
#include "Point.h"
#include <map>
#include <list>
using namespace std;

class Game {
	AbstractPlayer* p[2];
	int delay = 20;
	bool boardFile;
	bool quiet;
	int cycle = 0, maxCycle = 10;
	string path = ".";
	bool isPath = false;
	int score[2] = { 0,0 };
	int steps[2] = { 0,0 };
	int winner = 0; //0 -none ,1- player A , 2- player B
	Board board;
	int exit = 0;
	list <string> files; // to store the board files
	Point flags[2] = { { 10,0 },{ 1,12 } };
public:
	void resetSteps() { steps[0] = 0; steps[1] = 0; }
	Game(int argc, char *argv[])  { SetCase(argc, argv); }
	void SetCase(int argc, char *argv[]);
	void setDelay(int d) { delay = d; }
	bool setBoardFromFile(string file);
	void init();
	void run();
	void play();
	bool checkPath(string dir);
	void showEndGameStats(int moves);
	void gameSummery();
	void printNames();
	void showBoard();
	void setExit() { exit = 1; };
	void initTools();// TODO - init the tools if the board is random
	bool isGameEnd();//TODO - check all the board if someone captured the flag or all tools dead // and change the winner and set the score
	void makeMove(int playerNum, GameMove move);//TODO - get move from the algo and make the move
	void printScreen(const char* screen[ROWS]);
	Point randPoint(int start);
	bool isAlive(int player);
	char whatInBoard(Point p);
	void setPlayers();
	bool isToolOk(int i, char ch);
	bool flagIsCaptured();
	void removeTools();
	void resetProperties();
	bool fight(char attacking, char defending, Point place);
};

#endif
