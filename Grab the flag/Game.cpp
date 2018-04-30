#include "Game.h"
Point fr_place[11] = { { 0,6 },{ 0,7 },{ 1,6 },{ 2,3 },{ 2,4 },{ 2,5 },{ 2,6 },{ 3,5 },{ 3,6 },{ 3,7 },{ 3,8 } };// array of points where the FR need to be
Point sea_place[14] = { { 7,5 },{ 8,4 },{ 8,5 },{ 9,3 },{ 9,4 },{ 9,5 },{ 9,6 },{ 9,7 },{ 9,8 },{ 9,9 },{ 10,6 },{ 10,7 },{ 10,8 },{ 11,7 } };// array of points where the SEA need to be
void Game::printScreen(const char* screen[ROWS])
{
	clear_screen();
	for (int i = 0;i < ROWS; i++)
	{
		cout << screen[i] << endl;
	}
	gotoxy(0, 0);
}

void Game::removeTools() {
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (board.getChar({i,j}) >= '1' && board.getChar({ i,j }) <= '9')
			{
				board.updateSquare({ i,j }, 0, ' ');
			}
		}
	}
}

void Game::initTools() {
	int lines = 0; // the start of the 5 lines to choose from
	Point q;
	bool flag = false;

	for (int i = 1; i <= 3; i++)
	{
		flag = false;
		while (!flag) {
			q = randPoint(0);
			if (board.isEmpty(q)) {
				board.updateSquare(q, 0, i+'0');
				flag = true;
			}
		}
	}

	for (int i = 1; i <= 3; i++)
	{
		flag = false;
		while (!flag) {
			q = randPoint(1);
			if (board.isEmpty(q)) {
				board.updateSquare(q, 0, i + '6');
				flag = true;
			}
		}
	}
	MyBoard charBoard1 = board.makeMyBoard(0), charBoard2 = board.makeMyBoard(1);
	p[0]->init(charBoard1);
	p[1]->init(charBoard2);
}


Point Game::randPoint(int start)//random point in the board between (start-start+4)
{
	int y = rand() % 5 + start * 8;
	int x = rand() % 13;
	return{ x,y };
}

void Game::SetCase(int argc, char *argv[]) {
	bool b = false, q = false;
	string tmp = "";

	for (int i = 0; i < argc; i++) {
		tmp = (string(argv[i]));
		if (tmp == "-quiet")
			q = true;
		if (tmp == "-board") {
			if (i + 1 < argc) {
				if ((string(argv[i + 1])) == "f") {
					i++;
					b = true;
				}
				else if ((string(argv[i + 1])) == "r")
				{
					i++;
					if ((atoi(argv[i + 1])) > 0) {
						maxCycle = (atoi(argv[i + 1]));
						i++;
					}
				}
			}
		}
		if (tmp == "-delay") {
			if (i + 1 < argc) {
				if ((atoi(argv[i + 1]))>0) {
					delay = atoi(argv[i + 1]);
					i++;
				}
			}
		}
		if (tmp == "-path") {
			if (i + 1 < argc) {
				isPath = true;
				path = string(argv[i + 1]);
			}
		}
	}
	if (q) {
		delay = 20;
	}
	boardFile = b;
	quiet = q;
	setDelay(delay);
}

