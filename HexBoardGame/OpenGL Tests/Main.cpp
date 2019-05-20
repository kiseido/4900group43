#include "ECS.h"

int main() {
	int e = 0;
	std::cout << "Starting Program" << std::endl;

	try {
		ECS::Game game;
		game.ShowSplash();
		game.RequestGameType();
		game.setupGame();
		game.GameLoop();

	}
	catch (std::logic_error& a) {
		std::cout << "Something went wrong: " << a.what() << std::endl;
		e = 1;
	}
	std::cout << "Exiting Program" << std::endl;
	return e;
}