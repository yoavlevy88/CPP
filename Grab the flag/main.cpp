#include "Game.h"
#include "AlgorithmRegistration.h"
using namespace std;


void main(int argc, char *argv[]) {
	
	Game game (argc, argv);
	game.init();
	game.run();
}

