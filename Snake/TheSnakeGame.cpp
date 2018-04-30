#include "TheSnakesGame.h"
#include <cstdlib>
#include <ctime>
#include "Point.h"
#include "Snake.h"
#include "mission.h"
#include "board.h"
#include "bullet.h"


void TheSnakesGame::replayFunction() {
	int last_update=0;
	vec.resize(vector_index);
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].is_board_update()) {
			vec[i].printmatrixcell();
			last_update = i;
		}
		else {
			vec[last_update].print_matrix();
			vec[i].printmatrixcell();
		}
	}
}


void TheSnakesGame::deleteCharFromBoard(int x, int y) {//function that delete number from board array
	do {
		x--;
	} while (board[y][x] != ' ');
	x++;
	do
	{
		board[y][x] = ' ';
		x++;
	} while (board[y][x] != ' ');
}

void TheSnakesGame::DeleteNumFromScreen(int x, int y) {
	int _x = x - 1;
	int flagL = 1, flagR = 1;

	while (flagL || flagR) {
		if (board[y][x] != ' ') {
			gotoxy(x, y);
			cout << ' ';
			x++;
		}
		else
			flagL = 0;

		if (board[y][_x] != ' ') {
			gotoxy(_x, y);
			cout << ' ';
			_x--;
		}
		else
			flagR = 0;
	}
}

int TheSnakesGame::GetNumFromBoard(Point const head) {//get number from the char board and make it  type int 
	int x = head.getX();
	int y = head.getY();
	int num = 0;
	while ((board[y][x - 1] >= '0') && (board[y][x - 1] <= '9'))
	{
		x--;
	}
	num = board[y][x] - '0';
	x++;
	if ((board[y][x] >= '0') && (board[y][x] <= '9'))
	{
		num *= 10;
		num += board[y][x] - '0';
		x++;
		if ((board[y][x] >= '0') && (board[y][x] <= '9'))
		{
			num *= 10;
			num += board[y][x] - '0';
		}
	}
	return num;
}

void TheSnakesGame::setBoard(char  originalBoard[ROWS][COLS + 1], const char* board_to_copy [ROWS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			originalBoard[i][j] = board_to_copy[i][j];
		}
		originalBoard[i][COLS] = '\0';
	}
}

void ::TheSnakesGame::initBoard() {
	int num, rendom_x, x, y;
	bool printed = false;
	Point P;
	srand(time(0));
	rendom_x = rand();
	num = rendom_x % 3;
	if (num == 0)
		rendom_x %= 25;
	else if (num == 1)
	{
		rendom_x %= 81;
		if (rendom_x < 26)
			rendom_x += 26;
	}
	else
	{
		rendom_x %= 169;
		if (rendom_x < 81)
			rendom_x += 81;
	}

	while (!printed) {
		P.set((rand() % 76) + 1, (rand() % 19) + 4);
		if (checkDotInTheBoard(P, rendom_x)) {
			UpdateNumInBoard(board, rendom_x, P.getX(), P.getY());
			//----------------------------
			
			vec[get_vector_index()].copyBoardToBoard_inMatrix(board);
			gotoxy(P.getX(), P.getY());
			setTextColor(Color::WHITE);
			cout << rendom_x;
			digit.InsertNumToArray(P.getX(), P.getY());//insert the location of the numbers to point array
//--------------------------------num_eater
			if (this->IsAnswerCorrect(rendom_x))//if the answer is currect we will insert to the array of the num eater creatures
				eat.Insert_Num_pos_VecAnswers(P);
			printed = true;
		}
	}

	//InsertNumToArray(number_array, &index_array);
}

void TheSnakesGame::UpdateNumInBoard(char board[ROWS][COLS + 1], int NumToUpdate, int x, int y) {
	int temp, res;
	char ch;
	res = CountDigit(NumToUpdate);

	if (NumToUpdate == 0)
		board[y][x] = '0';
	

	while (NumToUpdate && res) {
		temp = NumToUpdate % 10;
		ch = (char)(temp + '0');
		board[y][x + res - 1] = ch;
		NumToUpdate /= 10;
		res--;
	}
}

