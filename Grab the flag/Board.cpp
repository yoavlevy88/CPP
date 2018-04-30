#include "Board.h"

 
char Board::getTool(Point p)
{
	return (board[p.getX()])[p.getY()].getTool();
}
int Board::getType(Point p) const
{
	return (board[p.getX()])[p.getY()].getType();
}

char Board::getChar(Point p) {
	return (board[p.getX()]) [p.getY()].getTool();
}

void Board::printToScreen(Point p)
{
	enum { x_start = 5, y_start = 4, x_jump = 5, y_jump = 1};
	int x = p.getX(), y = p.getY();
 	gotoxy(x_start + x*x_jump, y_start + y*y_jump);
	int t = getType(p);
	char fr = 'Y', sea = 247, f1 = 222, f2 = 223;
	switch (t)
	{// EMPTY = 0, FR = 1, SEA = 2, FLAG_A = 3, FLAG_B = 4
	case 0:
		cout << "   ";
		break;
	case 1:
		setTextColor(GREEN);
		cout << fr << fr << " ";
		setTextColor(WHITE);
		break;
	case 2:
		setTextColor(LIGHTBLUE);
		cout <<sea << sea << " ";
		setTextColor(WHITE);
		break;
	case 3:
		setTextColor(LIGHTMAGENTA);
		cout << f1 << f2 << " ";
		setTextColor(WHITE);
		break;
	case 4:
		setTextColor(YELLOW);
		cout << f1 << f2 << " ";
		setTextColor(WHITE);
		break;
	default:
		cout << "    ";
		break;
	}

	char b = getTool(p);
	
	if (b != ' ')
	{
		int i = 0;
		if (b >= '7' && b <= '9')
			i = 1;
		switch (i)
		{
		case (0):
			setTextColor(LIGHTMAGENTA);
			break;
		case (1):
			setTextColor(YELLOW);
			break;
		}
		cout << b;
		setTextColor(WHITE);
	}

	else
	{
		cout << " ";
	}
}
void Board::updateSquare(Point p,int type = 0, char tool = ' ')
{
	(board[p.getX()])[p.getY()].setType(type);
	(board[p.getX()])[p.getY()].setTool(tool);
}

void Board::setBoardProperties(Point* points, int len, int type)
{
	for (int i = 0; i < len; i++)
	{
		updateSquare(points[i], type);
	}
}

bool Board::isEmpty(Point p) {
	if (board[p.getX()][p.getY()].getType() == EMPTY && board[p.getX()][p.getY()].getTool() == ' ')
	{
		return true;
	}
	return false;
}

//bool Board::checkNextStep(Point thisP, Point p) {
//	BattleTool* enemy = getTool(p);
//	BattleTool* thisTool = getTool(thisP);
//	if (((getType(p) == FLAG_A) && (thisTool->getMyPlayer()==0)) || ((getType(p) == FLAG_B) && (thisTool->getMyPlayer() == 1)))
//	{
//		return false;
//	}
//	if (getType(p) == SEA && !thisTool->isSea()) {
//		return false;
//	}
//	else {
//		if (getType(p) == FR && !thisTool->isFr()) {
//			return false;
//		}
//	}
//	if (enemy != nullptr) {
//		if (enemy->getPlayer() == thisTool->getPlayer())
//			return false;
//		else {
//			Beep(300, 300);
//			if (thisTool->fight(enemy, p)) {
//				enemy->dead();
//				updateSquare(p, getType(p), nullptr);
//				return true;
//			}
//			else {
//				updateSquare(thisTool->getPlace(), getType(thisTool->getPlace()), nullptr);
//				thisTool->dead();
//				return false;
//			}
//		}
//	}
//	return true;
//}

bool Board::isCaptureFlag(Point p) const {
	int x = p.getX(), y = p.getY();
	Square s = board[x][y];
	if (s.getTool() == ' ')
		return false;
	int player = 0;
	if (s.getTool() >= '7' && s.getTool() <= '9')
		player = 1;
	if (player == 0 && s.getType() == FLAG_B) {
	/*	Beep(1568, 200);
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1245, 1000);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1175, 1000);*/
		return true;
	}
	if (player == 1 && s.getType() == FLAG_A) {
	/*	Beep(1568, 200);
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1245, 1000);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1175, 1000);*/
		return true;
	}
	return false;
}

void Board::blinkTool(Point p) {
	enum { x_start = 8, y_start = 4, x_jump = 5, y_jump = 1 };
	int x = p.getX(), y = p.getY();
	int blinkX = x_start + x*x_jump, blinkY = y_start + y*y_jump;
	char b = getTool(p);
	int player = 0;
	if (b >= '7' && b <= '9')
		player = 1;
	if (b != ' ') {
		if (player ==0) {
			setTextColor(LIGHTMAGENTA);
		}
		else {
			setTextColor(YELLOW);
		}
		gotoxy(blinkX, blinkY);
		cout << b;
		Sleep(5);
		gotoxy(blinkX, blinkY);
		cout << " ";
		Sleep(5);
		gotoxy(blinkX, blinkY);
		cout << b;
		Sleep(5);
		gotoxy(blinkX, blinkY);
		cout << " ";
		Sleep(5);
		gotoxy(blinkX, blinkY);
		cout << b;
		setTextColor(WHITE);
	}
}

void Board::clean() {
	for (int x = 0; x < 13; x++) {
		for (int y = 0; y < 13; y++) {
			updateSquare({ x,y });
		}
	}
}

bool Board::checkIfGoodPoint(Point p, Point q) {
	int px = p.getX(), py = p.getY(), qx = q.getX(), qy = q.getY();
	if (qy > 12 || qy < 0 || qx>12 || qx < 0)
		return false;
	if (px == qx && ((py == qy - 1) || (py == qy + 1))) {
		return true;
	}
	if (py == qy && ((px == qx - 1) || (px == qx + 1))) {
		return true;
	}
	return false;
}

MyBoard Board::makeMyBoard(int playerNum) {
	MyBoard b;
	for (int x = 0; x < 13; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (isEmpty({ x,y }))
				b.setSquare(x,y, ' ');
			if(board[x][y].getType()== FR)
				b.setSquare(x, y, 'T');
			if (board[x][y].getType() == SEA)
				b.setSquare(x, y, 'S');
			if (board[x][y].getType() == FLAG_A)
				b.setSquare(x, y, 'A');
			if (board[x][y].getType() == FLAG_B)
				b.setSquare(x, y, 'B');
			if (board[x][y].getTool() >='1' && board[x][y].getTool() <= '3')
				if(playerNum==0)
					b.setSquare(x, y, board[x][y].getTool());
				else
					b.setSquare(x, y, '#');
			if (board[x][y].getTool() >= '7' && board[x][y].getTool() <= '9')
				if (playerNum == 1)
					b.setSquare(x, y, board[x][y].getTool());
				else
					b.setSquare(x, y, '#');
		}
	}
	return b;
}