#include <algorithm>
#include <iostream>
#include <math.h>

#include <SDL.h>

#include "Minesweeper.hpp"
#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"
#include "Tile.hpp"

Minesweeper::Minesweeper(int screenWidth, int screenHeight, int newSize) {
	size = newSize;
	width = screenWidth;
	height = screenHeight;
	tiles = new Tile**[size];
	lost = false;
	won = false;
	started = false;
	shouldPop = false;
	nextScene = NULL;
	bombCount = round(size * size / 4);

	int tileSize = std::min(width, height) / size;
	
	for (int i = 0; i < size; i++) {
		tiles[i] = new Tile*[size];

		for (int j = 0; j< size; j++) {
			tiles[i][j] = new Tile(
				tileSize * i + 2 * i,
				tileSize * j + 2 * j,
				tileSize,
				tileSize
			);
		}
	}
}

Minesweeper::~Minesweeper() {
	nextScene = NULL;
}

void Minesweeper::handleEvents(SDL_Event* event, SoundWrapper* soundWrapper) {
	int firstFlippedPositionX = -2;
	int firstFlippedPositionY = -2;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j< size; j++) {
			tiles[j][i]->handleEvents(event, soundWrapper);
			if (tiles[j][i]->showValue) {

				if (!started && firstFlippedPositionX == -2 && firstFlippedPositionY == -2) {
					firstFlippedPositionX = j;
					firstFlippedPositionY = i;
					started = true;
					placeBombs(firstFlippedPositionX, firstFlippedPositionY);
				}
				if (tiles[j][i]->isBomb()) {
					shouldPop = true;
					lost = true;
					printf(" YOU LOST \n");
				}
			}
		}
	}
}

void Minesweeper::flipNonBombs(int x, int y) {
	if (tiles[x][y]->value == 0 && tiles[x][y]->showValue && !tiles[x][y]->visited) {
		tiles[x][y]->visited = true;

		if (x-1 >= 0 && y-1 >= 0 && tiles[x-1][y-1]->value > -1) {
			tiles[x-1][y-1]->showValue = true;
			flipNonBombs(x-1, y-1);
		}
		if (x-1 >= 0 && tiles[x-1][y]-> value > -1) {
			tiles[x-1][y]->showValue = true;
			flipNonBombs(x-1, y);
		}
		if (x-1 >= 0 && y+1 < size && tiles[x-1][y+1]->value > -1) {
			tiles[x-1][y+1]->showValue = true;
			flipNonBombs(x-1, y+1);
		}
		if (y-1 >= 0 && tiles[x][y-1]->value > -1) {
			tiles[x][y-1]->showValue = true;
			flipNonBombs(x, y-1);
		}
		if (y+1 < size && tiles[x][y+1]->value > -1) {
			tiles[x][y+1]->showValue = true;
			flipNonBombs(x, y+1);
		}
		if (x+1 < size && y-1 >= 0 && tiles[x+1][y-1]->value > -1) {
			tiles[x+1][y-1]->showValue = true;
			flipNonBombs(x+1, y-1);
		}
		if (x+1 < size && tiles[x+1][y]->value > -1) {
			tiles[x+1][y]->showValue = true;
			flipNonBombs(x+1, y);
		}
		if (x+1 < size && y+1 < size && tiles[x+1][y+1]->value > -1) {
			tiles[x+1][y+1]->showValue = true;
			flipNonBombs(x+1, y+1);
		}
	}
}

void Minesweeper::update(GraphicsWrapper* graphicsWrapper) {
	int countVisibleNonBombs = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j< size; j++) {
			if (tiles[j][i]->showValue && tiles[j][i]->value > -1) {
				++countVisibleNonBombs;
			}

			if (tiles[j][i]->showValue && tiles[j][i]->value == 0 && !tiles[j][i]->visited) {
				if (tiles[j][i]->showValue) {
					flipNonBombs(j, i);
				}
			}
			tiles[j][i]->update(graphicsWrapper);
		}
	}

	if (countVisibleNonBombs == size*size - bombCount) {
		printf("win");
	}
}

void Minesweeper::render(GraphicsWrapper* graphicsWrapper) {
	printf("----Board----\n");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j< size; j++) {
			tiles[i][j]->render(graphicsWrapper);
			std::cout << tiles[j][i]->value << " | ";
		}
		std::cout << std::endl;
	}
	printf("-------------\n");
}

void Minesweeper::placeBombs(int firstFlippedPositionX, int firstFlippedPositionY) {
	int bombs = bombCount;
	int randomX, randomY;
 
	while (bombs > 0) {
		randomX = rand() % size;
		randomY = rand() % size;

		if (tiles[randomX][randomY]->isBomb()) {
			continue;
		} else if (randomX == firstFlippedPositionX && randomY == firstFlippedPositionY) {
			continue;
		} else if (randomX == firstFlippedPositionX - 1 && randomY == firstFlippedPositionY - 1) {
			continue;
		} else if (randomX == firstFlippedPositionX - 1 && randomY == firstFlippedPositionY) {
			continue;
		} else if (randomX == firstFlippedPositionX - 1 && randomY == firstFlippedPositionY + 1) {
			continue;
		} else if (randomX == firstFlippedPositionX && randomY == firstFlippedPositionY - 1) {
			continue;
		} else if (randomX == firstFlippedPositionX && randomY == firstFlippedPositionY + 1) {
			continue;
		} else if (randomX == firstFlippedPositionX + 1 && randomY == firstFlippedPositionY - 1) {
			continue;
		} else if (randomX == firstFlippedPositionX + 1 && randomY == firstFlippedPositionY) {
			continue;
		} else if (randomX == firstFlippedPositionX + 1 && randomY == firstFlippedPositionY + 1) {
			continue;
		} else {
			tiles[randomX][randomY]->placeBomb();

			if (randomX - 1 >= 0 && randomY - 1 >= 0) {
				tiles[randomX - 1][randomY - 1]->incrementBombProximityCount();
			}
			if (randomX - 1 >= 0) {
				tiles[randomX - 1][randomY]->incrementBombProximityCount();
			}
			if (randomX - 1 >= 0 && randomY + 1 < size) {
				tiles[randomX - 1][randomY + 1]->incrementBombProximityCount();
			}
			if (randomY - 1 >= 0) {
				tiles[randomX][randomY - 1]->incrementBombProximityCount();
			}
			if (randomY + 1 < size) {
				tiles[randomX][randomY + 1]->incrementBombProximityCount();
			}
			if (randomX + 1 < size && randomY - 1 >= 0) {
				tiles[randomX + 1][randomY - 1]->incrementBombProximityCount();
			}
			if (randomX + 1 < size) {
				tiles[randomX + 1][randomY]->incrementBombProximityCount();
			}
			if (randomX + 1 < size && randomY + 1 < size) {
				tiles[randomX + 1][randomY + 1]->incrementBombProximityCount();
			}

			--bombs;
		}
	}
}