int TheSnakesGame::checkNextMove(const Point& p) {
	if (('0' <= (this->board[p.getY()][p.getX()])) && ('9' >= (this->board[p.getY()][p.getX()])))
		return(2);
	else if (s[0].checkForSnakes(p) || s[1].checkForSnakes(p)) //if  next move  is a snake
		return(SNAKE);
	else if (s[0].checkforBullet(p) || s[1].checkforBullet(p))//if its a bullet
		return(BULLET);
	else if (s[0].checkforRowfly(p) || s[1].checkforRowfly(p))
		return(ROWFLY);
	else if (s[0].checkforColfly(p) || s[1].checkforColfly(p))
		return(COLFLY);
	else if (s[0].checkforEaterfly(p) || s[1].checkforEaterfly(p))
		return(NUMEATER);
	else//if its empty=space
		return(TRUE);
}

bool TheSnakesGame::checkDotInTheBoard(Point P_Tocheck, int num) {//this function check the dot in the board to set a place for digit 
	int x, y, counter;
	x = P_Tocheck.getX();
	y = P_Tocheck.getY();
	if (s[0].checkForSnakes(P_Tocheck) == FALSE && s[1].checkForSnakes(P_Tocheck) == FALSE) {//if the dot is not a snake we will continue to check

		if ((board[y][x] != ' ') || (board[y][x - 1] != ' ') || (board[y][x + 1] != ' '))
			return(false);
		else
			counter = CountDigit(num);
		switch (counter)
		{
		case 1:
			return(TRUE);
			break;
		case 2:
			if (board[y][x + 2] == ' ')
				return(TRUE);
		case 3:
			if ((board[y][x + 2] == ' ') && (board[y][x + 3] == ' '))
				return(TRUE);
		default:
			return(false);
		}
	}
	else
		return (FALSE);//if the dot is a snake it will return false to gat a new location 
}

int TheSnakesGame::CountDigit(int num) {
	int temp, counter;
	if (num < 99 && num>9)
		return 2;
	else if (num > 99)
		return 3;
	else
		return 1;
}

void TheSnakesGame::init() {
	this->setBoard(temp, Start_Board);
	s[0].setArrowKeys("wxadz");
	s[1].setArrowKeys("imjln");
	s[0].setDirection(RIGHT);
	s[1].setDirection(LEFT);
	s[0].setGame(this);
	s[1].setGame(this);
	s[0].setPointerToOtherSnake(&this->s[1]);
	s[1].setPointerToOtherSnake(&this->s[0]);
	digit.setmission(this);
	digit.set_point_to_eater(&eat);
	this->setBoard(originalBoard, board_example);
	this->setBoard(board, board_example);
	this->r[0].setGamePointer(this, &this->s[0]);
	this->r[1].setGamePointer(this, &this->s[0]);
	this->c[0].setGamePointer(this, &this->s[0]);
	this->c[1].setGamePointer(this, &this->s[0]);
	eat.setGame(this,&digit, &this->s[0]);
	vec.resize(10);
}

void TheSnakesGame::copyBoardToBoard(char originalBoard[ROWS][COLS + 1], char board[ROWS][COLS + 1]) {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			board[i][j] = originalBoard[i][j];
		}
		board[i][COLS] = '\0';
	}
}