bool Game::setBoardFromFile(string file) {
	char ch;
	int i = 0;
	map <int, char> checkMap;
	ifstream boardFile(file);
	bool flag = true;
	string str;
	int checkArr[8] = { 0 };
	board.clean();
	if (boardFile.is_open()) {
		while (flag) {
			for (int y = 0; y < 13; y++) {
				if (boardFile.eof()) {
					flag = false;
					continue;
				}
				getline(boardFile, str, '\n');
				for (int x = 0; x < 13; x++) {
					if ((int)str.length() > x) {
						ch = str[x];
						Point point(x, y);
						switch (ch)
						{
						case 'S':
							board.updateSquare(point, SEA, ' ');
							break;
						case 'T':
							board.updateSquare(point, FR, ' ');
							break;
						case 'A':
							checkArr[0]++;
							flags[0] = point;
							board.updateSquare(point, FLAG_A, ' ');
							break;
						case 'B':
							checkArr[1]++;
							flags[1] = point;
							board.updateSquare(point, FLAG_B, ' ');
							break;
						case '1':
							checkArr[2]++;
							board.updateSquare(point, EMPTY, ch);
							break;
						case '2':
							checkArr[3]++;
							board.updateSquare(point, EMPTY, ch);
							break;
						case '3':
							checkArr[4]++;
							board.updateSquare(point, EMPTY, ch);
							break;
						case '7':
							checkArr[5]++;
							board.updateSquare(point, EMPTY, ch);
							break;
						case '8':
							checkArr[6]++;
							board.updateSquare(point, EMPTY, ch);
							break;
						case '9':
							checkArr[7]++;
							board.updateSquare(point, EMPTY,ch);
							break;
						default:
							if (ch != ' ') {
								checkMap[i] = ch;
								i++;
							}
							break;
						}
					}
				}
			}
			flag = false;
		}
	}
	MyBoard charBoard1 = board.makeMyBoard(0), charBoard2 = board.makeMyBoard(1);
	p[0]->init(charBoard1);
	p[1]->init(charBoard2);
	flag = true;
	boardFile.close();
	if (!quiet)
		clear_screen();
	if (checkArr[0] != 1) {
		cout << "Wrong setting for FLAG A in file " << file << endl;
		flag = false;
	}
	if (checkArr[1] != 1) {
		cout << "Wrong setting for FLAG B in file " << file << endl;
		flag = false;
	}
	if (checkArr[2] != 1 || checkArr[3] != 1 || checkArr[4] != 1) {
		cout << "Wrong settings for player A tools in file " << file << endl;
		flag = false;
	}
	if (checkArr[5] != 1 || checkArr[6] != 1 || checkArr[7] != 1) {
		cout << "Wrong settings for player B tools in file " << file << endl;
		flag = false;
	}
	for (i = 0; i < (int)checkMap.size(); i++) {
		cout << "Wrong character on board: " << checkMap[i] << " in file " << file << endl;
		flag = false;
	}
	return flag;
}

bool Game::isGameEnd() { //TODO!
	if (flagIsCaptured())
		return true;
	if (isAlive(0) && isAlive(1)) {
		if (steps[0]+steps[1] >= 1250) {
			score[0]++;
			score[1]++;
			return true;
		}
		return false;
	}
	if (!isAlive(0)) {
		score[1]++;
		winner = 2;
	}	
	if (!isAlive(1)) {
		score[0]++;
		winner = 1;
	}
	return true;
}

char Game::whatInBoard(Point p) {
	return (board.getChar(p));
}

bool Game::isAlive(int player) {
	for (int k = (player * 6) + 1; k <= (player * 6) + 3; k++)
	{
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (whatInBoard({ i, j }) == (char)(k+'0'))
					return true;
			}
		}
	}
	return false;
}

void Game::init() {
	setPlayers();
	board.setBoardProperties(fr_place,11,FR);
	board.setBoardProperties(sea_place, 14, SEA);
	board.setBoardProperties(flags, 1, FLAG_A); 
	board.setBoardProperties(flags+1, 1, FLAG_B);


}

void Game::run() {
	hideCursor();
	if (boardFile) {
		checkPath(path);
	}
	while (!exit && cycle < maxCycle) {
		play();
		if (!quiet) {
			Sleep(delay * 50);
		}
	}
	gameSummery();
}

void Game::play() {
	winner = 0;
	int i = 0;
	cycle++;
	string tmp, nameOfFiles;
	bool flag = true;
	int moves_num = 0;
	GameMove thisMove(0, 0, 0, 0), lastMove(0, 0, 0, 0);
	if (boardFile) {
		if (files.size() == 0) {
			setExit();
			flag = false;
		}
		else {
			if (setBoardFromFile(files.front())) {
				nameOfFiles = files.front().substr(0, files.front().find(".gboard"));
				files.pop_front();
			}
			else {
				setExit();
				flag = false;
			}
		}
	}
	else {
		removeTools();
		resetProperties();
		resetSteps();
		initTools();
	}
	if (!quiet && flag)
		showBoard();
	while (flag) {
		if (isGameEnd()) {
			flag = false;
		}
		else {
			Sleep(delay);
			thisMove = p[i]->play(lastMove);
			steps[i]++;
			makeMove(i, thisMove);
			lastMove = thisMove;
			moves_num++;
		}
		i = (i + 1) % 2;
	}
	if(!exit)
		showEndGameStats(moves_num);
}

