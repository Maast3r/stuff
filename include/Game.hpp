#include <stack>

#include <SDL.h>

#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"
#include "Minesweeper.hpp"
#include "Scene.hpp"

#ifndef GAME_HPP
#define GAME_HPP

class Game {
	public:
		GraphicsWrapper* graphicsWrapper;
		SoundWrapper* soundWrapper;
		bool isRunning;
		std::stack <Scene*> scenes;

		Game();
		~Game();
		void handleEvents();
		void update();
		void render();
};

#endif