int TheSnakesGame::declareyouTheWinner(int win1, int  win2) {
	if (win1 == TRUE) {
		setTextColor(Color::YELLOW);
		gotoxy(11, 8);
		cout << "**********************************************************" << endl;
		gotoxy(11, 9);
		cout << "*                                                        *" << endl;
		gotoxy(11, 10);
		cout << "*    **  **  ******  **      ******  **    **   **       *" << endl;
		gotoxy(11, 11);
		cout << "*     ****   **      **      **  **   **  * ** **        *" << endl;
		gotoxy(11, 12);
		cout << "*      **    ******  **      **  **    * *   * *         *" << endl;
		gotoxy(11, 13);
		cout << "*      **    **      **      **  **     **   **          *" << endl;
		gotoxy(11, 14);
		cout << "*      **    ******  ******  ******      *   *           *" << endl;
		gotoxy(11, 15);
		cout << "*                                                        *" << endl;
		gotoxy(11, 16);
		cout << "*                Snake Won this level!                   *" << endl;
		gotoxy(11, 17);
		cout << "**********************************************************" << endl;
		setTextColor(Color::WHITE);
		s[0].setLen();
		gotoxy(0, 24);
		return 1;
	}
	else if (win1 == FALSE) {
		setTextColor(Color::GREEN);
		gotoxy(11, 8);
		cout << "**********************************************************" << endl;
		gotoxy(11, 9);
		cout << "*                                                        *" << endl;
		gotoxy(11, 10);
		cout << "*    **  **  ******  **      ******  **    **   **       *" << endl;
		gotoxy(11, 11);
		cout << "*     ****   **      **      **  **   **  * ** **        *" << endl;
		gotoxy(11, 12);
		cout << "*      **    ******  **      **  **    * *   * *         *" << endl;
		gotoxy(11, 13);
		cout << "*      **    **      **      **  **     **   **          *" << endl;
		gotoxy(11, 14);
		cout << "*      **    ******  ******  ******      *   *           *" << endl;
		gotoxy(11, 15);
		cout << "*                                                        *" << endl;
		gotoxy(11, 16);
		cout << "*                Snake lose this level!                  *" << endl;
		gotoxy(11, 17);
		cout << "**********************************************************" << endl;
		setTextColor(Color::WHITE);
		s[1].setLen();
		gotoxy(0, 24);
		return 1;
	}
	else if ((win2 == TRUE)) {
		setTextColor(Color::GREEN);
		gotoxy(11, 8);
		cout << "******************************************************" << endl;
		gotoxy(11, 9);
		cout << "*                                                    *" << endl;
		gotoxy(11, 10);
		cout << "*    ******   ******   ******   ******   **   **     *" << endl;
		gotoxy(11, 11);
		cout << "*    **       ** **    **       **       ** * **     *" << endl;
		gotoxy(11, 12);
		cout << "*    **  **   ** **    ******   ******   **  ***     *" << endl;
		gotoxy(11, 13);
		cout << "*    **   *   **  **   **       **       **   **     *" << endl;
		gotoxy(11, 14);
		cout << "*    ******   **   **  ******   ******   **   **     *" << endl;
		gotoxy(11, 15);
		cout << "*                                                    *" << endl;
		gotoxy(11, 16);
		cout << "*                Snake Won this level!               *" << endl;
		gotoxy(11, 17);
		cout << "******************************************************" << endl;
		setTextColor(Color::WHITE);
		s[1].setLen();
		gotoxy(0, 24);
		return 2;
	}
	else if ((win2 == FALSE)) {
		setTextColor(Color::YELLOW);
		gotoxy(11, 8);
		cout << "******************************************************" << endl;
		gotoxy(11, 9);
		cout << "*                                                    *" << endl;
		gotoxy(11, 10);
		cout << "*    ******   ******   ******   ******   **   **     *" << endl;
		gotoxy(11, 11);
		cout << "*    **       ** **    **       **       ** * **     *" << endl;
		gotoxy(11, 12);
		cout << "*    **  **   ** **    ******   ******   **  ***     *" << endl;
		gotoxy(11, 13);
		cout << "*    **   *   **  **   **       **       **   **     *" << endl;
		gotoxy(11, 14);
		cout << "*    ******   **   **  ******   ******   **   **     *" << endl;
		gotoxy(11, 15);
		cout << "*                                                    *" << endl;
		gotoxy(11, 16);
		cout << "*                Snake lose this level!              *" << endl;
		gotoxy(11, 17);
		cout << "******************************************************" << endl;
		setTextColor(Color::WHITE);
		s[0].setLen();
		gotoxy(0, 24);
		return 2;
	}
	else
		return(FALSE);
}

bool TheSnakesGame::IsAnswerCorrect(int answer) {
	switch (digit.getNumberMission()) {
	case 1:
		return (digit.isPrime(answer));
	case 0:
		return (digit.CollectAnumberDividedBy(answer));
	case 2:
		return (digit.IsTheSquertInteger(answer));
	case 3:
		return (digit.IsDiviedeByX_with_carry_y(answer));
	case 4:
		return(digit.isPalindrom(answer));
	case 5:
		return (digit.GetSingleDigitNumber(answer));
	case 6:
		return (digit.findTheCrrentDate(answer));
	case 7:
		return (digit.Equation(answer));
	case 8:
		return (digit.CollectAnumberDividedBy_X_and_Y_(answer));
	}


}

