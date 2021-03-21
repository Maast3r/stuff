#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "GraphicsWrapper.hpp"
#include "Minesweeper.hpp"
#include "MainMenu.hpp"
#include "Scene.hpp"
#include "Game.hpp"

Game::Game() {
	isRunning = true;

	graphicsWrapper = new GraphicsWrapper();
	soundWrapper = new SoundWrapper();
	scenes.push(new MainMenu(graphicsWrapper->screenWidth, graphicsWrapper->screenHeight));
}

Game::~Game() {
	graphicsWrapper = NULL;
	soundWrapper = NULL;
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	scenes.top()->handleEvents(&event, soundWrapper);

	switch(event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) {
				case SDLK_9:
					if (Mix_PlayingMusic() == 0) {
						Mix_PlayMusic(soundWrapper->music, -1);
					} else if (Mix_PausedMusic() == 1) {
						Mix_ResumeMusic();
					} else {
						Mix_PauseMusic();
					}
					break;
				case SDLK_0:
					Mix_HaltMusic();
					break;
			}
			break;
		default:
			break;
	}
}

void Game::update() {
	Scene* currentScene = scenes.top();
	
	if (currentScene) {
		Scene* nextScene = NULL;

		if (currentScene->shouldPop) {
			scenes.pop();
		}
		
		nextScene = currentScene->getNextScene();
		if (nextScene) {
			currentScene->destroyNextScene();
			scenes.push(nextScene);
		}

		scenes.top()->update(graphicsWrapper);

		nextScene = NULL;
	}

	currentScene = NULL;
}

void Game::render() {
	SDL_SetRenderDrawColor(graphicsWrapper->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(graphicsWrapper->renderer);
	scenes.top()->render(graphicsWrapper);
	SDL_RenderPresent(graphicsWrapper->renderer);
}
