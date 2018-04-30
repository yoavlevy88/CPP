using namespace std;
#include <windows.h>
#include <iostream>
#include "TheSnakesGame.h"



int main() {
	TheSnakesGame game;
	game.init();
 	game.ShowTheFirstScreen();
	game.run();
}