void TheSnakesGame::ShowMainMenu() {
	system("CLS");
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+          **********************************************************          +" << endl;
	cout << "+          *                WELCOME To Crazy Snake!                 *          +" << endl;
	cout << "+          **********************************************************          +" << endl;
	cout << "+          *                                                        *          +" << endl;
	cout << "+          *                      Main menu:                        *          +" << endl;
	cout << "+          **********************************************************          +" << endl;
	cout << "+          *                                                        *          +" << endl;
	cout << "+          *       Please select from the following options:        *          +" << endl;
	cout << "+          *                  *Instructions (1)                     *          +" << endl;
	cout << "+          *                  *Start game!  (2)                     *          +" << endl;
	cout << "+          *                  *Exit         (9)                     *          +" << endl;
	cout << "+          *                                                        *          +" << endl;
	cout << "+          **********************************************************          +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "+                                                                              +" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

void TheSnakesGame::ShowInstructions() {
	this->setBoard(temp, Instructions);
	PrintBoard(temp);
	gotoxy(77, 1);
	cout << ' ';
	gotoxy(14, 1);
	cout << ' ';
	gotoxy(0, 24);
	_getch();
	Beep(300, 300);
	system("CLS");
	MainMenu();
}

void TheSnakesGame::startScreenSound() {
	Beep(440, 1200);
	Beep(349, 350);
	Beep(523, 150);
	Beep(440, 400);
	Beep(349, 350);
	Beep(523, 150);
	Beep(440, 650);
	Beep(0, 150);
	Beep(659, 1200);
	Beep(698, 350);
	Beep(523, 150);
	Beep(415, 400);
	Beep(349, 350);
	Beep(523, 150);
	Beep(440, 650);
}

void TheSnakesGame::ShowTheFirstScreen() {
	system("CLS");
	PrintFirstBoard(temp);

	gotoxy(0, 24);
	//startScreenSound();
	gotoxy(25, 22);
	cout << "Press any key to continue!";
	gotoxy(0, 24);
	_getch();
	system("CLS");
	Beep(300, 300);
}

void TheSnakesGame::run() {
	char choice;
	int flag = 1;
	system("CLS");

	ShowMainMenu();
	choice = _getch();
	system("CLS");
	Beep(300, 300);
	switch (choice) {
	case '1':
		ShowInstructions();
		break;
	case '2':
		init();
		digit.load_mission_from_file();
		play();
		break;
	case '9':
		statusOfTheGame = FINISH;
		break;
	}
}

void TheSnakesGame::MainMenu() {
	char choice;
	ShowMainMenu();
	choice = _getch();
	system("CLS");
	Beep(300, 300);
	switch (choice) {
		case '1':
			ShowInstructions();
			break;
		case '2':
			//call to the dtor of the game
			init();
			play();
			break;
		case '9':
			statusOfTheGame = FINISH;
			//call to dtor of the game
			break;
		}
}

void TheSnakesGame::subMenu(int *count, char choice) {

	switch (choice) {
	case '1':
		statusOfTheGame = FINISH;
		break;
	case '2':
		setBoard(board, board_example);
		system("CLS");
		digit.setLogSize(0);
		s[0].ResetSnake(10, 9, RIGHT);
		s[1].ResetSnake(70, 9, LEFT);
		run();
		break;
	case '3':
		break;
	case '4':
		setBoard(board, board_example);
		system("CLS");
		*count = 0;
		digit.setLogSize(0);
		break;
	case '5':
		setBoard(board, board_example);
		system("CLS");
		*count = 0;
		digit.setLogSize(0);
		break;
	case '6':
		setBoard(board, board_example);
		system("CLS");
		digit.setLogSize(0);
		s[0].ResetSnake(10, 9, RIGHT);
		s[1].ResetSnake(70, 9, LEFT);
		init();
		play();
		break;
	case '7':
		choice = 3;
		SHOW_REPLAY = TRUE;
		break;
	}
}

void TheSnakesGame::ShowSubMenu() {
	setTextColor(WHITE);
	gotoxy(11, 5);
	cout << "**********************************************************" << endl;
	gotoxy(11, 6);
	cout << "*                      Crazy Snake!                      *" << endl;
	gotoxy(11, 7);
	cout << "**********************************************************" << endl;
	gotoxy(11, 8);
	cout << "*                       Sub menu:                        *" << endl;
	gotoxy(11, 9);
	cout << "**********************************************************" << endl;
	gotoxy(11, 10);
	cout << "*                                                        *" << endl;
	gotoxy(11, 11);
	cout << "*        Please select from the following options:       *" << endl;
	gotoxy(11, 12);
	cout << "*             *Exit                      (1)             *" << endl;
	gotoxy(11, 13);
	cout << "*             *Return to the main menu!  (2)             *" << endl;
	gotoxy(11, 14);
	cout << "*             *Continue to play          (3)             *" << endl;
	gotoxy(11, 15);
	cout << "*             *Start over this mission   (4)             *" << endl;
	gotoxy(11, 16);
	cout << "*             *Start new mission         (5)             *" << endl;
	gotoxy(11, 17);
	cout << "*             *Start over                (6)             *" << endl;
	gotoxy(11, 18);
	cout << "*                                                        *" << endl;
	gotoxy(11, 19);
	cout << "**********************************************************" << endl;
}

void TheSnakesGame::PrintBoard(const char board[ROWS][COLS + 1]) {//print full board
	char c;
	system("CLS");
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}

	gotoxy(77, 1);
	cout << s[0].getLen() - 3;
	gotoxy(14, 1);
	cout << s[1].getLen() - 3;
}

