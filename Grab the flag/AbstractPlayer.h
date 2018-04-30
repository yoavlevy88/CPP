#ifndef _ABSTRACTPLAYER_H_
#define _ABSTRACTPLAYER_H_

#include "BoardData.h"
#include "GameMove.h"
#include <string>
#include <iostream>


class AbstractPlayer {
public:
	virtual ~AbstractPlayer() { }
	/* player: 1 for 1-2-3 player, 2 for 7-8-9 */
	virtual void setPlayer(int player) = 0;
	virtual void init(const BoardData& board) = 0;
	virtual GameMove play(const GameMove& opponentsMove) = 0;
	virtual std::string getName() const = 0;
};


#endif