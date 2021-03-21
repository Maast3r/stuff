#include <SDL.h>

#include "GraphicsWrapper.hpp"
#include "SoundWrapper.hpp"
#include "Scene.hpp"
#include "Hero.hpp"
#include "Platform.hpp"

#ifndef PLATFORMER_HPP
#define PLATFORMER_HPP

class Platformer: public Scene {
	private:
		int width;
		int height;
		bool started;
		bool lost;
		bool won;
		Hero* hero;
		Platform** platforms;

	public:
		Platformer(int screenWidth, int screenHeight);
		~Platformer();
		void handleEvents(SDL_Event* event, SoundWrapper* soundWrapper);
		void update(GraphicsWrapper* graphicsWrapper);
		void render(GraphicsWrapper* graphicsWrapper);
};

#endif