void TheSnakesGame::PrintFirstBoard(const char board[ROWS][COLS + 1]) {//print full board
	char c;
	system("CLS");
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

void TheSnakesGame::someoneWonSound() {
	Beep(330, 100); Sleep(100);
	Beep(330, 100); Sleep(300);
	Beep(330, 100); Sleep(300);
	Beep(262, 100); Sleep(100);
	Beep(330, 100); Sleep(300);
	Beep(392, 100); Sleep(700);
}

void TheSnakesGame::someoneLoseSound() {
	Beep(658, 100); Sleep(100);
	Beep(425, 100); Sleep(300);
	Beep(412, 100); Sleep(300);
	Beep(425, 100); Sleep(100);
	Beep(456, 100); Sleep(300);
	Beep(213, 100); Sleep(700);
}

void TheSnakesGame::updateVector(int vector_index) {
	vec[vector_index].Setmatrix(board);
	vec[vector_index].setUpdate();
	vec[vector_index].setmission(&digit);
	vec[vector_index].set_rowColFly(r[0].getRowflyX(), r[0].getRowflyY(), '1');
	vec[vector_index].set_rowColFly(r[1].getRowflyX(), r[1].getRowflyY(), '2');
	vec[vector_index].set_rowColFly(c[0].getColflyX(), c[0].getColflyY(), '3');
	vec[vector_index].set_rowColFly(c[1].getColflyX(), c[1].getColflyY(), '4');
	vec[vector_index].set_rowColFly(eat.getEaterX(), eat.getEaterY(), '5');
	vec[vector_index].copySnake_parametrs(s);
}

void TheSnakesGame::play() {
	char choice='0', key = 0;
	int dir, i=0;
	int whoWin, count=0;
	bool flag = true;
	bool justOnce = TRUE;

	while ((key != ESC) && (statusOfTheGame != FINISH)) {
		board[1][39] = i + 1 + '0';
		PrintBoard(board);

		if (SHOW_REPLAY && FINISH_STAGE) {
			system("CLS");
			replayFunction();
			system("CLS");
			SHOW_REPLAY = FALSE;
			choice = '5';
			gotoxy(15, 15);
			cout << "Get ready for a new stage...";
			Sleep(1500);
			PrintBoard(board);
		}
		if (FINISH_STAGE)
		{
			vector_index = 0;
			vec.resize(10);
		}

		if (choice != '3' && choice != '4' && choice != '7') {
			digit.SetRandNumberForMissions();
			digit.set_currMission_after_rendom();
			i++;
			digit.PrintMission();
			FINISH_STAGE = FALSE;
			s[0].setOptionalCountAndSize();
			s[1].setOptionalCountAndSize();
		}
		else if ((choice == '3' || choice == '4') && digit.getNumberMission() == 7)
			digit.printMission7NotRandomNUM();
		else
			digit.PrintMission();
		eat.drawStartingPos();
		checkForRightAnswers(count);
		updateVector(vector_index);

		do {
			if (_kbhit()) {
				key = _getch();

				if ((dir = s[0].getDirection(key)) != -1) {
					if (dir == BULLET) {
						s[0].setbulletArray();
					}
					else {
						s[0].setDirection(dir);
					}
				}
				else if ((dir = s[1].getDirection(key)) != -1) {
					if (dir == BULLET)
						s[1].setbulletArray();
					else
						s[1].setDirection(dir);
				}
			}
			if (s[0].get_counter_bullet() != NUTRAL) {
				s[0].moveBullet();
				update_counter_vector();
				updateVector(vector_index);
			}
			if (s[1].get_counter_bullet() != NUTRAL) {
				s[1].moveBullet();
				update_counter_vector();
				updateVector(vector_index);
			}

			if (!s[0].IsDisapear()) {
				s[0].move();
				update_counter_vector();
				updateVector(vector_index);
			}
			if (!s[1].IsDisapear()) {
				s[1].move();
				update_counter_vector();
				updateVector(vector_index);
			}

			if (eat.is_VecArr_Full()) {
				if (justOnce) {
					eat.checkWhereToGo();
					justOnce = FALSE;
				}
				eat.moveEater();

			}

			r[0].moveRowfly();
			r[1].moveRowfly();
			if((c[0].getColflyX()!=1) || (c[0].getColflyY()!=24)){
				c[0].moveColfly();
			}
			if ((c[1].getColflyX() != 1) || (c[1].getColflyY() != 24)) {
				c[1].moveColfly();
			}
			
			update_counter_vector();
			updateVector(vector_index);
			Sleep(200);
			if (whoWin = declareyouTheWinner(s[0].getWin(), s[1].getWin())) {//if one of the users won 
				if (s[0].getWin() == 0 || s[1].getWin() == 0) {
					someoneLoseSound();
					system("CLS");
					PrintBoard(board);
					digit.ShowTherightAnswers();
				}
				else
					someoneWonSound();
				system("CLS");
				s[0].setIfSnackWon(-1);
				s[1].setIfSnackWon(-1);
				digit.deleteRandomNumbersFromArr();
				PrintBoard(board);
				eat.Myclear();
				eat.resetPlace();
				justOnce = TRUE;
				count = count / 2;//insilized count after deleting half of the numbers 
				flag = false;
				s[0].setOptionalCountAndSize();
				s[1].setOptionalCountAndSize();
				Sleep(200);
				FINISH_STAGE = true;
			}
			if (count % 5 == 0) {
				initBoard();
				s[0].SetFiveNumbersCount();
				s[1].SetFiveNumbersCount();
				if ((s[0].IsDisapear()) && (s[0].getFiveNumbersCount())) {
					s[0].replaceSnakeInRandomPlace();
					s[0].IsNotDisapear();
				}
				if ((s[1].IsDisapear()) && (s[1].getFiveNumbersCount())) {
					s[1].replaceSnakeInRandomPlace();
					s[1].IsNotDisapear();
				}
			}
			count++;
		} while ((key != ESC) && (count < 300) && (flag));
		if (key == ESC) {
			key = 0;
			ShowSubMenu();
			choice = _getch();
			subMenu(&count, choice);
		}
		flag = true;
		if (count == 300) {//if any player won the misiion and there are 60 numbers on the board
			digit.ShowTherightAnswers();
			digit.deleteRandomNumbersFromArr();
			s[0].setOptionalCountAndSize();
			s[1].setOptionalCountAndSize();
			eat.resetPlace();
			eat.Myclear();
			justOnce = TRUE;
			count = 150;
		}
		system("CLS");

		if (s[0].getLen() == 15){
			setBoard(temp, Yellow);
			setTextColor(Color::YELLOW);
			PrintBoard(temp);
			gotoxy(77, 1);
			cout << ' ';
			gotoxy(14, 1);
			cout << ' ';
			gotoxy(0, 24);
			statusOfTheGame = FINISH;
		}
		else if (s[1].getLen() == 15) {
			setBoard(temp, Green);
			setTextColor(Color::GREEN);
			PrintBoard(temp);
			gotoxy(77, 1);
			cout << ' ';
			gotoxy(14, 1);
			cout << ' ';
			gotoxy(0, 24);
			statusOfTheGame = FINISH;
		}
	}

}

void TheSnakesGame::checkForRightAnswers(int count) {
	int i;
	for  ( i = 0;  i < count/5;  i++)
	{
		if (IsAnswerCorrect( GetNumFromBoard(digit.getPointFromArray(i))))
		{
			eat.Insert_Num_pos_VecAnswers(digit.getPointFromArray(i));
		}
	}
}