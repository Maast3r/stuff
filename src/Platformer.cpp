#include "Platformer.hpp"
#include "Hero.hpp"
#include "Platform.hpp"

/**
 * The concept of this game is that the hero can only move along "walls"
 * - If you jump across, the perspective stays the same
 * - If you touch a "wall", your perspective shifts so you're always standing "up"
 */
Platformer::Platformer(int screenWidth, int screenHeight){
	width = screenWidth;
	height = screenHeight; 
	started = false;
	lost = false;
	won = false;
	shouldPop = false;
	nextScene = NULL;
	hero = new Hero();

	platforms = new Platform*[5];
	platforms[0] = new Platform(0, 0, screenWidth, 20);
	platforms[1] = new Platform(0, 0, 20, screenHeight);
	platforms[2] = new Platform(0, screenHeight - 20, screenWidth, 20);
	platforms[3] = new Platform(screenWidth - 20, 0, 20, screenHeight);
	platforms[4] = new Platform(screenWidth / 5, screenHeight /2 , 50, 300);
}

Platformer::~Platformer() {
	nextScene = NULL;
	hero = NULL;
	platforms = NULL;
}

void Platformer::handleEvents(SDL_Event* event, SoundWrapper* soundWrapper) {
	hero->handleEvents(event, soundWrapper);
}

void Platformer::update(GraphicsWrapper* graphicsWrapper) {
	hero->update(graphicsWrapper, platforms);
}

void Platformer::render(GraphicsWrapper* graphicsWrapper) {
	hero->render(graphicsWrapper);

	for (int i = 0; i < 5; i++) {
		platforms[i]->render(graphicsWrapper);
	}
}
