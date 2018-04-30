#ifndef _BOARDDATA_H_
#define _BOARDDATA_H_

class BoardData {
public:
	enum { rows = 13, cols = 13 };
	virtual ~BoardData() { };
	virtual char charAt(int x, int y) const = 0;
};

#endif