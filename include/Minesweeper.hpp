#include <SDL.h>

#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"
#include "Tile.hpp"
#include "Scene.hpp"

#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

class Minesweeper: public Scene {
	private:
		Tile*** tiles;
		int size;
		int width;
		int height;
		bool started;
		bool lost;
		bool won;
		int bombCount;

		void flipNonBombs(int x, int y);
		int getNumberOfFlippedTiles();
		void placeBombs(int firstFlippedPositionX, int firstFlippedPositionY);

	public:
		Minesweeper(int screenWidth, int screenHeight, int newSize);
		~Minesweeper();
		void handleEvents(SDL_Event* event, SoundWrapper* soundWrapper);
		void update(GraphicsWrapper* graphicsWrapper);
		void render(GraphicsWrapper* graphicsWrapper);
};

#endif
