#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GraphicsWrapper.hpp"

GraphicsWrapper::GraphicsWrapper() {
	window = NULL;
	renderer = NULL;
	font = NULL;
	frame = 0;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	} else {
		TTF_Init();
		window = SDL_CreateWindow("Game",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									screenWidth, screenHeight,
									SDL_WINDOW_SHOWN);
		if (!window) {
			std::cout << "Window could not be created!" << std::endl
					  << "SDL_Error: " << SDL_GetError() << std::endl;
		} else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (!renderer) {
				std::cout << "Renderer could not be created!" << std::endl
						  << "SDL_Error: " << SDL_GetError() << std::endl;
			}
		}
	}

	font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 12);
}

GraphicsWrapper::~GraphicsWrapper() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);

	renderer = NULL;
	window = NULL;
	font = NULL;

	TTF_Quit();
	SDL_Quit();
}