void Game::resetProperties() {
	board.setBoardProperties(fr_place, 11, FR);
	board.setBoardProperties(sea_place, 14, SEA);
	board.setBoardProperties(flags, 1, FLAG_A);
	board.setBoardProperties(flags + 1, 1, FLAG_B);
}

bool Game::checkPath(string dir) {
	_finddata_t data;
	string str = dir + "/*.gboard";
	bool flag = false;
	int ff = _findfirst(str.c_str(), &data);
	if (ff != -1)
	{
		int res = 0;
		while (res != -1)
		{
			flag = true;
			files.push_back(data.name);
			res = _findnext(ff, &data);
		}
		_findclose(ff);
	}
	//	files[i].sort();
	return flag;
}

void Game::gameSummery() {
	if (!quiet)
		system("cls");
	cout << "Game Summary\n" << p[0]->getName() << " for A points: " << score[0] << endl<<p[1]->getName()<< " for B points: " << score[1] << endl;
}

void Game::showEndGameStats(int moves) {
	/*	Game cycle : <number>
	Num moves : <total number of moves of A + B including �no op� moves>
	Winner : <A or B or NONE>*/
	clear_screen();
	cout << "Game cycle : " << cycle << endl;
	cout << "Num moves : " << moves << endl;
	cout << "Winner : ";
	if (winner == 0) {
		cout << "NONE" << endl;
	}
	if (winner == 1) {
		cout << "A" << endl;
	}
	if (winner == 2) {
		cout << "B" << endl;
	}
}

void Game::printNames() {
	gotoxy(1, 0);
	setTextColor(LIGHTMAGENTA);
	cout << p[0]->getName();//print the names
	gotoxy(40, 0);
	setTextColor(YELLOW);
	cout << p[1]->getName();
	setTextColor(WHITE);
	gotoxy(24, 0);
	cout << score[0];//print the score
	gotoxy(63, 0);
	cout << score[1];

}

void Game::showBoard() {
	printScreen(Board_Of_Game);
	printNames();
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			board.printToScreen({ i,j });
		}
	}
	gotoxy(0, 0);
}

void Game::setPlayers() {
	int i = 0;
	for (auto& p_id_func : AlgorithmRegistration::algoFactory) {
		auto& func = p_id_func.second;
		p[i++] = (func());
	}
	p[0]->setPlayer(1);
	p[1]->setPlayer(2);
}

void Game::makeMove(int playerNum, GameMove move) {
	Point from = { move.from_y-1, move.from_x-1 }, to = { move.to_y-1, move.to_x-1 };
	char tool = board.getTool(from), defending_tool = board.getTool(to);
	if (isToolOk(playerNum,tool)) {
		if (defending_tool == ' ') {
			board.updateSquare(from, board.getType(from), ' ');
			board.updateSquare(to, board.getType(to), tool);
		}
		else {
			if(tool!=defending_tool)
				board.updateSquare(from, board.getType(from), ' ');
			if (fight(tool, defending_tool, to)) 
				board.updateSquare(to, board.getType(to), tool);
		}
		if (!quiet) {
			board.printToScreen({ from });
			board.printToScreen({ to });
		}
	}
}

bool Game::isToolOk(int i, char ch) {
	if (ch == ('1'+(i*6)) || ch == ('2' + (i * 6)) || ch == ('3' + (i * 6)))
		return true;
	return false;
}

bool Game::flagIsCaptured() {
	for (int i = 0; i < 2; i++)
	{
		if (board.getTool(flags[i]) != ' ') {
			score[(i+1)%2]++;
			winner = ((i + 1) % 2)+1;
			return true;
		}
	}
	return false;
}

bool Game::fight(char attacking, char defending, Point place) {
	int x = place.getX(), y = place.getY();
	switch (attacking)
	{
	case '1':
		if (x == 3)
			return false;
		if (y >= 9 && y <= 12)
			return false;
		return true;
		break;
	case '2':
		if (defending == '9')
			return false;
		if (x == 10)
			return true;
		if (y >= 2 && y <= 3)
			return true;
		return false;
		break;
	case '3':
		if (y == 7 || x == 6)
			return true;
		return false;
		break;
	case 7:
		return !(fight(defending,attacking,place));
		break;
	case 8:
		return !(fight(defending, attacking, place));
		break;
	case 9:
		return !(fight(defending, attacking, place));
		break;
	default:
		return false; /// there is no way this will happen!
		break;
	}
}