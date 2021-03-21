#include <stack>

#include <SDL.h>

#include "Scene.hpp"
#include "SoundWrapper.hpp"

#ifndef MAINMENU_HPP
#define MAINMENU_HPP

class MainMenu: public Scene {
	private:
		std::stack <Scene*> scenes;
		SDL_Rect menu;
		SDL_Rect easyButton;
		SDL_Rect mediumButton;
		SDL_Rect hardButton;
		SDL_Texture* easyTexture;
		SDL_Texture* mediumTexture;
		SDL_Texture* hardTexture;
		int screenWidth;
		int screenHeight;

	public:
		MainMenu(int newScreenWidth, int newScreenHeight);
		~MainMenu();
		void handleEvents(SDL_Event* event, SoundWrapper* soundWrapper);
		void update(GraphicsWrapper* graphicsWrapper);
		void render(GraphicsWrapper* graphicsWrapper);
};

#endif
