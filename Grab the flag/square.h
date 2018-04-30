#ifndef _SQUARE_H_
#define _SQUARE_H_

using namespace std;

enum { EMPTY = 0, FR = 1, SEA = 2, FLAG_A = 3, FLAG_B = 4 };

class Square {
	int type;
	int player;
	char tool;
public:
	Square(): type(0), tool(' '), player(0){}
	~Square() {}
	void setType(int t);
	void setPlayer(int t);
	void setTool(char b);
	char getTool();
	int getType() const;
};


#endif