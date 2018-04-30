#include "Algo_301675872.h"

AlgorithmRegistration Algo301675872("Algo_301675872", [] {return new Algo_301675872(); });
AlgorithmRegistration Algo302849831("Algo_302849831", [] {return new Algo_301675872(); });

string Algo_301675872::getName() const { return name; }

GameMove Algo_301675872::play(const GameMove& opponentsMove) {
	GameMove op = { opponentsMove.from_x - 1,opponentsMove.from_y - 1,opponentsMove.to_x - 1,opponentsMove.to_y - 1 };
    updateBoard(op);
	updateToolsPlaces();
	bool flag = false;
	bool round = false;
	int i = 1;
	point301675872 q = { 0,0 };
	point301675872 p = get_tool(i);	
	q = p;
	int r = rand() % 2;
	while (!flag) {
		switch (r) {
		case 0:
			if (p.x == target.x)
				break;
			if (p.x < target.x) {
				p.x++;
			}
			else {
				p.x--;
			}
			break;
		case 1:
			if (p.y == target.y)
				break;
			if (p.y < target.y) {
				p.y++;
			}
			else {
				p.y--;
			}
			break;
		default:
			break;
		}
		flag = isPointOk(myBoard[q.x][q.y]-'1'-Me*3 ,p);
		if (!(p.x == target.x && p.y == target.y)) {
			if (!round && !flag) {
				round = true;
				r = (r + 1) % 2;
			}
			else if (round)
			{
				p = get_tool(++i);
				q = p;
				if (p.x == 0 && p.y == 0)
					return{ q.x,q.y,p.x,p.y };
				round = false;
			}
		}
		else
			flag = true;
	}
    updateBoard({ q.x,q.y,p.x,p.y });
	return{ q.x+1,q.y+1,p.x+1,p.y+1 };
}

void Algo_301675872::setFlags() {
	for (int x = 0; x < 13; x++) {
		for (int y = 0; y < 13; y++)
		{
			if (myBoard[x][y] == 'A') {
				if (Me == 0) {
					myFlag = { x ,y };
				}
				else
					target = { x ,y  };
			}
			if (myBoard[x][y] == 'B') {
				if (Me == 1) {
					myFlag = { x ,y  };
				}
				else
					target = { x ,y  };
			}
		}
	}
}

void Algo_301675872::setBoard(const BoardData& board) {
	for (int x = 0; x < 13; x++) {
		for (int y = 0; y < 13; y++)
		{
			myBoard[x][y] = board.charAt(x, y);
			if ((board.charAt(x, y) >= '1') && (board.charAt(x, y) <= '9')) {
				tools.push_back({ x,y });
			}
			if ((board.charAt(x, y) == '#') ||( (board.charAt(x, y) >='1') &&(board.charAt(x, y)<='9')))
				oldBoard[x][y] = ' ';
			else
				oldBoard[x][y] = board.charAt(x, y);
		}
	}
}


void Algo_301675872::updateBoard(GameMove move) {
	if (!((move.from_x == move.to_x) && (move.from_y == move.to_y)))
	{
		myBoard[move.to_x][move.to_y] = myBoard[move.from_x][move.from_y];
		myBoard[move.from_x][move.from_y] = oldBoard[move.from_x][move.from_y];
	}
}

point301675872 Algo_301675872::get_tool(int i) {
	if (i > (int)tools.size())
		return{ 0,0 };
	auto it = tools.begin();
	for (int j = 1; j < i; j++)
		it++;
	return *it;
}

void Algo_301675872::init(const BoardData& board) {
	setBoard(board);
	setFlags();
	//setHowFar();
}

void Algo_301675872::updateToolsPlaces() {
	char ch = 0;
	tools.clear();
	for (int x = 0; x < 13; x++) {
		for (int y = 0; y < 13; y++)
		{
			ch = myBoard[x][y];
			if ((ch >= '1') && (ch <= '9')) {
				tools.push_back({ x,y });
			}
		}
	}
}

bool Algo_301675872::isPointOk(int tool,point301675872 p)
{
	if (p.x < 0 || p.x>12 || p.y < 0 || p.y>12)
		return false;
	switch (myBoard[p.x][p.y])
	{
	//case '#':
	//	return false;
	//	break;
	case ' ':
		return true;
		break;
	case 'T':
		return fr[tool];
		break;
	case 'S':
		return sea[tool];
		break;
	case '1':
		return false;
		break;
	case '2':
		return false;
		break;
	case '3':
		return false;
		break;
	case '7':
		return false;
		break;
	case '8':
		return false;
		break;
	case '9':
		return false;
		break;
	default:
		return true;
		break;
	}	
}