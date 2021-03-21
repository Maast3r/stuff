#include "Game.hpp"
#include "Timer.hpp"

int main(int argc, char* argv[]) {
	(void) argc;
	(void) argv;
	Game* game = NULL;
	
	game = new Game();

	Timer fpsTimer;
	int countedFrames = 0;
	fpsTimer.start();

	while (game->isRunning) {
		game->handleEvents();
		game->update();
		game->render();

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000) {
			avgFPS = 0;
		}
		// printf("FPS %f\n", avgFPS);
		++countedFrames;
	}

	game = NULL;

	return 0;
}
