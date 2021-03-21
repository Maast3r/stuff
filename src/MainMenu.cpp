#include <stack>

#include <SDL.h>

#include "MainMenu.hpp"
#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"
#include "Minesweeper.hpp"
#include "Platformer.hpp"

MainMenu::MainMenu(int newScreenWidth, int newScreenHeight) {
	shouldPop = false;
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
	nextScene = NULL;

	int buttonLength = screenWidth / 2 - 10;
	int buttonHeight = screenHeight / 3 - 10;

	menu.x = 0;
	menu.y = 0;
	menu.w = screenWidth ;
	menu.h = screenHeight;

	easyButton.x = buttonLength / 2;
	easyButton.y = 5;
	easyButton.w = buttonLength;
	easyButton.h = buttonHeight;

	mediumButton.x = buttonLength / 2;
	mediumButton.y = buttonHeight + 10;
	mediumButton.w = buttonLength;
	mediumButton.h = buttonHeight;

	hardButton.x = buttonLength / 2;
	hardButton.y = buttonHeight * 2 + 15;
	hardButton.w = buttonLength;
	hardButton.h = buttonHeight;

	easyTexture = NULL;
	mediumTexture = NULL;
	hardTexture = NULL;
}

MainMenu::~MainMenu() {
	nextScene = NULL;

	SDL_DestroyTexture(easyTexture);
	SDL_DestroyTexture(mediumTexture);
	SDL_DestroyTexture(hardTexture);

	easyTexture = NULL;
	mediumTexture = NULL;
	hardTexture = NULL;
}

void MainMenu::handleEvents(SDL_Event* event, SoundWrapper* soundWrapper) {
	int mouseX = 0, mouseY = 0;
	(void) soundWrapper;

	if (event->type == SDL_MOUSEBUTTONDOWN) {
		if (event->button.button == SDL_BUTTON_LEFT) {
			mouseX = event->button.x;
			mouseY = event->button.y;
		
			if (
				(easyButton.x < mouseX) &&
				(mouseX < easyButton.x + easyButton.w) &&
				(easyButton.y < mouseY) &&
				(mouseY < easyButton.y + easyButton.h)
			) {
				nextScene = new Minesweeper(screenWidth, screenHeight, 9);
			} else if (
				(mediumButton.x < mouseX) &&
				(mouseX < mediumButton.x + mediumButton.w) &&
				(mediumButton.y < mouseY) &&
				(mouseY < mediumButton.y + mediumButton.h)
			) {
				nextScene = new Minesweeper(screenWidth, screenHeight, 16);
			} else if (
				(hardButton.x < mouseX) &&
				(mouseX < hardButton.x + hardButton.w) &&
				(hardButton.y < mouseY) &&
				(mouseY < hardButton.y + hardButton.h)
			) {
				// nextScene = new Minesweeper(screenWidth, screenHeight, 30);
				nextScene = new Platformer(screenWidth, screenHeight);
			}
		}
	}
}

void MainMenu::update(GraphicsWrapper* graphicsWrapper) {
	if (!easyTexture) {
		SDL_Surface* easySurface = NULL;
		SDL_Color color = { 0, 255, 0 ,255 };

		easySurface = TTF_RenderText_Solid(graphicsWrapper->font, "Easy", color);
		easyTexture = SDL_CreateTextureFromSurface(graphicsWrapper->renderer, easySurface);

		SDL_FreeSurface(easySurface);
		easySurface = NULL;
	} else if (!mediumTexture) {
		SDL_Surface* mediumSurface = NULL;
		SDL_Color color = { 0, 255, 0 ,255 };

		mediumSurface = TTF_RenderText_Solid(graphicsWrapper->font, "Medium", color);
		mediumTexture = SDL_CreateTextureFromSurface(graphicsWrapper->renderer, mediumSurface);

		SDL_FreeSurface(mediumSurface);
		mediumSurface = NULL;
	} else if (!hardTexture) {
		SDL_Surface* hardSurface = NULL;   
		SDL_Color color = { 0, 255, 0 ,255 };

		hardSurface = TTF_RenderText_Solid(graphicsWrapper->font, "Hard", color);
		hardTexture = SDL_CreateTextureFromSurface(graphicsWrapper->renderer, hardSurface);

		SDL_FreeSurface(hardSurface);
		hardSurface = NULL;
	}
}

void MainMenu::render(GraphicsWrapper* graphicsWrapper) {
	SDL_SetRenderDrawColor(graphicsWrapper->renderer, 0xDD, 0xDD, 0xDD, 0xFF);

	SDL_RenderFillRect(graphicsWrapper->renderer, &easyButton);
	SDL_RenderFillRect(graphicsWrapper->renderer, &mediumButton);
	SDL_RenderFillRect(graphicsWrapper->renderer, &hardButton);

	if (easyTexture) {
		SDL_RenderCopy(graphicsWrapper->renderer, easyTexture, NULL, &easyButton);
	}
	if (mediumTexture) {
		SDL_RenderCopy(graphicsWrapper->renderer, mediumTexture, NULL, &mediumButton);
	}
	if (hardTexture) {
		SDL_RenderCopy(graphicsWrapper->renderer, hardTexture, NULL, &hardButton);
	}
}
