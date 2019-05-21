#include "ECS.h"
#include "Window.h"
#include "Renderer.h"

int main() {
	int e = 0;
	std::cout << "Starting Program" << std::endl;

	try {
        Window::Init();
        Renderer::Setup();
		ECS::Game game;
		game.ShowSplash();
		game.RequestGameType();
		game.Setup();
		game.GameLoop();

	}
	catch (std::logic_error& a) {
		std::cout << "Something went wrong: " << a.what() << std::endl;
		e = 1;
	}
    Window::Close();
	std::cout << "Exiting Program" << std::endl;
	return e;
}