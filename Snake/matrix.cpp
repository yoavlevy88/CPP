#include "matrix.h"

void matrix::printmatrixcell() {
	enum{ BULLETS = 4,BODY = 0 };
	if (MYBORD == UPDATE) {
		print_matrix();
	}
	for (int i = 0; i < 2; i++) {
		s_temp[i].printMyarray(BULLETS);
		s_temp[i].printMyarray(BODY);
		r_temp[i].PrintMe();
		c_temp[i].PrintMe();
	}
	eater.PrintMe();
}

void matrix::update_snake_location_len(Snake& copy) {
	int index;
	int k;

	if (which_snack_to_update(copy)) 
		index = 0;
	else
		index = 1;
	


	for (k = 0; k < copy.getLen(); k++) {
		Point p = copy.get_body_cell(k);
		s_temp[index].update_cell_in_snake_body_arr(k, p);

	}
	s_temp[index].setLen(copy.getLen());//update the matrix temp snack len


}

void matrix::copyBoardToBoard_inMatrix(char  originalBoard[ROWS][COLS + 1]) {
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			gotoxy(j, i);
			vec_board[i][j] = originalBoard[i][j];
		}
		vec_board[i][COLS] = '\0';
	}
	MYBORD = UPDATE;
}
void matrix::UpdateNumInBoard2( int NumToUpdate, int x, int y) {
	int temp, res;
	char ch;
	res = CountDigit(NumToUpdate);

	if (NumToUpdate == 0)
		vec_board[y][x] = '0';


	while (NumToUpdate && res) {
		temp = NumToUpdate % 10;
		ch = (char)(temp + '0');
		vec_board[y][x + res - 1] = ch;
		NumToUpdate /= 10;
		res--;
	}
}

int matrix::CountDigit(int num) {
	int temp, counter;
	if (num < 99 && num>9)
		counter = 2;
	else if (num > 99)
		counter = 3;
	else
		counter = 1;
	return(counter);
}



void matrix:: update_score_to_mat(int s1, int s2) {//this function update the score to the mat in the beginnig  of the level
	char l, r;
	if (s1 > 9) {
		r = s1 % 10;
		l = s1 / 10;
		setcol_row(1, 77, l);
		setcol_row(1, 78, r);
	}
	else
		setcol_row(1, 77, char('0' + s1));

	if (s2 > 9) {
		r = s2 % 10;
		l = s2 / 10;
		setcol_row(1, 14, l);
		setcol_row(1, 15, r);
	}
	else
		setcol_row(1, 14, char('0' + s2));
}

char matrix:: getcol_row(int i, int j)
{
	return(vec_board[i][j]);
}

void matrix:: printToMatrix(int x, int y, char* str) {
	int size = strlen(str);
	for (int i = 0; i < size; i++)
	{
		vec_board[y][x] = str[i];
		x++;
	}
}

void matrix:: setcol_row(int i, int j, int c)
{
	this->vec_board[i][j] = c;
}

void matrix::set_rowColFly(int i, int j, char name)
{
	if (name == '1')
	{
		r_temp[0].setRowflyPlace(i, j);
	}
	else if (name == '2')
	{
		r_temp[1].setRowflyPlace(i, j);
	}
	else if (name == '3')
	{
		c_temp[0].setColflyPlace(i, j);
	}
	else if (name == '4')
	{
		c_temp[1].setColflyPlace(i, j);
	}
	else if (name == '5')
	{
		eater.setEater(i, j);
	}
}

void matrix:: Setmatrix(const char board[ROWS][COLS + 1]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			this->setcol_row(i, j, board[i][j]);

		}
	}
}

void matrix:: print_matrix() {
	gotoxy(0, 0);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if ((i == 2) && (j == 10)) {
				digit->PrintMission();
				j += digit->getLenOfMission()-1;
				if (digit->getNumberMission() == 7)
				{
					j += 16;
				}
			}
			else if (((i == 1) && (j == 2)) || ((i == 1) && (j == 64))) {
				cout << "             ";
				j += 12;
			}
			else
				cout << vec_board[i][j];
		}
		cout << endl;
	}
}

void matrix::copySnake_parametrs( Snake org[2]) {
	s_temp[0] = org[0];
	s_temp[1] = org[1];
	p_to_s1 = &org[0];
	p_to_s2 = &org[1];

}
bool  matrix::which_snack_to_update(Snake& s) {//return 1 if the address of s is equal to the snake s[0]
	if (p_to_s1 == &s)
		return(1);
	else
		return(0);

}
void matrix::update_bullet_inMat(Snake& s) {
	bullet *res;
	int k;
	int index;
	if (which_snack_to_update(s))// return which snake if it true -its snak[0]
		index = 0;
	else 
		index = 1;
	
	for (k = 0; k <= s.get_counter_bullet(); k++) {
		res = s.get_bullet_array(k);
		Point p = res->getBullet_point();
		s_temp[index].update_cell_in_bullets_arr(k, p);
		

	}
	s_temp[index].set_counter_bullet(s.get_counter_bullet());


}