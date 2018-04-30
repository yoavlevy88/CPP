#ifndef _ALGO301675872_H_
#define _ALGO301675872_H_
#define _CRT_SECURE_NO_WARNINGS

#include "AlgorithmRegistration.h"
#include "AbstractPlayer.h"
#include "BoardData.h"
#include "GameMove.h"
#include <list>
#include <iostream>
#include <string>
#include <Windows.h>
struct point301675872 {
	int x, y;
	point301675872(int _x = 0, int _y = 0) :x(_x), y(_y) {};
};
class Algo_301675872 :public AbstractPlayer {
	int Me = 0;
	char myBoard[13][13];
	char oldBoard[13][13];
	std::string name = "Algo_301675872";
	std::list<point301675872> tools;
	point301675872 myFlag;
	point301675872 target;
	bool fr[6] = { false, true,false,true,true,false};
	bool sea[6] = { false,true,true,true,false,false };
public:
	Algo_301675872() { }
	~Algo_301675872() { }
	/* player: 1 for 1-2-3 player, 2 for 7-8-9 */
	void setPlayer(int player) { Me = player-1; }
	void init(const BoardData& board);
	void updateBoard(GameMove move);
	void setBoard(const BoardData& board);
	GameMove play(const GameMove& opponentsMove);
	std::string getName() const;
	void setFlags();
	point301675872 get_tool(int i);
	void updateToolsPlaces();
	bool isPointOk(int tool, point301675872 p);
};

#endif